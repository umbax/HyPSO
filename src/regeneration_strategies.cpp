/*
 * regeneration_strategies.cpp
 *
 *  Created on: Aug 25, 2016
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

#include <stdlib.h>     /* srand, rand */

int regenerate_on_boundary(double** p_coord, int spacedim, double** bounds)
{
	/*
		Function that regenerate a point in case it is out of bounds.
		The unfeasible point is regenerated on the boundary.
		Inputs:
		- p_coord    point coordinates - array spacedim x 1
		- spacedim  number of dimensions
		- bounds    array with lower and upper bounds (array spacedim x 2)
		Output:
		- p_coord    new feasible coordinates of the new point on the design space boundary
	*/

	// check current position - array
	for (int i=0; i<spacedim; i++) {
    	// check single coordinate is inside corresponding bounds
        if (*(p_coord[i]) > bounds[i][1])
        	// p_coord[i] exceeds upper bound
        	*(p_coord[i]) = bounds[i][1];
        if (*(p_coord[i]) < bounds[i][0])
			// p_coord is below lower bound
        	*(p_coord[i]) = bounds[i][0];

	}
    return 1;

}




int regenerate_from_swarm_best(double** p_coord, int spacedim, int nparticles, double** bounds, double** zLocal)
{

    /*
        Function that regenerate a particle in case it is out of bounds.
        The unfeasible coordinates of the particle are selected randomly
        from the coordinates of the swarm best particles (see Xu11).
        Inputs:
        - p_coord  	coordinates of the unfeasible particle - array spacedim x 1
        - bounds   	array with lower and upper bounds (array spacedim x 2)
        - zLocal   	matrix containing the coordinates of the personal best of each particle so far (n_var x Npop - 2D even for n_var =1))
        Output:
        - p_coord    new feasible coordinates of the new point on the design space boundary
        - number of particle chosen for the regeneration
    */

	int s_particle=0;

    // check current position - array
	for (int i=0; i<spacedim; i++) {
    	// check single coordinate is inside corresponding bounds
    	if ((*(p_coord[i]) < bounds[i][0]) || (*(p_coord[i]) > bounds[i][1])) {
        	// pick the corresponding coordinate of a randomly selected particle among best so far
            s_particle = rand() % nparticles; // random integer between 0 and nparticles-1
            // assign the new feasible coordinates
            for (int i=0; i<spacedim; i++) *(p_coord[i])=zLocal[i][s_particle];
    	}
    }


	return s_particle;

}
