#include <carrot/empty_block.hpp>

namespace carrot
{

void empty_block::render(form & mat) const
{
}

std::array<long int, 2> empty_block::extent() const
{
    return std::array<long int, 2>{0, 0};
}

std::shared_ptr<block> make_empty()
{
    return std::make_shared<empty_block>();
}
}
