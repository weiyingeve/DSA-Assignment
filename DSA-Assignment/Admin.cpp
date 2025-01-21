#include "Admin.h"
#include <iostream>
using namespace std;

//Constructor
Admin::Admin(string name, int adminId)
	: name(name), adminId(adminId) {}

//Deconstructor
Admin::~Admin() {};

//Purpose: Retrieve the username of the user.
//Precondition: None.
//Postcondition: Returns the username of the user.
string Admin::getName() const 
{
	return name;
};

//Purpose: Retrieve the id of the user.
//Precondition: None.
//Postcondition: Returns the user id.
int Admin::getAdminId() const {
	return adminId;
};

//Purpose: Add a new actor to the dictionary
//Precondition: Actor must not exist already
//Postcondition: Adds actor to dictionary
void Admin::addActor(const Actor actor) {
    if (actors.contains(actor.getActorId())) {
        cout << "Actor already exists!" << endl;
        return;
    }
    actors.add(actor.getActorId(), actor);
    actorList.add(actor);
    cout << "Actor " << actor.getName() << " added successfully." << endl;
}

//Purpose: Add a new movie to the dictionary
//Precondition: Movie must not exist already
//Postcondition: Adds movie to dictionary
void Admin::addMovie(const Movie movie) {
	if (movies.contains(movieName)) {
		cout << "Movie already exists!" << endl;
		return;
	}
	movies.add(movieName, "Movie Details Placeholder");
	movieList.add(movieName);
	cout << "Movie " << movieName << " added successfully." << endl;
}

//Purpose: Add/link actor to a movie
//Precondition: Movie exists, Actor exists
//Postcondition: Actor is added to an existing movie
void Admin::addActorToMovie(const string& actorName, const string& movieName) {
    if (!actors.contains(actorName)) {
        cout << "Actor does not exist!" << endl;
        return;
    }
    if (!movies.contains(movieName)) {
        cout << "Movie does not exist!" << endl;
        return;
    }
    string currentActors = movies.get(movieName);
    currentActors += ", " + actorName;
    movies.add(movieName, currentActors);
    cout << "Actor " << actorName << " added to movie " << movieName << " successfully." << endl;
}

//Purpose: Update movie/actor details
//Precondition: Movie and actor exists 
//Postcondition:Movie/Actor details are updated
void Admin::updateDetails(const string& type, const string& key, const string& newValue) {
    if (type == "movie") {
        if (movies.contains(key)) {
            movies.add(key, newValue);
            cout << "Movie details updated successfully." << endl;
        }
        else {
            cout << "Movie does not exist." << endl;
        }
    }
    else if (type == "actor") {
        if (actors.contains(key)) {
            actors.add(key, newValue);
            cout << "Actor details updated successfully." << endl;
        }
        else {
            cout << "Actor does not exist." << endl;
        }
    }
    else {
        cout << "Invalid type. Use 'movie' or 'actor'." << endl;
    }
}