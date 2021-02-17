#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

	// This class handles all functionality and calculations to do with the tweet cards. The drawing mainly, however distances between different elements and their sizes have to be determined.

class Tweet : public ofBaseApp {
public:
	void setup(ofxTrueTypeFontUC* nameFontPtr, ofxTrueTypeFontUC* usernameFontPtr, ofxTrueTypeFontUC* textFontPtr, ofxTrueTypeFontUC* statFontPtr, ofxTrueTypeFontUC* labelFontPtr, ofxTrueTypeFontUC* detailsFontPtr);
	void update(float x, int y, int h, int w);
	void draw();
	std::string wrapString(std::string s, int w);

	std::string name;
	std::string username;
	std::string text;
	int retweets;
	int quoteTweets;
	int likes;
	std::string timestamp;
	std::string device;

	int x;
	int y;
	int width;
	int height;
	int usernameY;
	int textY;
	int statAY;
	pair<int, int> labelA;
	pair<int, int> statB;
	pair<int, int> labelB;
	pair<int, int> statC;
	pair<int, int> labelC;
	std::string retweetPlural;
	std::string quoteTweetPlural;
	std::string likePlural;

	ofxTrueTypeFontUC* nameFont;
	ofxTrueTypeFontUC* usernameFont;
	ofxTrueTypeFontUC* textFont;
	ofxTrueTypeFontUC* statFont;
	ofxTrueTypeFontUC* labelFont;
	ofxTrueTypeFontUC* detailsFont;
};

