#include <carrot/caret_underline_block.hpp>

namespace carrot
{

caret_underline_block::caret_underline_block(std::shared_ptr<block> underlined_element_,
                                             long int pos_)
: underlined_element_(underlined_element_), pos_(pos_)
{
}

void caret_underline_block::render(form & mat) const
{
    auto extent = underlined_element_->extent();

    underlined_element_->render(mat);

    for (long int i = 0; i < extent[1]; ++i)
    {
        if (i == pos_)
        {
            mat.set(extent[0], i, '^');
        }
        else
        {
            mat.set(extent[0], i, '~');
        }
    }
}

std::array<long int, 2> caret_underline_block::extent() const
{
    auto extent = underlined_element_->extent();

    return std::array<long int, 2>{extent[0] + 1, extent[1]};
}
}
