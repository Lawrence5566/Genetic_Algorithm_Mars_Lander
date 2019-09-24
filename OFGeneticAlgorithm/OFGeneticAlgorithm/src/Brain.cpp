#include "Brain.h"

Brain::Brain(int s) {
	size = s;
	directions = new vector<thrustRot>(size);
	randomize();
}

Brain::~Brain() {//we need to delete directions but it's giving us read access violations
	//cout << "delete" << endl;
	//delete directions;
	//cout << "done deleteing" << endl;
}

void Brain::randomize() { //randomise each thrust and rotation step
	for (int i = 0; i < size; i++) {
		//clamp each angle within the range 90/-90 (since we dont wanna be pushing the landers upwards)
		//and thrust to 4 (since that's max on the program)

	
		if (i != 0) { //set random next step to be within 15* of the last rotation
			generateRandomThrustRot(i);
		}else { //if i = 0, this is the first value, so set manually:
			thrustRot randomThrustRot;

			randomThrustRot.rot = ofRandom(-PI/2 , PI/2 ) + (PI/2); //-90 to 90 , + 90* to account for origin of rotatons being in the east
			randomThrustRot.thrust = ofRandom(4); //0 to 4

			(*directions)[i] = randomThrustRot;
		}

		//convert angle to unit vector
		//ofVec2f v1(cos(randomAngle), sin(randomAngle));

		//(*directions)[i] = randomThrustRot;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------

Brain Brain::clone() { //clone brain and return new clone		///this might not clone properly? (not copying properly)
	Brain clone = Brain(directions->size());
	for (int i = 0; i < (int)directions->size(); i++) { //copy structs
		(*clone.getDirections())[i] = (*directions)[i];
	}
	return clone;
}

void Brain::mutate() {
	float mutationRate = 0.01f; //chance of a ThrustRot (direction) being overwritten by new one
	for (int i = 1; i < (int)directions->size(); i++) {
		float rand = ofRandom(1);
		if (rand < mutationRate) {
			generateRandomThrustRot(i);
		}

	}
}

void Brain::generateRandomThrustRot(int i) { //pass in index for directions
	//generate random thrustRot for a direction
	thrustRot randomThrustRot;

	randomThrustRot.rot = ofRandom((*directions)[i - 1].rot - (PI / 12), (*directions)[i - 1].rot + (PI / 12)); //+-15
	randomThrustRot.thrust = (int)ofRandom((*directions)[i - 1].thrust - 1, (*directions)[i - 1].thrust + 2); //+-1 (+2 as the top range is exclusive)

	//clamp values so they don't go over the thrust or rotation limit
	randomThrustRot.rot = CLAMP(randomThrustRot.rot, 0, PI); //-90 to 90 (taking into account of easten origin)
	randomThrustRot.thrust = CLAMP(randomThrustRot.thrust, 0, 4);

	(*directions)[i] = randomThrustRot;

}

