#ifndef Math_h
#define Math_h

/// Mathematics library containing general mathematic functions that used
/// across several math modules or anything that cannot be grouped or
/// categorized separately.

#include <limits>
#include <cmath>

namespace Math
{
    /// @see https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
    template< typename fp_t >
    inline bool isEqualEpsilon( const fp_t a, const fp_t b, const fp_t unitsInLastPlace = 2 )
    {
        static_assert( std::is_floating_point< fp_t >::value, "types passed must be floating point." );
        const auto epsilon = std::numeric_limits< fp_t >::epsilon() * std::fabs( a + b ) * unitsInLastPlace;
        return std::fabs( b - a ) <= epsilon;
    }
}

#endif // Math_h