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
static inline int factorial(int n)
{
	static std::vector<int> cache{1};
	try {
		return cache.at(n);
	} catch (const std::out_of_range&) {
		int out = n * factorial(n - 1);
		if (cache.size() < n + 1)
			cache.resize(n + 1);
		cache[n] = out;
		return out;
	}
}
static inline int C(int n, int k)
{
	if (k == 0 || k == n)
		return 1;

	return factorial(n) / factorial(k) / factorial(n - k);
}

static inline MyFloat sin4(const MyFloat x)
{
	// return x;
	constexpr int n = 4;
	MyFloat out{0.};
	for (int k{0u}; k <= n; ++k) {
		out += std::sin(k * 1. / n) * C(n, k) * std::pow(x, k)
			* std::pow(1 - x, n - k);
	}
	return out;
}
} // namespace helper

MyFloat sin4(const MyFloat x)
{
	if (x < 0)
		return -sin4(-x);
	if (x <= PI / 2)
		return helper::sin4(x);
	if (x <= PI)
		return helper::sin4(PI - x);
	if (x <= 2 * PI)
		return -sin4(x - PI);

	MyFloat x2 = std::remainder(x, 2 * PI);
	return sin4(x2);
}

MyFloat cos4(const MyFloat x)
{
	return sin4(PI / 2 - x);
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
		const MyFloat result_sin4 = sin4(x);
		results.push_back({x,
						   result_sin,
						   result_sin4,
						   blad(result_sin4, result_sin),
						   blad_wzgledny(result_sin4, result_sin)});
	}

	std::cout << "x,sin,sin4,błąd,błąd względny" << std::endl;
	for (const auto& v : results) {
		std::cout << v[0] << "," << v[1] << "," << v[2] << "," << v[3] << ","
				  << v[4] << std::endl;
	}
}
