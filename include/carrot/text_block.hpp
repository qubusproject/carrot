#ifndef CARROT_TEXT_BLOCK_HPP
#define CARROT_TEXT_BLOCK_HPP

#include <carrot/block.hpp>

#include <carrot/style_flags.hpp>

#include <vector>
#include <string>

namespace carrot
{

class text_block final : public block_base<text_block>
{
public:
    explicit text_block(const std::string& content_);
    text_block(const std::string& content_, style_flags style_);

    void render(form & mat) const;

    std::array<long int, 2> extent() const;

private:
    std::vector<std::string> rows_;
    style_flags style_;
};

text_block text(const std::string& content);
text_block text(const std::string& content, style_flags style);

}

#endif
