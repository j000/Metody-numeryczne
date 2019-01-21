#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

#include "common.hpp"

constexpr MyFloat PLOT_POINTS{1024.};

////////////////////////////////////////

namespace helper {
constexpr double silnia(size_t N)
{
	if (N == 0)
		return 1.;
	return 1. / N * silnia(N - 1);
}

static inline MyFloat sin3(const MyFloat x)
{
	const double x2 = x * x;
	return x * (silnia(1) - x2 * (silnia(3) - x2 * (silnia(5) - x2 * (silnia(7) - x2 * silnia(9)))));
}
} // namespace helper

MyFloat sin3(const MyFloat x)
{
	if (x < 0)
		return -sin3(-x);
	if (x <= PI / 2)
		return helper::sin3(x);
	if (x <= PI)
		return helper::sin3(PI - x);
	if (x <= 2 * PI)
		return -sin3(x - PI);

	MyFloat x2 = std::remainder(x, 2 * PI);
	return sin3(x2);
}

MyFloat cos3(const MyFloat x)
{
	return sin3(PI / 2 - x);
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
		const MyFloat result_sin3 = sin3(x);
		results.push_back({x,
						   result_sin,
						   result_sin3,
						   blad(result_sin3, result_sin),
						   blad_wzgledny(result_sin3, result_sin)});
	}

	std::cout << "x,sin,sin3,błąd,błąd względny" << std::endl;
	for (const auto& v : results) {
		std::cout << v[0] << "," << v[1] << "," << v[2] << "," << v[3] << ","
				  << v[4] << std::endl;
	}
}
