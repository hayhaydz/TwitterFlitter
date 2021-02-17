#include "Sidebar.h"

void Sidebar::setup() {
    // String used to store the location of where the user currently is.
    localLocationStr = "gibberish";
    // Colour variable for the active colour of a button.
    activeBtnColor.r = 255;
    activeBtnColor.g = 0;
    activeBtnColor.b = 0;
    // Colour variable for the inactive colour of a button.
    inactiveBtnColor.r = 255;
    inactiveBtnColor.g = 255;
    inactiveBtnColor.b = 0;
    // Colour variable for the enter buttons background colour.
    enterBColor.r = 19;
    enterBColor.g = 173;
    enterBColor.b = 22;
    // Colour variable for the enter buttons background colour when hovered over.
    enterHoverBColor.r = 8;
    enterHoverBColor.g = 115;
    enterHoverBColor.b = 10;
    // Colour variable for the warning message.
    warningColor.r = 255;
    warningColor.g = 0;
    warningColor.b = 0;
    // Boolean for the first setting of it's values and others.
    enterButtonSet = false;
    // Boolean for displaying or not displaying the warning message.
    showWarning = false;

    // Filling out an array with the last seven days dates.
    for (int i = 0; i < dateSelectionNew.size(); i++) {
        std::time_t now = time(NULL);
        if (i != 0) {
            now = dateSelectionNew[i-1] - (24 * 60 * 60);
        }
        dateSelectionNew[i] = now;
    }
    
    // Taking the array and filling another one with the dates converted into strings.
    for (int j = 0; j < dateSelectionNew.size(); j++) {
        std::tm tm = *std::localtime(&dateSelectionNew[j]);
        std::stringstream ss;
        ss << std::put_time(&tm, "%d/%m/%Y");
        dateSelection.push_back(ss.str());
    }

    // Gui setup
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    gui->setTheme(new ofxDatGuiCustomFontSize());
    gui->addLabel(localLocationStr)->setName("TitleLabel");
    gui->addBreak()->setHeight(1.0f);

    // Menu items
    gui->addButton("Search")->setName("SearchBtn");
    gui->addButton("Location")->setName("LocationBtn");
    gui->addButton("Date")->setName("DateBtn");
    gui->addButton("Hashtag")->setName("HashtagBtn");
    gui->addButton("User")->setName("UserBtn");
    gui->addButton("Donald Trump")->setName("DonaldTrumpBtn");
    gui->addButton("Bath Spa University")->setName("BathSpaUniversityBtn");
    gui->addBreak()->setHeight(1.0f);
    gui->addLabel("Parameters");

    // Possible input types
    gui->addTextInput("Query", "value")->setName("SearchQueryInpt");
    gui->addTextInput("Lat", "value")->setName("LocationLatInpt");
    gui->addTextInput("Lon", "value")->setName("LocationLonInpt");
    gui->getTextInput("LocationLatInpt")->setVisible(false);
    gui->getTextInput("LocationLonInpt")->setVisible(false);
    gui->getTextInput("LocationLatInpt")->setInputType(ofxDatGuiInputType::NUMERIC);
    gui->getTextInput("LocationLonInpt")->setInputType(ofxDatGuiInputType::NUMERIC);
    gui->addDropdown("Date", dateSelection)->setName("DateDropdown");
    gui->addTextInput("Query", "value")->setName("DateInpt");
    gui->getDropdown("DateDropdown")->setVisible(false);
    gui->getTextInput("DateInpt")->setVisible(false);
    gui->addTextInput("#", "value")->setName("HashtagInpt");
    gui->getTextInput("HashtagInpt")->setVisible(false);
    gui->addTextInput("@", "value")->setName("UserInpt");
    gui->getTextInput("UserInpt")->setVisible(false);

    // Enter search button
    gui->addBreak()->setHeight(1.0f);
    gui->addButton("ENTER")->setName("EnterBtn");

    // Warning
    gui->addFooter()->setLabel("Error try again");
    gui->getFooter()->setLabelColor(warningColor);
    gui->getFooter()->setVisible(false);

    // Event listeners
    gui->onButtonEvent(this, &Sidebar::onButtonEvent);
    gui->onTextInputEvent(this, &Sidebar::onTextInputEvent);
    gui->onDropdownEvent(this, &Sidebar::onDropdownEvent);
}

void Sidebar::update(my_enums::Locations *location, SearchQuery* searchQuery, bool *searchQueryUpdated) {
    // Assigning local variables passed values.
    localLocation = location;
    localSearchQuery = searchQuery;
    localSearchQueryUpdated = searchQueryUpdated;
    
    // Boolean that will only run on the first update that is called.
    if (!enterButtonSet) {
        GUIChanges();
        gui->getButton("EnterBtn")->setBackgroundColor(enterBColor);
        gui->getButton("EnterBtn")->setBackgroundColorOnMouseOver(enterHoverBColor);
        gui->getButton("EnterBtn")->setStripeVisible(false);
        gui->getButton("EnterBtn")->setLabelAlignment(ofxDatGuiAlignment::CENTER);
        enterButtonSet = true;
    }
}

void Sidebar::draw() {
    ofSetColor(26, 26, 26);
    ofDrawRectangle(0, 0, 270, ofGetHeight());
}

// Function that will listen and handle any button clicks.
void Sidebar::onButtonEvent(ofxDatGuiButtonEvent e) {
    // Deciding what to do based on the button that is clicked.
    if (e.target->is("SearchBtn")) {
        *localLocation = my_enums::Locations::SEARCH;
    }
    else if (e.target->is("LocationBtn")) {
        *localLocation = my_enums::Locations::LOCATION;
    }
    else if (e.target->is("DateBtn")) {
        *localLocation = my_enums::Locations::DATE;
    }
    else if (e.target->is("HashtagBtn")) {
        *localLocation = my_enums::Locations::HASHTAG;
    }
    else if (e.target->is("UserBtn")) {
        *localLocation = my_enums::Locations::USER;
    }
    else if (e.target->is("DonaldTrumpBtn")) {
        *localLocation = my_enums::Locations::DONALDTRUMP;
    }
    else if (e.target->is("BathSpaUniversityBtn")) {
        *localLocation = my_enums::Locations::BATHSPAUNIVERSITY;
    }
    else if (e.target->is("EnterBtn")) {
        handleEnter();
    }

    GUIChanges();
}

// Listening to text input changes.
void Sidebar::onTextInputEvent(ofxDatGuiTextInputEvent e) {
    std::cout << "Text input value has been set." << std::endl;
}

// Listening to dropdown changes.
void Sidebar::onDropdownEvent(ofxDatGuiDropdownEvent e) {
    std::cout << "Dropdown input value has been set." << std::endl;
}

void Sidebar::handleEnter() {
    // Resetting warning boolean.
    showWarning = false;

    // Determining what calculations need to be done depending on the location of the user.
    if (*localLocation == my_enums::Locations::SEARCH) {
        std::string input = gui->getTextInput("SearchQueryInpt")->getText();
        // Validating the users input.
        // Checking the input is not blank or greater than 150 characters long.
        if (input == "" || input.length() > 150 || std::find_if(input.begin(), input.end(), isspace) != input.end() && std::find_if(input.begin(), input.end(), isalpha) == input.end()) {
            showWarning = true;
        } else {
            localSearchQuery->query = gui->getTextInput("SearchQueryInpt")->getText();
        }
    } else if (*localLocation == my_enums::Locations::LOCATION) {
        // Checking that the lat and lon values are not equal to their placeholder values of "value". Validation is not necessary for location because inputs are set to only register number inputs.
        if (gui->getTextInput("LocationLatInpt")->getText() != "value" && gui->getTextInput("LocationLonInpt")->getText() != "value") {
            localSearchQuery->lat = gui->getTextInput("LocationLatInpt")->getText();
            localSearchQuery->lon = gui->getTextInput("LocationLonInpt")->getText();
        } else {
            showWarning = true;
        }
    } else if (*localLocation == my_enums::Locations::DATE) {
        std::string input = gui->getTextInput("DateInpt")->getText();
        // Checking that the input of the date location is not blank or greater than 150 characters.
        if (input == "" || input.length() > 150 || std::find_if(input.begin(), input.end(), isspace) != input.end() && std::find_if(input.begin(), input.end(), isalpha) == input.end()) {
            showWarning = true;
        } else {
            localSearchQuery->date = gui->getDropdown("DateDropdown")->getSelected()->getName();
            localSearchQuery->query = gui->getTextInput("DateInpt")->getText();
        }
    } else if (*localLocation == my_enums::Locations::HASHTAG) {
        std::string input = gui->getTextInput("HashtagInpt")->getText();
        // Checking if the first value of the input is a hashtag. Catching if a user misinterprets the use of the input and thinks they need to add their own additional hashtag.
        if (input[0] == '#') {
            input.erase(0, 1);
        }

        // Checks that the user does not enter an input with whitespace in, the input is not blank and not longer than 150 characters.
        if (std::find_if(input.begin(), input.end(), isspace) != input.end() || input == "" || input.length() > 150) {
            showWarning = true;
        }
        else {
            localSearchQuery->query = gui->getTextInput("HashtagInpt")->getText();
        }

    } else if (*localLocation == my_enums::Locations::USER) {
        std::string input = gui->getTextInput("UserInpt")->getText();
        // The same as hashtag except checking with and at symbol instead.
        if (input[0] == '@') {
            input.erase(0, 1);
        }

        if (std::find_if(input.begin(), input.end(), isspace) != input.end() || input == "" || input.length() > 150) {
            showWarning = true;
        }
        else {
            localSearchQuery->query = gui->getTextInput("UserInpt")->getText();
        }
    } else if (*localLocation == my_enums::Locations::DONALDTRUMP) {
        localSearchQuery->query = "Donald Trump";
    } else if (*localLocation == my_enums::Locations::BATHSPAUNIVERSITY) {
        localSearchQuery->query = "Bath Spa University";
    }

    // If there is not a warning to show or error in validation then allow the search to be executed.
    if (!showWarning) {
        *localSearchQueryUpdated = true;
    }
}

void Sidebar::GUIChanges() {
    // Configuring button properties depending on the current location of the user.
    // Changing stripe colours and setting inputs visible or not visible.

    if (*localLocation != my_enums::Locations::SEARCH) {
        gui->getButton("SearchBtn")->setStripeColor(inactiveBtnColor);

        if (gui->getTextInput("SearchQueryInpt")->getVisible()) {
            gui->getTextInput("SearchQueryInpt")->setVisible(false);
        }
    }
    if (*localLocation != my_enums::Locations::LOCATION) {
        gui->getButton("LocationBtn")->setStripeColor(inactiveBtnColor);

        if (gui->getTextInput("LocationLatInpt")->getVisible()) {
            gui->getTextInput("LocationLatInpt")->setVisible(false);
        }
        if (gui->getTextInput("LocationLonInpt")->getVisible()) {
            gui->getTextInput("LocationLonInpt")->setVisible(false);
        }
    }
    if (*localLocation != my_enums::Locations::DATE) {
        gui->getButton("DateBtn")->setStripeColor(inactiveBtnColor);

        if (gui->getDropdown("DateDropdown")->getVisible()) {
            gui->getDropdown("DateDropdown")->setVisible(false);
        }
        if (gui->getTextInput("DateInpt")->getVisible()) {
            gui->getTextInput("DateInpt")->setVisible(false);
        }
    }
    if (*localLocation != my_enums::Locations::HASHTAG) {
        gui->getButton("HashtagBtn")->setStripeColor(inactiveBtnColor);

        if (gui->getTextInput("HashtagInpt")->getVisible()) {
            gui->getTextInput("HashtagInpt")->setVisible(false);
        }
    }
    if (*localLocation != my_enums::Locations::USER) {
        gui->getButton("UserBtn")->setStripeColor(inactiveBtnColor);

        if (gui->getTextInput("UserInpt")->getVisible()) {
            gui->getTextInput("UserInpt")->setVisible(false);
        }
    }
    if (*localLocation != my_enums::Locations::DONALDTRUMP) {
        gui->getButton("DonaldTrumpBtn")->setStripeColor(inactiveBtnColor);
    }
    if (*localLocation != my_enums::Locations::BATHSPAUNIVERSITY) {
        gui->getButton("BathSpaUniversityBtn")->setStripeColor(inactiveBtnColor);
    }

    // Does the same as above except this is for setting them if they need to be active. Above was for inactive setting.
    switch (*localLocation) {
        case my_enums::Locations::SEARCH:
            localLocationStr = "Search";
            gui->getButton("SearchBtn")->setStripeColor(activeBtnColor);
            if (!gui->getTextInput("SearchQueryInpt")->getVisible()) {
                gui->getTextInput("SearchQueryInpt")->setVisible(true);
            }
            break;
        case my_enums::Locations::LOCATION:
            localLocationStr = "Location";
            gui->getButton("LocationBtn")->setStripeColor(activeBtnColor);
            if (!gui->getTextInput("LocationLatInpt")->getVisible()) {
                gui->getTextInput("LocationLatInpt")->setVisible(true);
            }
            if (!gui->getTextInput("LocationLonInpt")->getVisible()) {
                gui->getTextInput("LocationLonInpt")->setVisible(true);
            }
            break;
        case my_enums::Locations::DATE:
            localLocationStr = "Date";
            gui->getButton("DateBtn")->setStripeColor(activeBtnColor);
            if (!gui->getDropdown("DateDropdown")->getVisible()) {
                gui->getDropdown("DateDropdown")->setVisible(true);
            }
            if (!gui->getTextInput("DateInpt")->getVisible()) {
                gui->getTextInput("DateInpt")->setVisible(true);
            }
            break;
        case my_enums::Locations::HASHTAG:
            localLocationStr = "Hashtag";
            gui->getButton("HashtagBtn")->setStripeColor(activeBtnColor);
            if (!gui->getTextInput("HashtagInpt")->getVisible()) {
                gui->getTextInput("HashtagInpt")->setVisible(true);
            }
            break;
        case my_enums::Locations::USER:
            localLocationStr = "User";
            gui->getButton("UserBtn")->setStripeColor(activeBtnColor);
            if (!gui->getTextInput("UserInpt")->getVisible()) {
                gui->getTextInput("UserInpt")->setVisible(true);
            }
            break;
        case my_enums::Locations::DONALDTRUMP:
            localLocationStr = "Donald Trump";
            gui->getButton("DonaldTrumpBtn")->setStripeColor(activeBtnColor);
            break;
        case my_enums::Locations::BATHSPAUNIVERSITY:
            localLocationStr = "Bath Spa University";
            gui->getButton("BathSpaUniversityBtn")->setStripeColor(activeBtnColor);
            break;
    }

    // Setting the label at the top of the sidebar to display the current location of the user.
    if (gui->getLabel("TitleLabel")->getLabel() != localLocationStr) {
        gui->getLabel("TitleLabel")->setLabel(localLocationStr);
    }

    // If there is a warning to show showing the warning message.
    if (showWarning) {
        if (!gui->getFooter()->getVisible()) {
            gui->getFooter()->setVisible(true);
        }
    } else {
        if (gui->getFooter()->getVisible()) {
            gui->getFooter()->setVisible(false);
        }
    }
}