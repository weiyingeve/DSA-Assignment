#include "Actor.h"
using namespace std;
#include <string>
#include <iostream>
#include <ctime>

//Constructor
Actor::Actor(int actorId, string name, int yearOfBirth) 
	: actorId(actorId), name(name), yearOfBirth(yearOfBirth) {}

//Deconstructor
Actor::~Actor() {
	movies.~DoublyLinkedList();
}

//Purpose: Retrieve the actor's name.
//Precondition : None.
//Postcondition : Returns the name of the actor.
string Actor::getName() const {
	return name;
}

//Purpose: Retrieve the actor's year of birth.
//Precondition : None.
//Postcondition : Returns the year of birth of the actor.
int Actor::getYearOfBirth() const {
	return yearOfBirth;
}

//Purpose: Calculate the age of the actor.
//Precondition: YearOfBirth is valid
//Postcondition: Returns age of the actor.
int Actor::calculateAge() const {
	time_t now = time(0);
	tm localTime; 
	localtime_s(&localTime, &now);  

	int currentYear = 1900 + localTime.tm_year;

	return currentYear - yearOfBirth;
}

//Purpose: Add a movie to the actor's list of movies.
//Precondition : The movie title must be a valid, non - empty string.
//Postcondition : The movie title is added to the actor's movie list.
void Actor::addMovie(const string title) {
	if (!title.empty()) {
		if (!movies.search(title)) {
			movies.add(title);
			cout << "Movie \"" << title << "\" added to list. " << endl;
		}
		else {
			cout << "Movie \"" << title << "\" is already in the list. " << endl;
		}
	}
	else {
		cout << "Error: Movie title cannot be empty" << endl;
	}
}

//Purpose: Print list of movies the actor has starred in.
//Precondition : None.
//Postcondition : Prints movies actor has starred in in alphabetical order.
void Actor::getMovies() {
	cout << "Movie starring " << name << ":" << endl;
	if (movies.isEmpty()) {
		cout << "No movies found. " << endl;
	}
	else {
		movies.print();
	}
}