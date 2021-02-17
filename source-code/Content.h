#pragma once

#include "ofMain.h"

#include "Scroll.h"
#include "TweetRoll.h"

	// This handles all information to the right of the sidebar. Storing the top value of the information. Being a parent class to the Scroll class and TweetRoll Class. Drawing the Result title and also the status message.

class Content : public ofBaseApp {
public:
	void setup();
	void update(std::vector<Tweet>& tweets);
	void draw(std::vector<Tweet>& tweets, std::string statusMessage);
	void mouseScrolled(int x, int y, float scrollX, float scrollY);
	void mouseDragged(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	Scroll scroll;
	TweetRoll tweetRoll;

	int left;
	float top;
	int contentHeight;
	bool noScroll;
	bool localSearchQueryUpdated;

	ofTrueTypeFont titleResult;
	ofTrueTypeFont statusText;
};

