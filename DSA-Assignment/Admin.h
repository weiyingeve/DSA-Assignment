#pragma once
#include <string>
#include "Dictionary.h"
#include "DoublyLinkedList.h"
#include "Movie.h"
#include "Actor.h"
using namespace std;

typename ItemType;
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

	//Purpose: Update movie details
	//Precondition: Movie exists 
	//Postcondition:Movie details are updated
	void updateDetails(const string& type, const int& key, const Movie& newValue);

	//Purpose: Update actor details
	//Precondition: actor exists 
	//Postcondition:actor details are updated
	void updateDetails(const string& type, const int& key, const Actor& newValue);

	//Purpose: View list of reports made by users.
	//Precondition: none
	//Postcondition: Display all unresolved reports.
	void viewReports();

	//Purpose: Resolves a report made by a user.
	//Precondition: Report exists.
	//Postcondition: Updates details based on the report, updates status of report.
	void resolveIssue();
};

