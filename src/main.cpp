/*
 * main.cpp *
 *  Created on: Aug 19, 2016
 *      Author: umba
 */


// Copyright 2016 Dr Umberto Armani
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


using namespace std;

#include <iostream>

#include "model.h"
#include "psominimize.h"
#include "matrix_operations.h"


int main ()
{
	cout << "\n\n HyPSO first experiments\n" << endl;

	// set initial values of ?
	int out = .0;


	// inputs - so far only the version for a number of variable > 2 works!
	int spacedim = 2; //1;
	double swarmcentre[2] = {2.0, 2.0}; // {1.0}; //swarmcentre[2] = {2.0, 2.0};  // for nD design spaces
	double swarmspan[2] = {5.0, 5.0}; //{5.0}; //swarmspan[2] = {5.0, 5.0};  // for nD design spaces
	int nparticles = 100;
	int nsteps = 100;
	double** bounds=zeros(2,2); // rows corresponds to variable (1st row= 1st variable) - 1st column= lower bound - 2nd column= upper bound
	// for 1D design spaces, use to rows but only the first row is considered
	bounds[0][0] = -5.0;
	bounds[0][1] = 5.0;
	bounds[1][0] = -5.0;
	bounds[1][1] = 5.0;

	// get address of objective function
	double (*p_objfun)(double*, int);
	p_objfun = &Rosenbrock; //&Salustowicz;    // model contains the objective function to be minimised (user defined)

	// launch single PSO search for global minima (function for now)
	//double** results = new double[]
	out = psominimize(p_objfun, spacedim, swarmcentre, swarmspan, nparticles, nsteps, bounds);

	cout << "\n\nout = " << out << endl << endl;

}


