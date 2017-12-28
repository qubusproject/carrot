//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_STYLE_HPP
#define CARROT_STYLE_HPP

#include <carrot/color.hpp>
#include <carrot/exception.hpp>

#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace carrot
{

class missing_style_info_error : public virtual exception, public virtual std::runtime_error
{
public:
    explicit missing_style_info_error()
    : std::runtime_error("The current style does not contain an applicable rule.")
    {
    }
};

class mismatched_attribute_type_error : public virtual exception, public virtual std::runtime_error
{
public:
    explicit mismatched_attribute_type_error(std::string attribute_id_)
    : std::runtime_error("The requested type does not match the type of attribute " +
                         std::move(attribute_id_) + ".")
    {
    }
};

class style_rule
{
public:
    struct attribute
    {
        using integer = int;

        template <typename T>
        attribute(T value) : value(std::move(value))
        {
        }

        attribute(const char* value) : value(std::string(value))
        {
        }

        std::variant<bool, std::string, color, integer> value;
    };

    using integer = attribute::integer;

    explicit style_rule(std::string element_id_, std::string id_, std::string tag_);

    std::optional<style_rule::attribute> get_attribute(std::string_view attribute_id) const;

    style_rule& add_attribute(std::string attribute_id, attribute value);

    class selector_type
    {
    public:
        explicit selector_type(std::string element_id_, std::string id_, std::string tag_);

        bool does_match(std::string_view element_id, std::string_view id,
                        const std::vector<std::string>& tags) const;

    private:
        class pattern
        {
        public:
            explicit pattern(std::string pattern_);

            bool does_match(std::string_view value) const;

            bool is_matching_anything() const
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

    const selector_type& selector() const
    {
        return selector_;
    }
private:
    selector_type selector_;
    std::vector<std::pair<std::string, attribute>> attributes_;
};

class style
{
public:
    using integer = style_rule::integer;
    using attribute = style_rule::attribute;

    virtual ~style() = default;

    virtual attribute get_attribute(std::string_view element_id, std::string_view id,
                                    const std::vector<std::string>& tags,
                                    std::string_view attribute_id) const = 0;

    template <typename T>
    T get_attribute(std::string_view element_id, std::string_view id,
                    const std::vector<std::string>& tags, std::string_view attribute_id) const
    {
        try
        {
            return std::get<T>(get_attribute(element_id, id, tags, attribute_id).value);
        }
        catch (const std::bad_variant_access&)
        {
            throw mismatched_attribute_type_error(std::string(attribute_id));
        }
    }
};

class user_defined_style final : public style
{
public:
    user_defined_style() = default;
    explicit user_defined_style(std::unique_ptr<style> base_style_);

    attribute get_attribute(std::string_view element_id, std::string_view id,
                            const std::vector<std::string>& tags,
                            std::string_view attribute_id) const override;

    style_rule& add_rule(std::string element_id);
    style_rule& add_rule(std::string element_id, std::string tag);
    style_rule& add_rule(std::string element_id, std::string tag, std::string id);

private:
    std::vector<style_rule> rules_;

    std::unique_ptr<style> base_style_;
};

class augmented_style final : public style
{
public:
    explicit augmented_style(const style& base_style_);

    attribute get_attribute(std::string_view element_id, std::string_view id,
                            const std::vector<std::string>& tags,
                            std::string_view attribute_id) const override;

    style_rule& add_rule(std::string element_id);
    style_rule& add_rule(std::string element_id, std::string tag);
    style_rule& add_rule(std::string element_id, std::string tag, std::string id);

private:
    std::vector<style_rule> rules_;

    const style* base_style_;
};

std::unique_ptr<style> get_default_style();
}

#endif
