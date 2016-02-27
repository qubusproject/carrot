#ifndef CARROT_GRID_BLOCK_HPP
#define CARROT_GRID_BLOCK_HPP

#include <carrot/block.hpp>

#include <boost/multi_array.hpp>

#include <memory>
#include <tuple>
#include <vector>

namespace carrot
{

class grid_block final : public block
{
public:
    grid_block(long int rows_, long int columns_);
    virtual ~grid_block() = default;

    void set(long int row, long int column, std::shared_ptr<block> block);

    void append_rows(long int n);
    void append_columns(long int n);

    void append_row();
    void append_column();

    long int rows() const;
    long int cols() const;

    void render(form & mat) const override;

    std::array<long int, 2> extent() const override;

private:
    std::tuple<std::vector<long int>, std::vector<long int>> compute_layout() const;

    boost::multi_array<std::shared_ptr<block>, 2> blocks_;
};

std::shared_ptr<grid_block> make_grid(long int rows, long int columns);
}

#endif
