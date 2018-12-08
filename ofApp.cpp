#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofEnableDepthTest();
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->locations.clear();

	for (int i = 0; i < 100; i++) {

		glm::vec3 location = glm::vec3(
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * ofRandom(0.001, 0.0005)), 0, 1, -ofGetWidth() * 0.5, ofGetWidth() * 0.5),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * ofRandom(0.001, 0.0005)), 0, 1, -ofGetHeight() * 0.5, ofGetHeight() * 0.5),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * ofRandom(0.001, 0.0005)), 0, 1, -360, 360));
		this->locations.push_back(location);

		ofColor color;
		color.setHsb(ofRandom(255), 235, 255);
		this->colors.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	for (int i = 0; i < this->locations.size(); i++) {

		ofFill();
		ofSetColor(this->colors[i]);
		ofDrawSphere(this->locations[i], 10);
		for (int j = 0; j < this->locations.size(); j++) {

			if (i == j) {

				continue;
			}

			glm::vec3 distance = this->locations[i] - this->locations[j];
			float distance_lenght = glm::length(distance);

			if (distance_lenght < 100) {

				ofDrawSphere(this->locations[j] + glm::normalize(distance) * 20, 5);
				ofSetColor(this->colors[i] + this->colors[j]);
				ofDrawLine(this->locations[i] - glm::normalize(distance) * 20, this->locations[j] + glm::normalize(distance) * 20);
				ofSetColor(this->colors[i]);
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}