#include <carrot/empty_block.hpp>

namespace carrot
{

void empty_block::render(matrix& mat) const
{
}

std::array<long int, 2> empty_block::extent() const
{
    return std::array<long int, 2>{0, 0};
}
}
