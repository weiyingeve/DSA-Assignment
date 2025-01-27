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

//Purpose: Update status of the report.
//Precondition: Report status is currently 'U' (Unresolved)
//Postcondition: Status is updated to Resolved.
bool Report::updateStatus() {
	if (status == 'U') {
		status = 'R';
	}
	else {
		cout << "Status is already resolved." << endl;
	}
}

//Purpose: Print details of the report.
//Precondition: None.
//Postcondition: Displays details of the report.
void Report::print() {
	cout << "Report ID: " << reportId << endl;
	cout << "Type: " << type << endl;
	cout << "Description: " << description << endl;
	cout << "Status: " << status << endl;
}