#include <functional>

#include "parametry.hpp"

double pochodna(
	const std::function<double(double)>& f,
	const double x,
	const double delta)
{
	// clang-format off
	double tmp =
			+ 1. * f(x - 2. * delta)
			- 8. * f(x - delta)
			// + 0. * f(x)
			+ 8. * f(x + delta)
			- 1. * f(x + 2. * delta);
	// clang-format on
	return tmp / (12. * delta);
}
