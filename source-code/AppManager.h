#pragma once

#include "ofMain.h"
#include "ofxTwitter.h"
#include "ofxTrueTypeFontUC.h"

#include "enum.h"
#include "Sidebar.h"
#include "Content.h"
#include "SearchQuery.h"

	//This class is the root parent of all subsequent classes. It handles backend interaction with the Twitter APIand hands this returned data off to its child classes.
	//Storage of certain variables are used here as pointers to then be accessed by child classes.This way variables can be passed between classes without becoming mutated in any way, this is because one variable is always being accessed from memory.

class AppManager: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void mouseScrolled(int x, int y, float scrollX, float scrollY);
	void mouseDragged(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void onStatus(const ofxTwitter::Status& status);
	void onError(const ofxTwitter::Error& error);
	void onException(const std::exception& exception);
	void onMessage(const ofJson& json);

	ofxTwitter::SearchClient client;

	Sidebar sidebar;
	Content content;
	Tweet tweet;

	my_enums::Locations* location;
	my_enums::Locations loc;
	SearchQuery* searchQuery;
	SearchQuery sQ;

	//std::string* searchQuery;
	//std::string sQ;
	bool *searchQueryUpdated;
	bool sQU;
	std::vector<Tweet> tweets;

	int tweetCount;
	bool tweetStop;
	bool firstSetup;
	bool isLoading;
	std::string tweetMonth;
	std::string statusMessage;

	ofxTrueTypeFontUC* nameFontPtr;
	ofxTrueTypeFontUC nameFont;
	ofxTrueTypeFontUC* usernameFontPtr;
	ofxTrueTypeFontUC usernameFont;
	ofxTrueTypeFontUC* textFontPtr;
	ofxTrueTypeFontUC textFont;
	ofxTrueTypeFontUC* statFontPtr;
	ofxTrueTypeFontUC statFont;
	ofxTrueTypeFontUC* labelFontPtr;
	ofxTrueTypeFontUC labelFont;
	ofxTrueTypeFontUC* detailsFontPtr;
	ofxTrueTypeFontUC detailsFont;
};

