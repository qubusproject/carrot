//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/style.hpp>

#include <algorithm>
#include <utility>

namespace carrot
{
style_rule::selector_type::pattern::pattern(std::string pattern_)
{
    if (pattern_ != "*")
    {
        this->pattern_ = pattern_;
    }
}

bool style_rule::selector_type::pattern::does_match(std::string_view value) const
{
    if (pattern_)
    {
        return *pattern_ == value;
    }

    return true;
}

style_rule::selector_type::selector_type(std::string element_id_, std::string id_, std::string tag_)
: element_id_(std::move(element_id_)), id_(std::move(id_)), tag_(std::move(tag_))
{
}

bool style_rule::selector_type::does_match(std::string_view element_id, std::string_view id,
                                           const std::vector<std::string>& tags) const
{
    if (!element_id_.does_match(element_id))
        return false;

    if (!id_.does_match(id))
        return false;

    for (const auto& tag : tags)
    {
        if (tag_.does_match(tag))
            return true;
    }

    return tag_.is_matching_anything();
}

style_rule::style_rule(std::string element_id_, std::string id_, std::string tag_)
: selector_(std::move(element_id_), std::move(id_), std::move(tag_))
{
}

std::optional<style_rule::attribute> style_rule::get_attribute(std::string_view attribute_id) const
{
    auto search_result = std::find_if(attributes_.begin(), attributes_.end(), [&](const auto& value) {
        return value.first == attribute_id;
    });

    if (search_result == attributes_.end())
        return {};

    return search_result->second;
}

style_rule& style_rule::add_attribute(std::string attribute_id, attribute value)
{
    attributes_.emplace_back(std::move(attribute_id), std::move(value));

    return *this;
}

user_defined_style::user_defined_style(std::unique_ptr<style> base_style_)
: base_style_(std::move(base_style_))
{
}

style::attribute user_defined_style::get_attribute(std::string_view element_id, std::string_view id,
                                                   const std::vector<std::string>& tags,
                                                   std::string_view attribute_id) const
{
    for (const auto& rule : rules_)
    {
        if (rule.selector().does_match(element_id, id, tags))
        {
            if (auto attr = rule.get_attribute(attribute_id))
                return *attr;
        }
    }

    if (base_style_)
    {
        return base_style_->get_attribute(element_id, id, tags, attribute_id);
    }
    else
    {
        throw missing_style_info_error();
    }
}

style_rule& user_defined_style::add_rule(std::string element_id)
{
    return add_rule(std::move(element_id), "*");
}

style_rule& user_defined_style::add_rule(std::string element_id, std::string tag)
{
    return add_rule(std::move(element_id), std::move(tag), "*");
}

style_rule& user_defined_style::add_rule(std::string element_id, std::string tag, std::string id)
{
    rules_.emplace_back(std::move(element_id), std::move(id), std::move(tag));

    return rules_.back();
}

augmented_style::augmented_style(const style& base_style_) : base_style_(&base_style_)
{
}

style::attribute augmented_style::get_attribute(std::string_view element_id, std::string_view id,
                                                const std::vector<std::string>& tags,
                                                std::string_view attribute_id) const
{
    for (const auto& rule : rules_)
    {
        if (rule.selector().does_match(element_id, id, tags))
        {
            if (auto attr = rule.get_attribute(attribute_id))
                return *attr;
        }
    }

    if (base_style_)
    {
        return base_style_->get_attribute(element_id, id, tags, attribute_id);
    }
    else
    {
        throw missing_style_info_error();
    }
}

style_rule& augmented_style::add_rule(std::string element_id)
{
    return add_rule(std::move(element_id), "*");
}

style_rule& augmented_style::add_rule(std::string element_id, std::string tag)
{
    return add_rule(std::move(element_id), std::move(tag), "*");
}

style_rule& augmented_style::add_rule(std::string element_id, std::string tag, std::string id)
{
    rules_.emplace_back(std::move(element_id), std::move(id), std::move(tag));

    return rules_.back();
}

std::unique_ptr<style> get_default_style()
{
    auto s = std::make_unique<user_defined_style>();

    s->add_rule("*")
        .add_attribute("color", default_color())
        .add_attribute("background-color", default_color())
        .add_attribute("bold", false)
        .add_attribute("indent", 4)
        .add_attribute("content", u8"");

    s->add_rule("checkbox-list")
        .add_attribute("symbol-color", rgb_color(0, 255, 0))
        .add_attribute("symbol", u8"x");

    s->add_rule("caret-underline")
            .add_attribute("caret.color", rgb_color(0, 255, 0))
            .add_attribute("caret.bold", false);

    return s;
}
}
