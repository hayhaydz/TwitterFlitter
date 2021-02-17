#include "Tweet.h"

void Tweet::setup(ofxTrueTypeFontUC* nameFontPtr, ofxTrueTypeFontUC* usernameFontPtr, ofxTrueTypeFontUC* textFontPtr, ofxTrueTypeFontUC* statFontPtr, ofxTrueTypeFontUC* labelFontPtr, ofxTrueTypeFontUC* detailsFontPtr) {
	x = 0;
	y = 0;
	height = 0;
	width = 0;
	// Variable for storing their plural or no plural words.
	retweetPlural = "Retweets";
	quoteTweetPlural = "Quote Tweets";
	likePlural = "Likes";
	// Fonts that were loaded in AppManager are passed into the Tweet class on setup and stored in local variables.
	nameFont = nameFontPtr;
	usernameFont = usernameFontPtr;
	textFont = textFontPtr;
	statFont = statFontPtr;
	labelFont = labelFontPtr;
	detailsFont = detailsFontPtr;

	// Calculations necessary for the positions to be added on to the tweet cards x and y values.
	usernameY = 50 + nameFont->stringHeight(name);
	textY = 50 + nameFont->stringHeight(name) + usernameFont->stringHeight(username) + 25;
	statAY = (100 / 2) + statFont->stringHeight(to_string(retweets)) / 2 - 20;
	labelA.first = 20 + statFont->stringWidth(to_string(retweets)) + 10;
	labelA.second = (100 / 2) + statFont->stringHeight(to_string(retweets)) / 2 - 22;
	statB.first = 20 + statFont->stringWidth(to_string(retweets)) + 10 + labelFont->stringWidth(retweetPlural) + 25;
	statB.second = (100 / 2) + statFont->stringHeight(to_string(retweets)) / 2 - 20;
	labelB.first = 20 + statFont->stringWidth(to_string(retweets)) + 10 + labelFont->stringWidth(retweetPlural) + 25 + statFont->stringWidth(to_string(quoteTweets)) + 10;
	labelB.second = (100 / 2) + statFont->stringHeight(to_string(retweets)) / 2 - 22;
	statC.first = 20 + statFont->stringWidth(to_string(retweets)) + 10 + labelFont->stringWidth(retweetPlural) + 25 + statFont->stringWidth(to_string(quoteTweets)) + 10 + labelFont->stringWidth(quoteTweetPlural) + 25;
	statC.second = (100 / 2) + statFont->stringHeight(to_string(retweets)) / 2 - 20;
	labelC.first = 20 + statFont->stringWidth(to_string(retweets)) + 10 + labelFont->stringWidth(retweetPlural) + 25 + statFont->stringWidth(to_string(quoteTweets)) + 10 + labelFont->stringWidth(quoteTweetPlural) + 25 + statFont->stringWidth(to_string(likes)) + 10;
	labelC.second = (100 / 2) + statFont->stringHeight(to_string(retweets)) / 2 - 22;

	text = wrapString(text, (ofGetWidth() - 470) - 20);
}

void Tweet::update(float x, int y, int h, int w) {
	// Updating positon values.
	this->x = x;
	this->y = y;
	height = h;
	width = w;
}

void Tweet::draw() {
	// Determing if a tweet card has to be drawn depending if it is visible on the screen.
	if (y > 0 - height && y < ofGetHeight() - 25) {
		// Drawing the border rectangle at a slightly larger size.
		ofSetColor(26);
		ofDrawRectRounded(x, y, width + 6, height + 6, 20);
		// Drawing the background rectangle at a slightly smaller size.
		ofSetColor(239);
		ofDrawRectRounded(x + 3, y + 3, width, height, 20);
		// Drawing the rectangle strip covering the bottom of the Tweet cards.
		ofSetColor(26);
		ofDrawRectRounded(x + 3, y + (height - 100) + 3, 0, width, 100, 0, 0, 20, 20);
		// Drawing the tweet posters name.
		nameFont->drawString(name, x + 20, y + 50);
		// Drawing the tweet posters username.
		ofEnableAlphaBlending();
		ofSetColor(26, 26, 26, 85);
		usernameFont->drawString(username, x + 20, y + usernameY);
		ofDisableAlphaBlending();
		// Drawing the tweets text.
		ofSetColor(30);
		textFont->drawString(text, x + 20, y + textY);
		// Drawing the tweets retweets about.
		ofSetColor(12, 232, 151);
		statFont->drawString(to_string(retweets), x + 20, y + height - statAY);
		// Drawing the retweets label
		ofSetColor(239);
		if (retweets == 1) {
			retweetPlural = "Retweet";
		}
		labelFont->drawString(retweetPlural, x + labelA.first, y + height - labelA.second);
		// Drawing the quote tweets count.
		ofSetColor(12, 232, 151);
		statFont->drawString(to_string(quoteTweets), x + statB.first, y + height - statB.second);
		// Drawing the quote tweets label.
		ofSetColor(239);
		if (quoteTweets == 1) {
			quoteTweetPlural = "Quote Tweet";
		}
		labelFont->drawString(quoteTweetPlural, x + labelB.first, y + height - labelB.second);
		// Drawing the likes count.
		ofSetColor(12, 232, 151);
		statFont->drawString(to_string(likes), x + statC.first, y + height - statC.second);
		// Drawing the likes label.
		ofSetColor(239);
		if (likes == 1) {
			likePlural = "Like";
		}
		labelFont->drawString(likePlural, x + labelC.first, y + height - labelC.second);
		// Drawing the details line at the very bottom.
		ofSetColor(152);
		detailsFont->drawString(timestamp + " · " + device, x + 20, y + height - 20);
	}
}

std::string Tweet::wrapString(std::string s, int w) {
	std::string typeWrapped = "";
	std::string tempString = "";
	std::vector<std::string> words = ofSplitString(s, " ");

	// Breaking the string up into new lines when it exceeds the width that is passed through. Used for the tweet text.
	for (int i = 0; i < words.size(); i++) {
		std::string wrd = words[i];

		if (i > 0) {
			tempString += " ";
		}

		tempString += wrd;
		int stringWidth = textFont->stringWidth(tempString);

		if (stringWidth >= w) {
			typeWrapped += "\n";
			tempString = wrd;
		}
		else if (i > 0) {
			typeWrapped += " ";
		}
		typeWrapped += wrd;
	}

	return typeWrapped;
}