#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>

#include "common.hpp"

////////////////////////////////////////

double metoda_trapezow(
	const std::function<double(double)>& f,
	unsigned ilosc_punktow,
	double limit)
{
	double out{0.};
	const double dx{limit / (ilosc_punktow - 1)};
	out += 0.5 * std::exp(0.) / std::sqrt(limit) * f(0.);
	out += 0.5 * std::exp(-limit) / std::sqrt(limit) * f(limit);
	for (auto i{1u}; i < (ilosc_punktow - 1); ++i) {
		const double x = i * dx;
		out += std::exp(-x) / std::sqrt(x) * f(x);
	}

	return dx * out;
}

double metoda_simpsona(
	const std::function<double(double)>& f,
	unsigned ilosc_punktow,
	double limit)
{
	double out = 0.;
	const double dx{limit / (ilosc_punktow - 1)};
	out += 0.5 * std::exp(0.) / std::sqrt(limit) * f(0.);
	out += 0.5 * std::exp(-limit) / std::sqrt(limit) * f(limit);
	for (auto i{1u}; i < (ilosc_punktow - 1); ++i) {
		const double x{i * dx};
		const double tmp{std::exp(-x) / std::sqrt(x) * f(x)};
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
	const double x0 = 2. - std::sqrt(2.);
	const double x1 = 2 + std::sqrt(2.);
	const double w0 = 1. / 4. * x1;
	const double w1 = 1. / 4. * x0;

	double out = 0.;
	out += w0 * f(x0);
	out += w1 * f(x1);
	return out;
}

double kwadratura_gaussa2(const std::function<double(double)>& f)
{
	// z różnych tablic
	static const std::array<double, 4> x{
		0.322548, 1.745761, 4.536620, 9.395071};
	static const std::array<double, 4> w{
		0.603154, 0.357419, 0.0388879, 0.000539295};

	double out = 0.;
	for (auto i{0u}; i < 4; ++i) {
		out += w[i] * f(x[i]);
	}
	return out;
}

double kwadratura_sinhtanh(
	const std::function<double(double)>& f,
	unsigned ilosc_punktow)
{
	static const double max
		= std::log(std::log(std::numeric_limits<double>::max()));
	static const double min = std::exp(1.);

	auto x = [](double t) -> double { return std::exp(t - std::exp(-t)); };
	auto dx = [&x](double t) -> double { return x(t) * (1 + std::exp(-t)); };

	// metoda trapezów
	const double step{(max - min) / (ilosc_punktow - 1)};

	double out{0.};
	out += 0.5 * std::exp(-x(min)) / std::sqrt(x(min)) * f(x(min));
	out += 0.5 * std::exp(-x(max)) / std::sqrt(x(max)) * f(x(max));
	for (auto t{min}; t <= max; t += step) {
		out += std::exp(-x(t)) / std::sqrt(x(t)) * f(x(t)) * dx(t);
	}
	return step * out;
}

////////////////////////////////////////

void policz_trapezy(
	const std::function<double(double)>& f,
	double wynik,
	double limit)
{
	std::cout << "\tmetoda trapezów [0, " << limit << "]:" << std::endl;
	for (auto i{1000u}; i <= 1'000'000; i *= 10) {
		std::cout << "\t\t" << i
				  << " punktów, błąd: " << wynik - metoda_trapezow(f, i, limit)
				  << std::endl;
	}
}

void policz_trapezy(const std::function<double(double)>& f, double wynik)
{
	for (auto i{1e2}; i <= 1e6; i *= 1e2) {
		policz_trapezy(f, wynik, i);
	}
}

void policz_simpsonem(
	const std::function<double(double)>& f,
	double wynik,
	double limit)
{
	std::cout << "\tmetoda Simpsona [0, " << limit << "]:" << std::endl;
	for (auto i{1000u}; i <= 1'000'000; i *= 10) {
		std::cout << "\t\t" << i
				  << " punktów, błąd: " << wynik - metoda_simpsona(f, i, limit)
				  << std::endl;
	}
}

void policz_simpsonem(const std::function<double(double)>& f, double wynik)
{
	for (auto i{1e2}; i <= 1e6; i *= 1e2) {
		policz_simpsonem(f, wynik, i);
	}
}

void policz_gaussem(const std::function<double(double)>& f, double wynik)
{
	std::cout << "\t2-punktowa kwadratura Gaussa, błąd: "
			  << wynik - kwadratura_gaussa(f) << std::endl;
	std::cout << "\t4-punktowa kwadratura Gaussa, błąd: "
			  << wynik - kwadratura_gaussa2(f) << std::endl;
}

void policz_sinhtanh(const std::function<double(double)>& f, double wynik)
{
	std::cout << "\tkwadratura sinh-tanh:" << std::endl;
	for (auto i{10u}; i <= 10'000; i *= 10) {
		std::cout << "\t\t" << i
				  << " punktów, błąd: " << wynik - kwadratura_sinhtanh(f, i)
				  << std::endl;
	}
}

void policz(
	const std::function<double(double)>& f,
	const std::string_view& f_name,
	double wynik,
	const std::string_view& wynik_name)
{
	std::cout << "całḱa z exp(-x) / sqrt(x) * " << f_name << " = " << wynik_name
			  << ":" << std::endl;
	policz_trapezy(f, wynik);
	policz_simpsonem(f, wynik);
	policz_gaussem(f, wynik);
	policz_sinhtanh(f, wynik);
	std::cout << std::endl;
}

////////////////////////////////////////

int main(int, char**)
{
	// number of digits that are necessary to uniquely represent distinct values
	std::cout << std::setprecision(std::numeric_limits<double>::max_digits10);

	policz([](double) { return 1.; }, "1", std::sqrt(PI), "sqrt(pi)");
	policz([](double x) { return x; }, "x", std::sqrt(PI) / 2, "sqrt(pi)/2");
	policz(
		[](double x) { return x * x; },
		"(x^2)",
		std::sqrt(PI) * 0.75,
		"sqrt(pi) * 0.75");
	policz(
		[](double x) { return std::abs(x - 20) + 20; },
		"(abs(x - 20) + 20)",
		70.01,
		"70.01"); // wynik z Wolframa
}
