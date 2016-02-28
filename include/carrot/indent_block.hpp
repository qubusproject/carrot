#ifndef CARROT_INDENT_BLOCK_HPP
#define CARROT_INDENT_BLOCK_HPP

#include <carrot/block.hpp>

namespace carrot
{

class indent_block final : public block_base<indent_block>
{
public:
    indent_block(block indented_block_, long int indent_);

    void render(form & mat) const;

    std::array<long int, 2> extent() const;
private:
    block indented_block_;
    long int indent_;
};

indent_block indent(block indented_block, long int indent);

}

#endif
