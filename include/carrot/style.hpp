//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_STYLE_HPP
#define CARROT_STYLE_HPP

#include <carrot/color.hpp>
#include <carrot/exception.hpp>

#include "carrot_export.hpp"

#include <boost/variant.hpp>

#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

/** @brief carrot's root namespace.
 */
namespace carrot
{

class CARROT_EXPORT missing_style_info_error : public virtual exception,
                                               public virtual std::runtime_error
{
public:
    explicit missing_style_info_error()
    : std::runtime_error("The current style does not contain an applicable rule.")
    {
    }
};

class CARROT_EXPORT mismatched_attribute_type_error : public virtual exception,
                                                      public virtual std::runtime_error
{
public:
    explicit mismatched_attribute_type_error(std::string attribute_id_)
    : std::runtime_error("The requested type does not match the type of attribute " +
                         std::move(attribute_id_) + ".")
    {
    }
};

/** @brief A single style rule.
 */
class CARROT_EXPORT style_rule
{
public:
    /** @brief A style attribute.
     */
    struct attribute
    {
        /// The integer type used by style attributes.
        using integer = int;

        /** @brief Creates a new attribute.
         *
         * @tparam T The value type.
         * @param value The value.
         */
        template <typename T>
        attribute(T value) : value(std::move(value))
        {
        }

        /** @brief Creates a string attribute from a null-terminated string.
         *
         * @param value The value.
         */
        attribute(const char* value) : value(std::string(value))
        {
        }

        /// The value of the attribute.
        boost::variant<bool, std::string, color, integer> value;
    };

    /// The integer type used by style attributes.
    using integer = attribute::integer;

    /** @brief Constructs a new rule.
     *
     * The rule will be applied for each element with the specified element type,
     * block ID and tag.
     *
     * @param element_id_ The element type pattern.
     * @param id_ The block ID pattern.
     * @param tag_ The tag pattern.
     */
    explicit style_rule(std::string element_id_, std::string id_, std::string tag_);

    /** @brief Gets the specified attribute.
     *
     * @param attribute_id The ID of the queried attribute.
     * @return The attribute.
     */
    [[nodiscard]] std::optional<style_rule::attribute>
    get_attribute(std::string_view attribute_id) const;

    /** @brief Add an attribute to the rule.
     *
     * The attribute will be applied to each element which matches the rule.
     *
     * @param attribute_id The ID of the attribute.
     * @param value The value.
     * @return This rule.
     */
    style_rule& add_attribute(std::string attribute_id, attribute value);

    /** @brief A rule selector.
     */
    class selector_type
    {
    public:
        /** @brief Creates a new selector using the specified patterns.
         *
         * @param element_id_ The element type pattern.
         * @param id_ The block ID pattern.
         * @param tag_ The tag pattern.
         */
        explicit selector_type(std::string element_id_, std::string id_, std::string tag_);

        /** @brief Queries if a block with the specified element type, ID and tags
         *         matches this selector.
         *
         * @param element_id The element type of the block.
         * @param id The ID of the block.
         * @param tags The tags of the block.
         * @return True, if the selector matches the block. False, otherwise.
         */
        [[nodiscard]] bool does_match(std::string_view element_id, std::string_view id,
                                      const std::vector<std::string>& tags) const;

    private:
        class pattern
        {
        public:
            explicit pattern(std::string pattern_);

            [[nodiscard]] bool does_match(std::string_view value) const;

            [[nodiscard]] bool is_matching_anything() const
            {
                return !pattern_.has_value();
            }

        private:
            std::optional<std::string> pattern_;
        };

        pattern element_id_;
        pattern id_;
        pattern tag_;
    };

    /** @brief The block selectors associated with this rule.
     *
     * @return The block selectors.
     */
    [[nodiscard]] const selector_type& selector() const
    {
        return selector_;
    }

private:
    selector_type selector_;
    std::vector<std::pair<std::string, attribute>> attributes_;
};

/** @brief A rendering style.
 */
class CARROT_EXPORT style
{
public:
    /// The integer type used for attributes.
    using integer = style_rule::integer;
    /// The style attribute type.
    using attribute = style_rule::attribute;

    /** @brief Constructs an empty style.
     */
    style() = default;

    virtual ~style() noexcept = default;

    /** @brief Queries the attribute value for a block with the specified element type, ID and tags.
     *
     * @param element_id The type of the block.
     * @param id The ID of the block.
     * @param tags The tags of the block.
     * @param attribute_id The ID of the attribute.
     * @return The attribute value.
     */
    [[nodiscard]] virtual attribute get_attribute(std::string_view element_id, std::string_view id,
                                                  const std::vector<std::string>& tags,
                                                  std::string_view attribute_id) const = 0;

    /** @brief Queries the attribute value for a block with the specified element type, ID and tags.
     *
     * @tparam T The assumed type of the attribute.
     * @param element_id The type of the block.
     * @param id The ID of the block.
     * @param tags The tags of the block.
     * @param attribute_id The ID of the attribute.
     * @return The attribute value.
     */
    template <typename T>
    [[nodiscard]] T get_attribute(std::string_view element_id, std::string_view id,
                                  const std::vector<std::string>& tags,
                                  std::string_view attribute_id) const
    {
        try
        {
            return boost::get<T>(get_attribute(element_id, id, tags, attribute_id).value);
        }
        catch (const boost::bad_get&)
        {
            throw mismatched_attribute_type_error(std::string(attribute_id));
        }
    }

protected:
    style(const style&) = default;
    style(style&&) noexcept = default;

    style& operator=(const style&) = default;
    style& operator=(style&&) noexcept = default;
};

/** @brief A style with user-defined rules.
 *
 * If no suitable rule is found in this style, it will fallback
 * to the base style.
 *
 */
class CARROT_EXPORT user_defined_style final : public style
{
public:
    /** @brief Constructs an empty style.
     */
    explicit user_defined_style() = default;

    /** @brief Constructs a style which is derived from the specified style.
     *
     * @param base_style_ The base style.
     */
    explicit user_defined_style(std::unique_ptr<style> base_style_);

    /** @brief Queries the attribute value for a block with the specified element type, ID and tags.
     *
     * @param element_id The type of the block.
     * @param id The ID of the block.
     * @param tags The tags of the block.
     * @param attribute_id The ID of the attribute.
     * @return The attribute value.
     */
    [[nodiscard]] attribute get_attribute(std::string_view element_id, std::string_view id,
                                          const std::vector<std::string>& tags,
                                          std::string_view attribute_id) const final;

    /** @brief Add a new rule.
     *
     * @param element_id The element types for which this rule will be applied.
     * @return This created rule.
     */
    style_rule& add_rule(std::string element_id);

    /** @brief Add a new rule.
     *
     * @param element_id The element types for which this rule will be applied.
     * @param tag The tags for which this rule will be applied.
     * @return This created rule.
     */
    style_rule& add_rule(std::string element_id, std::string tag);

    /** @brief Add a new rule.
     *
     * @param element_id The element types for which this rule will be applied.
     * @param tag The tags for which this rule will be applied.
     * @param id The IDs for which this rule will be applied.
     * @return This created rule.
     */
    style_rule& add_rule(std::string element_id, std::string tag, std::string id);

private:
    std::vector<style_rule> rules_;

    std::unique_ptr<style> base_style_;
};

/** @brief An augmented style.
 *
 * This primary purpose of this type is the temporary extension of a
 * pre-existing style. If no suitable rule is found in this style, it will fallback
 * to the base style.
 *
 */
class CARROT_EXPORT augmented_style final : public style
{
public:
    /** @brief Constructs a style which is derived from the specified style.
     *
     * @param base_style_ The base style.
     */
    explicit augmented_style(const style& base_style_);

    /** @brief Queries the attribute value for a block with the specified element type, ID and tags.
     *
     * @param element_id The type of the block.
     * @param id The ID of the block.
     * @param tags The tags of the block.
     * @param attribute_id The ID of the attribute.
     * @return The attribute value.
     */
    [[nodiscard]] attribute get_attribute(std::string_view element_id, std::string_view id,
                                          const std::vector<std::string>& tags,
                                          std::string_view attribute_id) const final;

    /** @brief Add a new rule.
    *
    * @param element_id The element types for which this rule will be applied.
    * @return This created rule.
    */
    style_rule& add_rule(std::string element_id);

    /** @brief Add a new rule.
     *
     * @param element_id The element types for which this rule will be applied.
     * @param tag The tags for which this rule will be applied.
     * @return This created rule.
     */
    style_rule& add_rule(std::string element_id, std::string tag);

    /** @brief Add a new rule.
     *
     * @param element_id The element types for which this rule will be applied.
     * @param tag The tags for which this rule will be applied.
     * @param id The IDs for which this rule will be applied.
     * @return This created rule.
     */
    style_rule& add_rule(std::string element_id, std::string tag, std::string id);

private:
    std::vector<style_rule> rules_;

    const style* base_style_;
};

/** @brief Obtains the default style.
 *
 * @return The default style.
 */
[[nodiscard]] CARROT_EXPORT std::unique_ptr<style> get_default_style();
} // namespace carrot

#endif
