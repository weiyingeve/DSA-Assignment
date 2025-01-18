#pragma once
#include <string>
#include "DoublyLinkedList.h"
#include "Dictionary.h"
using namespace std;
class User
{
private:
	string username;
	int userId;

	DoublyLinkedList favoriteMovies;
	DoublyLinkedList favoriteActors;
public:
	//Constructor
	User(const string username, const int userId);

	//deconstructor
	~User();

	//Purpose: Retrieve the username of the user.
	//Precondition: None.
	//Postcondition: Returns the username of the user.
	string getUsername() const;

	//Purpose: Retrieve the id of the user.
	//Precondition: None.
	//Postcondition: Returns the user id.
	int getUserId() const;

	//Purpose: Display (in ascending order of age) the actors with age between x and y (entered by user)
	//Precondition: x and y entered must be a valid number (y>x)
	//Postcondition: Actors displayed must be in ascending order
	void displayActorsByAgeRange(Dictionary& actorDict, int x, int y);

	//Purpose: Display movies made within the past 3 years 
	//Precondition: None
	//Postcondition: Movies displayed in ascending order of year
	void displayMoviesPast3Years(Dictionary& movieDict);

	//Purpose: Display all movies an actor starred in
	//Precondition: Actor must exist
	//Postcondition: Movies displayed must be in alphabetical order
	void displayMoviesByActor(Dictionary& actorDict, const string& actorName);
	
	//Purpose: Display actors in a movie
	//Precondition: Movie must exist
	//Postcondition: Actor displayed must be in alphebetical order
	void displayActorsByMovie(Dictionary& movieDict, const string& movieName);

	//Purpose: . Display a list of all actors that a particular actor knows.
	//Precondition: Actor must exist
	//Postcondition: 
	void displayActorsKnown(Dictionary& movieDict, const string& actorName);
};

