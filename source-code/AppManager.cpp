#include "AppManager.h"

void AppManager::setup() {
    // This variable is used to declare which location the user is currently in. Enum shared across two classes.
    location = &loc;
    *location = my_enums::Locations::SEARCH;
    // This one stores all necessary data related to the query that the user is current performing.
    searchQuery = &sQ;
    // This boolean helps notify the AppManager class that a search needs to be performed.
    searchQueryUpdated = &sQU;
    *searchQueryUpdated = false;
    // This stores how many tweets have currently been recieved by the Twitter API.
    tweetCount = 0;
    // Used to know when to stop the Twitter API from running. Fail safe as well as using a maximum poll count.
    tweetStop = false;
    // Knowing what message to display depending on if the user has just started the application.
    firstSetup = true;
    // Storing if the application is currently loading tweets.
    isLoading = false;
    // Storing what month the tweet was posted in.
    tweetMonth = "";
    // The text that is shown just below the result title if no tweets are being drawn.
    statusMessage = "";

    // All necessary fonts used for drawing tweets. These are stored in AppManager as pointers in order to load them once on the applications setup. This increases app performance.
    nameFontPtr = &nameFont;
    usernameFontPtr = &usernameFont;
    textFontPtr = &textFont;
    statFontPtr = &statFont;
    labelFontPtr = &labelFont;
    detailsFontPtr = &detailsFont;

    nameFontPtr->load("fonts/Roboto/Roboto-Bold.ttf", 28, true, true);
    nameFontPtr->setLineHeight(33);
    usernameFontPtr->load("fonts/Roboto/Roboto-Light.ttf", 16, true, true);
    usernameFontPtr->setLineHeight(19);
    textFontPtr->load("fonts/Roboto/Roboto-Regular.ttf", 18, true, true);
    textFontPtr->setLineHeight(30);
    statFontPtr->load("fonts/Roboto/Roboto-Bold.ttf", 28, true, true);
    statFontPtr->setLineHeight(33);
    labelFontPtr->load("fonts/Roboto/Roboto-Regular.ttf", 14, true, true);
    labelFontPtr->setLineHeight(16);
    detailsFontPtr->load("fonts/Roboto/Roboto-Regular.ttf", 12, true, true);
    detailsFontPtr->setLineHeight(14);

    // Setting the background to a colour of white and the framerate to sixty frames per second.
    ofBackground(255);
    ofSetFrameRate(60);

    // ofxTwitter setup
    client.registerSearchEvents(this);
    client.setCredentialsFromFile("credentials.json");
    client.setPollingInterval(6000);
    client.setMaximumPollingCount(15);

    // Setup child classes.
    sidebar.setup();
    content.setup();
}

void AppManager::update() {
    // Updating and passing through pointers to AppManager variables for the sidebar to change if necessary.
    sidebar.update(location, searchQuery, searchQueryUpdated);

    if (*searchQueryUpdated) {
        content.localSearchQueryUpdated = true;
        isLoading = true;
        // Clearing the prior stored array of tweets.
        tweets.clear();
        ofxTwitter::SearchQuery query("");
        std::cout << "Search query has been updated... Start searching..." << std::endl;
        // Deciding how the ofxTwitter variable will be interacted with depending on the location of the user.
        if (*location == my_enums::Locations::SEARCH) {
            query.setQuery(searchQuery->query);
        } else if (*location == my_enums::Locations::LOCATION) {
            query.setGeoCode(std::stod(searchQuery->lat), std::stod(searchQuery->lon), 50, ofxTwitter::SearchQuery::UNITS_KILOMETERS);
        } else if (*location == my_enums::Locations::DATE) {
            // Breaking up the passed date into it's individual parts of year, month and day.
            std::stringstream ss(searchQuery->date);
            std::array<int, 3> results;
            int count = 0;
            while (ss.good()) {
                std::string substr;
                getline(ss, substr, '/');
                results[count] = std::stoi(substr);
                count++;
            }
            query.setQuery(searchQuery->query);
            query.setUntil(results[2], results[1], results[0] + 1);
        } else if (*location == my_enums::Locations::HASHTAG) {
            query.setQuery("#" + searchQuery->query);
        } else if (*location == my_enums::Locations::USER) {
            query.setQuery("@" + searchQuery->query);
        } else if (*location == my_enums::Locations::DONALDTRUMP) {
            query.setQuery("tiemvksmwofnslsonmcas");
        } else if (*location == my_enums::Locations::BATHSPAUNIVERSITY) {
            query.setQuery(searchQuery->query);
            query.setGeoCode(51.381052, -2.359023, 10, ofxTwitter::SearchQuery::UNITS_MILES);
        }

        // Calling the search of the built query.
        query.setLanguage("en");
        client.search(query);
        *searchQueryUpdated = false;
        tweetCount = 0;
    }
    // Fail safe to stop tweets and change booleans.
    if (tweetStop) {
        client.stop();
        tweetStop = false;
        isLoading = false;
    }

    // Calculating the message that will be displayed.
    if (tweets.size() > 1 || isLoading) {
        firstSetup = false;
    }

    if (firstSetup) {
        statusMessage = "Tweet results will display here...";
    } else {
        statusMessage = "No results found...";
    }

    if (isLoading) {
        statusMessage = "Loading...";
    }

    content.update(tweets);
    if (!*searchQueryUpdated) {
        content.localSearchQueryUpdated = false;
    }
}

void AppManager::draw() {
    sidebar.draw();
    content.draw(tweets, statusMessage);
}

void AppManager::mouseScrolled(int x, int y, float scrollX, float scrollY) {
    content.mouseScrolled(x,y,scrollX,scrollY);
}

void AppManager::mouseDragged(int x, int y, int button) {
    content.mouseDragged(x, y, button);
}

void AppManager::mouseReleased(int x, int y, int button) {
    content.mouseReleased(x, y, button);
}

//This function is called everytime the a new tweet is recieved
void AppManager::onStatus(const ofxTwitter::Status& status) {
    // Handling what to do when tweet vector exceeds 15 tweets. This is necessary for when new tweets are searched for and received.
    if (tweets.size() >= 16) {
        tweets.clear();
        tweetCount = 0;
    }
    tweetCount++;
    if (tweetCount < 15) {
        // Assigning tweet data to the tweets class.
        tweet.name = status.user().name();
        tweet.username = "@" + status.user().screenName();
        tweet.text = status.text();
        tweet.retweets = status.retweetCount();
        tweet.quoteTweets = status.quoteCount();
        if (tweet.quoteTweets == -1) {
            tweet.quoteTweets = 0;
        }
        tweet.likes = status.favoriteCount();
        tweet.timestamp = to_string(status.createdAt().hour()) + ":";
        if (status.createdAt().minute() < 10) {
            tweet.timestamp = tweet.timestamp + "0";
        }
        tweet.timestamp = tweet.timestamp + to_string(status.createdAt().minute()) + " ";
        tweet.timestamp = tweet.timestamp + to_string(status.createdAt().hourAMPM()) + " ";
        // Calculating the month in text form based on the number that is returned.
        switch (status.createdAt().month()) {
            case 1:
                tweetMonth = "Jan";
                break;
            case 2:
                tweetMonth = "Feb";
                break;
            case 3:
                tweetMonth = "Mar";
                break;
            case 4:
                tweetMonth = "Apr";
                break;
            case 5:
                tweetMonth = "May";
                break;
            case 6:
                tweetMonth = "Jun";
                break;
            case 7:
                tweetMonth = "Jul";
                break;
            case 8:
                tweetMonth = "Aug";
                break;
            case 9:
                tweetMonth = "Sep";
                break;
            case 10:
                tweetMonth = "Oct";
                break;
            case 11:
                tweetMonth = "Nov";
                break;
            case 12:
                tweetMonth = "Dec";
                break;
        }
        tweet.timestamp = tweet.timestamp + tweetMonth + " ";
        tweet.timestamp = tweet.timestamp + to_string(status.createdAt().dayOfYear()) + ", " + to_string(status.createdAt().year());
        tweet.device = status.source();
        // Cleaning up the device property by removing all data between the HTML tags.
        // https://stackoverflow.com/questions/37645029/delete-text-between-two-characters
        if (tweet.device.length() > 1) {
            for (int i = 0; i < 2; i++) {
                auto first = tweet.device.find("<");
                auto last = tweet.device.find(">", first);
                tweet.device.erase(first, last - first + 1);
            }
        }
        // Calling the setup for the tweet and then pushing it to the vector.
        tweet.setup(nameFontPtr, usernameFontPtr, textFontPtr, statFontPtr, labelFontPtr, detailsFontPtr);
        tweets.push_back(tweet);

        std::cout << "Username: " << tweet.username << std::endl;
        std::cout << "Display Name: " << tweet.name << endl;
        std::cout << "Tweet: " << tweet.text << endl;
        std::cout << "Retweets: " << tweet.retweets << std::endl;
        std::cout << "Quote Tweets: " << tweet.quoteTweets << std::endl;
        std::cout << "Likes: " << tweet.likes << std::endl;
        std::cout << "Timestamp: " << tweet.timestamp << std::endl;
        std::cout << "Device: " << tweet.device << std::endl;
        std::cout << "\n -----------------------------\n" << endl;
    }
    else {
        tweetStop = true;
    }
}

void AppManager::onError(const ofxTwitter::Error& error) {
    std::cout << "Error: " << error.code() << " " << error.message();
}

void AppManager::onException(const std::exception& notice) {
    std::cout << "Exception: " << notice.what();
}

void AppManager::onMessage(const ofJson& json) {
    // This is the raw message json and is ignored here.
    //std::cout << json << std::endl;
    // Checking whether the tweets returned were less than one and if so stopping loading.
    if (json["statuses"].size() < 1) {
        isLoading = false;
    }
}