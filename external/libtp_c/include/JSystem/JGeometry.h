#ifndef JGEOMETRY_H
#define JGEOMETRY_H

#include <stdint.h>

namespace JGeometry {

template <typename T>
struct TVec3 {
    T x;
    T y;
    T z;
};

template <typename T>
struct TVec2 {
    TVec2() {}
    TVec2(T x, T y) { set(x, y); }

    void set(T x, T y) {
        this->x = x;
        this->y = y;
    }

    void set(const TVec2& other) {
        x = other.x;
        y = other.y;
    }

    void setMin(const TVec2<float>& min) {
        if (min.x <= x)
            x = min.x;
        if (min.y <= y)
            y = min.y;
    }

    void setMax(const TVec2<float>& max) {
        if (x <= max.x)
            x = max.x;
        if (y <= max.y)
            y = max.y;
    }

    void add(const TVec2<T>& other) {
        x += other.x;
        y += other.y;
    }

    bool isAbove(const TVec2<T>& other) const {
        return (other.x <= x) && (other.y <= y) ? true : false;
    }

    T x;
    T y;
};

template <class T>
struct TBox {
    TBox() : i(), f() {}
    TBox(const TBox& other) : i(other.f), f(other.y) {}

    T i, f;
};

template <>
struct TBox<TVec2<float>> {
    float getWidth() const { return f.x - i.x; }
    float getHeight() const { return f.y - i.y; }

    bool isValid() const { return f.isAbove(i); }

    void addPos(const TVec2<float>& pos) {
        i.add(pos);
        f.add(pos);
    }

    bool intersect(const TBox<TVec2<float>>& other) {
        i.setMax(other.i);
        f.setMin(other.f);
        return isValid();
    }

    TVec2<float> i, f;
};

template <typename T>
struct TBox2 : TBox<TVec2<T>> {
    TBox2() {}
    TBox2(float x0, float y0, float x1, float y1) { set(x0, y0, x1, y1); }

    inline const TBox2& operator=(const TBox2& rhs) { *(TBox<TVec2<T>>*)this = rhs; }
    void set(const TBox2& other) { set(other.i, other.f); }
    void set(const TVec2<float>& i, const TVec2<float> f) { this->i.set(i), this->f.set(f); }
    void set(float x0, float y0, float x1, float y1) {
        this->i.set(x0, y0);
        this->f.set(x1, y1);
    }
};

}  // namespace JGeometry

#endif