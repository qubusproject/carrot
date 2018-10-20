//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "catch.hpp"

#include <boost/range/adaptor/sliced.hpp>

#include <carrot/color.hpp>
#include <carrot/color_map.hpp>

TEST_CASE("RGB color initialisation", "[color]")
{
    carrot::rgb_color color1(255, 127, 42);

    REQUIRE(color1.red() == 255);
    REQUIRE(color1.green() == 127);
    REQUIRE(color1.blue() == 42);

    auto color2 = rgb(color1);

    REQUIRE(color1.red() == color2.red());
    REQUIRE(color1.green() == color2.green());
    REQUIRE(color1.blue() == color2.blue());

    auto color3 = rgb(carrot::color(color1));

    REQUIRE(color1.red() == color3.red());
    REQUIRE(color1.green() == color3.green());
    REQUIRE(color1.blue() == color3.blue());
}

TEST_CASE("HSL color initialisation", "[color]")
{
    carrot::hsl_color color1(255, 0.5f, 0.42f);

    REQUIRE(color1.hue() == 255);
    REQUIRE(color1.saturation() == 0.5f);
    REQUIRE(color1.lightness() == 0.42f);

    auto color2 = hsl(color1);

    REQUIRE(color1.hue() == color2.hue());
    REQUIRE(color1.saturation() == color2.saturation());
    REQUIRE(color1.lightness() == color2.lightness());

    auto color3 = hsl(carrot::color(color1));

    REQUIRE(color1.hue() == color3.hue());
    REQUIRE(color1.saturation() == color3.saturation());
    REQUIRE(color1.lightness() == color3.lightness());
}

TEST_CASE("RGB to HSL conversion", "[color]")
{
    carrot::rgb_color purple(128, 0, 128);

    auto purple_hsl = hsl(purple);

    REQUIRE(purple_hsl.hue() == Approx(300).epsilon(1e-4));
    REQUIRE(purple_hsl.saturation() == Approx(1.0f).epsilon(1e-2));
    REQUIRE(purple_hsl.lightness() == Approx(0.25f).epsilon(1e-2));

    carrot::rgb_color yellow4(135, 135, 0);

    auto yellow4_hsl = hsl(yellow4);

    REQUIRE(yellow4_hsl.hue() == Approx(60).epsilon(1e-4));
    REQUIRE(yellow4_hsl.saturation() == Approx(1.0f).epsilon(1e-2));
    REQUIRE(yellow4_hsl.lightness() == Approx(0.265f).epsilon(1e-2));
}

TEST_CASE("HSL to RGB conversion", "[color]")
{
    carrot::hsl_color purple(300, 1.0f, 0.25f);

    auto purple_rgb = rgb(purple);

    REQUIRE(purple_rgb.red() == 128);
    REQUIRE(purple_rgb.green() == 0);
    REQUIRE(purple_rgb.blue() == 128);
}

TEST_CASE("Empty color maps are invalid", "[color]")
{
    using namespace carrot;

    std::vector<hsl_color> colors;

    REQUIRE_THROWS_AS(color_map(colors), invalid_color_map_error);
}

TEST_CASE("Color map initialisation", "[color]")
{
    using namespace carrot;

    std::vector<hsl_color> colors = {
        {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.25f}, {120.0f, 1.0f, 0.25f}, {120.0f, 1.0f, 0.5f}};

    color_map cmap(colors);

    REQUIRE(cmap.map_color(rgb_color(0, 150, 0)) == 2);
    REQUIRE(cmap.map_color(rgb_color(0, 200, 0)) == 3);
}

TEST_CASE("XTerm standard color map", "[color]")
{
    using namespace carrot;

    color_map cmap(carrot::get_xterm_color_table() | boost::adaptors::sliced(0, 16));

    REQUIRE(cmap.map_color(rgb_color(0, 150, 0)) == 2);
    REQUIRE(cmap.map_color(rgb_color(0, 200, 0)) == 10);
}

TEST_CASE("Extended XTerm color map", "[color]")
{
    using namespace carrot;

    color_map cmap(carrot::get_xterm_color_table());

    REQUIRE(cmap.map_color(rgb_color(0, 150, 0)) == 28);
    REQUIRE(cmap.map_color(rgb_color(0, 200, 0)) == 40);
    REQUIRE(cmap.map_color(rgb_color(0, 215, 135)) == 42);
    REQUIRE(cmap.map_color(rgb_color(95, 0, 0)) == 52);
    REQUIRE(cmap.map_color(rgb_color(135, 135, 0)) == 100);
    REQUIRE(cmap.map_color(rgb_color(135, 135, 95)) == 101);
    REQUIRE(cmap.map_color(rgb_color(135, 135, 255)) == 105);
    REQUIRE(cmap.map_color(rgb_color(175, 95, 95)) == 131);
    REQUIRE(cmap.map_color(rgb_color(255, 135, 215)) == 212);
    REQUIRE(cmap.map_color(rgb_color(255, 135, 255)) == 213);
    REQUIRE(cmap.map_color(rgb_color(228, 228, 228)) == 254);
    REQUIRE(cmap.map_color(rgb_color(238, 238, 238)) == 255);
    REQUIRE(cmap.map_color(rgb_color(0, 0, 0)) == 0);
    REQUIRE(cmap.map_color(rgb_color(8, 8, 8)) == 232);
    REQUIRE(cmap.map_color(rgb_color(18, 18, 18)) == 233);
    REQUIRE(cmap.map_color(rgb_color(28, 28, 28)) == 234);
}

TEST_CASE("Named color support", "[color]")
{
    using namespace carrot;

    REQUIRE_THROWS_AS(rgb(named_color("red")), invalid_color_error);
    REQUIRE_THROWS_AS(hsl(named_color("red")), invalid_color_error);

    color_table ctable;

    REQUIRE_THROWS_AS(rgb(named_color("red"), ctable), invalid_color_error);

    ctable = get_default_color_table();

    ctable.add_color("mycolor", rgb_color(42, 128, 70));

    auto mycolor = rgb(named_color("mycolor"), ctable);

    REQUIRE(mycolor.red() == 42);
    REQUIRE(mycolor.green() == 128);
    REQUIRE(mycolor.blue() == 70);

    auto mycolor_hsl = hsl(named_color("mycolor"), ctable);

    REQUIRE(mycolor_hsl.hue() == Approx(139.5).epsilon(1e-1));
    REQUIRE(mycolor_hsl.saturation() == Approx(0.5059).epsilon(1e-3));
    REQUIRE(mycolor_hsl.lightness() == Approx(0.3333).epsilon(1e-3));

    auto mycolor2 = rgb(canonicalize(named_color("mycolor"), ctable));

    REQUIRE(mycolor2.red() == 42);
    REQUIRE(mycolor2.green() == 128);
    REQUIRE(mycolor2.blue() == 70);
}

TEST_CASE("Special default colors", "[color]")
{
    using namespace carrot;

    auto ctable = get_default_color_table();

    REQUIRE_THROWS_AS(rgb(get_default_color()), invalid_color_error);
    REQUIRE_THROWS_AS(rgb(get_default_color(), ctable), invalid_color_error);
    REQUIRE_THROWS_AS(hsl(get_default_color()), invalid_color_error);
    REQUIRE_THROWS_AS(hsl(get_default_color(), ctable), invalid_color_error);

    REQUIRE_THROWS_AS(canonicalize(get_default_color(), ctable), invalid_color_error);

    REQUIRE(is_default_color(get_default_color()));
}