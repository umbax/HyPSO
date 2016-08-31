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

	// check model ------------------------
	double x[2] = {1.0, 1.0};
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
	// check model ------------------------


	// regenerate_on_boundary nD ------------------------
	cout << "\nTest regenerate_on_boundary (nD)";
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
	// regenerate_on_boundary nD ------------------------


	cout << "\n\n\nTOTAL ERRORS: " << nerrors << endl;
}

