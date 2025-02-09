// Done by: Rena Soong_Group4_S10258053C

#include "Report.h"
using namespace std;
#include <iostream>


//default constructor
Report::Report() {}

//constructor
Report::Report(int reportId, string type, string description) 
	: reportId(reportId), type(type), description(description) {
	status = 'U';
}

//deconstructor
Report::~Report() {}

//Purpose: Retrieve the report type
//Precondition : None.
//Postcondition : Returns the report type
string Report::getType() const {
	return type;
}

//Purpose: Retrieve the report type
//Precondition : None.
//Postcondition : Returns the report type
string Report::getDescription() const {
	return description;
}

//Purpose: Retrieve the actor's year of birth.
//Precondition : None.
//Postcondition : Returns the year of birth of the actor.
int Report::getReportId() const {
	return reportId;
}

//Purpose: Update status of the report.
//Precondition: Report status is currently 'U' (Unresolved)
//Postcondition: Status is updated to Resolved.
bool Report::updateStatus() {
	if (status == 'U') {
		return status = 'R';
	}
	else {
		cout << "Status is already resolved." << endl;
	}
}

//Purpose: Print details of the report.
//Precondition: None.
//Postcondition: Displays details of the report.
void Report::print() const{
	cout << "Report ID: " << reportId << endl;
	cout << "Type: " << type << endl;
	cout << "Description: " << description << endl;
	cout << "Status: " << status << endl;
}

bool Report::operator<(const Report& report) const {
	return report.reportId < reportId;
}