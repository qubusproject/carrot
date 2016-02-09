#include <carrot/form_view.hpp>

namespace carrot
{

form_view::form_view(form & mat_, long int row_offset_, long int column_offset_)
: mat_(&mat_), row_offset_(row_offset_), column_offset_(column_offset_)
{
}

void form_view::set(long int row, long int column, glyph value)
{
    mat_->set(row_offset_ + row, column_offset_ + column, value);
}
}