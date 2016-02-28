#ifndef CARROT_LIST_BLOCK_HPP
#define CARROT_LIST_BLOCK_HPP

#include <carrot/grid_block.hpp>

#include <carrot/block.hpp>

namespace carrot
{

class list_block final : public block_base<list_block>
{
public:
    list_block();

    list_block& add(block b);

    void render(form & mat) const;
    std::array<long int, 2> extent() const;

private:
    grid_block grid_;
};

list_block make_list();

}

#endif
