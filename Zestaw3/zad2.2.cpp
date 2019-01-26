#include <functional>

#include "parametry.hpp"

double pochodna(const std::function<double(double)>& f, double x, double delta)
{
	// clang-format off
	double tmp =
			+ 1. * f(x - 2. * delta)
			- 6. * f(x - delta)
			+ 3. * f(x)
			+ 2. * f(x + delta);
	// clang-format on
	return tmp / (6. * delta);
}
