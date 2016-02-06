#ifndef CARROT_CARROT_UNDERLINE_BLOCK_HPP
#define CARROT_CARROT_UNDERLINE_BLOCK_HPP

#include <carrot/block.hpp>

#include <memory>

namespace carrot
{

class caret_underline_block final : public block
{
public:
    explicit caret_underline_block(std::shared_ptr<block> underlined_element_, long int pos_);
    virtual ~caret_underline_block() = default;

    void render(matrix& mat) const override;

    std::array<long int, 2> extent() const override;

private:
    std::shared_ptr<block> underlined_element_;
    long int pos_;
};
}

#endif
