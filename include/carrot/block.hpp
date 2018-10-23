//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_BLOCK_HPP
#define CARROT_BLOCK_HPP

#include <carrot/form.hpp>
#include <carrot/style.hpp>
#include <carrot/target_info.hpp>

#include <array>
#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

namespace carrot
{

class style;

template <typename T>
class block_base
{
public:
    block_base() = default;

    explicit block_base(std::vector<std::string> tags_) : block_base("", std::move(tags_))
    {
    }

    block_base(std::string id_, std::vector<std::string> tags_)
    : id_(std::move(id_)), tags_(std::move(tags_))
    {
    }

    std::string_view id() const
    {
        return id_;
    }

    const std::vector<std::string>& tags() const
    {
        return tags_;
    }

protected:
    ~block_base() = default;

private:
    std::string id_;
    std::vector<std::string> tags_;
};

template <typename T>
struct is_block : std::is_base_of<block_base<T>, T>
{
};

class block
{
public:
    block();

    template <typename Block,
              typename Enabler = typename std::enable_if<is_block<Block>::value>::type>
    block(Block self_) : self_(std::make_unique<block_wrapper<Block>>(std::move(self_)))
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

    block(block&& other) noexcept
    {
        self_ = std::move(other.self_);
    }

    block& operator=(block other) noexcept
    {
        other.swap(*this);

        return *this;
    }

    void render(form& output_form, const style& s) const
    {
        self_->render(output_form, s);
    }

    std::array<long int, 2> extent(const target_info& output_target, const style& s) const
    {
        return self_->extent(output_target, s);
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

        virtual void render(form& mat, const style& s) const = 0;

        virtual std::array<long int, 2> extent(const target_info& output_target, const style& s) const = 0;
    };

    template <typename Block>
    class block_wrapper final : public block_interface
    {
    public:
        explicit block_wrapper(Block value_) : value_(std::move(value_))
        {
        }

        std::unique_ptr<block_interface> clone() const override
        {
            return std::make_unique<block_wrapper<Block>>(value_);
        }

        void render(form& output_form, const style& s) const override
        {
            value_.render(output_form, s);
        }

        std::array<long int, 2> extent(const target_info& output_target, const style& s) const override
        {
            return value_.extent(output_target, s);
        };

    private:
        Block value_;
    };

    std::unique_ptr<block_interface> self_;
};

block operator<<(block lhs, block rhs);

class plain_form;

void render(const block& root, plain_form& output_form);
void render(const block& root, plain_form& output_form, const style& s);
} // namespace carrot

#endif
