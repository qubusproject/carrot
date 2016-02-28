#include <carrot/block.hpp>

#include <carrot/line_block.hpp>

#include <utility>

namespace carrot
{

block operator<<(block lhs, block rhs)
{
    line_block line(growth_direction::right);

    line.add(std::move(lhs));
    line.add(std::move(rhs));

    return line;
}

}