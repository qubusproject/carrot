#include <carrot/progress_bar_block.hpp>

#include <string>

namespace carrot
{

progress_bar_block::progress_bar_block(long int progress_)
: text_(std::make_shared<text_block>(std::string(progress_, '+')))
{
}

void progress_bar_block::render(form & mat) const
{
    text_->render(mat);
}

std::array<long int, 2> progress_bar_block::extent() const
{
    return text_->extent();
}

std::shared_ptr<block> progress_bar(long int progress)
{
    return std::make_shared<progress_bar_block>(progress);
}
}