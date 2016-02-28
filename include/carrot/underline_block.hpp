#ifndef CARROT_UNDERLINE_BLOCK_HPP
#define CARROT_UNDERLINE_BLOCK_HPP

#include <carrot/block.hpp>

namespace carrot
{

class underline_block final : public block_base<underline_block>
{
public:
    explicit underline_block(block underlined_element_);

    void render(form & mat) const;

    std::array<long int, 2> extent() const;

private:
    block underlined_element_;
};

underline_block underline(block underlined_element);
}

#endif
