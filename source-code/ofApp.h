#pragma once
#include "ofMain.h"
#include "AppManager.h"

class ofApp: public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void mouseScrolled(int x, int y, float scrollX, float scrollY);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    AppManager appManager;
};
