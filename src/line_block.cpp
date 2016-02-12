#include <carrot/line_block.hpp>

#include <carrot/form_view.hpp>

#include <algorithm>

namespace carrot
{

line_block::line_block(growth_direction direction_) : direction_(direction_)
{
}

line_block& line_block::add(std::shared_ptr<block> b)
{
    blocks_.push_back(b);
}

void line_block::render(form& mat) const
{
    long int offset = 0;

    for (const auto& block : blocks_)
    {
        auto extent = block->extent();

        switch (direction_)
        {
            case growth_direction::right:
            {
                form_view view(mat, 0, offset);
                block->render(view);

                offset += extent[1];
                break;
            }
            case growth_direction::down:
            {
                form_view view(mat, offset, 0);
                block->render(view);

                offset += extent[0];
                break;
            }
        }
    }
}

std::array<long int, 2> line_block::extent() const
{
    std::array<long int, 2> result{0, 0};

    for (const auto& block : blocks_)
    {
        auto extent = block->extent();

        switch (direction_)
        {
        case growth_direction::right:
            result[0] = std::max(result[0], extent[0]);
            result[1] += extent[1];
            break;
        case growth_direction::down:
            result[0] += extent[0];
            result[1] = std::max(result[1], extent[1]);
            break;
        }
    }

    return result;
}
}
