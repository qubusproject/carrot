#include <carrot/list_block.hpp>

#include <carrot/text_block.hpp>

namespace carrot
{
list_block::list_block()
: grid_(std::make_shared<grid_block>(0, 2))
{
}

list_block& list_block::add(std::shared_ptr<block> b)
{
    grid_->append_row();

    grid_->set(grid_->rows() - 1, 0, text("* "));
    grid_->set(grid_->rows() - 1, 1, b);

    return *this;
}

void list_block::render(form & mat) const
{
    grid_->render(mat);
}

std::array<long int, 2> list_block::extent() const
{
    return grid_->extent();
}

std::shared_ptr<block> make_list()
{
    return std::make_shared<list_block>();
}
}
