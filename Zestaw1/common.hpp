#ifndef COMMON_HPP
#define COMMON_HPP

#include <cmath>

#ifdef USE_FLOAT
using MyFloat = float;
#elif USE_EXTENDED
using MyFloat = long double;
#else
using MyFloat = double;
#endif

struct Point {
	const MyFloat x;
	const MyFloat y;

	Point(const MyFloat _x, const MyFloat _y) : x{_x}, y{_y}
	{
	}
};

constexpr MyFloat PI{3.14159265358979323846};
#include <iostream>

static inline MyFloat blad(const MyFloat x, const MyFloat x_prawdziwe)
{
	return std::abs(x - x_prawdziwe);
}

static inline MyFloat blad_wzgledny(const MyFloat x, const MyFloat x_prawdziwe)
{
	MyFloat out = std::abs((x - x_prawdziwe) / x_prawdziwe);
	if (std::isnan(out) || std::isinf(out) || out == MyFloat{1.})
		return 0.;
	return out;
}

#if 0
template <typename T>
void print_binary(T x)
{
	unsigned char* cp = (unsigned char*)&x;
	std::cout << x << ": ";
	std::cout << std::hex << std::setfill('0');
	for (auto i{0u}; i < sizeof(T); ++i) {
		std::cout << std::setw(2) << (int)cp[i] << ' ';
	}
	std::cout << std::endl;
}
#endif

#endif /* COMMON_HPP */
