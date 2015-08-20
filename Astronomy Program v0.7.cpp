/* University of Hawaii at Hilo Astronomy COSMOS Project Program

// The purpose of this script allows the user to search through any given Galaxy dataset separated by tabs in sets of '	' or '		'
//	Once the program has sorted the row of data from the given data set, it then searches through based off user inputs and search requirements.
//	If the search requirements match then the specific user defined data is output into a new file.


//~  * Copyright (c) 2015, Brandon Hendricks
//~  *All rights reserved.
//~  *
//~  *Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//~  *
//~     * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//~     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation 
//~			and/or other materials provided with the distribution.
//~     * Neither the name of the  Gregory Hendrickson nor the names of its contributors may be used to endorse or promote products derived from this software 
//~			without specific prior written permission.

//~  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
//~		THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS 
//~		BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
//~		GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
//~		LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;


// Function which gets the amount of column numbers in the first row and returns the line, column number, & dataSet
void getColNum(string &line, int &colNumber, ifstream &dataSet)
{
	getline(dataSet, line);	// Grabs the first line of the data set and puts a string value into the variable line
	vector<string> rowArray;	// Initializes a vector  to use with counting the amount of columns
	stringstream row(line);		// Converts the string variable into a set of data which works with more functions.
	string field;				// Place holder for values to be put into here

	while (!row.eof())			// While the row of data still has data in it, repeat the process.
	{
		row >> field;			// Take the first data in the row delete it, and transfer that data into the variable field.
		rowArray.push_back(field);	// Take the data in the variable field and add it to a new / end of the current vector list
	}
	colNumber = rowArray.size();	// The size of the vector list is then registered as the amount of column numbers throughout the data set.
}

// Function which handles all the collection of user input in order to run the program.
void setup(int &colNum, string &line, string &inFile, string &outFile, ifstream &dataSet, ofstream &outputFile, int &numOfComparisons, int &outputColNum)
{
	int choice;		// Variable thats used for user input

	cout << "Enter the path and data file name (Ex: 'D:\ sample.txt'): "; //ie, D:\sample.txt
	cin >> inFile;	// User enters a file path to the data set. Ex: ("C:\Users\Student\Desktop\SampleData.tbl");
	
	dataSet.open(inFile.c_str());	// Opens an instream to the specified file path.
	while (dataSet.fail())	// While the specified data set fails to open, the program runs through these options.
	{
		system("CLS");		// Clears the screen.
		cout << "Sorry, Failed to open with specified file path. Would you like to:" << endl;
		cout << " 1.) Enter a new file path." << endl;
		cout << " 2.) Exit the program." << endl;
		cout << "Enter '1' or '2': ";
		while (!(cin >> choice) || choice < 0)	// If theres no errors in choice
		{										// Takes the users input and uses it to select an option
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("CLS");		// Clears the screen.
			cout << "Error Wrong Input Type. Would you like to:" << endl;
			cout << " 1.) Enter a new file path." << endl;
			cout << " 2.) Exit the program." << endl;
			cout << "Enter '1' or '2': ";
		}

		switch (choice)		// Switch choice which determines the option selected based off user input
		{
		case 1:		// First option which lets you enter a new file path.
			system("CLS");		// Clears the screen.
			cout << "Enter the path and data file name (Ex: 'D:\ sample.txt'): "; //ie, D:\sample.txt
			cin >> inFile;	// User enters a file path to the data set. Ex: ("C:\Users\Student\Desktop\SampleData.tbl");
			break;	// breaks out of the switch statement.

		case 2:		// Second option which lets you exit the program
			system("CLS");				// Clears the screen.
			cout << "Now Exiting, ";
			outputFile.close();			// Closes the connection to outputFile
			dataSet.close();			// Closes the connection to dataSet
			system("pause");			// Pauses the program to let the user know it has finally exited.
			exit(1);					// Closes the program
			break;	// breaks out of the switch statement.

		default:	// Returns the program back to the beginning of the loop
			system("CLS");
			cout << "That was not a valid option, ";
			system("pause");
			break;	// breaks out of the switch statement.
		}
	}

	cout << "Enter your output file name (Ex: 'output.txt'): ";
	cin >> outFile;	// User enters a outputfile name and type, ie "Output.tbl"
	outputFile.open(outFile);		// Opens a connection to the output file


	// This section allows the user to specify how many lines of code they would like to skip in the file in the beginning of the program
	cout << "Enter # of lines to skip at beginning of Data Set: ";
	while (!(cin >> choice) || (choice < 0))	// If theres no errors in choice
	{
		cin.clear();			// Clears the current input value of cin
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("CLS");
		cout << "Error - Wrong input type." << endl;
		cout << "Enter # of lines to skip at beginning of Data Set (Non-Negative Integers): ";
	}
	for (int i = 0; i < choice; i++)	// Loops through the number of rows in the beginning of the data set specified by the user to skip
		getline(dataSet, line);			// Skips a number of lines based off of the number of rows the user chose.

	getColNum(line, colNum, dataSet);	// Automatically gets the column Number in the dataset

	system("CLS");			// Clears the Screen
	cout << "Total amount of columns found: " << colNum << endl;
	cout << "Enter the # of columns being stored in the output file (Ex: 1, 2, 4 = 3): ";
	while (!(cin >> outputColNum) || (outputColNum < 2)) // While input is not integers and less than 2, repeat asking for input
	{
		cin.clear();		// Clears cin input preventing looping error
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error - Wrong input type." << endl;
		cout << "Enter at least 2 columns being stored in the output file (Ex: 1, 2, 4 = 3): ";
	}

} // End setup()

// Function which lists the available choices of comparison options
void comparisonMenu(int &numOfComparisons, vector< vector <double> > &compareArray)
{
	int choice;		// Variable int declared which is used for user's choice input

	// Loops through a series of options n times depending on how many comparisons the user wanted to do.
	for (int i = 0; i < numOfComparisons; i++)
	{
		cout << "List of comparison types to choose from:" << endl;
		cout << "	1 - variable < value" << endl;
		cout << "	2 - variable > value" << endl;
		cout << "	3 - variable = value" << endl;
		cout << "	4 - variable - variable" << endl;
		cout << "	5 - value < variable < value" << endl;
		cout << "	6 - value > variable < value" << endl;
		cout << "	7 - value > variable > value" << endl;
		cout << "	8 - result[ variable - variable] < value" << endl;
		cout << "	9 - result[ variable - variable] > value" << endl;
		cout << "	10 - value < result[ variable - variable] < value" << endl;
		cout << "	11 - value > result[ variable - variable] < value" << endl;
		cout << "	12 - value > result[ variable - variable] > value" << endl;
		cout << " Enter the type of comparison being done (Ex: 1, 2, 3, etc) : ";

		// If the choice is not between 1-12 loop through the options again.
		while (!(cin >> choice) || (choice < 0 && choice > 13))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("CLS");
			cout << "Error - Wrong input type." << endl << endl;
			cout << "List of comparison types to choose from:" << endl;
			cout << "	1 - variable < value" << endl;
			cout << "	2 - variable > value" << endl;
			cout << "	3 - variable = value" << endl;
			cout << "	4 - variable - variable" << endl;
			cout << "	5 - value < variable < value" << endl;
			cout << "	6 - value > variable < value" << endl;
			cout << "	7 - value > variable > value" << endl;
			cout << "	8 - result[ variable1 - variable2] < value" << endl;
			cout << "	9 - result[ variable1 - variable2] > value" << endl;
			cout << "	10 - value < result[ variable1 - variable2] < value" << endl;
			cout << "	11 - value > result[ variable1 - variable2] < value" << endl;
			cout << "	12 - value > result[ variable1 - variable2] > value" << endl;
			cout << " Enter the type of comparison being done (Ex: 1, 2, 3, etc) : ";
		}
		compareArray[i][0] = choice;	// Store the desired users option choice in the compare array.

		system("CLS");

		// Switch based option which auto selects the users choice based off their selection of 1-12 any other numbers resets the loop
		switch (choice)
		{
		case 1:		// Option 1: variable < value
			cout << "Enter the column and value thats being compared to each other: column[variable] < value" << endl;
			cout << " Column: ";
			cin >> compareArray[i][1];
			cout << " Value: ";
			cin >> compareArray[i][2];
			break;

		case 2:		// Option 2:  variable > value
			cout << "Enter the inputs being compared to each other: column[variable] > value" << endl;
			cout << " Column: ";
			cin >> compareArray[i][1];
			cout << " Value: ";
			cin >> compareArray[i][2];
			break;

		case 3:		// Option 3: variable = value
			cout << "Enter the inputs being compared to each other: column[variable] = value" << endl;
			cout << " Column: ";
			cin >> compareArray[i][1];
			cout << " Value: ";
			cin >> compareArray[i][2];
			break;

		case 4:		// Option 4: variable - variable
			cout << "Enter the inputs being compared to each other: column[variable1] - column[variable2]" << endl;
			cout << " Column 1: ";
			cin >> compareArray[i][1];
			cout << " Column 2: ";
			cin >> compareArray[i][2];
			break;

		case 5:		// Option 5: value < variable < value
			cout << "Enter the inputs being compared to each other: value < column[variable] < value" << endl;
			cout << " Value: ";
			cin >> compareArray[i][1];
			cout << " Column: ";
			cin >> compareArray[i][2];
			cout << " Value: ";
			cin >> compareArray[i][3];
			break;

		case 6:		// Option 6: value > variable < value
			cout << "Enter the inputs being compared to each other: value > column[variable] < value" << endl;
			cout << " Value: ";
			cin >> compareArray[i][1];
			cout << " Column: ";
			cin >> compareArray[i][2];
			cout << " Value: ";
			cin >> compareArray[i][3];
			break;

		case 7:		// Option 7: value > variable > value
			cout << "Enter the inputs being compared to each other: value > column[variable] > value" << endl;
			cout << " Value: ";
			cin >> compareArray[i][1];
			cout << " Column: ";
			cin >> compareArray[i][2];
			cout << " Value: ";
			cin >> compareArray[i][3];
			break;

		case 8:		// Option 8: result( variable - variable) < value
			cout << "Enter the inputs being compared to each other: result(column[1] - column[2]) < value" << endl;
			cout << " Column 1: ";
			cin >> compareArray[i][1];
			cout << " Column 2: ";
			cin >> compareArray[i][2];
			cout << " Value: ";
			cin >> compareArray[i][3];
			break;

		case 9:		// Option 9: result( variable - variable) > value
			cout << "Enter the inputs being compared to each other: result(column[1] - column[2]) > value" << endl;
			cout << " Column 1: ";
			cin >> compareArray[i][1];
			cout << " Column 2: ";
			cin >> compareArray[i][2];
			cout << " Value: ";
			cin >> compareArray[i][3];
			break;

		case 10:	// Option 10: value < result( variable - variable) < value
			cout << "Enter the inputs being compared to each other: value < result(column[1] - column[2]) < value" << endl;
			cout << " Value: ";
			cin >> compareArray[i][1];
			cout << " Column 1: ";
			cin >> compareArray[i][2];
			cout << " Column 2: ";
			cin >> compareArray[i][3];
			cout << " Value: ";
			cin >> compareArray[i][4];
			break;

		case 11:	// Option 11: value > result( variable - variable) < value
			cout << "Enter the inputs being compared to each other: value > result(column[1] - column[2]) < value" << endl;
			cout << " Value: ";
			cin >> compareArray[i][1];
			cout << " Column 1: ";
			cin >> compareArray[i][2];
			cout << " Column 2: ";
			cin >> compareArray[i][3];
			cout << " Value: ";
			cin >> compareArray[i][4];
			break;

		case 12:	// Option 12: value > result( variable - variable) > value
			cout << "Enter the inputs being compared to each other: value > result(column[1] - column[2]) > value" << endl;
			cout << " Value: ";
			cin >> compareArray[i][1];
			cout << " Column 1: ";
			cin >> compareArray[i][2];
			cout << " Column 2: ";
			cin >> compareArray[i][3];
			cout << " Value: ";
			cin >> compareArray[i][4];
			break;

		}
		system("CLS");			// Clears the screen
	}
}	// End comparisonMenu()

// Function which skips the specified columns of the user
void colSkip(int &colNumSkip, vector<int> &colSkipArray)
{
	int choice;		// variable used for user input

	// This section asks the user the amount of columns they would like to skip
	cout << "Enter the amount of columns to skip in the Data Set: ";
	while (!(cin >> colNumSkip) || (colNumSkip < 0))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		system("CLS");
		cout << "Error - Wrong input type." << endl;
		cout << "Enter the amount of columns to skip in the Data Set (Non-Negative Integers): ";
	}

	// If the amount of columns the user inputs is 1 or more it then stores the specified columns in a vector
	if (colNumSkip > 0)
	{


		// loops n number of times depending on the amount of columns the user input
		cout << "Enter which columns to skip in the Data Set: \n";
		for (int i = 0; i < colNumSkip; i++)
		{
			cout << "	The " << i + 1 << " column to skip: ";
			while (!(cin >> choice) || (choice < 1))	// Loops through the choice of the column so there are no errors
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				system("CLS");
				cout << "Error - Wrong input type, Enter The" << i + 1 << " column to skip: ";
			}
			colSkipArray[choice - 1] = 1;	// Marks the users choice to skip the column in a vector which is then used later in the program
		}
	}
}	// End colSkip()

// Function which analyzes a row which was found to have more than the amount of columns first found in the first row, special analyzing reviews through the line and concatenates separated data.
void analyzeRow(string line, vector<double> &dataArray, vector <int> colSkipArray)
{
	stringstream row(line);	// String stream the line variable to allow input functions

	int arrayPos = 0, pass = 0;		// Variables used to help analyzeRow function
	string arrayTemp, arrayTemp2;

	// For loop which keeps track of the amount of lines in relation to the element size of line iterating through each element
	for (int lineCount = 0; lineCount < line.size(); lineCount++)
	{
		// Checks if the current element has a tab value and the pass variable is allowed
		if (line[lineCount] == '\t' && pass == 0)
		{
			if (line[lineCount + 1] == '\t')	// If a second tab separator is found then the program continues as normally
			{
				if (colSkipArray[arrayPos] == 0)	// If the current array slot is 0 then allow data to be put into the array.
				{
					row >> dataArray[arrayPos];	// Take the next data value of row and input it into the data array
				}
				else		// If the skip array does not find a 0, it skips the column and keeps it at 0.
				{
					row >> arrayTemp;		// Takes string values and puts them into a trash variable so that the program continues to run without errors occuring
				}
				lineCount++;	// Increase lineCount by 1

			}
			else		// If a second tab separator isn't found then the program converts the extra column with the previous one, and then puts it into the array.
			{
				if (colSkipArray[arrayPos] == 0)	// If the current array slot is 0 then allow data to be put into the array.
				{
					row >> arrayTemp >> arrayTemp2;		// Take the next two data values in row and put them into string variables.
					arrayTemp = arrayTemp + arrayTemp2;	// Concatenates the two string values into 1 variable
					dataArray[arrayPos] = atof(arrayTemp.c_str());	// Take the concatenation value and puts it into the current dataArray position.
				}
				else		// If the current array is marked to be skipped the current data value is skiped along with the next that would have been concatenated with it.
				{
					row >> arrayTemp >> arrayTemp;		// Takes string values and puts them into a trash variable so that the program continues to run without errors occuring
					if (arrayPos == 0 || arrayPos == 1) // Special case where the beginning of the dataset will be increased by one to offset the rest of the data set structure.
						arrayPos++;		// Increase the current array position by 1
				}
				pass++;		// Increases the amount of times the program will skip a tab
			}
			arrayPos++;		// Increase the current array position by 1.
		}
		else if (line[lineCount] == '\t' && pass > 0)		// checks to see if a current string char is a tab, if it is and pass is greater than 0
			pass--;			// Reduce the amount of times to pass by a tab char by 1
	}
}	// End analyzeRow()

// Function which takes users compare choices and uses them to analyze the current row data, if any of the of the statements arn't true they return false, other wise if they 
bool compareRow(vector< vector <double> > compare, vector<double> data)
{
	int value;	// variable which is used to determine the option to select based off the users choice for this option.
	for (int i = 0; i < compare.size(); i++)	// For loop which iterates through int i based off of the amount of compare options the user selected
	{
		value = compare[i][0];	// Value is set to the users option selection which was stored in the 2d vectors 
		switch (value)	// Switch function which uses value variable to as the option selector
		{
		case 1:	// variable < value
			if (!(data[compare[i][1] - 1] < compare[i][2]))
				return false;
			break;

		case 2:	// variable > value
			if (!(data[compare[i][1] - 1] > compare[i][2]))
				return false;
			break;

		case 3:	// variable = value
			if (!(data[compare[i][1] - 1] == compare[i][2]))
				return false;
			break;

		case 4:	// variable - variable
			if (!(data[compare[i][1] - 1] - data[compare[i][2] - 1]))
				return false;
			break;

		case 5:	// value < variable < value
			if (!(compare[i][1] < data[compare[i][2] - 1] && data[compare[i][2] - 1] < compare[i][3]))
				return false;
			break;

		case 6:	// value > variable < value
			if (!(data[compare[i][2] - 1] > compare[i][1] && data[compare[i][2] - 1] < compare[i][3]))
				return false;
			break;

		case 7:	// value > variable > value
			if (!(compare[i][1] > data[compare[i][2] - 1] && data[compare[i][2] - 1] > compare[i][3]))
				return false;
			break;

		case 8:	// result( variable - variable) < value
			if (!((data[compare[i][1] - 1] - data[compare[i][2] - 1]) < compare[i][3]))
				return false;
			break;

		case 9:	// result( variable - variable) > value
			if (!((data[compare[i][1] - 1] - data[compare[i][2] - 1]) > compare[i][3]))
				return false;
			break;

		case 10:	// value < result( variable - variable) < value
			if (!(compare[i][1] < (data[compare[i][2] - 1] - data[compare[i][3] - 1]) && (data[compare[i][2] - 1] - data[compare[i][3] - 1]) < compare[i][4]))
				return false;
			break;

		case 11:	// value > result( variable - variable) < value
			if (!((data[compare[i][2] - 1] - data[compare[i][3] - 1]) > compare[i][1] && (data[compare[i][2] - 1] - data[compare[i][3] - 1]) < compare[i][4]))
				return false;
			break;

		case 12:	// value > result( variable - variable) > value
			if (!(compare[i][1] > (data[compare[i][2] - 1] - data[compare[i][3] - 1]) && (data[compare[i][2] - 1] - data[compare[i][3] - 1]) > compare[i][4]))
				return false;
			break;
		}
	}
	return true;	// Returns true if all conditions are met
}	// End compareRow()

// Function which goes through the data set row by row analyzing it based off user input then putting the valid data into the user defined output file.
void calculations(string line, ifstream &dataSet, ofstream &outputFile, int colNum, vector<int> colSkipArray, vector<double> dataArray, vector< vector <double> > compareArray, vector<int> outputColArray)
{
	string trash;		// Used for getting rid of error prone data
	system("CLS");		// Clears the screen
	cout << "Processing, ";
	while (!dataSet.eof())	// While the program has not reached the end of the file
	{
		// First row of the dataset was loaded previously to count the amount of colums thus not requiring a new getline here
		stringstream row(line);	// String stream the line variable to allow input functions

		for (int i = 0; i < colNum; i++)	// For loop which goes through the amount of columns the program found and removes the columns the user specified.
		{
			if (colSkipArray[i] == 0)	// If the current array slot is 0 then allow data to be put into the array.
			{
				row >> dataArray[i];	// Take the next data value of row and input it into the data array
			}
			else		// If the skip array does not find a 0, it skips the column and keeps it at 0.
			{
				row >> trash;			// Takes string values and puts them into a trash variable so that the program continues to run without errors occuring
			}
		}

		if (!row.eof())		// Function that checks to see if the current row still has unchecked columns
		{
			analyzeRow(line, dataArray, colSkipArray);		// Calls the analyzeRow function
		}

		if (compareRow(compareArray, dataArray))		// If the compareRow function returns true matching all cases specified by the user
		{
			for (int i = 0; i < outputColArray.size(); i++)		// Loop through the column array values 
			{
				outputFile << dataArray[outputColArray[i] - 1] << "	";		// Stores all columns which the user specified in the output file.
			}
			outputFile << endl;		// Adds a new line to the output file
		}
		getline(dataSet, line);	// Get the next row of the dataSet and put it into the line
	}
}	// End calculations()


int main()
{
	int colNum = 0,			// Keeps track of the amount of columns the input file has
		numOfComparisons,	// Keeps track of the number of comparisons the user wishes to compare on a row
		outputColNum,		// Keeps track of the amount of columns the user wants to store in the output file
		colNumSkip;			// Keeps track of the amount of columns the user wants to skip.

	string line,			// Variable that stores the characters of each row of the dataset
		inFile,				// Variable which is used to store the name of the dataset and file location
		outFile;			// Variable thats used to store the desired output file name.

	ifstream dataSet;		// Initializes an input data variable with is used for the input file. ("C:\Users\Student\Documents\SampleFile.txt");
	ofstream outputFile;	// Initializes an output data variable which is used for the output file.

	setup(colNum, line, inFile, outFile, dataSet, outputFile, numOfComparisons, outputColNum);		// Calls the Setup function with the specified variables.

	vector<int> colSkipArray(colNum, 0);		// Creates a vector list which is used to keep track of which columns to handle skipping
	vector<double> dataArray(colNum);			// Creates a vector list based off the amount of columns input by the user to store all the data in the row
	vector<int> outputColArray(outputColNum);	// Creates an vector list which stores the specific columns which will be written to the output file if they meet the requirements.

	// This section of code asks the user for the amount of columns being stored in the output file
	for (int i = 0; i < outputColNum; i++)
	{
		cout << "Enter the " << i + 1 << " column being stored to the output file (Ex: 2, 3, 7, etc): ";
		cin >> outputColArray[i];		// Takes the users input into the vector outputColArray
	}

	system("CLS");		// Clears the screen

	// This section of code asks the user for the amount of comparisons they would like to do
	cout << "State the number of comparisons that will be calculated: ";
	while (!(cin >> numOfComparisons) || numOfComparisons < 1)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error - State the number of comparisons that will be calculated: ";
	}

	vector< vector <double> > compareArray(numOfComparisons, vector<double>(5));		// Initializes a vector which stores various data for comparing rows vs the user choosen options
	
	comparisonMenu(numOfComparisons, compareArray);			// Calls the Comparison menu using the compare array and the number of comparisons against the row data.

	colSkip(colNumSkip, colSkipArray);		// Calls the column skip function getting how many and which columns the user wants to have the program skip

	
	outputFile << fixed;	// Sets the output data to decimal rather than scientific

	calculations(line, dataSet, outputFile, colNum, colSkipArray, dataArray, compareArray, outputColArray);		// Calls the calculations function to sort through the data set an analyze all the rows

	outputFile.close();			// Closes access to the file stream.
	dataSet.close();			// Closes the dataset to free up extra ram the program was using.
	system("pause");			// Pauses the program for the user to see the program is done.
	return 0;					// Ends the program
}