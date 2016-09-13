/*
 * test_rig.cpp
 *
 *  Created on: Aug 20, 2016
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
#include <cmath>

#include "model.h"
#include "psominimize.h"
#include "matrix_operations.h"
#include "regeneration_strategies.h"

int main ()
{
	int nerrors = 0;
	double f=0.0;
	double x[2];

	// check zeros ------------------------
	cout << "\n TEST zeros(3,2) : generate a 3x2 matrix filled with 0";
	int nr = 3;
	int nc = 2;
	double** M = zeros(nr,nc);
	for (int i=0; i<nr; i++) {
		cout << "\n";
		for (int j=0; j<nc; j++)
			cout << M[i][j] << " ";
	}
	cout << endl;


	cout << "\n TEST zeros(3) : generate a column vector 3x1 filled with 0";
	int d=3;
	double* v=zeros(d);
	for (int i=0; i<d; i++)
		cout << "\n" << v[i];
	cout << endl;
	// check zeros ------------------------


	// check 1D test functions : Salustowicz ------------------------
	x[0] = 0.0;
	x[1] = 1000000.0;  // only the first entry is considered
	f = Salustowicz(x, 1);
	cout << "\n\nSalustowicz function in 0 - must be 0";
	cout << "\nf=" << f << " = 0?";
	if (abs(f)<1.0E-14)
		cout << "\nOK";
	else {
		cout << "\nERROR!";
		nerrors++;
	}
	// end check 1D test functions ------------------------


	// check 2D test functions : Rosenbrock ------------------------
	x[0] = 1.0;
	x[1] = 1.0;
	f = Rosenbrock(x, 2);
	cout << "\n\nRosenbrock function in 1,1 - must be 0";
	cout << "\nf=" << f << " = 0?";
	if (abs(f)<1.0E-14)
		cout << "\nOK";
	else {
		cout << "\nERROR!";
		nerrors++;
	}

	x[0] = 0.0;
	x[1] = 1.0;
	f = Rosenbrock(x, 2);
	cout << "\n\nRosenbrock function in 0,1 - must be 100";
	cout << "\nf=" << f << " = 100?";
	if (abs(f-100)<1.0E-14)
		cout << "\nOK";
	else {
		cout << "\nERROR!";
		nerrors++;
	}
	cout << endl;
	// end check 2D test functions ------------------------


	// test regenerate_on_boundary 2D ------------------------
	cout << "\nTest regenerate_on_boundary (2D)";
	int spacedim=2;
	double thisZ[2] = {500.0, -100.0};
	double** p_particle=new double*[spacedim];
	for (int i=0; i<spacedim; i++) p_particle[i] = &(thisZ[i]);
	double** bounds=zeros(2,2); // rows corresponds to variable (1st row= 1st variable) - 1st column= lower bound - 2nd column= upper bound
	bounds[0][0] = -1.0;
	bounds[0][1] = 1,0;
	bounds[1][0] = -2.0;
	bounds[1][1] = 2.0;
	cout << "\nInitial particle coordinates: ( " << thisZ[0] << " , " << thisZ[1] << " )";
	cout << "\nBounds variable 0: [ " << bounds[0][0] << " , " << bounds[0][1] << " ]";
	cout << "\nBounds variable 1: [ " << bounds[1][0] << " , " << bounds[1][1] << " ]";
	int ok = regenerate_on_boundary(p_particle, spacedim, bounds);
	cout << "\nregenerate_on_boundary = " << ok;
	cout << "\nRegenerated particle coordinates: ( " << thisZ[0] << " , " << thisZ[1] << " )";
	if (abs(thisZ[0]-1)<1.0E-14)
		cout << "\nOK";
	else {
		cout << "\nERROR!";
		nerrors++;
	}
	if (abs(thisZ[1]+2)<1.0E-14)
		cout << "\nOK";
	else {
		cout << "\nERROR!";
		nerrors++;
	}
	cout << endl;
	// end test regenerate_on_boundary 2D ------------------------


	// test regenerate_from_swarm_best 2D -------------------
	cout << "\nTest regenerate_from_swarm_best (2D)";
	spacedim=2;
	int nparticles = 2;
	thisZ[0] = 500.0;
	thisZ[1] = -100.0;
	p_particle=new double*[spacedim];
	for (int i=0; i<spacedim; i++) p_particle[i] = &(thisZ[i]);
	bounds=zeros(2,2); // rows corresponds to variable (1st row= 1st variable) - 1st column= lower bound - 2nd column= upper bound
	bounds[0][0] = 0.0;
	bounds[0][1] = 10.0;
	bounds[1][0] = -50.0;
	bounds[1][1] = -30.0;
	// set zLocal, collection of particles coordinates within the bounds
	double** zLocal=zeros(spacedim,nparticles);   // 2 dimensions (=spacedim), 2 particles (=nparticles)
	zLocal[0][0] = 5.0;
	zLocal[1][0] = -40.0;
	zLocal[0][1] = 10.0;
	zLocal[1][1] = -50.0;
	// launch function
	cout << "\nInitial particle coordinates: ( " << thisZ[0] << " , " << thisZ[1] << " )";
	cout << "\nBounds variable 0: [ " << bounds[0][0] << " , " << bounds[0][1] << " ]";
	cout << "\nBounds variable 1: [ " << bounds[1][0] << " , " << bounds[1][1] << " ]";
	ok=regenerate_from_swarm_best(p_particle, spacedim, nparticles, bounds, zLocal);
	cout << "\nregenerate_from_swarm_best: particle selected = " << ok;
	cout << "\nzLocal selected particle to regenerate from: ( " << zLocal[0][ok] << " , " << zLocal[1][ok] << " )";
	cout << "\nRegenerated particle coordinates: ( " << *(p_particle[0]) << " , " << *(p_particle[1]) << " )";
	if (ok<0) {
		cout << "\nERROR! ok should be positive or 0!";
		nerrors++;
	} else {
		if (abs(zLocal[0][ok]-*(p_particle[0]))<1.0E-14)
			cout << "\nOK";
		else {
			cout << "\nERROR! First entry of coordinates are not equal!";
			nerrors++;
		}
		if (abs(zLocal[1][ok]-*(p_particle[1]))<1.0E-14)
			cout << "\nOK";
		else {
			cout << "\nERROR! Second entry f coordinates are not equal!";
			nerrors++;
		}
	}
	cout << endl;
	// end test regenerate_from_swarm_best 2D -------------------


	// test 1D PSO search: Salustowicz ---------------
	cout << "\n\nTest PSO search on Salustowicz (1D)";
	int out = .0;
	// inputs - so far only the version for a number of variable > 2 works!
	spacedim = 1;
	double swarmcentre[1] = {1.0};
	double swarmspan[1] = {5.0};
	nparticles = 100;
	int nsteps = 100;
	bounds=zeros(1,2); // rows corresponds to variable (1st row= 1st variable) - 1st column= lower bound - 2nd column= upper bound
	bounds[0][0] = 0.0;
	bounds[0][1] = 10.0;
	// results container
	double* results = zeros(spacedim+1);
	// get address of objective function
	double (*p_objfun)(double*, int);
	p_objfun = &Salustowicz;    // model contains the objective function to be minimised (user defined)
	// launch single PSO search for global minima (function for now)
	out = psominimize(p_objfun, spacedim, swarmcentre, swarmspan, nparticles, nsteps, bounds, results);
	cout << "\nout = " << out << endl;
	if (ok) {
		cout << "\nOK";
		cout << "\n\nCoordinates of global minimum: ( ";
		for (int i=0; i<spacedim; i++) cout << results[i] << " ";
		cout << ")   Function at global minimum=" << results[spacedim];
	} else {
		cout << "\nERROR!";
		nerrors++;
	}
	// end test 1D PSO search ------------


	cout << "\n\n\nTOTAL ERRORS: " << nerrors << endl;
}

