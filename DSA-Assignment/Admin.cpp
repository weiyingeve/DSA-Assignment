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
    if (movies.contains(movie.getMovieId())) {
        cout << "Movie already exists!" << endl;
        return;
    }
    movies.add(movie.getMovieId(), movie);
    movieList.add(movie);
    cout << "Movie " << movie.getTitle() << " added successfully." << endl;
}

//Purpose: Add/link actor to a movie
//Precondition: Movie exists, Actor exists
//Postcondition: Actor is added to an existing movie
void Admin::addActorToMovie(const int& actorId, const int& movieId) {
    if (!actors.contains(actorId)) {
        cout << "Actor does not exist!" << endl;
        return;
    }
    if (!movies.contains(movieId)) {
        cout << "Movie does not exist!" << endl;
        return;
    }
    Movie movie = movies.get(movieId);
    Actor actor = actors.get(actorId);
    movie.addActor(actor); 
    movies.add(movieId, movie);
    cout << "Actor " << actor.getName() << " added to movie " << movie.getTitle() << " successfully." << endl;
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