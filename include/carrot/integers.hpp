#ifndef CARROT_INTEGERS_HPP
#define CARROT_INTEGERS_HPP

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
[[nodiscard]] constexpr Destination integer_cast(const Source& value)
{
    return static_cast<Destination>(value);
}

} // namespace carrot

#endif
