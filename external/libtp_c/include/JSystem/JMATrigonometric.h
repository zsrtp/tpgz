#include "../dolphin/types.h"
#include "../addrs.h"

namespace std {
template <class T1, class T2>
struct pair {
    T1 first;
    T2 second;

    pair() {
        first = T1();
        second = T2();
    }
};
}  // namespace std

template<int N, typename T>
struct TSinCosTable {
    std::pair<T, T> table[1 << N];

    T sinShort(s16 v) const { return table[(u16)v >> (16U - N)].first; }
    T cosShort(s16 v) const { return table[(u16)v >> (16U - N)].second; }

    // inline T sinLap(T v) {
    //     if (v < (T)0.0) {
    //         return -table[(u16)(-(T)(1 << N) * v) & ((1 << N) - 1)].first;
    //     }
    //     return table[(u16)((T)(1 << N) * v) & ((1 << N) - 1)].first;
    // }

    // inline T sinDegree(T degree) {
    //     if (degree < (T)0.0) {
    //         return -table[(u16)(((T)(1 << N) / 360.0) * degree) & ((1 << N) - 1)].first;
    //     } 
    //     return table[(u16)(((T)(1 << N) / 360.0) * degree) & ((1 << N) - 1)].first;
    // }

    // inline T cosDegree(T degree) {
    //     if (degree < (T)0.0) {
    //         degree = -degree;
    //     } 
    //     return table[(u16)(((T)(1 << N) / 360.0) * degree) & ((1 << N) - 1)].second;
    // }

    // inline T sinRadian(T radian) {
    //     if (radian < (T)0.0) {
    //         return -table[(u16)(-(T)(1 << N) / TAngleConstant_<T>::RADIAN_DEG360() * radian) & ((1 << N) - 1)].first;
    //     }
    //     return table[(u16)((T)(1 << N) / TAngleConstant_<T>::RADIAN_DEG360() * radian) & ((1 << N) - 1)].first;
    // }
};

#define tp_sincosTable_addr 0x80439A20

#define tp_sincosTable (*(TSinCosTable<13, f32>*)(tp_sincosTable_addr))

inline f32 JMASCosShort(s16 v) {
    return tp_sincosTable.cosShort(v);
}
inline f32 JMASinShort(s16 v) {
    return tp_sincosTable.sinShort(v);
}

inline f32 JMASCos(s16 v) {
    return JMASCosShort(v);
}
inline f32 JMASSin(s16 v) {
    return JMASinShort(v);
}

