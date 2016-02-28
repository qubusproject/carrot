#ifndef CARROT_GRID_BLOCK_HPP
#define CARROT_GRID_BLOCK_HPP

#include <carrot/block.hpp>

#include <boost/multi_array.hpp>

#include <tuple>
#include <vector>

namespace carrot
{

class grid_block final : public block_base<grid_block>
{
public:
    grid_block(long int rows_, long int columns_);

    void set(long int row, long int column, block b);

    void append_rows(long int n);
    void append_columns(long int n);

    void append_row();
    void append_column();

    long int rows() const;
    long int cols() const;

    void render(form & mat) const;

    std::array<long int, 2> extent() const;

private:
    std::tuple<std::vector<long int>, std::vector<long int>> compute_layout() const;

    boost::multi_array<block, 2> blocks_;
};

grid_block make_grid(long int rows, long int columns);
}

#endif
