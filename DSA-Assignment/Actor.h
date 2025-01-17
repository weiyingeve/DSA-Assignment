#pragma once
using namespace std;
#include<string>
#include "DoublyLinkedList.h"

typedef string ItemType;

class Actor
{
private:
	string name;
	int yearOfBirth;
	int actorId;
	float rating;
	DoublyLinkedList movies;

public:
	//Constructor
	Actor(int actorId, string name, int yearOfBirth);

	//Deconstructor
	~Actor();

	//Purpose: Retrieve the actor's name.
	//Precondition : None.
	//Postcondition : Returns the name of the actor.
	string getName() const;
	
	//Purpose: Retrieve the actor's year of birth.
	//Precondition : None.
	//Postcondition : Returns the year of birth of the actor.
	int getYearOfBirth() const;

	//Purpose: Calculate the age of the actor.
	//Precondition: YearOfBirth is valid
	//Postcondition: Returns age of the actor.
	int calculateAge() const;

	//Purpose: Add a movie to the actor's list of movies.
	//Precondition : The movie title must be a valid, non - empty string.
	//Postcondition : The movie title is added to the actor's movie list.
	void addMovie(const string title);

	//Purpose: Print list of movies the actor has starred in.
	//Precondition : None.
	//Postcondition : Prints movies actor has starred in in alphabetical order.
	void getMovies();
};