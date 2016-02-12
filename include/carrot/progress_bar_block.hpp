#ifndef CARROT_PROGRESS_BAR_BLOCK_HPP
#define CARROT_PROGRESS_BAR_BLOCK_HPP

#include <carrot/text_block.hpp>

#include <carrot/block.hpp>

#include <memory>

namespace carrot
{

class progress_bar_block final : public block
{
public:
    explicit progress_bar_block(long int progress_);
    virtual ~progress_bar_block() = default;

    void render(form& mat) const override;
    std::array<long int, 2> extent() const override;

private:
    std::shared_ptr<text_block> text_;
};

std::shared_ptr<block> progress_bar(long int progress);
}

#endif
