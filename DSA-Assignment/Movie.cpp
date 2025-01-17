#include "Movie.h"

//Constructor
Movie::Movie(int movieId, string title, string plot, int yearOfRelease)
	: movieId(movieId), title(title), plot(plot), yearOfRelease(yearOfRelease) {}

//deconstructor
Movie::~Movie() {
	actors.~DoublyLinkedList();
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

//Purpose: Add an actor to the movie's list of actors.
//Precondition: The actor name must be a valid, non-empty string.
//Postcondition: The actor name is added to the movie's actor list.
void Movie::addActor(const string name) {
	actors.add(name);
}

//Purpose: Retrieve the list of actors in the movie.
//Precondition: None.
//Postcondition: Returns a pointer to the head of the actor list.
void Movie::getActors() {
	actors.print();
}