#include <functional>

#include "parametry3.hpp"

double
pochodna(const std::function<double(double)>& f, const double x, const double q)
{
	// clang-format off
	double tmp =
		f(x / q) * q * q / (1 - q * q)
		+ f(x)
		+ f(q * x) / (q * q - 1);
	// clang-format on
	return tmp / (x);
}
