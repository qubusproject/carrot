//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_BLOCK_HPP
#define CARROT_BLOCK_HPP

#include <carrot/form.hpp>
#include <carrot/style.hpp>
#include <carrot/target_info.hpp>

#include "carrot_export.hpp"

#include <array>
#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

/** @brief carrot's root namespace.
 */
namespace carrot
{

class style;

#if __cpp_concepts >= 201507
template <typename T>
concept bool Block = requires(T x, form& output_form, const style& s, const target_info& ti)
{
    x.render(output_form, s);
    x.extent(ti, s);
};
#endif

/** @brief Mix-in to mark a type as a block.
 *
 * @tparam T The concrete type of the block.
 */
template <typename T>
class CARROT_EXPORT block_base
{
public:
    /** @brief Construct a new block without any tags.
     */
    block_base() = default;

    /** @brief Construct a new block with a list of tags.
     *
     * @param tags_ The list of applied tags.
     */
    explicit block_base(std::vector<std::string> tags_) : block_base("", std::move(tags_))
    {
    }

    /** @brief Construct a new named block and a list of tags applied.
     *
     * @param id_ The id of the block.
     * @param tags_ The list of applied tags.
     */
    explicit block_base(std::string id_, std::vector<std::string> tags_)
    : id_(std::move(id_)), tags_(std::move(tags_))
    {
    }

    /** @brief The ID of the block.
     *
     * @return The ID.
     */
    [[nodiscard]] std::string_view id() const
    {
        return id_;
    }

    /** @brief The list of tags which are attached to this block.
     *
     * @return The list of tags.
     */
    [[nodiscard]] const std::vector<std::string>& tags() const
    {
        return tags_;
    }

protected:
    ~block_base() = default;

    block_base(const block_base&) = default;
    block_base(block_base&&) noexcept = default;

    block_base& operator=(const block_base&) = default;
    block_base& operator=(block_base&&) noexcept = default;

private:
    /// The ID of the block.
    std::string id_;
    /// The list of tags attached to the block.
    std::vector<std::string> tags_;
};

/** A trait to check if a type is a block.
 *
 * Types which are derived from block_base are marked as
 * blocks by default.
 *
 * @tparam T The potential block type.
 */
template <typename T>
struct CARROT_EXPORT is_block : std::is_base_of<block_base<T>, T>
{
};

/** @brief A polymorphic block.
 *
 *  Objects of this type can store any concrete block implementation.
 *  In addition, this class implements the block concept itself.
 */
class CARROT_EXPORT block
{
public:
    /** @brief Construct a polymorphic block in its moved-from state.
     */
    block();

#if __cpp_concepts >= 201507
    template <Block BlockType>
    block(BlockType self_) : self_(std::make_unique<block_wrapper<BlockType>>(std::move(self_)))
    {
    }
#else
    /** @brief Constructs a new polymorphic block from the provided concrete block.
     *
     * @tparam Block The concrete type of the block.
     * @tparam Enabler SFINAE dummy parameter.
     * @param self_ The stored block.
     */
    template <typename Block,
              typename Enabler = typename std::enable_if<is_block<Block>::value>::type>
    block(Block self_) : self_(std::make_unique<block_wrapper<Block>>(std::move(self_)))
    {
    }
#endif

    ~block() noexcept = default;

    /** @brief Creates a deep copy of the underlying block.
     *
     * @param other The copied block.
     */
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

    block(block&& other) noexcept = default;

    /** @brief Assigns a deep copy of the underlying block.
     *
     * @param other The copied block.
     * @return This object.
     */
    block& operator=(const block& other)
    {
        block copy(other);

        copy.swap(*this);

        return *this;
    }

    block& operator=(block&& other) noexcept = default;

    /** @brief Renders the block into the provided form using the specified style.
     *
     * @param output_form The output form.
     * @param s The applied style.
     */
    void render(form& output_form, const style& s) const
    {
        self_->render(output_form, s);
    }

    /** @brief Calculates the extent of the block.
     *
     * To calculate the extent, it is assumed that the block
     * will be rendered using the specified style and will
     * be displayed by the provided target.
     *
     * @param output_target The output target.
     * @param s The applied style.
     * @return The extent of the block.
     */
    [[nodiscard]] std::array<long int, 2> extent(const target_info& output_target,
                                                 const style& s) const
    {
        return self_->extent(output_target, s);
    }

    /** @brief Swaps this block with another one.
     *
     * @param other the other block.
     */
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

        [[nodiscard]] virtual std::unique_ptr<block_interface> clone() const = 0;

        virtual void render(form& mat, const style& s) const = 0;

        [[nodiscard]] virtual std::array<long int, 2> extent(const target_info& output_target,
                                                             const style& s) const = 0;
    };

    template <typename Block>
    class block_wrapper final : public block_interface
    {
    public:
        explicit block_wrapper(Block value_) : value_(std::move(value_))
        {
        }

        [[nodiscard]] std::unique_ptr<block_interface> clone() const override
        {
            return std::make_unique<block_wrapper<Block>>(value_);
        }

        void render(form& output_form, const style& s) const override
        {
            value_.render(output_form, s);
        }

        [[nodiscard]] std::array<long int, 2> extent(const target_info& output_target,
                                                     const style& s) const override
        {
            return value_.extent(output_target, s);
        };

    private:
        Block value_;
    };

    std::unique_ptr<block_interface> self_;
};

/** @brief Concatenates two block horizontally.
 *
 * @param lhs The left-hand side block.
 * @param rhs The right-hand side block.
 * @return The concatenated blocks.
 */
CARROT_EXPORT block operator<<(block lhs, block rhs);

class plain_form;

/** @brief Renders the provided block into a form using the default style.
 *
 * @param root The rendered block.
 * @param output_form The output form.
 */
CARROT_EXPORT void render(const block& root, plain_form& output_form);

/** @brief Renders the provided block into a form using the specified style.
 *
 * @param root The rendered block.
 * @param output_form The output form.
 * @param s The applied style.
 */
CARROT_EXPORT void render(const block& root, plain_form& output_form, const style& s);
} // namespace carrot

#endif
