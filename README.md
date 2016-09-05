# HyPSO
C++ Particle Swarm Optimisation code - finds the global minimum/a of a user-defined function (text expression)

Features:
- single minimisation objective (cost function)
- design space bounds defined by the user 
- no constraints on dependent variables implemented yet (work in progress to implement multiobjective optimisation)

Inputs (provided by the user):
- minimisation objective (cost function) (in Model.cpp)
- swarm parameters (no. of particles, iterations, position of the initial swarm)

Outputs:
- position of the global minimum (currently only displayed on screen) 
