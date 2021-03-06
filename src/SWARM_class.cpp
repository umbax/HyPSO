/*
 * SWARM_class.cpp
 *
 *  Created on: Aug 30, 2016
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
#include <stdlib.h>     /* srand, rand */
#include <ctime>	 // to work with variables of type time_t and random number generator "srandom"
#include "matrix_operations.h"
#include "regeneration_strategies.h"

// SWARM class constructor
void Swarm::Swarm(int npart, int spdim, int niter)    //(RunParameters* pr, ProblemDefinition* pb)
{
	spacedim=spdim;
	nparticles=npart;
	niterations=niter;

	pop = zeros(spacedim, nparticles);		// matrix spacedim x nparticles
	vel = zeros(spacedim, nparticles);
	yValues = zeros(nparticles);			// vector nparticles x 1

}


// SWARM class destructor
void Swarm::~Swarm(void)
{
	// free memory of dynamically allocated variables!
	// pop
	// delete content
	for (int np=0;np<nparticles;np++) {
		delete pop[np];
		delete vel[np];
	}
	// delete container
	delete[] pop;
	delete[] vel;

}


void Swarm::Initialise(int method)
{

}


void Swarm::Fly(void)
{

}



