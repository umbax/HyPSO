/*
 * regeneration_strategies.h
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




#ifndef REGENERATION_STRATEGIES_H_
#define REGENERATION_STRATEGIES_H_

int regenerate_on_boundary(double**, int, double**);
int regenerate_from_swarm_best(double**, int, int, double**, double**);

#endif /* REGENERATION_STRATEGIES_H_ */
