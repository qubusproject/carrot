#ifndef CARROT_BLOCK_HPP
#define CARROT_BLOCK_HPP

#include <carrot/form.hpp>

#include <array>
#include <type_traits>
#include <memory>
#include <utility>

namespace carrot
{

template <typename T>
class block_base
{
protected:
    ~block_base() = default;
};

template <typename T>
struct is_block : std::is_base_of<block_base<T>, T>
{
};

class block
{
public:
    block();

    template<typename Block, typename Enabler = typename std::enable_if<is_block<Block>::value>::type>
    block(Block self_)
    : self_(std::make_unique<block_wrapper<Block>>(std::move(self_)))
    {
    }

    block(const block& other)
    {
        if (other.self_)
        {
            self_ = other.self_->clone();
        }
        else
        {
            self_.reset();
        }
    }

    block(block&& other)
    {
        self_ = std::move(other.self_);
    }

    block& operator=(block other)
    {
        other.swap(*this);

        return *this;
    }

    void render(form& mat) const
    {
        self_->render(mat);
    }

    std::array<long int, 2> extent() const
    {
        return self_->extent();
    }

    void swap(block& other) noexcept
    {
        std::swap(self_, other.self_);
    }
private:
    class block_interface
    {
    public:
        block_interface() = default;

        virtual ~block_interface() = default;

        block_interface(const block_interface&) = delete;

        block_interface& operator=(const block_interface&) = delete;

        block_interface(block_interface&&) = delete;

        block_interface& operator=(block_interface&&) = delete;

        virtual std::unique_ptr<block_interface> clone() const = 0;

        virtual void render(form& mat) const = 0;

        virtual std::array<long int, 2> extent() const = 0;
    };

    template<typename Block>
    class block_wrapper final : public block_interface
    {
    public:
        explicit block_wrapper(Block value_)
        : value_(std::move(value_))
        {
        }

        std::unique_ptr<block_interface> clone() const override
        {
            return std::make_unique<block_wrapper<Block>>(value_);
        }

        void render(form& mat) const override
        {
            value_.render(mat);
        }

        std::array<long int, 2> extent() const override
        {
            return value_.extent();
        };
    private:
        Block value_;
    };

    std::unique_ptr<block_interface> self_;
};

block operator<<(block lhs, block rhs);
}

#endif
