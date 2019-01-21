#ifndef COMMON_HPP
#define COMMON_HPP

#include <cmath>

struct Point {
	const double x;
	const double y;

	Point(const double _x, const double _y) : x{_x}, y{_y}
	{
	}
};

constexpr double PI{3.14159265358979323846};
#include <iostream>

static inline double blad(const double x, const double x_prawdziwe)
{
	return std::abs(x - x_prawdziwe);
}

static inline double blad_wzgledny(const double x, const double x_prawdziwe)
{
	double out = std::abs((x - x_prawdziwe) / x_prawdziwe);
	if (std::isnan(out) || out == double{1.})
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
