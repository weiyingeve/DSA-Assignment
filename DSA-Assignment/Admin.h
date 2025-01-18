#pragma once
#include <string>
#include "Dictionary.h"
#include "DoublyLinkedList.h"
using namespace std;

class Admin
{
private:
	string name;
	int adminId;

	Dictionary movies;
	Dictionary actors;
	DoublyLinkedList movieList;
	DoublyLinkedList actorList;
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
	void addActor(const string& actorName);

	//Purpose: Add a new movie to the dictionary
	//Precondition: Movie must not exist already
	//Postcondition: Adds movie to dictionary
	void addMovie(const string& movieName);

	//Purpose: Add/link actor to a movie
	//Precondition: Movie exists, Actor exists
	//Postcondition: Actor is added to an existing movie
	void addActorToMovie(const string& actorName, const string& movieName);

	//Purpose: Update movie/actor details
	//Precondition: Movie and actor exists 
	//Postcondition:Movie/Actor details are updated
	void updateDetails(const string& type, const string& key, const string& newValue);
};

