#pragma once
#include <string>
using namespace std;
class User
{
private:
	string username;
	int userId;

public:
	//Constructor
	User(const string username, const int userId);

	//deconstructor
	~User();

	//Purpose: Retrieve the username of the user.
	//Precondition: None.
	//Postcondition: Returns the username of the user.
	string getUsername() const;

	//Purpose: Retrieve the id of the user.
	//Precondition: None.
	//Postcondition: Returns the user id.
	int getUserId() const;
};

