#ifndef CARROT_GRAPHEME_CLUSTER_VIEW_HPP
#define CARROT_GRAPHEME_CLUSTER_VIEW_HPP

#include <cstdint>
#include <iterator>
#include <locale>
#include <memory>
#include <string>
#include <string_view>

namespace carrot
{

class grapheme_cluster_iterator_state;

struct grapheme_cluster_sentinel
{
};

class grapheme_cluster_iterator
{
public:
    using difference_type = std::ptrdiff_t;
    using value_type = std::string_view;

    grapheme_cluster_iterator(std::string_view utf8_string_, std::locale locale_);

    value_type operator*();

    grapheme_cluster_iterator& operator++();
    grapheme_cluster_iterator operator++(int) &;

    friend bool operator==(grapheme_cluster_iterator lhs, grapheme_cluster_sentinel rhs);

    friend bool operator!=(grapheme_cluster_iterator lhs, grapheme_cluster_sentinel rhs)
    {
        return !(lhs == rhs);
    }

private:
    std::shared_ptr<grapheme_cluster_iterator_state> state_;
};

typename grapheme_cluster_iterator::difference_type distance(grapheme_cluster_iterator first,
                                                             grapheme_cluster_sentinel last);

class grapheme_cluster_view
{
public:
    grapheme_cluster_view(std::string_view utf8_string_, std::locale locale_);

    grapheme_cluster_iterator begin();
    grapheme_cluster_sentinel end();

private:
    std::string_view utf8_string_;
    std::locale locale_;
};

} // namespace carrot

#endif
