#pragma once

#include "ofxDatGui.h"

// This class is used to customise the appearance of the sidebar. Changing mainly the font size values, as well as also fixing the padded break height due to it breaking when changing the font size.

class ofxDatGuiCustomFontSize : public ofxDatGuiTheme {
public:
    ofxDatGuiCustomFontSize() {
        font.size = 12;
        font.file = "fonts/Roboto/Roboto-Medium.ttf";
        font.ptr = ofxSmartFont::add(font.file, font.size);
        layout.breakHeight = 50.0f;
        init();
    }
};