//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_COLOR_HPP
#define CARROT_COLOR_HPP

#include <carrot/exception.hpp>

#include "carrot_export.hpp"

#include <boost/variant.hpp>

#include <array>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace carrot
{
class CARROT_EXPORT invalid_color_error : public virtual exception, public virtual std::runtime_error
{
public:
    explicit invalid_color_error(std::string message_)
    : std::runtime_error("Invalid color: " + std::move(message_))
    {
    }
};

class CARROT_EXPORT default_color
{
};

class CARROT_EXPORT rgb_color
{
public:
    constexpr rgb_color(short red_, short green_, short blue_) noexcept
    : red_(red_), green_(green_), blue_(blue_)
    {
    }

    [[nodiscard]] constexpr short red() const
    {
        return red_;
    }

    [[nodiscard]] constexpr short green() const
    {
        return green_;
    }

    [[nodiscard]] constexpr short blue() const
    {
        return blue_;
    }
private:
    short red_;
    short green_;
    short blue_;
};

class CARROT_EXPORT hsl_color
{
public:
    constexpr hsl_color(float hue_, float saturation_, float lightness_) noexcept
    : hue_(hue_), saturation_(saturation_), lightness_(lightness_)
    {
    }

    [[nodiscard]] constexpr float hue() const
    {
        return hue_;
    }

    [[nodiscard]] constexpr float saturation() const
    {
        return saturation_;
    }

    [[nodiscard]] constexpr float lightness() const
    {
        return lightness_;
    }

private:
    float hue_;
    float saturation_;
    float lightness_;
};

class CARROT_EXPORT named_color
{
public:
    explicit named_color(std::string name_) : name_(std::move(name_))
    {
    }

    [[nodiscard]] const std::string& name() const
    {
        return name_;
    }

private:
    std::string name_;
};

using color = boost::variant<default_color, rgb_color, hsl_color, named_color>;

class CARROT_EXPORT color_table
{
public:
    color_table& add_color(std::string name, color c);

    const color& lookup_color(const std::string& name) const;

private:
    std::unordered_map<std::string, color> color_map_;
};

[[nodiscard]] CARROT_EXPORT color_table get_default_color_table();

[[nodiscard]] CARROT_EXPORT rgb_color rgb(const color& c, const color_table& ctable);
[[nodiscard]] CARROT_EXPORT rgb_color rgb(const color& c);
[[nodiscard]] CARROT_EXPORT rgb_color rgb(rgb_color c);

[[nodiscard]] CARROT_EXPORT hsl_color hsl(const color& c, const color_table& ctable);
[[nodiscard]] CARROT_EXPORT hsl_color hsl(const color& c);
[[nodiscard]] CARROT_EXPORT hsl_color hsl(hsl_color c);

[[nodiscard]] CARROT_EXPORT color canonicalize(const color& c, const color_table& ctable);

[[nodiscard]] CARROT_EXPORT float distance(const color& color1, const color& color2);

[[nodiscard]] CARROT_EXPORT color get_default_color();

[[nodiscard]] CARROT_EXPORT bool is_default_color(const color& c);

[[nodiscard]] CARROT_EXPORT const std::array<hsl_color, 256>& get_xterm_color_table();
}

#endif
