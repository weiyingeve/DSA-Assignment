#include "User.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime> 

using namespace std;

//Constructor
User::User(const string username, const int userId)
    : username(username), userId(userId) {}

//deconstructor
User::~User() {}

//Purpose: Retrieve the username of the user.
//Precondition: None.
//Postcondition: Returns the username of the user.
string User::getUsername() const {
    return username;
}

//Purpose: Retrieve the id of the user.
//Precondition: None.
//Postcondition: Returns the user id.
int User::getUserId() const {
    return userId;
}

//Purpose: Display (in ascending order of age) the actors with age between x and y (entered by user)
//Precondition: x and y entered must be a valid number (y>x)
//Postcondition: Actors displayed must be in ascending order
void User::displayActorsByAgeRange(Dictionary& actorDict, int x, int y) {
    if (x >= y) {
        cout << "Invalid age range: y must be greater than x." << endl;
    }

    cout << "Actors between ages " << x << " and " << y << ":" << endl;

    // Iterate through all potential keys in the dictionary
    for (char c = 'A'; c <= 'Z'; ++c) {  
        string key(1, c);

        if (actorDict.contains(key)) {
            int age = stoi(actorDict.get(key));
            if (age >= x && age <= y) {
                cout << "Name: " << key << ", Age: " << age << endl;
            }
        }
    }
}

//Purpose: Display movies made within the past 3 years 
//Precondition: None
//Postcondition: Movies displayed in ascending order of year
void User::displayMoviesPast3Years(Dictionary& movieDict) {
    int currentYear = 2025; 

    cout << "Movies released in the past 3 years:" << endl;

    for (char c = 'A'; c <= 'Z'; ++c) { 
        string key(1, c);

        if (movieDict.contains(key)) {
            int releaseYear = stoi(movieDict.get(key));
            if (currentYear - releaseYear <= 3) {
                cout << "Name: " << key << ", Year: " << releaseYear << endl;
            }
        }
    }
}

//Purpose: Display all movies an actor starred in
//Precondition: Actor must exist
//Postcondition: Movies displayed must be in alphabetical order
void User::displayMoviesByActor(Dictionary& actorDict, const string& actorName) {
    if (!actorDict.contains(actorName)) {
        cout << "Actor not found in the dictionary." << endl;
    }

    string movies = actorDict.get(actorName); 
    cout << "Movies starring " << actorName << ": " << movies << endl;
}

//Purpose: Display actors in a movie
//Precondition: Movie must exist
//Postcondition: Actor displayed must be in alphebetical order
void User::displayActorsByMovie(Dictionary& movieDict, const string& movieName) {
    if (!movieDict.contains(movieName)) {
        cout << "Movie not found in the dictionary." << endl;
    }

    string actors = movieDict.get(movieName);
    cout << "Actors in movie " << movieName << ": " << actors << endl;
}


//Purpose: . Display a list of all actors that a particular actor knows.
//Precondition: Actor must exist
//Postcondition: 
void User::displayActorsKnown(Dictionary& movieDict, const string& actorName) {
    vector<string> knownActors;

    for (char c = 'A'; c <= 'Z'; ++c) { 
        string key(1, c);

        if (movieDict.contains(key)) {
            string actors = movieDict.get(key);
            vector<string> actorList;

            size_t pos = 0;
            while ((pos = actors.find(',')) != string::npos) {
                actorList.push_back(actors.substr(0, pos));
                actors.erase(0, pos + 1);
            }
            actorList.push_back(actors); 

            if (find(actorList.begin(), actorList.end(), actorName) != actorList.end()) {
                for (const auto& actor : actorList) {
                    if (actor != actorName && find(knownActors.begin(), knownActors.end(), actor) == knownActors.end()) {
                        knownActors.push_back(actor);
                    }
                }
            }
        }
    }

    cout << "Actors known by " << actorName << ":" << endl;
    sort(knownActors.begin(), knownActors.end());
    for (const auto& actor : knownActors) {
        cout << actor << endl;
    }
}