#define _CRT_SECURE_NO_DEPRECATE

#include "utilities.h"
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

const char WORDFILENAME[] = "C:/Users/tiany/Desktop/smallwords.txt";

int runOneRound(const char words[][7], int nWords, int wordnum)
{
	if (nWords < 0 || wordnum < 0 || wordnum >= nWords) //check for invalid parameters being passed
	{
		return -1;
	}

	else
	{
		int match = 0; //flag variable for successfully finding word

		int score = 0;

		while (match == 0) //running round
		{
			int flag = 0; //flag variable for invalid input check
			int inList = 0; //flag variable for word being in list

			cout << "Probe word: ";

			char probe[101];
			cin.getline(probe, 101);

			for (int i = 4; i <= 6; i++) //check for input length
			{
				if (probe[i] == '\0') //if end of c-string does fall between positions 4 and 6
				{
					flag = 1;
					break;
				}
			}

			for (int i = 0; probe[i] != '\0'; i++) //check for lower case letters
			{
				if (islower(probe[i]) == false) //if any character is not lowercase
				{
					flag = 0;
					break;
				}
			}

			for (int i = 0; i < nWords; i++) //check for part of list
			{
				if (strcmp(probe, words[i]) == 0)  //if c-string matches any other c-string in the list
				{
					inList = 1;
				}
			}

			if (flag != 1) //given test for lowercase or length failed
			{
				cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			}

			else if (inList != 1) //given test for being element of array failed
			{
				cout << "I don't know that word." << endl;
			}

			else //main function for single turn interation
			{
				score++; //increment score
				int stars = 0;
				int planets = 0;

				char tempKey[7];
				strcpy(tempKey, words[wordnum]);

				int i = 0;

				int keyLength = 0; //define length of keyword
				while (tempKey[keyLength] != '\0')
				{
					keyLength++;
				}

				int probeLength = 0; //define length of user input
				while (probe[probeLength] != '\0')
				{
					probeLength++;
				}

				if (probeLength < keyLength)
				{
					while (probe[i] != '\0') //block to count stars
					{
						if (tempKey[i] == probe[i]) //if match, replace with placeholder variables and increment star
						{
							stars++;
							tempKey[i] = ' ';
							probe[i] = '*';
						}
						i++;
					}
				}
				
				else
				{
					while (tempKey[i] != '\0') //block to count stars
					{
						if (tempKey[i] == probe[i]) //if match, replace with placeholder variables and increment star
						{
							stars++;
							tempKey[i] = ' ';
							probe[i] = '*';
						}
						i++;
					}
				}
			

				for (i = 0; i<keyLength; i++) //block to count planets
				{
					for(int j = 0; j<probeLength; j++)
					{
						if (tempKey[i] == probe[j]) //if match, replace with placeholder variables and increment planets
						{
							planets++;
							tempKey[i] = '&';
							probe[j] = '%';
						}
					}
				}

				if (probe[stars] == '\0') //if complete match, break loop and return score
				{
					match = 1;
					return score;
					break;
				}

				else //if not complete match, return stars and planets to output and rerun loop
				{
					cout << "Stars: " << stars << ", Planets: " << planets << endl;
				}

			}

		}

	}
	return 0;
}

int main()
{
	char wordList[9000][7];

	const int n = getWords(wordList, 9000, WORDFILENAME);

	if (n < 1) //test for no words
	{
		cout << "No words were loaded, so I can't play the game." << endl;
	}

	else
	{
		int rounds;
		cout << "How many rounds do you want to play? ";
		cin >> rounds;
		cin.ignore();
		cout << endl;

		if (rounds < 0)
		{
			cout << "The number of rounds must be positive." << endl;
		}

		else
		{
			double average = 0;
			int minimum = 0;
			int maximum = 0;

			for (int i = 1; i < rounds + 1; i++)
			{
				int rand = randInt(0, n - 1);

				cout << "Round " << i << endl;

				int length = 0;

				while (wordList[rand][length] != '\0') //test for keyword length
				{
					length++;
				}

				cout << "The secret word is " << length << " letters long." << endl;

				int score = runOneRound(wordList, n, rand); 

				if (score == 1)
				{
					cout << "You got it in " << score << " try." << endl;
				}
				else
				{
					cout << "You got it in " << score << " tries." << endl;
				}

				if (i == 1) //block for setting minimum
				{
					minimum = score;
				}
				else
				{
					if (score < minimum)
					{
						minimum = score;
					}
				}

				if (score > maximum) //block for setting maximum
				{
					maximum = score;
				}

				average = (average*(i - 1) + score) / i; //block for setting average

				cout << "Average: " << average << ", minimum: " << minimum << ", maximum: " << maximum << endl << endl;
			}
		}
	}
	return 0;
}