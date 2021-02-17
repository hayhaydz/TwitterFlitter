#include "ofApp.h"

void ofApp::setup() {
	appManager.setup();
}

void ofApp::update() {
	appManager.update();
}

void ofApp::draw() {
	ofClear(255);
	appManager.draw();
}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {
	appManager.mouseScrolled(x, y, scrollX, scrollY);
}

void ofApp::mouseDragged(int x, int y, int button) {
	appManager.mouseDragged(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button) {
	appManager.mouseReleased(x, y, button);
}