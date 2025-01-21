#include "Movie.h"
using namespace std;
#include <iostream>
# include "Actor.h"

//Constructor
Movie::Movie(int movieId, string title, string plot, int yearOfRelease)
	: movieId(movieId), title(title), plot(plot), yearOfRelease(yearOfRelease) {
	noOfVoters = 0;
	totalRatings = 0;
}

//deconstructor
Movie::~Movie() {
	actors.~DoublyLinkedList();
}

//Purpose: Retrieve the movie's id.
//Precondition : None.
//Postcondition : Returns the id of the movie.
int Movie::getMovieId() const {
	return movieId;
}

//Purpose: Retrieve the movie's title.
//Precondition: None.
//Postcondition: Returns the title of the movie.
string Movie::getTitle() const{
	return title;
}

//Purpose: Retreive the movie's plot.
//Precondition: None.
//Postcondition: Returns the plot of the movie.
string Movie::getPlot() const{
	return plot;
}

//Purpose: Retrieve the movie's year of release.
//Precondition: None.
//Postcondition: Returns the year of release of the movie.
int Movie::getYearOfRelease() const {
	return yearOfRelease;
}

//Purpose: Retrieve the actor's total ratings.
//Precondition : None.
//Postcondition : Returns the total ratings of the actor.
float Movie::getTotalRatings() const {
	return totalRatings;
}

//Purpose: Retrieve the number of voters of the actor's rating.
//Precondition : None.
//Postcondition : Returns the number of voters of the actor's rating.
int Movie::getNoOfVoters() const {
	return noOfVoters;
}

//Purpose: Calculate and updates the rating of the actor.
//Precondition: None
//Postcondition: Returns the updated rating of the actor.
float Movie::calculateRating() const {
	float newRating = totalRatings / noOfVoters;
	return newRating;
}

//Purpose: Updates rating based on user input.
//Precondition : None.
//Postcondition : Updates rating for the actor.
void Movie::updateRating() {
	cout << "Add rating: ";
	float newRating;
	cin >> newRating;
	noOfVoters += 1;
	totalRatings += newRating;

	float rating = calculateRating();

	cout << "Rating for " << title << " has been updated to " << rating << "/5." << endl;
}

//Purpose: Add an actor to the movie's list of actors.
//Precondition: None.
//Postcondition: The actor is added to the movie's actor list.
void Movie::addActor(Actor actor) {
	actors.add(actor);
}

//Purpose: Retrieve the list of actors in the movie.
//Precondition: None.
//Postcondition: Returns a pointer to the head of the actor list.
void Movie::getActors() {
	actors.print();
}