#include "Actor.h"
using namespace std;
#include <string>
#include <iostream>
#include <ctime>
#include "Movie.h"


//helper methods for sorting
bool compareMoviesByTitle(Movie a, Movie b) {
	return b < a;
}

//default constructor
Actor::Actor() {}

//Constructor
// Constructor
Actor::Actor(int actorId, string name, int yearOfBirth)
	: actorId(actorId), name(name), yearOfBirth(yearOfBirth), totalRatings(), noOfVoters() {
}


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

//Purpose: Retrieve the actor's id.
//Precondition : None.
//Postcondition : Returns the id of the actor.
int Actor::getActorId() const {
	return actorId;
}

//Purpose: Retrieve the actor's list of movies.
//Precondition : None.
//Postcondition : Returns the list of movies the actor acted in.
DoublyLinkedList<Movie> Actor::getMovieList() const {
	return movies;
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
	if (noOfVoters == 0) return 0.0f;
	float ratings = totalRatings / noOfVoters;
	return ratings;
}

//Purpose: Updates rating based on user input.
//Precondition : None.
//Postcondition : Updates rating for the actor.
void Actor::updateRating() {
	float newRating;

	do {
		cout << "Enter a rating between 0 and 5: ";
		cin >> newRating;

		if (cin.fail() || newRating < 0.0f || newRating > 5.0f) {
			cout << "Invalid rating. Please enter a value between 0 and 5." << endl;
			cin.clear(); 
			cin.ignore(1000, '\n');  
		}
		else {
			break;
		}
	} while (true);

	// Update rating values
	noOfVoters++;
	totalRatings += newRating;
	float updatedRating = calculateRating();

	// Print updated rating
	cout << "Rating for " << name << " has been updated to " << updatedRating << "/5." << endl;
}

//Purpose: Add a movie to the actor's list of movies.
//Precondition : None.
//Postcondition : The movie is added to the actor's movie list.
void Actor::addMovie(const Movie& movie) {
	movies.add(movie);
}

// Purpose: Print list of movies the actor has starred in in alphabetical order.
// Precondition: None.
// Postcondition: Prints movies actor has starred in in alphabetical order.
void Actor::getMovies() {
	cout << "Movies starring " << name << ":" << endl;
	if (movies.isEmpty()) {
		cout << "No movies found." << endl;
		return;
	}

	movies.mergeSort(compareMoviesByTitle);
	// Print sorted movies
	movies.print();
}

// Purpose: Display details of the actor.
// Precondition: None.
// Postcondition: The actor is displayed.
void Actor::print() const{
	cout << "ID: " << actorId;
	cout << "\tName: " << name;
	cout << "\tYear of Birth: " << yearOfBirth;
	cout << "\tRating: " << calculateRating() << "/5" << endl;
}

//for comparison reasons
bool Actor::operator<(const Actor& actor) const{
	return actor.name < name;
}
bool Actor::operator==(const Actor& actor) const {
	return actor.getActorId() == actorId;
}