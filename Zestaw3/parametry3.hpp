#ifndef PARAMETRY_HPP
#define PARAMETRY_HPP

#include <cmath>

// const double x = 4.;
// const double real_result = 19.;
// const auto f = [](const double x) { return (2. * x + 3.) * x - 1.; };
const double x = 0.5;
const double real_result = std::cos(x);
const auto f = [](const double x) { return std::sin(x); };

////////////////////////////////////////

#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>

double blad(const double x, const double x_prawdziwe)
{
	return std::abs(x - x_prawdziwe);
}

double blad_wzgledny(const double x, const double x_prawdziwe)
{
	double out = std::abs(x / x_prawdziwe - 1.);
	if (std::isnan(out) || std::isinf(out) || out == 1.)
		return 0;
	return out;
}

////////////////////////////////////////

double
pochodna(const std::function<double(double)>&, const double, const double);

int main(int, char**)
{
	// number of digits that are necessary to uniquely represent distinct values
	std::cout << std::setprecision(std::numeric_limits<double>::max_digits10);

	std::cout << "i,pochodna,wyliczona pochodna,błąd,błąd względny"
			  << std::endl;
	for (double i{1. / (16. * 1024.)}; i <= 4. * 1024.; i *= 2.) {
		const double delta = 1. + i;
		const double result = pochodna(f, x, delta);
		const double err = blad(result, real_result);
		const double err_rel = blad_wzgledny(result, real_result);
		std::cout << i << "," << real_result << "," << result << "," << err
				  << "," << err_rel << std::endl;
	}
	return 0;
}

#endif /* PARAMETRY_HPP */
