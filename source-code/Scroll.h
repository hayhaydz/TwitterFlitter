#pragma once

#include "ofMain.h"
#include "ofxEasing.h"

// This class handles everything to do with the scrolling behaviour of the application. The manipulation of the top value passed in by content means that drawn information can be moved both up and down depending on the actions of this class.

class Scroll : public ofBaseApp {
public:
	void setup();
	void update(int cHeight, bool noScrl, float &t);
	void draw();
	void mouseScrolled(int x, int y, float scrollX, float scrollY, float &t);
	void mouseDragged(int x, int y, int button, float &t);
	void mouseReleased(int x, int y, int button);
	void toTop();

	int velocity;
	int speed;
	int contentHeight;
	bool noScroll;

	//int initTime;
	//float currentWindowPosition;
	//float newTop;
	bool isScrolling;
	//double windowPositionDurationRatio;
	//std::string scrollingDirection;
	//std::string oldScrollingDirection;

	//scrollbar properties
	int windowHeight;
	int trackHeight;
	double windowContentRatio;
	int gripHeight;
	int minimalGripHeight;
	int windowScrollAreaHeight;
	float windowPosition;
	float oldWindowPosition;
	float newWindowPosition;
	double windowPositionRatio;
	int trackScrollAreaHeight;
	double gripPositionOnTrack;
	double gripPositionOnTrackTemp;
	double oldGripPositionOnTrack;
	double newGripPositionOnTrack;
	int mousePositionDelta;
	int oldMousePosition;
	double gripPositionRatio;
	bool isMouseDown;
};

