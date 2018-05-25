#pragma once

#include <iostream>

template <class T = float>
class Vec2 {
   public:
	T x;
	T y;

	Vec2() : x(0), y(0) {}
	Vec2(T _x, T _y) : x(_x), y(_y) {}
	Vec2(const Vec2& cpy) : x(cpy.x), y(cpy.y) {}

	inline Vec2& operator=(const Vec2& rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	inline Vec2 operator+(const Vec2& rhs) {
		Vec2 v(*this);

		v.x += rhs.x;
		v.y += rhs.y;
		return v;
	}
	inline Vec2 operator-(const Vec2& rhs) {
		Vec2 v(*this);

		v.x -= rhs.x;
		v.y -= rhs.y;
		return v;
	}

	inline Vec2 operator*(const Vec2& rhs) {
		Vec2 v(*this);

		v.x *= rhs.x;
		v.y *= rhs.y;
		return v;
	}

	inline Vec2 operator/(const Vec2& rhs) {
		Vec2 v(*this);

		v.x /= rhs.x;
		v.y /= rhs.y;
		return v;
	}

	inline void Print() {
		std::cout << "Vec2 x: " << x << ", y: " << y << "\n";
	}
};
