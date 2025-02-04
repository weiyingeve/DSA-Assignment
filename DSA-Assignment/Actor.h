#pragma once
using namespace std;
#include<string>
#include "DoublyLinkedList.h"

class Movie;

typedef string ItemType;

class Actor
{
private:
	string name;
	int yearOfBirth;
	int actorId;
	float totalRatings;
	int noOfVoters;
	static DoublyLinkedList<Movie> movies;

public:
	//default constructor
	Actor();

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

	//Purpose: Retrieve the actor's id.
	//Precondition : None.
	//Postcondition : Returns the id of the actor.
	int getActorId() const;

	//Purpose: Retrieve the actor's total ratings.
	//Precondition : None.
	//Postcondition : Returns the total ratings of the actor.
	float getTotalRatings() const;

	//Purpose: Retrieve the number of voters of the actor's rating.
	//Precondition : None.
	//Postcondition : Returns the number of voters of the actor's rating.
	int getNoOfVoters() const;

	//Purpose: Calculate the age of the actor.
	//Precondition: YearOfBirth is valid
	//Postcondition: Returns age of the actor.
	int calculateAge() const;

	//Purpose: Calculate the rating of the actor.
	//Precondition: None.
	//Postcondition: Returns the updated rating of the actor.
	float calculateRating() const;

	//Purpose: Updates rating based on user input.
	//Precondition : None.
	//Postcondition : Updates rating for the actor.
	void updateRating();

	//Purpose: Add a movie to the actor's list of movies.
	//Precondition : None.
	//Postcondition : The movie is added to the actor's movie list.
	void addMovie(const Movie& movie);

	//Purpose: Print list of movies the actor has starred in.
	//Precondition : None.
	//Postcondition : Prints movies actor has starred in in alphabetical order.
	void getMovies();

	// Purpose: Display details of the actor.
	// Precondition: None.
	// Postcondition: The actor is displayed.
	void print();

	//for comparison reasons
	bool operator<(const Actor& actor);
};