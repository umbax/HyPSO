# HyPSO
C++ Particle Swarm Optimisation code - finds the global minimum/a of a user-defined function (text expression)

Features:
- single minimisation objective (cost function)
- design space bounds defined by the user 


Inputs (provided by the user):
- minimisation objective (cost function) (in Model.cpp)
- swarm parameters (no. of particles, iterations, position of the initial swarm)


Outputs:
- position of the global minimum and corresponding value of the minimisation objective (cost function) 


FUTURE WORK:
- implementation of constraints on dependent variables (multiobjective optimisation, either using a weighted approach or a Pareto approach)
- implementation of a pre- and post-processing code to visualize results and swarm parameters (probably in Python with Matplotlib)
