#include "TweetRoll.h"

void TweetRoll::setup() {
	localTop = 0;
	tweetCount = 0;
	tweetTotalHeight = 0;
	tweetHeight = 400;
	tweetWidth = ofGetWidth() - 470;
}

void TweetRoll::update(float top, int left, std::vector<Tweet>& tweets) {
	tweetCount = 0;
	tweetTotalHeight = 0;
	localTop = top;
	//localTweets = tweets;
	// Calculate the total height of all the tweets and also update them.
	for (auto &tweet : tweets) {
		if (tweetCount >= 1) {
			tweetTotalHeight += tweetHeight + 50;
		}
		else {
			tweetTotalHeight = 100;
		}
		tweet.update(left + 100, top + tweetTotalHeight, tweetHeight, tweetWidth);
		tweetCount++;
	}
}

void TweetRoll::draw(std::vector<Tweet>& tweets) {
	// Call the draw function for all the tweets.
	for (auto &tweet : tweets) {
		tweet.draw();
	}
}