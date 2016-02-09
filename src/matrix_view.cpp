#include <carrot/matrix_view.hpp>

namespace carrot
{

matrix_view::matrix_view(matrix& mat_, long int row_offset_, long int column_offset_)
: mat_(&mat_), row_offset_(row_offset_), column_offset_(column_offset_)
{
}

void matrix_view::set(long int row, long int column, glyph value)
{
    mat_->set(row_offset_ + row, column_offset_ + column, value);
}
}