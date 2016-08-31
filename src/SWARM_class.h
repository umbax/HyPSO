/*
 * SWARM_class.h
 *
 *  Created on: Aug 31, 2016
 *      Author: umba
 */

#ifndef SWARM_CLASS_H_
#define SWARM_CLASS_H_


class SWARM {

	public:

    // SWARM constructor
	Swarm(int, int);

	// Population destructor
    ~Swarm(void);


    void Initialise(int);

    void Fly(void);


};


#endif /* SWARM_CLASS_H_ */
