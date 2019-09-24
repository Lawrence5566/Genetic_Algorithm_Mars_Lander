#pragma once

#include "dot.h"

class Population {
	vector<Dot>* dots;
	float fitnessSum;
	int gen = 1; //the generation of dots 
	int bestDot;
	int bestSteps = 500;

public:
	Population(int size);
	void show();
	void update();
	void calculateFitness(vector<ofVec2f> goal);
	bool allDotsDead();
	void naturalSelection();
	void mutateOffspring();
	void calculateFitnessSum();
	Dot selectParent();
	void setBestDot();

	Dot returnBestDot();

};
