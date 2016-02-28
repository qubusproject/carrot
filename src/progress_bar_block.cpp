#include <carrot/progress_bar_block.hpp>

#include <string>

namespace carrot
{

progress_bar_block::progress_bar_block(long int progress_)
: text_(std::string(progress_, '+'))
{
}

void progress_bar_block::render(form & mat) const
{
    text_.render(mat);
}

std::array<long int, 2> progress_bar_block::extent() const
{
    return text_.extent();
}

progress_bar_block progress_bar(long int progress)
{
    return progress_bar_block(progress);
}
}