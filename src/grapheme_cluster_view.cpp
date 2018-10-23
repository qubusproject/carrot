#include <carrot/grapheme_cluster_view.hpp>

#include <carrot/exception.hpp>

#include <unicode/brkiter.h>
#include <unicode/utext.h>

#include <cassert>
#include <memory>

namespace carrot
{

namespace
{
class utext_deleter
{
public:
    void operator()(UText* ptr) const
    {
        utext_close(ptr);
    }
};

icu::Locale create_icu_locale(std::locale locale)
{
    auto icu_locale = icu::Locale::createCanonical(locale.name().c_str());

    return icu_locale;
}

std::unique_ptr<UText, utext_deleter> create_buffer(std::string_view utf8_string)
{
    using namespace std::string_literals;

    UErrorCode error_code = U_ZERO_ERROR;

    auto buffer = std::unique_ptr<UText, utext_deleter>(
        utext_openUTF8(nullptr, utf8_string.data(), utf8_string.size(), &error_code));

    if (!U_SUCCESS(error_code))
        throw runtime_error("ICU error: "s + u_errorName(error_code));

    return buffer;
}

std::unique_ptr<icu::BreakIterator>
create_grapheme_cluster_break_iterator(UText& buffer, const icu::Locale& locale)
{
    using namespace std::string_literals;

    UErrorCode error_code = U_ZERO_ERROR;

    auto iterator = std::unique_ptr<icu::BreakIterator>(
        icu::BreakIterator::createCharacterInstance(locale, error_code));

    if (!U_SUCCESS(error_code))
        throw runtime_error("ICU error: "s + u_errorName(error_code));

    error_code = U_ZERO_ERROR;

    iterator->setText(&buffer, error_code);

    if (!U_SUCCESS(error_code))
        throw runtime_error("ICU error: "s + u_errorName(error_code));

    return iterator;
}

} // namespace

class grapheme_cluster_iterator_state
{
public:
    grapheme_cluster_iterator_state(std::string_view utf8_string_, const std::locale& locale_)
    : utf8_string_(utf8_string_),
      locale_(create_icu_locale(locale_)),
      buffer_(create_buffer(this->utf8_string_)),
      iterator_(create_grapheme_cluster_break_iterator(*buffer_, this->locale_)),
      done_(false)
    {
        next_cluster();
    }

    bool has_next_cluster() const
    {
        return !done_;
    }

    void next_cluster()
    {
        assert(has_next_cluster());

        auto first = iterator_->current();
        auto last = iterator_->next();

        if (last != icu::BreakIterator::DONE)
        {
            auto count = last - first;

            current_cluster_ = utf8_string_.substr(first, count);
        }
        else
        {
            current_cluster_ = utf8_string_.substr(first);
            done_= true;
        }
    }

    std::string_view get_current_cluster() const
    {
        return current_cluster_;
    }

private:
    std::string_view utf8_string_;
    icu::Locale locale_;
    std::unique_ptr<UText, utext_deleter> buffer_;
    std::unique_ptr<icu::BreakIterator> iterator_;

    std::string current_cluster_;
    // BreakIterator::current will never return DONE.
    // Therefore we have to track the state separately.
    bool done_;
};

grapheme_cluster_iterator::grapheme_cluster_iterator(std::string_view utf8_string_, std::locale locale_)
: state_(std::make_shared<grapheme_cluster_iterator_state>(utf8_string_, locale_))
{
}

grapheme_cluster_iterator::value_type grapheme_cluster_iterator::operator*()
{
    assert(state_ != nullptr);

    return state_->get_current_cluster();
}

grapheme_cluster_iterator& grapheme_cluster_iterator::operator++()
{
    assert(state_ != nullptr);

    state_->next_cluster();

    return *this;
}

grapheme_cluster_iterator grapheme_cluster_iterator::operator++(int) &
{
    auto copy = *this;

    ++(*this);

    return copy;
}

bool operator==(grapheme_cluster_iterator lhs, grapheme_cluster_sentinel rhs)
{
    if (lhs.state_ == nullptr)
        return true;

    return !lhs.state_->has_next_cluster();
}

typename grapheme_cluster_iterator::difference_type distance(grapheme_cluster_iterator first,
                                                             grapheme_cluster_sentinel last)
{
    typename grapheme_cluster_iterator::difference_type diff = 0;

    for (auto iter = first; iter != last; ++iter)
    {
        ++diff;
    }

    return diff;
}

grapheme_cluster_view::grapheme_cluster_view(std::string_view utf8_string_, std::locale locale_)
: utf8_string_(utf8_string_), locale_(locale_)
{
}

grapheme_cluster_iterator grapheme_cluster_view::begin()
{
    return grapheme_cluster_iterator(utf8_string_, locale_);
}

grapheme_cluster_sentinel grapheme_cluster_view::end()
{
    return grapheme_cluster_sentinel();
}

} // namespace carrot
