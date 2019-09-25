# Genetic_Algorithm_Mars_Lander
 A genetic algorithm approach to solve the mars lander problem
 
 using vs2017 and openframeworks

Installing:
-The project uses visual studio 2017 and the latest version of openframeworks
-It uses only the 'ofxGui' addon in openframeworks.
-The files I've written are in OFGeneticAlgorithm/OFGeneticAlgorithm/src/
-The project will not run out the box, as it requires openframeworks and it maybe easiest to create a new opeframeworks project (with the ofxGui addon) and add the files in "OFGeneticAlgorithm/OFGeneticAlgorithm/src/" to the solution.

Running:
-If you manage to get the program running, it will iterate a number of times showing a graphical display of the process it takes to find a path.
-The yellow dot is the 'bestDot' and represents the path it decides is currently the best.
-After it's finished it will output thrust values and angles of the best path in the format of cout << angle << " " << thrust << endl; to mirror what was meant to output to the online platform.
