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

    void set(long int row, long int column, std::shared_ptr<block> block);

    void render(matrix& mat) const override;

    std::array<long int, 2> extent() const override;

private:
    std::tuple<std::vector<long int>, std::vector<long int>> compute_layout() const;

    boost::multi_array<std::shared_ptr<block>, 2> blocks_;
};
}

#endif
