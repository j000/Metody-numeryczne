#include <functional>

#include "parametry.hpp"

double pochodna(const std::function<double(double)>& f, double x, double delta)
{
	// clang-format off
	double tmp =
			- 5. * f(x + delta)
			+ 8. * f(x + 2. * delta)
			- 3. * f(x + 3 * delta);
	// clang-format on
	return tmp / (2. * delta);
}
