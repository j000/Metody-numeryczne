#include <functional>

#include "parametry.hpp"

double pochodna(
	const std::function<double(double)>& f,
	const double x,
	const double delta)
{
	// clang-format off
	double tmp =
			- 3. * f(x)
			+ 4. * f(x + delta)
			- 1. * f(x + 2 * delta);
	// clang-format on
	return tmp / (2. * delta);
}
