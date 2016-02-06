#ifndef CARROT_BLOCK_HPP
#define CARROT_BLOCK_HPP

#include <carrot/matrix.hpp>

#include <array>

namespace carrot
{

class block
{
public:
    virtual ~block() = default;

    virtual void render(matrix& mat) const = 0;
    virtual std::array<long int, 2> extent() const = 0;
};
}

#endif
