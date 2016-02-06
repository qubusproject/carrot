#ifndef CARROT_GRID_HPP
#define CARROT_GRID_HPP

#include <carrot/block.hpp>

#include <vector>
#include <memory>

namespace carrot
{

class irregular_grid_block : public block
{
public:
    class row
    {
    public:
        void render(matrix& mat) const;

        std::array<long int, 2> extent() const;

        void append(std::shared_ptr<block> element);

    private:
        std::vector<std::shared_ptr<block>> elements_;
    };

    void add_to_row(long int row, std::shared_ptr<block> element);

    void render(matrix& mat) const override;

    std::array<long int, 2> extent() const override;

private:
    std::vector<row> rows_;
};
}

#endif
