#ifndef CARROT_PROGRESS_BAR_BLOCK_HPP
#define CARROT_PROGRESS_BAR_BLOCK_HPP

#include <carrot/text_block.hpp>

#include <carrot/block.hpp>

namespace carrot
{

class progress_bar_block final : public block_base<progress_bar_block>
{
public:
    explicit progress_bar_block(long int progress_);

    void render(form& mat) const;
    std::array<long int, 2> extent() const;

private:
    text_block text_;
};

progress_bar_block progress_bar(long int progress);
}

#endif
