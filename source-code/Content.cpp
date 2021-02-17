#include "Content.h"

void Content::setup() {
	// Loading fonts and setting their sizes.
	titleResult.load("fonts/Roboto/Roboto-Black.ttf", 42);
	statusText.load("fonts/Roboto/Roboto-Medium.ttf", 16);
	// Distance needed to provide room for the sidebar.
	left = 270;
	// Value for the top of the screen. Also seen as Y.
	top = 0;
	// Boolean for storing whether the application should allow scrolling yet or not.
	noScroll = true;
	// A local boolean for knowing if the search query has been updated.
	localSearchQueryUpdated = false;

	// Setting up child classes.
	scroll.setup();
	tweetRoll.setup();
}

void Content::update(std::vector<Tweet>& tweets) {
	// Calculating the height of all tweets along with the space between them of around fifty pixels.
	if (tweets.size() > 1) {
		contentHeight = 100 + (450 * tweets.size());
		contentHeight = contentHeight;
		noScroll = false;
	}
	else {
		contentHeight = 0;
		noScroll = true;
	}
	// Resetting the scrolling position back to the start if a new search query has been performed.
	if (localSearchQueryUpdated) {
		top = 0;
		scroll.toTop();
	}

	// Updating child classes.
	scroll.update(contentHeight, noScroll, top);
	tweetRoll.update(top, left, tweets);
}

void Content::draw(std::vector<Tweet>& tweets, std::string statusMessage) {
	ofSetColor(239);
	ofDrawRectangle(left, 0, ofGetWidth()-left, ofGetHeight());
	ofSetColor(26);
	// Drawing the title result text.
	titleResult.drawString("Results", left + 100, top + 65);
	// Drawing the status message text if no tweets are in the vector.
	if (tweets.size() < 1) {
		ofSetColor(175);
		statusText.drawString(statusMessage, ofGetWidth() / 2 - statusText.stringWidth(statusMessage) / 2 + 100, top + 110);
	}

	scroll.draw();
	tweetRoll.draw(tweets);
}

void Content::mouseScrolled(int x, int y, float scrollX, float scrollY) {
	scroll.mouseScrolled(x,y,scrollX,scrollY, top);
}

void Content::mouseDragged(int x, int y, int button) {
	scroll.mouseDragged(x, y, button, top);
}

void Content::mouseReleased(int x, int y, int button) {
	scroll.mouseReleased(x, y, button);
}