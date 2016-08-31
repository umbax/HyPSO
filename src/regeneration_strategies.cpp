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



int regenerate_on_boundary(double* p_coord, int spacedim, double* bounds)
{
    /*
        1D VERSION
        Function that regenerate a point in case it is out of bounds.
        The unfeasible point is regenerated on the boundary.
        Inputs:
        - p_coord   point coordinates - pointer to scalar
        - spacedim  number of dimensions
        - bounds    array with lower and upper bounds (array 1 x 2)
        Output:
        - int    	1 if successful, -1 if not successful
    */

    //print "bounds"
    //print bounds
    //print shape(bounds)

    if (*p_coord > bounds[1])
    	// p_coord exceeds upper bound
    	*p_coord = bounds[1];
    if (*p_coord < bounds[0])
        // p_coord is below lower bound
    	*p_coord = bounds[0];

    return 1;
}





int regenerate_on_boundary(double** p_coord, int spacedim, double** bounds)
{
	/*
		nD VERSION
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


