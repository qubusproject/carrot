#ifndef CARROT_BLOCK_HPP
#define CARROT_BLOCK_HPP

#include <carrot/form.hpp>

#include <array>

namespace carrot
{

class block
{
public:
    block() = default;
    virtual ~block() = default;

    block(const block&) = delete;
    block& operator=(const block&) = delete;

    block(block&&) = delete;
    block& operator=(block&&) = delete;

    virtual void render(form & mat) const = 0;
    virtual std::array<long int, 2> extent() const = 0;
};
}

#endif
