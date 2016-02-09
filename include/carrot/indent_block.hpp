#ifndef CARROT_INDENT_BLOCK_HPP
#define CARROT_INDENT_BLOCK_HPP

#include <carrot/block.hpp>

#include <memory>

namespace carrot
{

class indent_block : public block
{
public:
    indent_block(std::shared_ptr<block> indented_block_, long int indent_);
    virtual ~indent_block() = default;

    void render(form & mat) const override;

    std::array<long int, 2> extent() const override;
private:
    std::shared_ptr<block> indented_block_;
    long int indent_;
};

}

#endif
