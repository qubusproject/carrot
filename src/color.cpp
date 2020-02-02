//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/color.hpp>

#include <carrot/integers.hpp>

#include <algorithm>
#include <array>
#include <cmath>

namespace carrot
{

color_table& color_table::add_color(std::string name, color c) noexcept
{
    color_map_.emplace(std::move(name), std::move(c));

    return *this;
}

const color& color_table::lookup_color(const std::string& name) const
{
    auto search_result = color_map_.find(name);

    if (search_result == color_map_.end())
        throw invalid_color_error("Unknown named color.");

    return search_result->second;
}

color_table get_default_color_table() noexcept
{
    return color_table();
}

namespace
{
/** @brief Converts an RGB-encoded color value to its HLS-encoding.
 *
 * @param c An RGB-encoded color value.
 * @return The color's HLS representation.
 */
hsl_color rgb2hls(const rgb_color& c) noexcept
{
    constexpr short rgb_component_maximum = 255;

    float r = convert_constrained_integer<float>(c.red(), short(0), rgb_component_maximum) /
              rgb_component_maximum;
    float g = convert_constrained_integer<float>(c.green(), short(0), rgb_component_maximum) /
              rgb_component_maximum;
    float b = convert_constrained_integer<float>(c.blue(), short(0), rgb_component_maximum) /
              rgb_component_maximum;

    auto c_min = std::min({r, g, b});
    auto c_max = std::max({r, g, b});

    auto delta = c_max - c_min;

    auto L = (c_max + c_min) / 2;

    auto S = delta == 0 ? 0 : delta / (1 - std::abs(2 * L - 1));

    constexpr short degree_maximum = 360;

    constexpr short number_of_hexagon_edges = 6;
    constexpr short angular_shift_per_edge = 60;

    auto H = [&]() -> float {
        if (delta == 0)
            return 0;

        if (c_max == r)
        {
            auto result =
                std::fmod((g - b) / delta, number_of_hexagon_edges) * angular_shift_per_edge;

            if (b > g)
            {
                result += degree_maximum;
            }

            return result;
        }

        if (c_max == g)
        {
            return ((b - r) / delta + 2) * angular_shift_per_edge;
        }

        return ((r - g) / delta + 4) * angular_shift_per_edge;
    }();

    return hsl_color(H, S, L);
}

/** @brief Converts an HLS-encoded color value to its RGB-encoding.
 *
 * @param c An HLS-encoded color value.
 * @return The color's RGB representation.
 */
rgb_color hsl2rgb(const hsl_color& c) noexcept
{
    constexpr short angular_shift_per_edge = 60;

    float C = (1 - std::abs(2 * c.lightness() - 1)) * c.saturation();

    float X = C * (1 - std::abs(std::fmod(c.hue() / angular_shift_per_edge, 2.0f) - 1));

    float m = c.lightness() - C / 2;

    auto [r, g, b] = [&]() -> std::array<float, 3> {
        if (c.hue() < angular_shift_per_edge)
        {
            return {C, X, 0};
        }

        if (c.hue() < 2 * angular_shift_per_edge)
        {
            return {X, C, 0};
        }

        if (c.hue() < 3 * angular_shift_per_edge)
        {
            return {0, C, X};
        }

        if (c.hue() < 4 * angular_shift_per_edge)
        {
            return {0, X, C};
        }

        if (c.hue() < 5 * angular_shift_per_edge)
        {
            return {X, 0, C};
        }

        return {C, 0, X};
    }();

    constexpr short rgb_component_maximum = 255;

    const auto r_discrete = convert_constrained_integer<short>(
        std::round((r + m) * rgb_component_maximum), short(0), rgb_component_maximum);
    const auto g_discrete = convert_constrained_integer<short>(
        std::round((g + m) * rgb_component_maximum), short(0), rgb_component_maximum);
    const auto b_discrete = convert_constrained_integer<short>(
        std::round((b + m) * rgb_component_maximum), short(0), rgb_component_maximum);

    return rgb_color(r_discrete, g_discrete, b_discrete);
}
} // namespace

rgb_color rgb(const color& c, const color_table& ctable)
{
    struct rgb_converter
    {
        explicit rgb_converter(const color_table& ctable) noexcept : ctable(&ctable)
        {
        }

        rgb_color operator()(const default_color& c [[maybe_unused]]) const
        {
            throw invalid_color_error("Trying to use the default color as an explicit color.");
        }

        rgb_color operator()(const rgb_color& c) const noexcept
        {
            return c;
        }

        rgb_color operator()(const hsl_color& c) const noexcept
        {
            return hsl2rgb(c);
        }

        rgb_color operator()(const named_color& c) const
        {
            return rgb(ctable->lookup_color(c.name()));
        }

        const color_table* ctable;
    };

    return boost::apply_visitor(rgb_converter(ctable), c);
}

rgb_color rgb(const color& c)
{
    struct rgb_converter
    {
        rgb_color operator()(const default_color& c [[maybe_unused]]) const
        {
            throw invalid_color_error("Trying to use the default color as an explicit color.");
        }

        rgb_color operator()(const rgb_color& c) const noexcept
        {
            return c;
        }

        rgb_color operator()(const hsl_color& c) const noexcept
        {
            return hsl2rgb(c);
        }

        rgb_color operator()(const named_color& c [[maybe_unused]]) const
        {
            throw invalid_color_error("Unknown named color.");
        }
    };

    return boost::apply_visitor(rgb_converter(), c);
}

rgb_color rgb(rgb_color c) noexcept
{
    return c;
}

hsl_color hsl(const color& c, const color_table& ctable)
{
    struct hsl_converter
    {
        explicit hsl_converter(const color_table& ctable) : ctable(&ctable)
        {
        }

        hsl_color operator()(const default_color& c [[maybe_unused]]) const
        {
            throw invalid_color_error("Trying to use the default color as an explicit color.");
        }

        hsl_color operator()(const rgb_color& c) const noexcept
        {
            return rgb2hls(c);
        }

        hsl_color operator()(const hsl_color& c) const noexcept
        {
            return c;
        }

        hsl_color operator()(const named_color& c) const
        {
            return hsl(ctable->lookup_color(c.name()));
        }

        const color_table* ctable;
    };

    return boost::apply_visitor(hsl_converter(ctable), c);
}

hsl_color hsl(const color& c)
{
    struct hsl_converter
    {
        hsl_color operator()(const default_color& c [[maybe_unused]]) const
        {
            throw invalid_color_error("Trying to use the default color as an explicit color.");
        }

        hsl_color operator()(const rgb_color& c) const noexcept
        {
            return rgb2hls(c);
        }

        hsl_color operator()(const hsl_color& c) const noexcept
        {
            return c;
        }

        hsl_color operator()(const named_color& c [[maybe_unused]]) const
        {
            throw invalid_color_error("Unknown named color.");
        }
    };

    return boost::apply_visitor(hsl_converter(), c);
}

hsl_color hsl(hsl_color c) noexcept
{
    return c;
}

color canonicalize(const color& c, const color_table& ctable)
{
    struct canonicalizer
    {
        explicit canonicalizer(const color_table& ctable) : ctable(&ctable)
        {
        }

        color operator()(const default_color& c [[maybe_unused]]) const
        {
            throw invalid_color_error("Trying to use the default color as an explicit color.");
        }

        color operator()(const rgb_color& c) const
        {
            return c;
        }

        color operator()(const hsl_color& c) const
        {
            return c;
        }

        color operator()(const named_color& c) const
        {
            return ctable->lookup_color(c.name());
        }

        const color_table* ctable;
    };

    return boost::apply_visitor(canonicalizer(ctable), c);
}

float distance(const color& color1, const color& color2)
{
    // TODO: Implement a better metric which takes human color perception into account.

    auto color1_hsl = hsl(color1);
    auto color2_hsl = hsl(color2);

    constexpr float degree_maximum = 360;

    return std::abs(color1_hsl.hue() / degree_maximum - color2_hsl.hue() / degree_maximum) +
           std::abs(color1_hsl.saturation() - color2_hsl.saturation()) +
           std::abs(color1_hsl.lightness() - color2_hsl.lightness());
}

color get_default_color() noexcept
{
    return default_color();
}

bool is_default_color(const color& c) noexcept
{
    return boost::get<default_color>(&c) != nullptr;
}

namespace
{
constexpr std::array<hsl_color, xterm_color_table_size> xterm_color_table = {{
    {0.00000000f, 0.0f, 0.0f},     {0.00000000f, 1.0f, 0.25f},    {120.00000000f, 1.0f, 0.25f},
    {60.00000000f, 1.0f, 0.25f},   {240.00000000f, 1.0f, 0.25f},  {300.00000000f, 1.0f, 0.25f},
    {180.00000000f, 1.0f, 0.25f},  {0.00000000f, 0.0f, 0.75f},    {0.00000000f, 0.0f, 0.5f},
    {0.00000000f, 1.0f, 0.5f},     {120.00000000f, 1.0f, 0.5f},   {60.00000000f, 1.0f, 0.5f},
    {240.00000000f, 1.0f, 0.5f},   {300.00000000f, 1.0f, 0.5f},   {180.00000000f, 1.0f, 0.5f},
    {0.00000000f, 0.0f, 1.0f},     {0.00000000f, 0.0f, 0.0f},     {240.00000000f, 1.0f, 0.18f},
    {240.00000000f, 1.0f, 0.26f},  {240.00000000f, 1.0f, 0.34f},  {240.00000000f, 1.0f, 0.42f},
    {240.00000000f, 1.0f, 0.5f},   {120.00000000f, 1.0f, 0.18f},  {180.00000000f, 1.0f, 0.18f},
    {197.77777778f, 1.0f, 0.26f},  {207.42857143f, 1.0f, 0.34f},  {213.48837209f, 1.0f, 0.42f},
    {217.64705882f, 1.0f, 0.5f},   {120.00000000f, 1.0f, 0.26f},  {162.22222222f, 1.0f, 0.26f},
    {180.00000000f, 1.0f, 0.26f},  {193.71428571f, 1.0f, 0.34f},  {202.32558140f, 1.0f, 0.42f},
    {208.23529412f, 1.0f, 0.5f},   {120.00000000f, 1.0f, 0.34f},  {152.57142857f, 1.0f, 0.34f},
    {166.28571429f, 1.0f, 0.34f},  {180.00000000f, 1.0f, 0.34f},  {191.16279070f, 1.0f, 0.42f},
    {198.82352941f, 1.0f, 0.5f},   {120.00000000f, 1.0f, 0.42f},  {146.51162791f, 1.0f, 0.42f},
    {157.67441860f, 1.0f, 0.42f},  {168.83720930f, 1.0f, 0.42f},  {180.00000000f, 1.0f, 0.42f},
    {189.41176471f, 1.0f, 0.5f},   {120.00000000f, 1.0f, 0.5f},   {142.35294118f, 1.0f, 0.5f},
    {151.76470588f, 1.0f, 0.5f},   {161.17647059f, 1.0f, 0.5f},   {170.58823529f, 1.0f, 0.5f},
    {180.00000000f, 1.0f, 0.5f},   {0.00000000f, 1.0f, 0.18f},    {300.00000000f, 1.0f, 0.18f},
    {282.22222222f, 1.0f, 0.26f},  {272.57142857f, 1.0f, 0.34f},  {266.51162791f, 1.0f, 0.42f},
    {262.35294118f, 1.0f, 0.5f},   {60.00000000f, 1.0f, 0.18f},   {0.00000000f, 0.0f, 0.37f},
    {240.00000000f, 0.17f, 0.45f}, {240.00000000f, 0.33f, 0.52f}, {240.00000000f, 0.6f, 0.6f},
    {240.00000000f, 1.0f, 0.68f},  {77.77777778f, 1.0f, 0.26f},   {120.00000000f, 0.17f, 0.45f},
    {180.00000000f, 0.17f, 0.45f}, {210.00000000f, 0.33f, 0.52f}, {220.00000000f, 0.6f, 0.6f},
    {225.00000000f, 1.0f, 0.68f},  {87.42857143f, 1.0f, 0.34f},   {120.00000000f, 0.33f, 0.52f},
    {150.00000000f, 0.33f, 0.52f}, {180.00000000f, 0.33f, 0.52f}, {200.00000000f, 0.6f, 0.6f},
    {210.00000000f, 1.0f, 0.68f},  {93.48837209f, 1.0f, 0.42f},   {120.00000000f, 0.6f, 0.6f},
    {140.00000000f, 0.6f, 0.6f},   {160.00000000f, 0.6f, 0.6f},   {180.00000000f, 0.6f, 0.6f},
    {195.00000000f, 1.0f, 0.68f},  {97.64705882f, 1.0f, 0.5f},    {120.00000000f, 1.0f, 0.68f},
    {135.00000000f, 1.0f, 0.68f},  {150.00000000f, 1.0f, 0.68f},  {165.00000000f, 1.0f, 0.68f},
    {180.00000000f, 1.0f, 0.68f},  {0.00000000f, 1.0f, 0.26f},    {317.77777778f, 1.0f, 0.26f},
    {300.00000000f, 1.0f, 0.26f},  {286.28571429f, 1.0f, 0.34f},  {277.67441860f, 1.0f, 0.42f},
    {271.76470588f, 1.0f, 0.5f},   {42.22222222f, 1.0f, 0.26f},   {0.00000000f, 0.17f, 0.45f},
    {300.00000000f, 0.17f, 0.45f}, {270.00000000f, 0.33f, 0.52f}, {260.00000000f, 0.6f, 0.6f},
    {255.00000000f, 1.0f, 0.68f},  {60.00000000f, 1.0f, 0.26f},   {60.00000000f, 0.17f, 0.45f},
    {0.00000000f, 0.0f, 0.52f},    {240.00000000f, 0.2f, 0.6f},   {240.00000000f, 0.5f, 0.68f},
    {240.00000000f, 1.0f, 0.76f},  {73.71428571f, 1.0f, 0.34f},   {90.00000000f, 0.33f, 0.52f},
    {120.00000000f, 0.2f, 0.6f},   {180.00000000f, 0.2f, 0.6f},   {210.00000000f, 0.5f, 0.68f},
    {220.00000000f, 1.0f, 0.76f},  {82.32558140f, 1.0f, 0.42f},   {100.00000000f, 0.6f, 0.6f},
    {120.00000000f, 0.5f, 0.68f},  {150.00000000f, 0.5f, 0.68f},  {180.00000000f, 0.5f, 0.68f},
    {200.00000000f, 1.0f, 0.76f},  {88.23529412f, 1.0f, 0.5f},    {105.00000000f, 1.0f, 0.68f},
    {120.00000000f, 1.0f, 0.76f},  {140.00000000f, 1.0f, 0.76f},  {160.00000000f, 1.0f, 0.76f},
    {180.00000000f, 1.0f, 0.76f},  {0.00000000f, 1.0f, 0.34f},    {327.42857143f, 1.0f, 0.34f},
    {313.71428571f, 1.0f, 0.34f},  {300.00000000f, 1.0f, 0.34f},  {288.83720930f, 1.0f, 0.42f},
    {281.17647059f, 1.0f, 0.5f},   {32.57142857f, 1.0f, 0.34f},   {0.00000000f, 0.33f, 0.52f},
    {330.00000000f, 0.33f, 0.52f}, {300.00000000f, 0.33f, 0.52f}, {280.00000000f, 0.6f, 0.6f},
    {270.00000000f, 1.0f, 0.68f},  {46.28571429f, 1.0f, 0.34f},   {30.00000000f, 0.33f, 0.52f},
    {0.00000000f, 0.2f, 0.6f},     {300.00000000f, 0.2f, 0.6f},   {270.00000000f, 0.5f, 0.68f},
    {260.00000000f, 1.0f, 0.76f},  {60.00000000f, 1.0f, 0.34f},   {60.00000000f, 0.33f, 0.52f},
    {60.00000000f, 0.2f, 0.6f},    {0.00000000f, 0.0f, 0.68f},    {240.00000000f, 0.33f, 0.76f},
    {240.00000000f, 1.0f, 0.84f},  {71.16279070f, 1.0f, 0.42f},   {80.00000000f, 0.6f, 0.6f},
    {90.00000000f, 0.5f, 0.68f},   {120.00000000f, 0.33f, 0.76f}, {180.00000000f, 0.33f, 0.76f},
    {210.00000000f, 1.0f, 0.84f},  {78.82352941f, 1.0f, 0.5f},    {90.00000000f, 1.0f, 0.68f},
    {100.00000000f, 1.0f, 0.76f},  {120.00000000f, 1.0f, 0.84f},  {150.00000000f, 1.0f, 0.84f},
    {180.00000000f, 1.0f, 0.84f},  {0.00000000f, 1.0f, 0.42f},    {333.48837209f, 1.0f, 0.42f},
    {322.32558140f, 1.0f, 0.42f},  {311.16279070f, 1.0f, 0.42f},  {300.00000000f, 1.0f, 0.42f},
    {290.58823529f, 1.0f, 0.5f},   {26.51162791f, 1.0f, 0.42f},   {0.00000000f, 0.6f, 0.6f},
    {340.00000000f, 0.6f, 0.6f},   {320.00000000f, 0.6f, 0.6f},   {300.00000000f, 0.6f, 0.6f},
    {285.00000000f, 1.0f, 0.68f},  {37.67441860f, 1.0f, 0.42f},   {20.00000000f, 0.6f, 0.6f},
    {0.00000000f, 0.5f, 0.68f},    {330.00000000f, 0.5f, 0.68f},  {300.00000000f, 0.5f, 0.68f},
    {280.00000000f, 1.0f, 0.76f},  {48.83720930f, 1.0f, 0.42f},   {40.00000000f, 0.6f, 0.6f},
    {30.00000000f, 0.5f, 0.68f},   {0.00000000f, 0.33f, 0.76f},   {300.00000000f, 0.33f, 0.76f},
    {270.00000000f, 1.0f, 0.84f},  {60.00000000f, 1.0f, 0.42f},   {60.00000000f, 0.6f, 0.6f},
    {60.00000000f, 0.5f, 0.68f},   {60.00000000f, 0.33f, 0.76f},  {0.00000000f, 0.0f, 0.84f},
    {240.00000000f, 1.0f, 0.92f},  {69.41176471f, 1.0f, 0.5f},    {75.00000000f, 1.0f, 0.68f},
    {80.00000000f, 1.0f, 0.76f},   {90.00000000f, 1.0f, 0.84f},   {120.00000000f, 1.0f, 0.92f},
    {180.00000000f, 1.0f, 0.92f},  {0.00000000f, 1.0f, 0.5f},     {337.64705882f, 1.0f, 0.5f},
    {328.23529412f, 1.0f, 0.5f},   {318.82352941f, 1.0f, 0.5f},   {309.41176471f, 1.0f, 0.5f},
    {300.00000000f, 1.0f, 0.5f},   {22.35294118f, 1.0f, 0.5f},    {0.00000000f, 1.0f, 0.68f},
    {345.00000000f, 1.0f, 0.68f},  {330.00000000f, 1.0f, 0.68f},  {315.00000000f, 1.0f, 0.68f},
    {300.00000000f, 1.0f, 0.68f},  {31.76470588f, 1.0f, 0.5f},    {15.00000000f, 1.0f, 0.68f},
    {0.00000000f, 1.0f, 0.76f},    {340.00000000f, 1.0f, 0.76f},  {320.00000000f, 1.0f, 0.76f},
    {300.00000000f, 1.0f, 0.76f},  {41.17647059f, 1.0f, 0.5f},    {30.00000000f, 1.0f, 0.68f},
    {20.00000000f, 1.0f, 0.76f},   {0.00000000f, 1.0f, 0.84f},    {330.00000000f, 1.0f, 0.84f},
    {300.00000000f, 1.0f, 0.84f},  {50.58823529f, 1.0f, 0.5f},    {45.00000000f, 1.0f, 0.68f},
    {40.00000000f, 1.0f, 0.76f},   {30.00000000f, 1.0f, 0.84f},   {0.00000000f, 1.0f, 0.92f},
    {300.00000000f, 1.0f, 0.92f},  {60.00000000f, 1.0f, 0.5f},    {60.00000000f, 1.0f, 0.68f},
    {60.00000000f, 1.0f, 0.76f},   {60.00000000f, 1.0f, 0.84f},   {60.00000000f, 1.0f, 0.92f},
    {0.00000000f, 0.0f, 1.0f},     {0.00000000f, 0.0f, 0.03f},    {0.00000000f, 0.0f, 0.07f},
    {0.00000000f, 0.0f, 0.1f},     {0.00000000f, 0.0f, 0.14f},    {0.00000000f, 0.0f, 0.18f},
    {0.00000000f, 0.0f, 0.22f},    {0.00000000f, 0.0f, 0.26f},    {0.00000000f, 0.0f, 0.3f},
    {0.00000000f, 0.0f, 0.34f},    {0.00000000f, 0.0f, 0.37f},    {0.00000000f, 0.0f, 0.4f},
    {0.00000000f, 0.0f, 0.46f},    {0.00000000f, 0.0f, 0.5f},     {0.00000000f, 0.0f, 0.54f},
    {0.00000000f, 0.0f, 0.58f},    {0.00000000f, 0.0f, 0.61f},    {0.00000000f, 0.0f, 0.65f},
    {0.00000000f, 0.0f, 0.69f},    {0.00000000f, 0.0f, 0.73f},    {0.00000000f, 0.0f, 0.77f},
    {0.00000000f, 0.0f, 0.81f},    {0.00000000f, 0.0f, 0.85f},    {0.00000000f, 0.0f, 0.89f},
    {0.00000000f, 0.0f, 0.93f},
}};
}

const std::array<hsl_color, xterm_color_table_size>& get_xterm_color_table() noexcept
{
    return xterm_color_table;
}
} // namespace carrot
