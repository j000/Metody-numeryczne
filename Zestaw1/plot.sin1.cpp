#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

#include "common.hpp"

constexpr auto PLOT_POINTS{1024.};

////////////////////////////////////////
// tablica wartości
static inline const Point data[]{{0., 0.},
						  {PI / 6., 1. / 2.},
						  {PI / 4., sqrt(2.) / 2.},
						  {PI / 3., sqrt(3.) / 2.},
						  {PI / 2., 1.}};

static inline const size_t data_size = sizeof(data) / sizeof(data[0]);

////////////////////////////////////////

static inline MyFloat lerp(const Point first, const Point second, MyFloat x)
{
	return (first.y * (second.x - x) + second.y * (x - first.x))
		/ (second.x - first.x);
}

static inline MyFloat
sin1(const MyFloat x, const Point* const data, const size_t data_size)
{
	if (x < data[0].x)
		return data[1].y;
	for (auto i = 1u; i < data_size; ++i) {
		if (x < data[i].x)
			return lerp(data[i - 1], data[i], x);
	}
	return data[data_size - 1].y;
}

MyFloat sin1(const MyFloat x)
{
	if (x < 0)
		return -sin1(-x);
	if (x <= PI / 2)
		return sin1(x, data, data_size);
	if (x <= PI)
		return sin1(
			PI - x, data, data_size);
	if (x <= 2 * PI)
		return -sin1(x - PI);

	MyFloat x2 = std::remainder(x, 2 * PI);
	return sin1(x2);
}

MyFloat cos1(const MyFloat x)
{
	return sin1(PI / 2 - x);
}

////////////////////////////////////////

int main(int, char**)
{
	// number of digits that are necessary to uniquely represent distinct values
	std::cout << std::setprecision(std::numeric_limits<MyFloat>::max_digits10);

	std::vector<std::array<MyFloat, 5>> results;
	results.reserve(PLOT_POINTS);
	for (MyFloat i{0.}; i <= 1.; i += MyFloat{1. / PLOT_POINTS}) {
		const MyFloat x{i * PI / 2};
		const MyFloat result_sin = std::sin(x);
		const MyFloat result_sin1 = sin1(x);
		results.push_back({x,
						   result_sin,
						   result_sin1,
						   blad(result_sin1, result_sin),
						   blad_wzgledny(result_sin1, result_sin)});
	}

	std::cout << "x,sin,sin1,błąd,błąd względny" << std::endl;
	for (const auto& v : results) {
		std::cout << v[0] << "," << v[1] << "," << v[2] << "," << v[3] << ","
				  << v[4] << std::endl;
	}
}
