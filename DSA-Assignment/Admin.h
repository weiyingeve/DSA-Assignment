#pragma once
#include <string>
#include "Dictionary.h"
#include "DoublyLinkedList.h"
#include "Movie.h"
#include "Actor.h"
using namespace std;

class Admin
{
private:
	string name;
	int adminId;

	Dictionary<int, Movie> movies;
	Dictionary<int, Actor> actors;
	DoublyLinkedList<Movie> movieList;
	DoublyLinkedList<Actor> actorList;
public:
	//Constructor
	Admin(const string name, const int adminId);

	//Deconstructor
	~Admin();

	//Purpose: Retrieve the username of the admin.
	//Precondition: None.
	//Postcondition: Returns the username of the admin.
	string getName() const;

	//Purpose: Retrieve the id of the admin.
	//Precondition: None.
	//Postcondition: Returns the admin id.
	int getAdminId() const;

	//Purpose: Add a new actor to the dictionary
	//Precondition: Actor must not exist already
	//Postcondition: Adds actor to dictionary
	void addActor(const Actor actor);

	//Purpose: Add a new movie to the dictionary
	//Precondition: Movie must not exist already
	//Postcondition: Adds movie to dictionary
	void addMovie(const Movie movie);

	//Purpose: Add/link actor to a movie
	//Precondition: Movie exists, Actor exists
	//Postcondition: Actor is added to an existing movie
	void addActorToMovie(const int& actorId, const int& movieId);

	//Purpose: Update movie/actor details
	//Precondition: Movie and actor exists 
	//Postcondition:Movie/Actor details are updated
	void updateDetails(const string& type, const int& key, const string& newValue);
};

