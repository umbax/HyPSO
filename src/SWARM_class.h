/*
 * SWARM_class.h
 *
 *  Created on: Aug 31, 2016
 *      Author: umba
 */

#ifndef SWARM_CLASS_H_
#define SWARM_CLASS_H_


class Swarm {

	public:

    // SWARM constructor
	Swarm(int, int);

	// Population destructor
    ~Swarm(void);

    // variables
    double MAX_VALUE = 1000000.0;
    // for the future -> double* Particle;	// array of Particle classes
    int spacedim;
    int nparticles;		// number of particles
    int niterations;		// number of iterations (generations)

    double** pop;		// matrix of particles' positions - matrix (spacedim x nparticles)
    double** vel;		// matrix of particles' velocities - matrix (spacedim x nparticles)
    double* yValues;	// objective function value associated to a particle - array (1xnparticles)



    // functions
    void Initialise(int);
    void Fly(void);





};


#endif /* SWARM_CLASS_H_ */
