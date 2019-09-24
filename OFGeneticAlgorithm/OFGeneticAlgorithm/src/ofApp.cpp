#include "ofApp.h"
#include "algorithm"

float normaliseToScreen(float n,float min, float max, float lower, float upper) {
	return (upper-lower) / (max-min) * (n - max) + upper;
}

vector<ofVec2f> findLandingPoints(vector<ofVec2f> points) {
	//finds the 2 connecting flat points for the landing zone
	for (int i = 0; i < (int)points.size() - 1; i++) { //check each point with the one in front
		if (points[i].y == points[i + 1].y) { //if they are on the same y
			return vector<ofVec2f>{points[i], points[i+1]};
		}
	}
	return vector<ofVec2f>{ofVec2f(0, 0)}; //return blank if no landing zone found
}

void ofApp::buildLand() {
	//zone is 7000 by 3000m
	//flat ground is 1000m at least
	//coordinates to draw land with:
	vector<ofVec2f> landPoints{
		ofVec2f(0 , 3000 - 100),
		ofVec2f(1000, 3000 - 500),
		ofVec2f(1500, 3000 - 1500),
		ofVec2f(3000, 3000 - 1000),
		ofVec2f(4000, 3000 - 150),
		ofVec2f(5500, 3000 - 150),
		ofVec2f(6999, 3000 - 800)
	};

	for (ofVec2f v : landPoints) {
		//normalise to our window
		int x = normaliseToScreen(v.x, 0.0f, 7000.0f, 0.0f, 1280.0f);
		int y = normaliseToScreen(v.y, 0.0f, 3000.0f, 0.0f, 780.0f);
		land.addVertex(x,y,0.0f);
	}

	lz = findLandingPoints(landPoints);

	for (int i = 0; i < (int)lz.size(); i++) { //prints landing zone position
		lz[i].x = normaliseToScreen(lz[i].x, 0.0f, 7000.0f, 0.0f, 1280.0f);
		lz[i].y = normaliseToScreen(lz[i].y, 0.0f, 3000.0f, 0.0f, 780.0f);
		//cout << lz[i].x << "," << lz[i].y << endl;
	}

}


//--------------------------------------------------------------
void ofApp::setup(){
	buildLand();
	test = new Population(300);


}

//--------------------------------------------------------------
void ofApp::update(){


}

//--------------------------------------------------------------
void ofApp::draw(){ 

	if (stop) { return; }


	//draw our land
	ofSetColor(255, 0, 0); //red
	land.draw();

	
	if (test->allDotsDead()) { 
		if (iterations == 7) {
			Dot bestDot = test->returnBestDot();
			int steps = bestDot.brain.getStep();
			for (int i = 0; i < steps; i++) {
				//mutliply by -1 to get proper thrust direction
				cout << "cout << " << (int)(((*bestDot.brain.getDirections())[i].rot * 180/PI) - 90) * -1 << "<< " << '"' << " "<< '"' << " <<" << (int)(*bestDot.brain.getDirections())[i].thrust << "<< endl;" << endl;
				//cout << "cout << " << (int)(((*bestDot.brain.getDirections())[i].rot * 180/PI) - 90) * -1 << "<< " << '"' << " "<< '"' << " <<" << (int)(*bestDot.brain.getDirections())[i].thrust << "<< endl;" << endl;
			}
			stop = true;
		}

		//genetic algorithm
		test->calculateFitness(lz);
		test->naturalSelection();
		test->mutateOffspring();
		iterations++;
	}
	else { //move population
		test->update(); //if any other dots alive, update and show them
		test->show();
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
