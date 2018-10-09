// fare.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
using namespace std;

int main()
{
	int age;
	int boundaries;
	double fare;
	string destination = "";
	string student = "";

	int flag = 0; //if >18 flag = 1, if <64 flag = 2
	int studentStatus = 3; //0 = not a student, 1 = student
	int error = 0; //0 = valid, 1 = negative age, 2 = student status not y or n, 3 = no destination, 4 = zone boundaries negative

	cout << "Age of rider: ";
	cin >> age;
	cout << endl;
	if (age < 0)
		error = 1;
	else if (age < 18)
		flag = 1;
	else if (age > 64)
		flag = 2;

	cin.ignore(256, '\n');
	cout << "Student? (y/n) : ";
	getline(cin, student);
	cout << endl;
	if (student == "y")
		studentStatus = 1;
	else if (student == "n")
		studentStatus = 0;
	else
		error = 2;

	cout << "Destination: ";
	getline(cin, destination);
	cout << endl;
	if (destination == "")
		error = 3;

	cout << "Number of zone boundaries crossed: ";
	cin >> boundaries;
	cout << endl;
	if (boundaries < 0)
		error = 4;

	cout << "---" << endl;

	if (flag == 0 && studentStatus == 0) //generic
		fare = 1.35 + .55 * boundaries;
	else if (flag == 0 && studentStatus == 1) //generic student
		if (boundaries == 0 || boundaries == 1)
			fare = .65;
		else
			fare = 1.35 + .55 * boundaries;
	else if (flag == 1) //under 18
		if (boundaries == 0 || boundaries == 1)
			fare = .65;
		else
			fare = 1.35 + .55 * boundaries;
	else if (flag == 2 && boundaries == 0) //senior 0 boundaries
		fare = .45;
	else if (flag == 2 && studentStatus == 1 && boundaries == 1) //senior student
		fare = .65;
	else if (flag == 2) //senior
		fare = .55 + .25 * boundaries;


	if (error == 1)
	{
		cout << "The age must not be negative" << endl;
		return 0;
	}	
	else if (error == 2)
	{
		cout << "You must enter y or n" << endl;
		return 0;
	}
	else if (error == 3)
	{
		cout << "You must enter a destination" << endl;
		return 0;
	}	
	else if (error == 4)
	{
		cout << "The number of zone boundaries crossed must not be negative" << endl;
		return 0;
	}	
	else if (error == 0)
		cout << "The fare to " << destination << " is $" << fare <<endl;

    return 0;
}

