#include <carrot/underline_block.hpp>

#include <utility>

namespace carrot
{

underline_block::underline_block(std::shared_ptr<block> underlined_element_)
: underlined_element_(underlined_element_)
{
}

void underline_block::render(form & mat) const
{
    auto extent = underlined_element_->extent();

    underlined_element_->render(mat);

    for (long int i = 0; i < extent[1]; ++i)
    {
        mat.set(extent[0], i, '~');
    }
}

std::array<long int, 2> underline_block::extent() const
{
    auto extent = underlined_element_->extent();

    return std::array<long int, 2>{extent[0] + 1, extent[1]};
}

std::shared_ptr<block> underline(std::shared_ptr<block> underlined_element)
{
    return std::make_shared<underline_block>(std::move(underlined_element));
}
}