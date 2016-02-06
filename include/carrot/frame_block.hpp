#ifndef CARROT_FRAME_BLOCK_HPP
#define CARROT_FRAME_BLOCK_HPP

#include <carrot/block.hpp>

#include <memory>

namespace carrot
{

class frame_block final : public block
{
public:
    explicit frame_block(std::shared_ptr<block> framed_block_, long int margin_ = 1);

    void render(matrix& mat) const override;

    std::array<long int, 2> extent() const override;

private:
    std::shared_ptr<block> framed_block_;
    long int margin_;
};
}

#endif
