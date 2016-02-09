#ifndef CARROT_MATRIX_VIEW_HPP
#define CARROT_MATRIX_VIEW_HPP

#include <carrot/matrix.hpp>

namespace carrot
{

class matrix_view final : public matrix
{
public:
    matrix_view(matrix& mat_, long int row_offset_, long int column_offset_);
    virtual ~matrix_view() = default;

    void set(long int row, long int column, glyph value) override;

private:
    matrix* mat_;
    long int row_offset_;
    long int column_offset_;
};
}

#endif
