#ifndef CARROT_LINE_BLOCK_HPP
#define CARROT_LINE_BLOCK_HPP

#include <carrot/block.hpp>

#include <memory>
#include <vector>

namespace carrot
{

enum class growth_direction
{
    down,
    right
};

class line_block : public block
{
public:
    explicit line_block(growth_direction direction_);
    virtual ~line_block() = default;

    line_block& add(std::shared_ptr<block> b);

    void render(form & mat) const override;
    std::array<long int, 2> extent() const override;
private:
    growth_direction direction_;
    std::vector<std::shared_ptr<block>> blocks_;
};

std::shared_ptr<block> make_line(growth_direction direction);

}

#endif