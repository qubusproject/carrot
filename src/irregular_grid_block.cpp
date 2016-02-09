#include <carrot/irregular_grid_block.hpp>

#include <carrot/form_view.hpp>

namespace carrot
{

void irregular_grid_block::row::render(form & mat) const
{
    long int column_offset = 0;

    for (const auto& element : elements_)
    {
        auto element_extent = element->extent();

        form_view view(mat, 0, column_offset);

        element->render(view);

        column_offset += element_extent[1];
    }
}

std::array<long int, 2> irregular_grid_block::row::extent() const
{
    std::array<long int, 2> result{0, 0};

    for (const auto& element : elements_)
    {
        auto element_extent = element->extent();

        result[0] = std::max(result[0], element_extent[0]);
        result[1] += element_extent[1];
    }

    return result;
}

void irregular_grid_block::row::append(std::shared_ptr<block> element)
{
    elements_.push_back(element);
}

void irregular_grid_block::add_to_row(long int row, std::shared_ptr<block> element)
{
    rows_.resize(std::max(static_cast<std::size_t>(row + 1), rows_.size()));

    rows_.at(row).append(element);
}

void irregular_grid_block::render(form & mat) const
{
    long int row_offset = 0;

    for (const auto& row : rows_)
    {
        form_view view(mat, row_offset, 0);

        row.render(view);

        auto row_extent = row.extent();

        row_offset += row_extent[0];
    }
}

std::array<long int, 2> irregular_grid_block::extent() const
{
    std::array<long int, 2> result{0, 0};

    for (const auto& row : rows_)
    {
        auto row_extent = row.extent();

        result[0] += row_extent[0];
        result[1] = std::max(result[1], row_extent[1]);
    }

    return result;
}
}