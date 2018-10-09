//ButtonBass Software Encoder

#include<iostream>
#include<string>

using namespace std;

//hasCorrectSyntax Block Start

int loopCheck(int pos, string song)
{
	string check = song;
	int i = pos; //starting point within string

	int c = 0; //internal counter variable
	int flag1 = 0; //1 = note; 2 = accidental; 3 = octave; 4 = beat

	if (i == check.length() - 1 && check.at(i) != '/')
		return -1;
	switch (check.at(i)) //check for note letter
	{
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G': flag1 = 1; c++; break;

	case '/': flag1 = 4;  i += c; break;

	default: return -1;
	}

	if (flag1 == 1) //check given previous char is note
	{
		if (i+c == check.length() - 1 && check.at(i+c) != '/')
			return -1;
		switch (check.at(i + c))
		{
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G': i += c; return i;

		case '#':
		case 'b': flag1 = 2; c++; break;

		case '2':
		case '3':
		case '4':
		case '5': flag1 = 3; c++; break;

		case '6':
			if (check.at(i) == 'C') //special case C6
			{
				flag1 = 3;
				c++;
				break;
			}
			else
			{
				return -1;
			}

		case '/': flag1 = 4; i += c; break;

		default: return -1;
		}
	}

	if (flag1 == 2) //check given previous char is accidental
	{
		if (i + c == check.length() - 1 && check.at(i + c) != '/')
			return -1;
		switch (check.at(i + c))
		{
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G': i += c; return i;

		case '2':
		case '3':
		case '4':
		case '5': flag1 = 3; c++; break;

		case '6':
			if (check.at(i + c - 1) == 'b') //special case Cb6
			{
				if (check.at(i + c - 2) == 'C')
				{
					flag1 = 3;
					c++;
					break;
				}
				else
					return -1;
			}
			else
				return -1;

		case '1':
			if (check.at(i + c - 1) == '#') //special case B#1
			{
				if (check.at(i + c - 2) == 'B')
				{
					flag1 = 3;
					c++;
					break;
				}
				else
					return -1;
			}
			else
				return -1;

		case '/': i += c; flag1 = 4; break;

		default: return -1;
		}
	}

	if (flag1 == 3) //check given previous char is octave number
	{
		if (i + c == check.length() - 1 && check.at(i + c) != '/')
			return -1;
		switch (check.at(i + c))
		{
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G': i += c; return i;

		case '/': i += c; flag1 = 4; break;

		default: return -1;
		}
		
	}

	if (flag1 == 4) //check at end of beat
	{
		int x = 0;
		while (check.at(i + x) == '/')
		{
			if (i + x == check.length() - 1)
				return -2;
			else
				x++;
		}
		i += x;
		if (i == check.length() - 1 && check.at(i) == '/')
			return -2;
		else if (i == check.length() - 1 && check.at(i) != '/')
			return -1;
		return i;
	}

}

bool hasCorrectSyntax(string song)
{
	string input = song;
	int count = 0;

	while (count != input.length())
	{
		if (loopCheck(count, input) == -1)
		{
			return false;
			break;
		}	
		else if (loopCheck(count, input) == -2)
		{
			return true;
			break;
		}
		//cout << count << input.at(count) << " "; //displays each note iteration
		count = loopCheck(count, input);
	}

	return true;
}

//hasCorrectSyntax Block End

//encodeNote Block Start

char encodeNote(int octave, char noteLetter, char accidentalSign)
{
	// This check is here solely to report a common CS 31 student error.
	if (octave > 9)
	{
		cerr << "********** encodeNote was called with first argument = "
			<< octave << endl;
	}

	// Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
	//      to -1, 0,   1,   2,   3, ...,  11, 12

	int note;
	switch (noteLetter)
	{
	case 'C':  note = 0; break;
	case 'D':  note = 2; break;
	case 'E':  note = 4; break;
	case 'F':  note = 5; break;
	case 'G':  note = 7; break;
	case 'A':  note = 9; break;
	case 'B':  note = 11; break;
	default:   return ' ';
	}
	switch (accidentalSign)
	{
	case '#':  note++; break;
	case 'b':  note--; break;
	case ' ':  break;
	default:   return ' ';
	}

	// Convert ..., A#1, B1, C2, C#2, D2, ... to
	//         ..., -2,  -1, 0,   1,  2, ...

	int sequenceNumber = 12 * (octave - 2) + note;

	string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
	if (sequenceNumber < 0 || sequenceNumber >= keymap.size())
		return ' ';
	return keymap[sequenceNumber];
}

//encodeNote Block End

//encodeSong Playable Song Block Start

bool singleNote(string song, int start) //checks for a single note
{
	int flag = 0; //0 = single note, 1 = chord
	for (int count = 1; count <= 3; count++)
	{
		if (song[start + count] == '/')
		{
			if (flag == 0)
				return true;
		}
		else if (flag == 1)
			return false;	
		else
		{
			switch (song[start + count])
			{
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G': flag = 1; return false;
			default: break;
			}
		}
	}
	return false;
}

void encodeOneNote(string song, int& start, string& instructions) //encodes a single note
{
	int octaveNum = 4;
	char letter = ' ';
	char accidental = ' ';

	while (song[start] != '/')
	{
		if (isalpha(song[start]) && song[start] != 'b')
		{
			letter = song[start];
			start++;
		}
			
		if (song[start] == 'b' || song[start] == '#')
		{
			accidental = song[start];
			start++;
		}
			
		if (isdigit(song[start]))
		{
			switch (song[start])
			{
			case '1': octaveNum = 1; break;
			case '2': octaveNum = 2; break;
			case '3': octaveNum = 3; break;
			case '4': octaveNum = 4; break;
			case '5': octaveNum = 5; break;
			case '6': octaveNum = 6; break;
			}
			start++;
		}
	}
	instructions = instructions + encodeNote(octaveNum, letter, accidental);
	start++;
}

void encodeChord(string song, int& start, string& instructions) //encodes a chord
{
	instructions = instructions + "[";
	while (song[start] != '/')
	{
		int octaveNum = 4;
		char letter = ' ';
		char accidental = ' ';
		
		if (isalpha(song[start]) && song[start] != 'b')
		{
			letter = song[start];
			start++;
		}

		if (song[start] == 'b' || song[start] == '#')
		{
			accidental = song[start];
			start++;
		}

		if (isdigit(song[start]))
		{
			switch (song[start])
			{
			case '1': octaveNum = 1; break;
			case '2': octaveNum = 2; break;
			case '3': octaveNum = 3; break;
			case '4': octaveNum = 4; break;
			case '5': octaveNum = 5; break;
			case '6': octaveNum = 6; break;
			}
			start++;
		}
		instructions = instructions + encodeNote(octaveNum, letter, accidental);
	}
	instructions = instructions + "]";
	start++;
}

//encodeSong Playable Song Block End

//encodeSong Valid Song Block End

int songLoopCheck(int pos, string song)
{
	string check = song;
	int i = pos; //starting point within string

	int c = 0; //internal counter variable
	int flag1 = 0; //1 = note; 2 = accidental; 3 = octave; 4 = beat

	if (i == check.length() - 1 && check.at(i) != '/')
		return -1;
	switch (check.at(i)) //check for note letter
	{
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G': flag1 = 1; c++; break;

	case '/': flag1 = 4;  i += c; break;

	default: return -1;
	}

	if (flag1 == 1) //check given previous char is note
	{
		if (i+c == check.length() - 1 && check.at(i+c) != '/')
			return -1;
		switch (check.at(i + c))
		{
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G': i += c; return i;

		case '#':
		case 'b': flag1 = 2; c++; break;

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': flag1 = 3; c++; break;

		case '/': flag1 = 4; i += c; break;

		default: return -1;
		}
	}

	if (flag1 == 2) //check given previous char is accidental
	{
		if (i + c == check.length() - 1 && check.at(i + c) != '/')
			return -1;
		switch (check.at(i + c))
		{
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G': i += c; return i;

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': flag1 = 3; c++; break;

		case '/': i += c; flag1 = 4; break;

		default: return -1;
		}
	}

	if (flag1 == 3) //check given previous char is octave number
	{
		if (i + c == check.length() - 1 && check.at(i + c) != '/')
			return -1;
		switch (check.at(i + c))
		{
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G': i += c; return i;

		case '/': i += c; flag1 = 4; break;

		default: return -1;
		}
	}

	if (flag1 == 4)
	{
		int x = 0;
		while (check.at(i + x) == '/')
		{
			if (i + x == check.length() - 1)
				return -2;
			else
				x++;
		}
		i += x;
		if (i == check.length() - 1 && check.at(i) == '/')
			return -2;
		else if (i == check.length() - 1 && check.at(i) != '/')
			return -1;
		return i;
	}

}

bool isASong(string song)
{
	string input = song;
	int count = 0;

	while (count != input.length())
	{
		if (songLoopCheck(count, input) == -1)
			return false;
		else if (songLoopCheck(count, input) == -2)
			return true;
		//cout << count << input.at(count) << " ";
		count = songLoopCheck(count, input);
	}

	return true;
}

int testOneBeat(string song, int& start)
{
	while (song[start] != '/')
	{
		if (isdigit(song[start]))
		{
			switch (song[start])
			{
			case '0':
			case '7':
			case '8':
			case '9': return -1;

			case '1':
				if (song[start - 1] != '#' || (song[start - 1] != '#' && song[start - 2] != 'B')) //special case 1 octave
					return -1;
				else
					break;

			case '6':
				if (song[start - 1] != 'C' || (song[start - 1] != 'b' && song[start - 2] != 'C')) //special case 6 octave
					return -1;

			default: break;
			}
			start++;
		}
		else
			start++;
	}
	start++;
}

//encodeSong Valid Song Block End

int encodeSong(string song, string& instructions, int& badBeat)
{
	string testSong = song;
	int count = 0;

	if (hasCorrectSyntax(testSong)) //Playable Song Block
	{
		instructions = "";
		while (count < testSong.length())
		{
			if (testSong[count] == '/')
			{
				instructions = instructions + " ";
				count++;
			}
			else if (singleNote(testSong, count))
				encodeOneNote(testSong, count, instructions);
			else
				encodeChord(testSong, count, instructions);
		}
		cerr << instructions << endl;
		return 0;
	}
	
	else if (hasCorrectSyntax(testSong) == false && isASong(testSong) == false) //Not Song Block
		return 1;

	else if (hasCorrectSyntax(testSong) == false && isASong(testSong) == true) //Song but not Playable Block
	{
		int beat = 0;
		while (count < testSong.length())
		{
			if (testOneBeat(testSong, count) != -1)
				beat++;
			else if (testOneBeat(testSong, count) == -1)
			{
				badBeat = beat;
				return 2;
			}			
			else if (testSong[count] == '/')
			{
				beat++;
				count++;
			}
		}
		return 2;
	}

}


int main()
{
	string t;
	string i;
	int Badbeat = -10;
		cout << "Enter song: ";
		getline(cin, t);
		cout << "hasCorrectSyntax returns ";
		if (hasCorrectSyntax(t) == true)
		{
			cout << "true" << endl;
			encodeSong(t, i, Badbeat);
		}

		else
		{
			int x = encodeSong(t, i, Badbeat);
			cout << "false" << endl << x << " badBeat = "  << Badbeat << endl;
		}
			
}

