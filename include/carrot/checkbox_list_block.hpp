#ifndef CARROT_CHECKBOX_BLOCK_HPP
#define CARROT_CHECKBOX_BLOCK_HPP

#include <carrot/grid_block.hpp>

#include <carrot/block.hpp>

#include <carrot/style_flags.hpp>

#include <memory>

namespace carrot
{

class checkbox_list_block final : public block
{
public:
    explicit checkbox_list_block(style_flags style_, char symbol_ = 'x');
    virtual ~checkbox_list_block() = default;

    checkbox_list_block& add(bool enabled, std::shared_ptr<block> description);

    void render(form & mat) const override;
    std::array<long int, 2> extent() const override;
private:
    std::shared_ptr<grid_block> grid_;
    style_flags style_;
    char symbol_;
};

std::shared_ptr<checkbox_list_block> make_checkbox_list(style_flags style, char symbol = 'x');

}

#endif
