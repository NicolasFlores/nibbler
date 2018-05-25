#include <Vec2.hpp>
#include <iostream>

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float _x, float _y) : x(_x), y(_y) {}

Vec2::Vec2(const Vec2& cpy) : x(cpy.x), y(cpy.y) {}

void Vec2::Print() {
	std::cout << "Vec2 x: " << x, << ", y: ", << y << "\n";
}

Vec2& Vec2::operator=(const Vec2& rhs) {
	x = rhs.x;
	y = rhs.y;
	return *this;
}

Vec2 Vec2::operator+(const Vec2& rhs) {
	Vec2 v(*this);

	v.x += rhs.x;
	v.y += rhs.y;
	return v;
}

Vec2 Vec2::operator-(const Vec2& rhs) {
	Vec2 v(*this);

	v.x -= rhs.x;
	v.y -= rhs.y;
	return v;
}

Vec2 Vec2::operator*(const Vec2& rhs) {
	Vec2 v(*this);

	v.x *= rhs.x;
	v.y *= rhs.y;
	return v;
}

Vec2 Vec2::operator/(const Vec2& rhs) {
	Vec2 v(*this);

	v.x /= rhs.x;
	v.y /= rhs.y;
	return v;
}
