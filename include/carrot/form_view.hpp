#ifndef CARROT_FORM_VIEW_HPP
#define CARROT_FORM_VIEW_HPP

#include <carrot/form.hpp>

namespace carrot
{

class form_view final : public form
{
public:
    form_view(form & mat_, long int row_offset_, long int column_offset_);
    virtual ~form_view() = default;

    void set(long int row, long int column, glyph value) override;

private:
    form * mat_;
    long int row_offset_;
    long int column_offset_;
};
}

#endif
