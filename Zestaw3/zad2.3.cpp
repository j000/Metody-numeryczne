#include <functional>

#include "parametry.hpp"

double pochodna(
	const std::function<double(double)>& f,
	const double x,
	const double delta)
{
	// clang-format off
	double tmp =
			- 11. * f(x)
			+ 18. * f(x + delta)
			- 9. * f(x + 2. * delta)
			+ 2. * f(x + 3 * delta);
	// clang-format on
	return tmp / (6. * delta);
}
