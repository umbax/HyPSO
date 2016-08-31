/*
 * model.cpp *
 *  Created on: Aug 19, 2016
 *      Author: umba
 */

#include <math.h>
#define PI (3.1415926535897932384626433832795028841971693994L)
#define E (2.7182818284590452353602874713526624977572470937L)


double model(double* x, int spacedim)
{
	double f;
	// Rosenbrock (minimum equal to 0 in 1,1)
	//f = 100*(x[0]-x[1]*x[1])*(x[0]-x[1]*x[1])+(1-x[1])*(1-x[1]);

	// Ackley's function (https://en.wikipedia.org/wiki/Test_functions_for_optimization)
	// global minimum: 0 in (0,0) | bounds -5 <= xi <= 5
	f = -20*exp(-0.2*sqrt(0.5*(pow(x[0],2)+pow(x[1],2))))-exp(0.5*(cos(2.0*PI*x[0])+cos(2.0*PI*x[1])))+E+20.0;

	return f;
}


double Rosenbrock(double* x, int spacedim)
{
	double f;
	// Rosenbrock (global minimum: 0 in 1,1)
	f = 100*(x[0]-x[1]*x[1])*(x[0]-x[1]*x[1])+(1-x[1])*(1-x[1]);

	return f;
}


double Ackley(double* x, int spacedim)
{
	double f;

	// Ackley's function (https://en.wikipedia.org/wiki/Test_functions_for_optimization)
	// global minimum: 0 in (0,0) | bounds -5 <= xi <= 5
	f = -20*exp(-0.2*sqrt(0.5*(pow(x[0],2)+pow(x[1],2))))-exp(0.5*(cos(2.0*PI*x[0])+cos(2.0*PI*x[1])))+E+20.0;

	return f;
}
