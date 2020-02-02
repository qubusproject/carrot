#ifndef CARROT_INTEGERS_HPP
#define CARROT_INTEGERS_HPP

#include <cassert>

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief Safely casts an integer into another integer type.
 *
 * @tparam Destination The destination type.
 * @tparam Source The source type.
 * @param value The value which will be converted.
 * @return The converted value.
 */
template <typename Destination, typename Source>
[[nodiscard]] constexpr Destination integer_cast(const Source& value) noexcept
{
    return static_cast<Destination>(value);
}

/** @brief Safely casts an integer with a constrained range into another integer type.
 *
 * @tparam Destination The destination type.
 * @tparam Source The source type.
 * @tparam RangeType The type of the integer range boundaries.
 * @param value The value which will be converted.
 * @param min The smallest value which the converted value might assume.
 * @param max The largest value which the converted value might assume.
 * @return The converted value.
 */
template <typename Destination, typename Source, typename RangeType>
[[nodiscard]] constexpr Destination convert_constrained_integer(Source value, RangeType min, RangeType max) noexcept
{
    // Assert that the constraint actually holds.
    assert(min <= value && value <= max);

    return static_cast<Destination>(value);
}

} // namespace carrot

#endif
