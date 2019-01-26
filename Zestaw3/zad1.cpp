#include <functional>

#include "parametry.hpp"

double pochodna(const std::function<double(double)>& f, const double x, const double delta)
{
	return (f(x + delta) - f(x)) / delta;
}
