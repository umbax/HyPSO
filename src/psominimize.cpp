/*
 * psominimize.cpp *
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
#include <stdlib.h>     /* srand, rand */
#include <ctime>	 // to work with variables of type time_t and random number generator "srandom"
#include "matrix_operations.h"
#include "regeneration_strategies.h"


/*
function to perform Particle Swarm Optimisation (minimisation of the given objective function)
Inputs:
- p_objfun     	pointer to objective function whose minima have to be found
- spacedim		number of independent variables (space dimension)
- swarmcentre 	centre of the initial swarm or of the design space (array)
- swarmspan   	radius of the sphere in which the particles are generated
- nparticles  	number of particles
- nsteps      	number of generations
- bounds      	array with lower and upper bounds for each variable (spacedim x 2)
- results		array where results are saved (spacedim+1)
Outputs assigned to array passed by reference:
- zIncumb  position of the global optimal point (minimum)
- yIncumb  value of the objective function at the global minimum point found zIncumb
- NOT YET: function_output_Incumb value of the metamodel (NOT the objective function) at zIncumb
- NOT YET: constraints_output_Incumb  array containing the values of the output constraints at the found optimum
*/
int psominimize(double (*p_objfun)(double*, int), int spacedim, double* swarmcentre, double* swarmspan, int nparticles, int niterations, double** bounds, double* results)
{
	// check input
	cout << "\npsominimize" << endl;
	cout << "spacedim = " << spacedim << endl;
	cout << "swarmcentre: ";
	for (int i=0; i<spacedim; i++) {
		cout << swarmcentre[i] << ", ";
	}
	cout << endl;
	cout << "swarmspan: ";
	for (int i=0; i<spacedim; i++) {
			cout << swarmspan[i] << ", ";
		}
	cout << endl;
	cout << "nparticles = " << nparticles << endl;
	cout << "niterations = " << niterations << endl;
	for (int i=0; i<spacedim; i++) {
		cout << "Bounds of variable " << i << ": " << "(" << bounds[i][0] << ", " << bounds[i][1] << ")" << endl;
	}


	// random value generator
	int seed = 1;
	if (seed<0) {
		// if seed = -1 use random seed (time)
	    time_t *tp = NULL; // seed the random value generator
		srand((unsigned int) time (tp));    //to be used normally
		seed = time(tp); // attention! two runs that starts with the same seed are identical!
	    cout << "\n\nRandom value generator : seed =-1 : seed randomly generated = " << seed << endl;
	} else {
		// if seed >0 use the value given in input file
	    srand(seed);
	    cout << "\n\n Random value generator : used seed = " << seed << endl;
	}


	// list of variables (all the pointers are dynamically allocated, so remember to free memory!)
	double MAX_VALUE = 1000000.0;
	double** pop;		// matrix of particles' positions - matrix (spacedim x nparticles)
	double** vel;		// matrix of particles' velocities - matrix (spacedim x nparticles)
	double* yValues;	// objective function value associated to a particle - array (1xnparticles)

	double** zLocal;	// archive storing the position of particles personal best  - matrix (spacedim x nparticles)
	double* yLocal;		// best objective values obtained by each particle (particle/personal bests) - array (1 x nparticles)
	double* zIncumb;	// archive storing position of the particle that corresponds to the global best value of objective function
	double yIncumb;		// global best objective value - scalar

	double* function_output_Local; // value of the metamodel at the local (particle) minimum of the objective function in the design space
	double function_output_Incumb; // value of the metamodel at the global minimum (best among particles) of the objective function in the design space

	double* constraints_output_Local; // array of scalars for now - values of constraints at particle best position - matrix (nparticles x n_constraints=1)
	double constraints_output_Incumb; // scalar for now - values of constraints at global best position - array (1 x n_constraints)


	double* thisZ=zeros(spacedim);	// coordinates of current particle, dynamically initialised to a vector of zeros
	double** p_particle=new double*[spacedim]; // array of addresses of particle coordinates (used to modify/correct pop[][])

	// PSO engine tuning parameters
	double wCurr = 0.75;   // inertia weight: regulates the trade off between global and local exploration
	// see dynamic version of wCurr in CSC2011 paper...
	double wLocal = 0.15;  // coefficient of trust in the single particle
	double wGlob = 0.15;   // coefficient of trust in the swarm or global trend

	double r1=0; //random float value
	double r2=0; //random float value
	int v=0;
	double g=0.0;

	int ok=0;
	// --------------------------------------------------------------------



	// ------------------ INITIALISATION --------------------------
	// yValues is an array storing the values of the function whose minima are sought corresponding to the particles
	// create and initialise yValues
	yValues = zeros(nparticles);

	// particles' position INITIALISATION ------------
	// pop is a matrix of dimensions space_dimension x n_particles : each column contains the coordinates of a single particle
	// create pop
	pop = zeros(spacedim, nparticles);
	// randomly initialise pop
	for (int particle=0; particle<nparticles; particle++) {
		for (int i=0; i<spacedim; i++) {
			v = rand() % 200 + 1; // random integer between 1 and 200
			g = (double(v)-100.0)/100.0; // random real number between -0.99 and 1.00
			pop[i][particle] = swarmspan[i]*g + swarmcentre[i];
		}

		////// IMPORTANT! Check that the initial swarm is inside the design space and regenerate points in case
		// necessary as swarmCentre and swarmSpan are not determined taking into account the input design space bounds...
		for (int i=0; i<spacedim; i++) {
			p_particle[i] = &(pop[i][particle]);
		}
		ok = regenerate_on_boundary(p_particle, spacedim, bounds);
	}


	// particles' velocity INITIALISATION ------------
	// it's the first set of velocities randomly generated...
    // vel is a matrix of the same dimensions of pop : each column represents a single particle velocity
    // velocity - random in [-swarmSpan,swarmSpan]
	// create vel
	vel = zeros(spacedim, nparticles);
	// initialise vel (FASTER IF IT IS DONE INSIDE THE CYCLE USED TO INITIALISE POP!!!)
	for (int j=0; j<nparticles; j++) {
		for (int i=0; i<spacedim; i++) {
			int v = rand() % 200 + 1; // random integer between 1 and 200
			double g = (double(v)-100.0)/100.0; // random real number between -0.99 and 1.00
			vel[i][j] = swarmspan[i]*g;
		}
	}

	// initialise best score so far in the swarm - global or incumbent
    yIncumb = MAX_VALUE;       			// initial value of the objective function (univariate function)
    zIncumb=zeros(spacedim);   			// initial position of the global minimum in the design space
    function_output_Incumb = MAX_VALUE;  // initial value of the metamodel at the global minimum in the design space
    constraints_output_Incumb = MAX_VALUE;   // scalar for now - it will be an array 1 x n_output_constraints

    // initialise local best score - considering the position of the single particle so far only
    yLocal = zeros(nparticles);
    for (int j=0; j<nparticles; j++) yLocal[j]=MAX_VALUE;
    zLocal = zeros(spacedim, nparticles);
    function_output_Local = zeros(nparticles);
    for (int j=0; j<nparticles; j++) function_output_Local[j]=MAX_VALUE;
    constraints_output_Local = zeros(nparticles); // values of constraints - single scalar for now
    // -------------------------------------------------------------------

	// --------- INITIAL FITNESS EVALUATION -----------------------------------
    // cout << "iteration = 0";
    double out = 0.0;
    for (int particle=0; particle<nparticles; particle++) {
		// assign coordinates of current particle
    	for (int i=0; i<spacedim; i++) thisZ[i] = pop[i][particle];

        // evaluate objective function related to particle ii and assign value to yValues[ii]
        out = p_objfun(thisZ, spacedim);

        yValues[particle]=out;    // assign objective function value to particle container

        /* print particle position
        cout << "\n Particle=" << particle << " (";
        for (int i=0; i<spacedim; i++) cout << thisZ[i] << " ";
        cout << ")   yValues=" << out;
        */

        function_output_Local[particle] = 0.0;   // assign metamodel value corresponding to particle best to particle container (identical to objective function for now)
        constraints_output_Local[particle] = 0.0; 	// values of the output constraints (scalar and null for now)
        // save minimisation objective and position of each particle in their respective container
        yLocal[particle] = yValues[particle];  // if you want to save the history, turn yLocal into a matrix...
        for (int i=0; i<spacedim; i++) zLocal[i][particle] = thisZ[i];

        // update incumbents (or global best)
		if (yValues[particle]<yIncumb) {
			yIncumb = yValues[particle];
			for (int i=0; i<spacedim; i++) zIncumb[i] = thisZ[i];
			function_output_Incumb = function_output_Local[particle];
			constraints_output_Incumb = constraints_output_Local[particle];
		}

    }

    // average output in the initial swarm
	//lastPopAve = mean(yValues)



	// ------------------ SEARCH THROUGH GENERATIONS -----------------------
	// generations/iterations
    for (int gg=0; gg<niterations; gg++) {

    	cout << "\nIteration : " << gg;

        // particles
        for (int particle=0; particle<nparticles; particle++) {
        	//cout << "\nParticle : " << particle;

        	// GENERATE
        	r1 = double(rand() % 100)/100.0; // random float between 0.00 and 0.99
        	r2 = double(rand() % 100)/100.0; // random float between 0.00 and 0.99
        	for (int i=0; i<spacedim; i++) {
        		// update velocity
        		vel[i][particle] = wCurr*vel[i][particle] + wLocal*r1*(zLocal[i][particle]-pop[i][particle]) + wGlob*r2*(zIncumb[i]-pop[i][particle]);
        		// update position
        		pop[i][particle] = pop[i][particle] + vel[i][particle];
        	}

			//// CHECK that the particle is inside the design space (bounds) and regenerate a feasible point in case
        	// collect position
        	for (int i=0; i<spacedim; i++) {
        		p_particle[i] = &(pop[i][particle]);
        	}
            v = rand() % 100 + 1;     // v2 in the range 1 to 100
            if (v >= 50) {
                // regenerate on boundary
        		ok = regenerate_on_boundary(p_particle, spacedim, bounds);
            } else {
            	ok=regenerate_from_swarm_best(p_particle, spacedim, nparticles, bounds, zLocal);
            }
        	////


            // EVALUATE
        	for (int i=0; i<spacedim; i++) thisZ[i] = pop[i][particle];
        	out = p_objfun(thisZ, spacedim);
			yValues[particle]=out;



            // UPDATE
			// if performance improved, update single particle and global performance
			if (yValues[particle]<yLocal[particle]) {
				// update particle best objective value so far
				yLocal[particle] = yValues[particle];
				// update position
				for (int i=0; i<spacedim; i++) zLocal[i][particle]=pop[i][particle];
				// update metamodel value corresponding to particle best
				function_output_Local[particle] = 0.0;
				// update constraints value corresponding to particle best
			    constraints_output_Local[particle] = 0.0; // values of the output constraints;
				// update incumbent (or global best)
                if (yLocal[particle]<yIncumb) {
                	// update global best objective value so far
                	yIncumb = yLocal[particle];
                	// update position
                	for (int i=0; i<spacedim; i++) zIncumb[i]=zLocal[i][particle];
                	// update metamodel value corresponding to global best
                	function_output_Incumb = function_output_Local[particle];
					// update constraints value corresponding to particle best
					constraints_output_Incumb = constraints_output_Local[particle];
                }
			}

		// end particles loop ---------------------------------------
        }


        cout << "\nGlobal best so far: ( ";
        for (int i=0; i<spacedim; i++) cout << zIncumb[i] << " ";
        cout << ")   yIncumb=" << yIncumb;

		//wCurr = wCurr*.8   # dynamic reduction of global weight

        // average values and termination criterion
        //lastPopAve = mean(yValues)

        // STOP CRITERIA
        /*
        // if contour lines are targeted
        best_abs_residual = abs(function_output_Incumb - output_level)
        if best_abs_residual<= min_residual:
            // terminate the search as the found point error is below the desired threshold
            return zIncumb, yIncumb, function_output_Incumb, constraints_output_Incumb
		*/


    // end iterations (generations) loop ---------------------------------------
    }

    cout << "\n\nGlobal best: ( ";
    for (int i=0; i<spacedim; i++) cout << zIncumb[i] << " ";
    cout << ")   yIncumb=" << yIncumb;

	// free all dynamically allocated variables (pop, vel, yValues, ..)


	// store minimum position and corresponding function output in results
    for (int i=0; i<spacedim; i++) results[i]=zIncumb[i];
    results[spacedim]=yIncumb;

    // ADD LATER ON: function_output_Incumb, constraints_output_Incumb;

    return 1;

}

