#pragma once
#include "Brain.h"
#include <chrono>

class Dot {
	ofVec2f pos;
	ofVec2f vel;
	ofVec2f acc; //in the ship, this is thrust power?
	
public:
	Brain brain{ 1000 };

	vector<ofVec2f> goal;
	bool dead = false;
	float fitness = 0;
	bool reachedGoal = false;
	bool isBest = false;

	Dot();
	void show();
	void move();
	void update();
	float distanceToGoal(vector<ofVec2f> goal);
	void calculateFitness(vector<ofVec2f> goal);
	Dot getOffspring();

};
