#ifndef CARROT_TEXT_BLOCK_HPP
#define CARROT_TEXT_BLOCK_HPP

#include <carrot/block.hpp>

#include <vector>
#include <string>

namespace carrot
{

class text_block final : public block
{
public:
    explicit text_block(const std::string& content_);
    virtual ~text_block() = default;

    void render(matrix& mat) const override;

    std::array<long int, 2> extent() const override;

private:
    std::vector<std::string> rows_;
};
}

#endif
