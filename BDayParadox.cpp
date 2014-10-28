/*********************** Birthday Paradox  ****************************
Name:  Chad Parnin
Date:  Feb 16, 2014
Homework#:  HW 3
Source File:  Hw3.cpp
Action:  Offers 4 choices, the user can choose from the following:
1.  Explain the birthday paradox.
2.  Check the paradox by generating 1000 sets of random bdays.
3.  Display table of 1 set of 23 bdays.
E.  Exit
***********************************************************************/

#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

const int SAMPLE_SIZE = 23;  // array size of 23 bdays
const int NUMBER_OF_SETS = 1000;

void MenuChoice(char &Choice);
void ExplainBDayParadox();
void VerifyBDayParadox(int BDaySet[]);
void GenerateBDaySet(int BDaySet[]);
void SortBDaySet(int BDaySet[], int SAMPLE_SIZE);
inline void Swap(int &A, int &B);
void DisplayBDaySet(int BDaySet[], int MonthNumber[]);
int DaysInMonth(int MonthNumber);
void ConvertDayOfYear(int BdaySet[], int MonthNumber[]);

int main()
{
	int BDaySet[SAMPLE_SIZE] = { 0 };  // day number of year
	int MonthNumber[SAMPLE_SIZE] = { 0 };  // month number matching index of each day number
	char Choice = ' ';

	do
	{
		MenuChoice(Choice);
		switch (Choice)
		{
		case '1': ExplainBDayParadox();
			break;
		case '2': VerifyBDayParadox(BDaySet);
			break;
		case '3': DisplayBDaySet(BDaySet, MonthNumber);
			break;
		default: cout << "Goodbye\n";
		}
	} while (Choice != 'E');
	
	return 0;
}

/***********************  Menu Choice  *********************************
Action:  Get menu choice
Parameters:
		IN:  Choice
		OUT: Choice
Returns: None
Precondition:  None
************************************************************************/

void MenuChoice(char &Choice)
{
	cout << "Make a selection for the birthday paradox:\n\n";
	cout << "1)   Explain birthday paradox\n";
	cout << "2)   Check birthday paradox by generating 1000 sets of 23 random birthdays\n";
	cout << "3)   Display one set of 23 birthdays\n";
	cout << "E)   Exit\n";
	cin >> Choice;
	if (Choice == 'e')
		Choice = toupper(Choice);
	while ((Choice != '1') && (Choice != '2') && (Choice != '3') && (Choice != 'E'))
	{
		cout << "Bad selection, please re-enter\n";
		cin >> Choice;
		if (Choice == 'e')
			Choice = toupper(Choice);
	}
}

/******************  Explain BDay Paradox (Choice 1)  *******************
Action:  Explains the paradox
Parameters:  None
Returns: None
Precondition:  None
************************************************************************/

void ExplainBDayParadox()
{
	cout << "\nThe birthday paradox states that if 23 random birthdays ";
	cout << "are chosen, there will be a greater than 50% chance that ";
	cout << "there will be at least one matching birthday.\n";
	cout << "This program allows you to generate 1000 sets of 23 random ";
	cout << "birthdays or display a table of 1 set of 23 random birthdays.\n";
	cout << setfill('-') << setw(75) << "-" << "\n\n";
}

/*******************  Verify BDay Paradox (Choice 2)********************
Action:  Calculates the bday paradox by generating 1000 sets of 23 bdays
Parameters:
		IN:  BDaySet array
		OUT: BDaySet array
Returns: None
Precondition:  BDaySet points to an int array and is within bounds
************************************************************************/

void VerifyBDayParadox(int BDaySet[])
{
	int NumberOfMatches = 0;
	int SetHasMatch = 0;
	srand((unsigned int) time(NULL));

	for (int i = 0; i < NUMBER_OF_SETS; ++i)  // do it 1000 times
	{
		GenerateBDaySet(BDaySet);  // calls function to make a set
		for (int j = 0; j < SAMPLE_SIZE - 1; ++j)
		{
			if (BDaySet[j] == BDaySet[j + 1])  // check for a bday match
				NumberOfMatches++;
		}
		if (NumberOfMatches >= 1)  // checks if the set has 1 match
			SetHasMatch++;
		NumberOfMatches = 0;
	}

	float Percent = (SetHasMatch * 100 / static_cast<float>(NUMBER_OF_SETS));  // calculates percentage

	cout << "\nRESULTS: " << SetHasMatch << " out of 1000 (" << setprecision(3);  // display results
	cout << Percent << "%) sets contained a matching birthday.\n\n";
	cout << setfill('-') << setw(75) << "-" << "\n\n";
}

/***********************  Generate BDay Set  ***************************
Action:  Generates a set of 23 random bdays
Parameters:
		IN:  BDaySet array
		OUT: BDaySet array
Returns: None
Precondition:  BDaySet points to an int array and is within bounds
************************************************************************/

void GenerateBDaySet(int BDaySet[])
{
	for (int i = 0; i < SAMPLE_SIZE; ++i)
		BDaySet[i] = 1 + (rand() % 365);  // assign random number to each index
	SortBDaySet(BDaySet, SAMPLE_SIZE);  // call function to sort it
}

/***********************  Sort BDay Set  *******************************
Action:  Sort array with help of Swap function
Parameters:
		IN:  BDaySet array
			 SAMPLE_SIZE const int of size 23
		OUT: BDaySet array
Returns: None
Precondition:  BDaySet points to an int array and is within SAMPLE-SIZE
************************************************************************/

void SortBDaySet(int BDaySet[], int SAMPLE_SIZE)  // sorts array in ascending order
{
	int i, Start, SubSmall = 0;

	for (Start = 0; Start < SAMPLE_SIZE; ++Start)
	{
		SubSmall = Start;

		for (i = Start + 1; i <= SAMPLE_SIZE - 1; i++)
			if (BDaySet[i] < BDaySet[SubSmall])
				SubSmall = i;

		Swap(BDaySet[SubSmall], BDaySet[Start]);  // call swap function to swap values
	}
}

/***********************  Swap Values  *********************************
Action:  Swap values in array
Parameters:
		IN:  A and B, which are sequential index values in BDaySet array
		OUT: A and B
Returns: None
Precondition:  A and B are within bounds of array
Note:  This function is declared inline so the overhead of a 
	   function call is avoided.
************************************************************************/

inline void Swap(int &A, int &B)
{
	int Temp = A;
	A = B;
	B = Temp;
}

/********************  Display BDay Set (Choice 3)  *********************
Action:  Displays one set of 23 random bdays and displays them
		 in chronological order
Parameters:
		IN:  BDaySet array
			 MonthNumber array
		OUT: BDaySet array
			 MonthNumber array
Returns: None
Precondition:  BDaySet and MonthNumber point to an int array
************************************************************************/

void DisplayBDaySet(int BDaySet[], int MonthNumber[])
{
	srand((unsigned int) time(NULL));  // seed random # generator
	GenerateBDaySet(BDaySet);  // create a bday set
	ConvertDayOfYear(BDaySet, MonthNumber);  // converts day of year to corresponding month number

	cout << "\nHere are the results of generating a set of 23 birthdays\n";
	cout << setfill('-') << setw(70) << "-" << "\n";

	for (int i = 0; i < SAMPLE_SIZE; ++i)  // this entire "for loop / switch statement" converts the month
										   // number to a month name and looks for bday matches
	{
		if (i % 3 == 0)  // display no more than 3 dates per line
			cout << endl;

		switch (MonthNumber[i])  // example: "MonthNumber 1" equals "January"
		{
		case 1:	if ((MonthNumber[i] == MonthNumber[i + 1]) && (BDaySet[i] == BDaySet[i + 1]))
				{
					cout << left << setfill(' ') << setw(12) << "(2)January" << right << setw(7) << BDaySet[i] << "     ";
					for (int j = 0; j < SAMPLE_SIZE; ++j)
					{
						MonthNumber[j] = MonthNumber[j + 1];  // increment month subscript so it doesn't print matching bday
						BDaySet[j] = BDaySet[j + 1];  // increment day of month subscript so it doesn't print matching bday
					}
				}
				else
					cout << left << setfill(' ') << setw(12) << "   January" << right << setw(7) << BDaySet[i] << "     ";
				break;
		case 2:	if ((MonthNumber[i] == MonthNumber[i + 1]) && (BDaySet[i] == BDaySet[i + 1]))
				{
					cout << left << setfill(' ') << setw(12) << "(2)February" << right << setw(7) << BDaySet[i] << "     ";
					for (int j = 0; j < SAMPLE_SIZE; ++j)
					{
						MonthNumber[j] = MonthNumber[j + 1];
						BDaySet[j] = BDaySet[j + 1];
					}
				}
				else
					cout << left << setfill(' ') << setw(12) << "   February" << right << setw(7) << BDaySet[i] << "     ";
				break;
		case 3:	if ((MonthNumber[i] == MonthNumber[i + 1]) && (BDaySet[i] == BDaySet[i + 1]))
				{
					cout << left << setfill(' ') << setw(12) << "(2)March" << right << setw(7) << BDaySet[i] << "     ";
					for (int j = 0; j < SAMPLE_SIZE; ++j)
					{
						MonthNumber[j] = MonthNumber[j + 1];
						BDaySet[j] = BDaySet[j + 1];
					}
				}
				else
					cout << left << setfill(' ') << setw(12) << "   March" << right << setw(7) << BDaySet[i] << "     ";
				break;
		case 4:	if ((MonthNumber[i] == MonthNumber[i + 1]) && (BDaySet[i] == BDaySet[i + 1]))
				{
					cout << left << setfill(' ') << setw(12) << "(2)April" << right << setw(7) << BDaySet[i] << "     ";
					for (int j = 0; j < SAMPLE_SIZE; ++j)
					{
						MonthNumber[j] = MonthNumber[j + 1];
						BDaySet[j] = BDaySet[j + 1];
					}
				}
				else
					cout << left << setfill(' ') << setw(12) << "   April" << right << setw(7) << BDaySet[i] << "     ";
				break;
		case 5:	if ((MonthNumber[i] == MonthNumber[i + 1]) && (BDaySet[i] == BDaySet[i + 1]))
				{
					cout << left << setfill(' ') << setw(12) << "(2)May" << right << setw(7) << BDaySet[i] << "     ";
					for (int j = 0; j < SAMPLE_SIZE; ++j)
					{
						MonthNumber[j] = MonthNumber[j + 1];
						BDaySet[j] = BDaySet[j + 1];
					}
				}
				else
					cout << left << setfill(' ') << setw(12) << "   May" << right << setw(7) << BDaySet[i] << "     ";
				break;
		case 6:	if ((MonthNumber[i] == MonthNumber[i + 1]) && (BDaySet[i] == BDaySet[i + 1]))
				{
					cout << left << setfill(' ') << setw(12) << "(2)June" << right << setw(7) << BDaySet[i] << "     ";
					for (int j = 0; j < SAMPLE_SIZE; ++j)
					{
						MonthNumber[j] = MonthNumber[j + 1];
						BDaySet[j] = BDaySet[j + 1];
					}
				}
				else
					cout << left << setfill(' ') << setw(12) << "   June" << right << setw(7) << BDaySet[i] << "     ";
				break;
		case 7:	if ((MonthNumber[i] == MonthNumber[i + 1]) && (BDaySet[i] == BDaySet[i + 1]))
				{
					cout << left << setfill(' ') << setw(12) << "(2)July" << right << setw(7) << BDaySet[i] << "     ";
					for (int j = 0; j < SAMPLE_SIZE; ++j)
					{
						MonthNumber[j] = MonthNumber[j + 1];
						BDaySet[j] = BDaySet[j + 1];
					}
				}
				else
					cout << left << setfill(' ') << setw(12) << "   July" << right << setw(7) << BDaySet[i] << "     ";
				break;
		case 8:	if ((MonthNumber[i] == MonthNumber[i + 1]) && (BDaySet[i] == BDaySet[i + 1]))
				{
					cout << left << setfill(' ') << setw(12) << "(2)August" << right << setw(7) << BDaySet[i] << "     ";
					for (int j = 0; j < SAMPLE_SIZE; ++j)
					{
						MonthNumber[j] = MonthNumber[j + 1];
						BDaySet[j] = BDaySet[j + 1];
					}
				}
				else
					cout << left << setfill(' ') << setw(12) << "   August" << right << setw(7) << BDaySet[i] << "     ";
				break;
		case 9:	if ((MonthNumber[i] == MonthNumber[i + 1]) && (BDaySet[i] == BDaySet[i + 1]))
				{
					cout << left << setfill(' ') << setw(12) << "(2)September" << right << setw(7) << BDaySet[i] << "     ";
					for (int j = 0; j < SAMPLE_SIZE; ++j)
					{
						MonthNumber[j] = MonthNumber[j + 1];
						BDaySet[j] = BDaySet[j + 1];
					}
				}
				else
					cout << left << setfill(' ') << setw(12) << "   September" << right << setw(7) << BDaySet[i] << "     ";
				break;
		case 10:	if ((MonthNumber[i] == MonthNumber[i + 1]) && (BDaySet[i] == BDaySet[i + 1]))
				{
					cout << left << setfill(' ') << setw(12) << "(2)October" << right << setw(7) << BDaySet[i] << "     ";
					for (int j = 0; j < SAMPLE_SIZE; ++j)
					{
						MonthNumber[j] = MonthNumber[j + 1];
						BDaySet[j] = BDaySet[j + 1];
					}
				}
					else
						cout << left << setfill(' ') << setw(12) << "   October" << right << setw(7) << BDaySet[i] << "     ";
				break;
		case 11:	if ((MonthNumber[i] == MonthNumber[i + 1]) && (BDaySet[i] == BDaySet[i + 1]))
				{
					cout << left << setfill(' ') << setw(12) << "(2)November" << right << setw(7) << BDaySet[i] << "     ";
					for (int j = 0; j < SAMPLE_SIZE; ++j)
					{
						MonthNumber[j] = MonthNumber[j + 1];
						BDaySet[j] = BDaySet[j + 1];
					}
				}
					else
						cout << left << setfill(' ') << setw(12) << "   November" << right << setw(7) << BDaySet[i] << "     ";
				break;
		case 12:	if ((MonthNumber[i] == MonthNumber[i + 1]) && (BDaySet[i] == BDaySet[i + 1]))
				{
					cout << left << setfill(' ') << setw(12) << "(2)December" << right << setw(7) << BDaySet[i] << "     ";
					for (int j = 0; j < SAMPLE_SIZE; ++j)
					{
						MonthNumber[j] = MonthNumber[j + 1];
						BDaySet[j] = BDaySet[j + 1];
					}
				}
					else
						cout << left << setfill(' ') << setw(12) << "   December" << right << setw(7) << BDaySet[i] << "     ";
				break;
		}
	}
	cout << "\n\n" << setfill('-') << setw(70) << "-" << "\n\n\n";
}

/*********************  Convert Day of Year ****************************
Action:  Determines what month a day falls on with "DaysInMonth function"
Parameters:
		IN:  BDaySet
			 MonthNumber
		OUT: BDaySet
			 MonthNumber
Returns: None
Precondition:  BDaySet and MonthNumber point to an int array
************************************************************************/

void ConvertDayOfYear(int BDaySet[], int MonthNumber[])  // for case 3: BDaySet indexes are
														 // random, sorted, then will be specific
														 // to day of that month
{
	int Month = 1;
	for (int i = 0; i < SAMPLE_SIZE; ++i)
	{
		while (BDaySet[i] > DaysInMonth(Month))  // compares day number to the number of days in each month
		{
			BDaySet[i] = BDaySet[i] - DaysInMonth(Month);  // dwindling down to the corresponding month number of that day
			Month++;
		}
		MonthNumber[i] = Month;  // input month numbers into array in ascending order
		Month = 1;
	}
}

/**********************  Days in Month *********************************
Action:  Returns month number to ConvertDayOfYear function
Parameters:
		IN:  MonthNumber
Returns: How many days this round of month has
Precondition:  MonthNumber is one of the actual month numbers
************************************************************************/

int DaysInMonth(int MonthNumber)
{
	switch (MonthNumber)
	{
	case 2:  return 28; // February
		break;
	case 4:
	case 6:
	case 9:
	case 11: return 30;  // 30 day months
		break;
	default: return 31;  // 31 day months
	}
}