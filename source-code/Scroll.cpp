#include "Scroll.h"

void Scroll::setup() {
	// This value is used to measure the increased distance of the pixels scrolled.
	velocity = 12;
	// This value stores the final calculated value of the distance to scroll.
	speed = 0;
	// Window calcualted maths.
	windowHeight = 0;
	trackHeight = 0;
	windowContentRatio = 0;
	windowScrollAreaHeight = 0;
	windowPosition = 0;
	oldWindowPosition = 0;
	newWindowPosition = 0;
	windowPositionRatio = 0;
	trackScrollAreaHeight = 0;
	// Grip calculated maths.
	gripHeight = 0;
	minimalGripHeight = 40;
	gripPositionOnTrack = 0;
	gripPositionOnTrackTemp = 0;
	oldGripPositionOnTrack = 0;
	newGripPositionOnTrack = 0;
	gripPositionRatio = 0;
	// Mouse calculated maths.
	mousePositionDelta = 0;
	oldMousePosition = 0;
	isMouseDown = false;

	//initTime = 0;
	//currentWindowPosition = 0;
	//newTop = 0;
	//isScrolling = false;
	//windowPositionDurationRatio = 0;
	//scrollingDirection = "down";
	//oldScrollingDirection = "down";
}

void Scroll::update(int cHeight, bool noScrl, float &t) {
	// Assigning local variables data. Local variables are used because their values need to be accessed in functions other than just this update.
	contentHeight = cHeight;
	noScroll = noScrl;

	if(contentHeight > 0) {
		// Resetting the velocity value if scrolling stops.
		if (!isScrolling) {
			velocity = 12;
		}
		//auto duration = 0.6f;
		//auto endTime = initTime + duration;
		//auto now = ofGetElapsedTimef();
		// http://csdgn.org/article/scrollbar
		// Calculating necessary maths for scrolling ratio.
		windowHeight = ofGetHeight();
		trackHeight = windowHeight;
		windowContentRatio = windowHeight / contentHeight;

		// Setting limits to the grips height both minimum and maximum.
		gripHeight = trackHeight * windowContentRatio;
		if (gripHeight < minimalGripHeight) {
			gripHeight = minimalGripHeight;
		}

		if (gripHeight > trackHeight) {
			gripHeight = trackHeight;
		}

		windowScrollAreaHeight = contentHeight - windowHeight;
		windowPositionRatio = windowPosition / windowScrollAreaHeight;
		trackScrollAreaHeight = trackHeight - gripHeight;
		gripPositionOnTrack = trackScrollAreaHeight * windowPositionRatio;
		t = -windowPosition;
		//gripPositionOnTrack = ofxeasing::map_clamp(now, initTime, endTime, oldGripPositionOnTrack, newGripPositionOnTrack, &ofxeasing::linear::easeInOut);
		//newTop = ofxeasing::map_clamp(now, initTime, endTime, currentWindowPosition, windowPosition, &ofxeasing::linear::easeInOut);
		//if (endTime < now) {
		//	isScrolling = false;
		//}
		//if (!isScrolling) {
		//	oldGripPositionOnTrack = gripPositionOnTrack;
		//}
		isScrolling = false;
	}
	else {
		gripHeight = ofGetHeight();
	}

}

void Scroll::draw() {
	ofSetColor(230);
	ofDrawRectangle(ofGetWidth() - 15, 0, 15, ofGetHeight());
	ofSetColor(26);
	ofDrawRectangle(ofGetWidth() - 15, gripPositionOnTrack, 15, gripHeight);
}

void Scroll::mouseScrolled(int x, int y, float scrollX, float scrollY, float &t) {
	if (contentHeight > 0) {
		if (x > 270) {
			//if (!isScrolling || scrollingDirection != oldScrollingDirection) {
			//	currentWindowPosition = windowPosition;
			//	oldScrollingDirection = scrollingDirection;
			//}
			//isScrolling = true;
			//initTime = ofGetElapsedTimef();
			isScrolling = true;
			// Slight scroll smoothing. Increases everytime user scrolls to maximum value.
			velocity *= 1.4;
			if (velocity > 32) {
				velocity = 32;
			}

			gripPositionOnTrackTemp = gripPositionOnTrack;
			// Maths for the speed that scrolling occurs. ScrollY variable changes based on how hard user scrolls.
			speed = scrollY * velocity;
			// Calculating the direction of scrolling.
			if (scrollY <= -1 && t >= -contentHeight && !noScroll) {
				gripPositionOnTrackTemp -= speed;
				if (gripPositionOnTrackTemp > trackScrollAreaHeight) {
					gripPositionOnTrackTemp = trackScrollAreaHeight;
				}
				//scrollingDirection = "down";
			}
			else if (scrollY >= 1 && t <= 0 && !noScroll) {
				gripPositionOnTrackTemp -= speed;
				if (gripPositionOnTrackTemp < 0) {
					gripPositionOnTrackTemp = 0;
				}
				//scrollingDirection = "up";
			}
		}

		// Calculating new window position based on grips location.
		gripPositionRatio = gripPositionOnTrackTemp / trackScrollAreaHeight;
		windowPosition = gripPositionRatio * windowScrollAreaHeight;
	}
}

void Scroll::mouseDragged(int x, int y, int button, float &t) {
	if (contentHeight > 0) {
		// Setting mouse down to true whilst the user is dragging and is within the bounds of the grips location.
		if (x > ofGetWidth() - 15 && y > gripPositionOnTrack && y < gripPositionOnTrack + gripHeight) {
			isMouseDown = true;
		}

		if (isMouseDown) {
			//if (!isScrolling) {
			//	currentWindowPosition = windowPosition;
			//}
			//isScrolling = true;
			//initTime = ofGetElapsedTimef();

			// Moving the grip based on the mouses delta position.
			oldMousePosition = gripPositionOnTrack;
			mousePositionDelta = y - oldMousePosition;
			oldMousePosition = y;

			gripPositionOnTrack += mousePositionDelta;

			if (gripPositionOnTrack < 0) {
				gripPositionOnTrack = 0;
			}
			if (gripPositionOnTrack > trackScrollAreaHeight) {
				gripPositionOnTrack = trackScrollAreaHeight;
			}

			// Updating window position after grip position changes.
			gripPositionRatio = gripPositionOnTrack / trackScrollAreaHeight;
			windowPosition = gripPositionRatio * windowScrollAreaHeight;
		}
	}
}

void Scroll::mouseReleased(int x, int y, int button) {
	// Updating necessary values after the user stops dragging the grip.
	isMouseDown = false;
	mousePositionDelta = 0;
	oldMousePosition = gripPositionOnTrack;
	//currentWindowPosition = windowPosition;
	newGripPositionOnTrack = gripPositionOnTrack;
	oldGripPositionOnTrack = gripPositionOnTrack;
}

void Scroll::toTop() {
	windowPosition = 0;
}