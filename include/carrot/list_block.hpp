#ifndef CARROT_LIST_BLOCK_HPP
#define CARROT_LIST_BLOCK_HPP

#include <carrot/grid_block.hpp>

#include <carrot/block.hpp>

#include <memory>

namespace carrot
{

class list_block final : public block
{
public:
    list_block();
    virtual ~list_block() = default;

    list_block& add(std::shared_ptr<block> b);

    void render(form & mat) const override;
    std::array<long int, 2> extent() const override;

private:
    std::shared_ptr<grid_block> grid_;
};

std::shared_ptr<block> make_list();

}

#endif
