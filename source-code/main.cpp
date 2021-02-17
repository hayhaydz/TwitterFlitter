#include "ofApp.h"

int main() {
    ofSetupOpenGL(1440, 1024, OF_WINDOW);
    return ofRunApp(std::make_shared<ofApp>());
}
