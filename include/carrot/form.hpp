#ifndef CARROT_FORM_HPP
#define CARROT_FORM_HPP

#include <carrot/glyph.hpp>

#include <carrot/target_info.hpp>

#include <boost/multi_array.hpp>

namespace carrot
{

class form
{
public:
    form() = default;
    virtual ~form() = default;

    form(const form &) = delete;
    form & operator=(const form &) = delete;

    form(form &&) = delete;
    form & operator=(form &&) = delete;

    virtual void set(long int row, long int column, glyph value) = 0;
};

class simple_form final : public form
{
public:
    simple_form(long int rows_ = 0, long int columns_ = 0);
    virtual ~simple_form() = default;

    void set(long int row, long int column, glyph value) override;

    std::string to_string(const target_info& target) const;

    void clear();
private:
    void resize_if_outside_matrix(long int row, long int column);

    boost::multi_array<glyph, 2> data_;
};
}

#endif
