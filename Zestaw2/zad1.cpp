#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>

#include "common.hpp"

////////////////////////////////////////

double
metoda_trapezow(const std::function<double(double)>& f, unsigned ilosc_punktow)
{
	double out{0.};
	const double dx{PI / (ilosc_punktow - 1)};
	// pomijamy pierwszy i ostatni wyraz, bo będą równe 0.
	// out += 0.5 * std::sin(0.) * f(0.);
	// out += 0.5 * std::sin(PI) * f(PI);
	for (auto i{1u}; i < (ilosc_punktow - 1); ++i) {
		const double x = i * dx;
		out += std::sin(x) * f(x);
	}

	return dx * out;
}

double
metoda_simpsona(const std::function<double(double)>& f, unsigned ilosc_punktow)
{
	double out = 0.;
	const double dx{PI / (ilosc_punktow - 1)};
	// pomijamy pierwszy i ostatni wyraz, bo będą równe 0.
	// out += 0.5 * std::sin(0.) * f(0.);
	// out += 0.5 * std::sin(PI) * f(PI);
	for (auto i{1u}; i < (ilosc_punktow - 1); ++i) {
		const double x{i * dx};
		const double tmp{std::sin(x) * f(x)};
		if (i % 2)
			out += 4 * tmp;
		else
			out += 2 * tmp;
	}

	return dx / 3. * out;
}

double kwadratura_gaussa(const std::function<double(double)>& f)
{
	// tak nam wyszło na ćwiczeniach
	// i tablice potwierdzają
	const double x0 = std::sqrt(1. / 3);
	const double x1 = -x0;
	const double w0 = 1.;
	const double w1 = 1.;

	const double t0 = (0. + PI) / 2 + ((PI - 0.) / 2) * x0;
	const double t1 = (0. + PI) / 2 + ((PI - 0.) / 2) * x1;

	double out = 0.;
	out += w0 * std::sin(t0) * f(t0);
	out += w1 * std::sin(t1) * f(t1);
	return ((PI - 0) / 2) * out;
}

namespace helper {
std::array<double, 4> init_t(const std::array<double, 4>& x)
{
	std::array<double, 4> out{};
	for (auto i{0u}; i < 4; ++i) {
		out[i] = (0. + PI) / 2 + ((PI - 0.) / 2) * x[i];
	}
	return out;
}
} // namespace helper

double kwadratura_gaussa2(const std::function<double(double)>& f)
{
	// z różnych tablic
	static const std::array<double, 4> x{
		(+1. / 35. * std::sqrt(525. - 70. * std::sqrt(30.))),
		(-1. / 35. * std::sqrt(525. - 70. * std::sqrt(30.))),
		(+1. / 35. * std::sqrt(525. + 70. * std::sqrt(30.))),
		(-1. / 35. * std::sqrt(525. + 70. * std::sqrt(30.)))};
	static const std::array<double, 4> w{
		(1. / 36. * (18. + std::sqrt(30.))),
		(1. / 36. * (18. + std::sqrt(30.))),
		(1. / 36. * (18. - std::sqrt(30.))),
		(1. / 36. * (18. - std::sqrt(30.))),
	};

	static const std::array<double, 4> t = helper::init_t(x);

	double out = 0.;
	for (auto i{0u}; i < 4; ++i) {
		out += w[i] * std::sin(t[i]) * f(t[i]);
	}
	return ((PI - 0) / 2) * out;
}

////////////////////////////////////////

void policz_trapezy(const std::function<double(double)>& f, double wynik)
{
	std::cout << "\tmetoda trapezów:" << std::endl;
	for (auto i{10u}; i <= 10'000; i *= 10) {
		std::cout << "\t\t" << i
				  << " punktów, błąd: " << metoda_trapezow(f, i) - wynik
				  << std::endl;
	}
}

void policz_simpsonem(const std::function<double(double)>& f, double wynik)
{
	std::cout << "\tmetoda Simpsona:" << std::endl;
	for (auto i{10u}; i <= 10'000; i *= 10) {
		std::cout << "\t\t" << i
				  << " punktów, błąd: " << metoda_simpsona(f, i) - wynik
				  << std::endl;
	}
}

void policz_gaussem(const std::function<double(double)>& f, double wynik)
{
	std::cout << "\t2-punktowa kwadratura Gaussa, błąd: "
			  << kwadratura_gaussa(f) - wynik << std::endl;
	std::cout << "\t4-punktowa kwadratura Gaussa, błąd: "
			  << kwadratura_gaussa2(f) - wynik << std::endl;
}

void policz(
	const std::function<double(double)>& f,
	const std::string_view& f_name,
	double wynik,
	const std::string_view& wynik_name)
{
	std::cout << "całḱa z sin(x) * " << f_name << " = " << wynik_name << ":"
			  << std::endl;
	policz_trapezy(f, wynik);
	policz_simpsonem(f, wynik);
	policz_gaussem(f, wynik);
	std::cout << std::endl;
}

////////////////////////////////////////

int main(int, char**)
{
	// number of digits that are necessary to uniquely represent distinct values
	std::cout << std::setprecision(std::numeric_limits<double>::max_digits10);

	policz([](double) { return 1.; }, "1", 2., "2");
	policz([](double x) { return std::sin(x); }, "sin(x)", PI / 2, "pi/2");
	policz([](double x) { return x * x; }, "(x^2)", PI * PI - 4, "pi^2-4");
	policz(
		[](double x) { return std::floor(x); },
		"floor(x)",
		3. + std::cos(1.) + std::cos(2.) + std::cos(3.),
		"3 + cos(1) + cos(2) + cos(3)");
}
