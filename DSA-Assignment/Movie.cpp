#include "Movie.h"
using namespace std;
#include <iostream>
# include "Actor.h"

//helper methods for sorting
bool compareActorByName(Actor a, Actor b) {
	return b < a;
}

//default constructor
Movie::Movie() {}

//Constructor
Movie::Movie(int movieId, string title, string plot, int yearOfRelease)
	: movieId(movieId), title(title), plot(plot), yearOfRelease(yearOfRelease) {
	noOfVoters = 0;
	totalRatings = 0;
}

//deconstructor
Movie::~Movie() {}

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

//Purpose: Retrieve the movie's cast.
//Precondition: None.
//Postcondition: Returns the cast of the movie.
DoublyLinkedList<Actor> Movie::getActorList() const {
	return actors;
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
	if (noOfVoters == 0) return 0.0f;
	float ratings = totalRatings / noOfVoters;
	return ratings;
}

//Purpose: Updates rating based on user input.
//Precondition : None.
//Postcondition : Updates rating for the actor.
void Movie::updateRating() {
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

	// Print updated rating
	cout << "Rating for " << title << " has been updated to " << calculateRating() << "/5." << endl;
}

//Purpose: Add an actor to the movie's list of actors.
//Precondition: None.
//Postcondition: The actor is added to the movie's actor list.
void Movie::addActor(const Actor& actor) {
	actors.add(actor);
}

//Purpose: Retrieve the list of actors in the movie.
//Precondition: None.
//Postcondition: Prints the actors.
void Movie::getActors() {
	cout << "Actors starring in " << title << ":" << endl;
	if (actors.isEmpty()) {
		cout << "No movies found." << endl;
		return;
	}
	DoublyLinkedList<Actor> actorList = actors;
	actorList.mergeSort(compareActorByName);
	// Print sorted movies
	actorList.print();
}

// Purpose: Display details of the movie.
// Precondition: None.
// Postcondition: The movie is displayed.
void Movie::print() const{
	cout << "ID: " << movieId;
	cout << "\tTitle: " << title;
	cout << "\tPlot: " << plot;
	cout << "\tYear of Release: " << yearOfRelease;
	cout << "\tRating: " << calculateRating() << "/5" << endl;
}

//for comparison reasons
bool Movie::operator<(const Movie& movie) const{
	return movie.title < title;
}