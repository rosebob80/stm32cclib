#ifndef REGBIT_HH
#define REGBIT_HH

#include "lib/types.hh"

namespace lib {
    template <u8 bit_n, typename U = bool, u8 bit_size = 1, U default_value = true>
    struct regbit {
        template<typename T>
        constexpr static T mask() {
                return
                    (static_cast<T>(default_value) & (-1 >> (sizeof(T) - bit_size))) << (bit_n);
        }

        template <U value>
        struct val {
            template<typename T>
            constexpr static T mask() {
                return
                    (static_cast<T>(value) & (-1 >> (sizeof(T) - bit_size))) << (bit_n);
            }
        };
    };

    template <typename T, typename ...Bits>
    struct regbits;

    template <typename T>
    struct regbits<T> {
        static const T mask = 0;
    };

    template <typename T, typename Bit, typename ...Bits>
    struct regbits<T, Bit, Bits...> {
        static const T mask =
            Bit::template mask<T>() | regbits<T, Bits...>::mask;
    };
}

#endif // REGBIT_HH
