#pragma once
using namespace std;
#include <string>;
#include "DoublyLinkedList.h"

class Movie
{
private:
	int movieId;
	string title;
	string plot;
	int yearOfRelease;
	float rating;
	DoublyLinkedList actors;
	

public:
	//Constructor
	Movie(int movieId, string title, string plot, int yearOfRelease);

	//deconstructor
	~Movie();

	//Purpose: Retrieve the movie's title.
	//Precondition: None.
	//Postcondition: Returns the title of the movie.
	string getTitle() const;

	//Purpose: Retreive the movie's plot.
	//Precondition: None.
	//Postcondition: Returns the plot of the movie.
	string getPlot() const;

	//Purpose: Retrieve the movie's year of release.
	//Precondition: None.
	//Postcondition: Returns the year of release of the movie.
	int getYearOfRelease() const;

	//Purpose: Add an actor to the movie's list of actors.
	//Precondition: The actor name must be a valid, non-empty string.
	//Postcondition: The actor name is added to the movie's actor list.
	void addActor(const string name);

	//Purpose: Retrieve the list of actors in the movie.
	//Precondition: None.
	//Postcondition: Returns a pointer to the head of the actor list.
	void getActors();
};

