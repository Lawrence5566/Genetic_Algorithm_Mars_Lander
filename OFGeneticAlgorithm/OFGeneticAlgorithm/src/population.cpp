#include "population.h"

Population::Population(int s) {
	dots = new vector<Dot>(s);

}

void Population::show() {

	for (int i = 1; i < (int)dots->size(); i++) { //skip best dot  (no.1)		
		(*dots)[i].show();
	}

	(*dots)[0].show();
}

void Population::update() {

	for (int i = 0; i < (int)dots->size(); i++) {
		if ((*dots)[i].brain.getStep() > bestSteps) { //remove dots that go over best steps(that take too long)
			(*dots)[i].dead = true;
		}
		else {
			(*dots)[i].update();
		}
	}
}

void Population::calculateFitness(vector<ofVec2f> goal) {

	for (int i = 0; i < (int)dots->size(); i++) {
		(*dots)[i].calculateFitness(goal);
	}
}

bool Population::allDotsDead() {
	for (int i = 0; i < (int)dots->size(); i++) {
		if (!(*dots)[i].dead && !(*dots)[i].reachedGoal) {
			return false;
		}
	}
	return true;
	
}

//--------------------------------------------------------------------

void Population::naturalSelection() {
	int currSize = (int)dots->size();

	vector<Dot> *newDots = new vector<Dot>(currSize);
	setBestDot();
	calculateFitnessSum();

	(*newDots)[0] = (*dots)[bestDot].getOffspring();//put champion from last generation into new generation
	(*newDots)[0].isBest = true;
	for (int i = 1; i < currSize; i++) { //skip champion
		//select parent based on fitness
		Dot parent = selectParent();

		//get offspring from them
		(*newDots)[i] = parent.getOffspring();

	}

	//delete old dots
	delete dots;
	// assign to new dots
	dots = newDots;

	//delete pointer
	newDots = NULL;

	//increment generation
	gen++;

}

void Population::calculateFitnessSum() { 
	fitnessSum = 0;
	for (int i = 0; i < (int)dots->size(); i++) {
		fitnessSum += (*dots)[i].fitness;
	}
}

Dot Population::selectParent() {  //select parent based on most fit
	float rand = ofRandom(fitnessSum);

	float runningSum = 0;
	for (int i = 0; i < (int)dots->size(); i++) {
		runningSum += (*dots)[i].fitness;
		if (runningSum > rand) {
			return (*dots)[i];
		}
	
	}

	//should never reach here

}

//-------------------------------------------------------------------------------------

void Population::mutateOffspring() {

	for (int i = 1; i < (int)(*dots).size(); i++) { //skip champion
		(*dots)[i].brain.mutate();		//mutate brains
	}

}

void Population::setBestDot() {			//place champion into net generation without mutating it, so that population as a whole doesnt decrease in quality each step
	float max = 0;
	int maxIndex = 0;
	for (int i = 0; i < (int)dots->size(); i++) {
		if ((*dots)[i].fitness > max) {
			max = (*dots)[i].fitness;
			maxIndex = i;
		}
	}

	bestDot = maxIndex;

	if ((*dots)[bestDot].reachedGoal) {
		bestSteps = (*dots)[bestDot].brain.getStep();
	}

}

Dot Population::returnBestDot() {
	return (*dots)[0];
}






























