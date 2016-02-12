#ifndef CARROT_EMPTY_BLOCK_HPP
#define CARROT_EMPTY_BLOCK_HPP

#include <carrot/block.hpp>

#include <memory>

namespace carrot
{

class empty_block final : public block
{
public:
    virtual ~empty_block() = default;

    void render(form & mat) const override;
    std::array<long int, 2> extent() const override;
};

std::shared_ptr<block> make_empty();
}

#endif
