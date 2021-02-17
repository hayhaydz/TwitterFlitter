#pragma once

#include "ofMain.h"

// This class stores all necessary data related to the searching of Twitter data. Often only the query variable will be used but on occasion such as the location method needs the lat and lon variable.

class SearchQuery : public ofBaseApp{
public:
	std::string query;
	std::string date;
	std::string lat;
	std::string lon;
};