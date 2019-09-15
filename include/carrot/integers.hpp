#ifndef CARROT_INTEGERS_HPP
#define CARROT_INTEGERS_HPP

namespace carrot
{

template <typename Destination, typename Source>
[[nodiscard]] constexpr Destination integer_cast(const Source& value)
{
    return static_cast<Destination>(value);
}

} // namespace carrot

#endif
