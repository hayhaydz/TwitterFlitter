#pragma once

#include "ofMain.h"
#include "ofxTwitter.h"
#include "ofxDatGui.h"
#include <sstream>
#include <iomanip>
#include <ctime>

#include "enum.h"
#include "ofxDatGuiCustomFontSize.h"
#include "SearchQuery.h"

	// This class handles everything to do with the left of the application. The sidebar on the left and it's necessary functions.

class Sidebar: public ofBaseApp {
public:
	void setup();
	void update(my_enums::Locations *location, SearchQuery* searchQuery, bool *searchQueryUpdated);
	void draw();
	void onButtonEvent(ofxDatGuiButtonEvent e);
	void onTextInputEvent(ofxDatGuiTextInputEvent e);
	void onDropdownEvent(ofxDatGuiDropdownEvent e);
	void handleEnter();
	void GUIChanges();

	ofxDatGui* gui;

	my_enums::Locations* localLocation;
	std::string localLocationStr;
	//std::string* localSearchQuery;
	SearchQuery* localSearchQuery;
	bool* localSearchQueryUpdated;
	
	
	ofColor activeBtnColor;
	ofColor inactiveBtnColor;
	ofColor enterBColor;
	ofColor enterHoverBColor;
	ofColor warningColor;
	bool enterButtonSet;
	bool showWarning;

	std::vector<std::string> dateSelection;
	std::array<std::time_t, 7> dateSelectionNew;
};

