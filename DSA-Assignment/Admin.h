#pragma once
#include <string>
using namespace std;

class Admin
{
private:
	string name;
	int adminId;

public:
	//Constructor
	Admin(const string name, const int adminId);

	//Deconstructor
	~Admin();

	//Purpose: Retrieve the username of the user.
	//Precondition: None.
	//Postcondition: Returns the username of the user.
	string getName() const;

	//Purpose: Retrieve the id of the user.
	//Precondition: None.
	//Postcondition: Returns the user id.
	int getAdminId() const;
};

