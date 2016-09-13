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

#include "model.h"	// contains the definition of the function whose minimum has to be found
#include "psominimize.h"
#include "matrix_operations.h"


int main ()
{
	cout << "\n\n HyPSO first experiments\n" << endl;

	int out = 0;


	// input parameters
	int spacedim = 2; //1;
	int nparticles = 100;
	int nsteps = 150;
	double swarmcentre[2] = {2.0, 2.0}; // {1.0}; //swarmcentre[2] = {2.0, 2.0};  // for nD design spaces
	double swarmspan[2] = {5.0, 5.0}; //{5.0}; //swarmspan[2] = {5.0, 5.0};  // for nD design spaces
	double** bounds=zeros(2,2); // rows corresponds to variable (1st row= 1st variable) - 1st column= lower bound - 2nd column= upper bound
	bounds[0][0] = -5.0;
	bounds[0][1] = 5.0;
	bounds[1][0] = -5.0;
	bounds[1][1] = 5.0;

	// get address of objective function
	double (*p_objfun)(double*, int);
	p_objfun = &Ackley; //&Rosenbrock; //&Salustowicz;    // model contains the objective function to be minimised (user defined)

	// optimisation output container (just an array fow now, easier to integrate into preexisting code)
	double* results = zeros(spacedim+1);  // minimum coordinates [spacedim], value of the function at minimum [1],

	// launch single PSO search for global minima (function for now)
	out = psominimize(p_objfun, spacedim, swarmcentre, swarmspan, nparticles, nsteps, bounds, results);

	// checks and output
	if (out==1) {
		cout << "\n\nOK, psominimize executed correctly.";
		cout << "\nCoordinates of global minimum: ( ";
		for (int i=0; i<spacedim; i++) cout << results[i] << " ";
		cout << ")   Function at global minimum=" << results[spacedim];
	} else {
		cout << "\nERROR in psominimize!";
	}

	cout << endl << endl;

}


