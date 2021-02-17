#pragma once

#include "ofMain.h"

#include "Tweet.h"

	// This class handles the storage and output of the tweets vector.

class TweetRoll : public ofBaseApp {
public:
	void setup();
	void update(float top, int left, std::vector<Tweet>& tweets);
	void draw(std::vector<Tweet>& tweets);

	Tweet tweet;

	float localTop;
	//std::vector<Tweet> localTweets;
	int tweetCount;
	int tweetTotalHeight;
	int tweetHeight;
	int tweetWidth;
};

