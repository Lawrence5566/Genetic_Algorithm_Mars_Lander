
#include "ofGraphics.h"
#include "dot.h"

//class Dot 

Dot::Dot() {
	pos.set(457, 780-702); //initiate in lander starting point
	vel.set(0, 0);
	acc.set(0, 0);

	goal = vector<ofVec2f>{ofVec2f(760,741), ofVec2f(980,741)}; //find some way to pass this in properly later(also altered the values to get more central onto lz)
}

void Dot::show() {
	if (isBest) { //show the champion to see how population is progressing
		ofSetColor(255, 223, 0);
		ofDrawCircle(pos, 5.0f);	
	}
	else {
		ofSetColor(255, 0, 0);
		ofDrawCircle(pos, 3.0f);
	}
}

void Dot::move() {
	//gravity should be a heavy driver.
	//the forces in 'directions' should all be to counteract that
	//instead of applying them as a forward force (in the direction of the force),
	//we should be applying the trust forces in the opposite direction (just like the landers thrusters)

	std::vector<thrustRot> *directions = brain.getDirections();
	int size = directions->size();
	if (size > brain.getStep()) { //if there are steps left to take


		thrustRot curr = (*directions)[brain.getStep()];
		//convert angle to unit vector
		ofVec2f v1(cos(curr.rot), sin(curr.rot));

		//flip vector for proper thrust direction when applying
		v1 = v1.rotate(180);

		//set acceleration to be unit vector * thrust
		acc = v1 * curr.thrust;

		//take into account of gravity (90* in this sim) - 3.711
		ofVec2f gravity(cos(PI / 2), sin(PI / 2)); //unit vector for gravity
		acc = acc + (gravity * 3.711);

		brain.setStep(brain.getStep() + 1); //increament step
		
	}
	else { //ran out of directions to follow
		dead = true; 
	}

	vel = vel + acc;
	
	pos = pos + vel; 
}

void Dot::update() {
	if (!dead && !reachedGoal) {

		move();
		if (pos.x < 2 || pos.y < 2 || pos.x > 1280 - 2 || pos.y > 780 - 2) {
			dead = true;
		}
		else if (distanceToGoal(goal) < 10) { //if touching goal (take into account of speed somewhere too?)
			reachedGoal = true;
		}
	}
}

float Dot::distanceToGoal(vector<ofVec2f> goal) {
	float ydist = abs(goal[0].y - pos.y);
	float xdist = abs(goal[0].x + (goal[1].x - goal[0].x)/2 - pos.x); //distance to center

	float closestX;

	//check which point along the lz it's closest too
	if (pos.x < goal[0].x) {
		closestX = goal[0].x;
	}
	else if (pos.x > goal[0].x && pos.x < goal[1].x) {
		closestX = pos.x;
	}
	else {
		closestX = goal[1].x;
	}

	return ofDist(pos.x, pos.y, closestX, goal[0].y);
}

void Dot::calculateFitness(vector<ofVec2f> goal) {
	//encourage dots that make it there with the least speed && with less steps?
	

	if (reachedGoal) {
		/*if (isBest) {
			cout << vel.length() << endl;
		}
		*/
		//encourage dots that make it to the goal with the lowest final speed
		fitness = 1.0f / 16.0f + 10000.0f / (vel.length() * vel.length());

		//encourage more dots that get there with a landing angle closest to 0?
		//int angle = (*brain.getDirections())[brain.getStep()].rot;
		//fitness = 1.0f / 16.0f + 10000.0f /  abs(angle * angle);

		//fitness = 1.0f/16.0f + 10000.0f / (brain.getStep() * brain.getStep()); //old fitness calculation (just looking at ones that make it there in least steps)
	}
	else { //give them score dependant on distance to goal
		float dist = distanceToGoal(goal);
		fitness = 1.0 / (dist * dist);
	}

}

Dot Dot::getOffspring() {
	Dot child = Dot();
	child.brain = brain.clone(); //make child brain exactly the same as parents
	return child;
}

