// DSA-Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Actor.h"
#include "Movie.h"
#include "Dictionary.h"
#include "DoublyLinkedList.h"
using namespace std;

void displayMainMenu();
void displayAdminMenu();
void displayUserMenu();
void loadDataFromCSV();

int main() {

}

void displayMainMenu() {
    cout << "\n===== Main Menu =====\n";
    cout << "[1] Admin\n";
    cout << "[2] User\n";
    cout << "[0] Exit\n";
    cout << "Choose an option: ";
}

void displayAdminMenu() {
    cout << "\n===== Admin Menu =====\n";
    cout << "[1] Add an item\n";
    cout << "[2] Remove an item\n";
    cout << "[3] Display all items\n";
    cout << "[0] Return to Main Menu\n";
    cout << "Choose an option: ";
}

void displayUserMenu() {
    cout << "\n===== User Menu =====\n";
    cout << "[1] Display actors in a movie\n";
    cout << "[2] Display movies by actor\n";
    cout << "[0] Return to Main Menu\n";
    cout << "Choose an option: ";
}

// Function to load data from CSV files into the dictionary
void loadDataFromCSV() {

}