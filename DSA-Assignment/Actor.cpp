#include "Actor.h"
using namespace std;
#include <string>
#include <iostream>
#include <ctime>

//Constructor
Actor::Actor(int actorId, string name, int yearOfBirth) 
	: actorId(actorId), name(name), yearOfBirth(yearOfBirth) {
	noOfVoters = 0;
	totalRatings = 0;
}

//Deconstructor
Actor::~Actor() {
	movies.~DoublyLinkedList();
	noOfVoters = 0;
	totalRatings = 0;
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

//Purpose: Retrieve the actor's id.
//Precondition : None.
//Postcondition : Returns the id of the actor.
int Actor::getActorId() const {
	return actorId;
}

//Purpose: Retrieve the actor's total ratings.
//Precondition : None.
//Postcondition : Returns the total ratings of the actor.
float Actor::getTotalRatings() const {
	return totalRatings;
}

//Purpose: Retrieve the number of voters of the actor's rating.
//Precondition : None.
//Postcondition : Returns the number of voters of the actor's rating.
int Actor::getNoOfVoters() const {
	return noOfVoters;
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

//Purpose: Calculate and updates the rating of the actor.
//Precondition: None
//Postcondition: Returns the updated rating of the actor.
float Actor::calculateRating() const {
	float newRating = totalRatings / noOfVoters;
	return newRating;
}

//Purpose: Updates rating based on user input.
//Precondition : None.
//Postcondition : Updates rating for the actor.
void Actor::updateRating() {
	cout << "Add rating: ";
	float newRating;
	cin >> newRating;
	noOfVoters += 1;
	totalRatings += newRating;

	float rating = calculateRating();

	cout << "Rating for " << name << " has been updated to " << rating << "/5." << endl;
}

//Purpose: Add a movie to the actor's list of movies.
//Precondition : None.
//Postcondition : The movie is added to the actor's movie list.
void Actor::addMovie(const Movie movie) {
	movies.add(movie);
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