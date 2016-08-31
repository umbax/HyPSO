# Copyright 2016 Dr Umberto Armani
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Basic Makefile 
# all is the default target and is called when just makefile with
# no options is run.
all: hypso test_rig

hypso: ./src/main.o ./src/model.o ./src/psominimize.o ./src/matrix_operations.o regeneration_strategies.o
	g++ -o hypso ./src/main.o ./src/model.o ./src/psominimize.o ./src/matrix_operations.o ./src/regeneration_strategies.o
	
test_rig: ./src/test_rig.o ./src/main.o ./src/model.o ./src/psominimize.o ./src/matrix_operations.o
	g++ -o test_rig ./src/test_rig.o ./src/model.o ./src/psominimize.o ./src/matrix_operations.o ./src/regeneration_strategies.o

test_rig.o: ./src/test_rig.cpp
	g++ -c -g ./src/test_rig.cpp -o ./src/test_rig.o

main.o: ./src/main.cpp
	g++ -c -g ./src/main.cpp -o ./src/main.o
	
model.o: ./src/model.cpp 
	g++ -c -g ./src/model.cpp -o ./src/model.o
	
psominimize.o: ./src/psominimize.cpp 
	g++ -c -g ./src/psominimize.cpp -o ./src/psominimize.o

matrix_operations.o: ./src/matrix_operations.cpp
	g++ -c -g ./src/matrix_operations.cpp -o ./src/matrix_operations.o
	
regeneration_strategies.o: ./src/regeneration_strategies.cpp
	g++ -c -g ./src/regeneration_strategies.cpp -o ./src/regeneration_strategies.o
	
clean:
	rm hypso
	rm test_rig
	rm ./src/test_rig.o
	rm ./src/main.o
	rm ./src/model.o
	rm ./src/psominimize.o
	rm ./src/matrix_operations.o
	rm ./src/regeneration_strategies.o
	