#pragma once
#include "ofVec2f.h"
#include "ofMath.h"

using namespace std;

//struct for thrust and rotations
struct thrustRot {
	float rot;
	int thrust;
};

//each lander has a brain with details of its path, as it moves it steps through the path
class Brain {
	int size;
	int step = 0;
	vector<thrustRot> *directions;
	void randomize();

public:
	Brain(int s);
	~Brain();
	vector<thrustRot>* getDirections() { return directions; }
	int getStep() { return step; }
	void setStep(int value) { step = value; }
	Brain clone();
	void mutate();
	void generateRandomThrustRot(int index);


};