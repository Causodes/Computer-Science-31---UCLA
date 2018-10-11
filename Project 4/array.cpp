// Project 4.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
#include <array>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value)
{
	if (n < 0) //check for invalid n
		return -1;
	if (n == 0)
		return 0;

	for (int i = 0; i < n; i++) //loop to append value to end of each string in array a[]
	{
		a[i] = a[i] + value;
	}
	return n;
}

int lookup(const string a[], int n, string target)
{
	if (n < 0) //check for invalid n
		return -1;

	for (int i = 0; i < n; i++) //loop to walk through every value in a[], and checks if value is equal to target
	{
		if (a[i] == target)
			return i;
	}
	return -1;
}

int positionOfMax(const string a[], int n) 
{
	string temp = a[0];
	int max = 0;

	if (n < 0) //check for invalid n
		return -1;
	if (n == 0) //check for n value of 0
		return 0;

	for (int i = 1; i < n; i++) //loop to walk through every value in a[]
	{
		if (a[i] > temp) //check to see if each given value of a[] is greater than current greatest
		{
			temp = a[i]; //sets temp to largest value
			max = i; //sets max to position of largest value
		}
	}
	return max;
}

int rotateLeft(string a[], int n, int pos)
{
	if (n < 0 || pos < 0) //check for invalid n
		return -1;
	if (pos >= n)
		return -1;
	if (n == 1 && pos == 0) //check for special case
		return 0;

	string temp = a[pos];
	
	for (int i = pos; i < n - 1; i++) //moves all values over to the left by one
	{
		a[i] = a[i + 1];
	}
	a[n - 1] = temp; //sets final position 
	return pos;
}

int countRuns(const string a[], int n)
{
	if (n < 0) //check for invalid n
		return -1;
	if (n == 0) //check for n value of 0
		return 0;

	int c = 1; //counter variable for consecutive runs

	for (int i = 0; i < n-1; i++) //loop to walk through every value of a[]
	{
		if (a[i] != a[i + 1]) //check for change in value of strings
		{
			c++;
		}	
	}
	//if (a[n - 1] != a[n - 2]) //check for final two values in a[]
		//c++;
	return c;
}

int flip(string a[], int n)
{
	string temp; 
	int i = 0;
	int f = n-1;

	if (n < 0) //check for invalid n
		return -1;

	while (i <= f) //loop to swap positions, walks inwards and stops once i and f values are same or cross
	{
		temp = a[f];
		a[f] = a[i];
		a[i] = temp;
		i++;
		f--;
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
	int f;

	if (n1 < 0 || n2 < 0) //check for invalid values of n
		return -1;

	if (n1 < n2) //sets f to value or smaller n
		f = n1;
	else
		f = n2;

	for (int i = 0; i < f; i++) //loop to walk through string arrays; if value differs, return location
	{
		if (a1[i] != a2[i])
			return i;
	}
	return f; //no difference, returns value of shorter string array.
}

int subsequence (const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0) //check for invalid value of n
		return -1;
	if ((n1 == 0 && n2 == 0) || n2 == 0) //check for n value of 0
		return 0;
	if (n1 == 0 && n2 > 0) //check for invalid n1
		return -1;

	int startpos = 0;
	int i = 0;

	while (i < n1) //loop to walk through a1[]
	{
		if (a1[i] == a2[0]) //check for first value
		{
			startpos = i; //marks a temporary starting position
			int c = 0;
			while (a1[i] == a2[c]) //loop to walk through a2[]
			{
				if (c == n2 - 1)
					return startpos; //if all values are the same, return starting position
				if (i == n1 - 1 && c != n2 - 1)
					return -1;
				i++;
				c++;
			}
		}
		i++;
	}
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 <= 0)
		return -1;

	if (n1 == 0)
		return 0;

	for (int i = 0; i < n1; i++) //loop to run though a1[]
	{
		for (int c = 0; c < n2; c++) //loop to run through a2[]
		{
			if (a1[i] == a2[c]) //statement to check equality in values
				return i;
		}
	}
	return -1;
}

int split(string a[], int n, string splitter)
{
	if (n == 0)
		return 0;
	if (n < 0)
		return -1;
	string temp;
	
	for (int i = 0; i < n - 1; i++) //bubble sort loop
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i] > a[j])
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}

	for (int c = 0; c < n; c++) //loop to walk through a[] and check for first value greater than or equal to splitter
	{
		if (a[c] >= splitter)
			return c;
	}
	return n;
}


int main()
{
	string h[7] = { "selina", "reed", "diana", "tony", "", "logan", "peter" };
	assert(lookup(h, 0, "logan") == -1);
	assert(lookup(h, 7, "diana") == 2);
	assert(lookup(h, 2, "diana") == -1);
	assert(positionOfMax(h, 7) == 3);

	string g[4] = { "selina", "reed", "peter", "sue" };
	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "selina?" && g[3] == "sue?");
	cout << "append" << endl;
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "peter?" && g[3] == "reed?");
	cout << "rotate" << endl;

	string e[4] = { "diana", "tony", "", "logan" };
	//assert(subsequence(h, 7, e, 4) == 2);
	cout << "subsequence" << endl;

	string d[5] = { "reed", "reed", "reed", "tony", "tony" };
	assert(countRuns(d, 5) == 2);
	cout << "countruns" << endl;

	string f[3] = { "peter", "diana", "steve" };
	assert(lookupAny(h, 7, f, 3) == 2);
	cout << "lookup" << endl;
	assert(flip(f, 3) == 3 && f[0] == "steve" && f[2] == "peter");
	cout << "flip" << endl;

	assert(split(h, 7, "peter") == 3);
	cout << "split" << endl;

	string a[5] = { "a", "A", "aa", "Aa", "AA" };
	string b[5] = { "b", "b", "BB", "b", "BB" };
	string b1[4] = { "b", "b", "bb", "bb" };
	string b2[9] = { "b", "b", "BB", "b", "BB","b", "b", "bb", "bb" };
	string b3[4] = { "b", "b", "bb", "bb" };
	string b4[4] = { "bbb", "bbb", "BB", "bb" };

	assert(appendToAll(a, 0, "!!") == 0 && a[0] == "a"); //string array on zero
	assert(appendToAll(a, -1, "!!") == -1 && a[0] == "a"); //invalid n value
	assert(appendToAll(a, 3, "!!") == 3 && a[1] == "A!!" && a[3] == "Aa"); //checks appendToAll, including stopping early

	assert(lookup(a, 0, "a!!") == -1); //string array of zero
	assert(lookup(a, 1, "aa!!") == -1); //"aa" out of index
	assert(lookup(a, 5, "aa!!") == 2); //position 2 in array

	assert(positionOfMax(a, 0) == 0); //string array of zero
	assert(positionOfMax(a, -1) == -1); //invalid n value
	assert(positionOfMax(a, 5) == 2); //maximum value

	assert(rotateLeft(a, 0, 0) == -1); //position same value as n
	assert(rotateLeft(a, -1, 0) == -1); //invalid n
	assert(rotateLeft(a, 1, -1) == -1); //invalid pos
	assert(rotateLeft(a, 1, 0) == 0); //speical case single element
	assert(rotateLeft(a, 5, 1) == 1 && a[1] == "aa!!" && a[4] == "A!!"); //test for valid rotation

	assert(countRuns(b, 0) == 0); //empty string array
	assert(countRuns(b, -1)); //invalid n
	assert(countRuns(b, 5) == 4); //test for different last two values
	assert(countRuns(b, 2) == 1); //test for no change

	assert(flip(b, 0) == 0); //empty string array
	assert(flip(b, -1) == -1); //invalid n
	assert(flip(b, 5) == 5 && b[0] == "BB" && b[4] == "b" && b[2] == "BB"); //test for odd number of elements
	assert(flip(b1, 4) == 4 && b1[0] == "bb" && b1[3] == "b" && b1[2] == "b"); //test for even number of elements

	assert(subsequence(b2, 0, b1, 0) == 0); //test for edge case
	assert(subsequence(b2, 9, b1, 0) == 0); //test for edge case
	assert(subsequence(b2, 0, b1, 1) == -1); //test for edge case
	assert(subsequence(b2, 0, b1, -1) == -1); //test for invalid input
	assert(subsequence(b2, -1, b1, 0) == -1); //test for invalid input
	assert(subsequence(b2, 9, b1, 4) == -1); //test for valid input; no match, out of bounds exception test
	assert(subsequence(b2, 9, a, 5) == -1); //test for valid input; no match
	assert(subsequence(b2, 9, b3, 4) == 5); //test for valid input

	assert(lookupAny(b1, 4, b2, 0) == -1); //test for invalid n2
	assert(lookupAny(b1, -1, b2, 9) == -1); //test for invalid n1
	assert(lookupAny(b1, 0, b2, 9) == 0); //test for valid edge scenario
	assert(lookupAny(b1, 4, a, 5) == -1); //no match
	assert(lookupAny(b4, 4, b3, 4) == 3); //match at nonzero location

	assert(split(b2, -1, "BBB") == -1); //test for invalid n
	assert(split(b2, 0, "BBB") == 0); //test for empty array
	assert(split(b2, 9, "BBB") == 2); //test for valid split

	cout << "All tests succeeded" << endl;
	return 0;
}

