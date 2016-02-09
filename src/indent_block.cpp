#include <carrot/indent_block.hpp>

#include <carrot/form_view.hpp>

namespace carrot
{

indent_block::indent_block(std::shared_ptr<block> indented_block_, long int indent_)
: indented_block_(indented_block_), indent_(indent_)
{
}

void indent_block::render(form & mat) const
{
    auto extent = indented_block_->extent();

    form_view view(mat, 0, indent_);

    indented_block_->render(view);
}

std::array<long int, 2> indent_block::extent() const
{
    auto extent = indented_block_->extent();

    return std::array<long int, 2>{extent[0], extent[1] + indent_};
}

}