//-------------------------------------------------------------------------------------------------
//Author:	   Jason McMullen and Arthur Lunn
//Due Date:	   4/1/14
//Program:	   Lab6
//Description: This program will read in input from a txt file, analyze the data, and perform 
//			   mathematical opereations on the set of numbers following the character identifing
//			   the operation to be used. The input file needs to be organized in such a way that 
//			   the first character of each line will be the operator needed to be preformed on the
//			   follwing numbers, if no numbers are found on the same line then it is assumed that
//			   the leading character will changed the notation in which decimals are displayed. 
//			   The program does all of this by saving each line of the input file in a cstring
//			   array. All output for this program will be displayed on the terminal.
//-------------------------------------------------------------------------------------------------
#define _USE_MATH_DEFINES
#include <fstream>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <math.h>
#include <cmath>
#include <string>
using namespace std;

static const double PI = M_PI;		//constant to represent our approx. value for PI
static const int MAX_LENGTH = 30;		//the length of the cstring array

//-------------------------------------------------------------------------------------------------
//readOperation: This function will read the char at the first index in the cstring array and 
//				 determine the appropriate mathematical operation to be perfromed on the given
//				 numerical values, located in the same cstring following the operation marker.
//				 After determining the operation, the function will pass control of the program
//				 to the corresponding function to perform the operation.
//
//Precondition:  This function needs the cstring array and the object of ifstream type sent to it.
//Postcondition: This program will not return anything.
//-------------------------------------------------------------------------------------------------
void readOperation(const char readLine[MAX_LENGTH], ifstream& input);

//-------------------------------------------------------------------------------------------------
//arithmetic:    This function will perform the basic arithmetic operations on the two values sent
//				 to it and then ouput the result. The function will use a switch statement to
//				 determine what operation will be performed based on the char in the first index
//				 of the cstring array.
//
//Precondition:  The function will need the cstring, the char at the first index of the cstring
//				 array, and the index of the cstring.
//Postcondition: The function will not return anything, but it will output the results of the 
//				 operation.
//-------------------------------------------------------------------------------------------------
void arithmetic(const char readLine[MAX_LENGTH], char operation, int& index);

//-------------------------------------------------------------------------------------------------
//readNumber:	 This function will find all of the numbers remaining in the cstring array, store
//				 them in a new cstring array and then convert those cstrings into doubles. It will
//				 then store those doubles into an array of doubles that the calling function has
//				 access to. This function uses the cleanToNext function to take care of the white
//				 spaces separating the numbers.
//
//Precondition:	 This function will require the cstring array, the array of type double, and the 
//				 current index of the cstring array.
//Postcondition: This function will not return anything.
//-------------------------------------------------------------------------------------------------
void stringToDouble(const char readLine[MAX_LENGTH], double numArray[2], int& index);

//-------------------------------------------------------------------------------------------------
//trigFunction:  This function will view the char holding the value that stands for the operation
//				 needed to be performed. Using a switch statement, the function will match this
//				 char with 'S', 'C', and 'T' and after finding the matching char, that trig
//				 function will be selected. The function will then call readNumber to determine
//				 the degree value that is within the cstring array. After recieving the value,
//				 double is then converted from degree to radians using the following formula:
//										PI(number)/180.
//				 The function will then do the trig operation on the radian and finally output the
//				 solution. 
//
//Precondition:  The function requires the cstring, first char in the cstring and the current
//				 index of the cstring array to be sent to it.
//Postcondition: The function will not return anything, but will change the value of the index
//			 for the calling function.
//-------------------------------------------------------------------------------------------------
void trigFunction(const char readLine[MAX_LENGTH], char operation, int& index);

//-------------------------------------------------------------------------------------------------
//modeToPrint:   This function will change the way decimal values are represented. A switch 
//				 statement will check the char sent from readOperation and determine which decimal
//			     structure should be used to print doubles. If an 'e' or 'E' is found, decimals
//				 will be displayed in scientific notation. If a 'f' or 'F' is found, decimals will
//				 be displayed with a fixed number of digits.
//
//Precondition:  The function requires the char read from the first index of the 
//				 cstring. If ch isn't 'e' 'E' 'f' or 'F' the method will default
//				 to fixed point notation.
//
//Postcondition: The function will not return anything. It will however, change the way all other
//				 functions will print double variables.
//-------------------------------------------------------------------------------------------------
void modeToPrint(char ch);

//-------------------------------------------------------------------------------------------------
//cleanToNext:	the function returns  the index of the next operand or operation
//				the function cleans all the white spaces, and returns the index where the 
//				next operand or operator starts 
//
//Precondition: Index must be within the bounds of str[].
//Postcondition:Changes the index value to the index of the next non-whitespace character.
//				If there is no non-whitespace character left returns -1.
//-------------------------------------------------------------------------------------------------
void cleanToNext(const char str[], int& index);

//-------------------------------------------------------------------------------------------------
//main:			 The main function will drive the program and make all of the necessary function
//				 calls. It also has the responsibility of making a connection with the input txt
//				 file and reading in the entire document line by line.
//
//Precondition:  main does not require anything to be sent to it for it to run.
//Postcondition: This function will return the value 0 letting the system know the program has
//				 finished.
//-------------------------------------------------------------------------------------------------

int main(){
	char readLine[MAX_LENGTH];//cstring array to hold, line by line, the contents of the txt file
	ifstream input;			  //ifstream to read in input
	
	input.open("PFN.txt");
	if (input.fail())		  //check to see if the input file is there, if it isnt then
		exit(1);			  //close this program instantly

	while (!(input.eof())){	  //continue reading the file until empty
		input.getline(readLine, MAX_LENGTH);
		readOperation(readLine, input);
	}//end while loop

	input.close();			  //close the input file
	system("pause");		  //pause to view results
	return 0;
}//end main

//-------------------------------------------------------------------------------------------------
//readOperation: This function will read the char at the first index in the cstring array and 
//				 determine the appropriate mathematical operation to be perfromed on the given
//				 numerical values, located in the same cstring following the operation marker.
//				 After determining the operation, the function will pass control of the program
//				 to the corresponding function to perform the operation.
//
//Precondition:  This function needs the cstring array and the object of ifstream type sent to it.
//Postcondition: This program will not return anything.
//-------------------------------------------------------------------------------------------------
void readOperation(const char readLine[MAX_LENGTH], ifstream& input){
	int index = 0;  //the current index in readLine
	cleanToNext(readLine, index);
	char next = readLine[index];

	if (isalpha(next)){			               //if char of alpha type (some type of letter)
		if (next == 'S' || next == 'T' || next == 'C'){		//for trig types
			trigFunction(readLine, next, index);
		}
		else{
			modeToPrint(next);	  //all remaining alpha types
		}
	}
	else if (isprint(next) || (next == '')){ //if char of print type (punctuation)
		arithmetic(readLine, next, index);
	}
	index++;
	next = readLine[index];
}


//-------------------------------------------------------------------------------------------------
//stringToDouble:This function will find all of the numbers remaining in the cstring array, store
//				 them in a new cstring array and then convert those cstrings into doubles. It will
//				 then store those doubles into an array of doubles that the calling function has
//				 access to. This function uses the cleanToNext function to take care of the white
//				 spaces separating the numbers.
//
//Precondition:	 This function will require the cstring array, the array of type double, and the 
//				 current index of the cstring array.
//Postcondition: This function will not return anything.
//-------------------------------------------------------------------------------------------------
void stringToDouble(const char readLine[MAX_LENGTH], double numArray[2], int& index){
	double answer = 0;		//stores the solution of the cast that will be stored in the new array
	int j = 0;				//the index of numArray[] to store the next double value to
	string digits = "";     //the string values of the double as its built

	for (unsigned int k = 0; (j != 2) && (k < (strlen(readLine) - 1)); k++){
		if (isdigit(readLine[k]) || (readLine[k] == '.')){
			digits += readLine[k];
			if (!(isdigit(readLine[k + 1]) || (readLine[k + 1] == '.'))){
				answer = atof(digits.c_str());
				numArray[j++] = answer;
				digits = "";
			}
		}//end if
	}//end for
}//end stringToDouble Function

//-------------------------------------------------------------------------------------------------
//arithmetic:    This function will perform the basic arithmetic operations on the two values sent
//				 to it and then ouput the result. The function will use a switch statement to
//				 determine what operation will be performed based on the char in the first index
//				 of the cstring array.
//
//Precondition:  The function will need the cstring, the char at the first index of the cstring
//				 array, and the index of the cstring.
//Postcondition: The function will not return anything, but it will output the results of the 
//				 operation.
//-------------------------------------------------------------------------------------------------
void arithmetic(const char readLine[MAX_LENGTH], char operation, int& index) {
	double numArray[2];		//array that will hold the two numerical values still in the cstring
	stringToDouble(readLine, numArray, index);
	double numberOne = numArray[0];	//take the first number out of the first index
	double numberTwo = numArray[1]; //take the second number out of the second index
	double answer;					//holds the solution to the operation
	switch (operation) {			//switch to figure out the operation that will be used
	case '+':						//case '+'
		answer = numberOne + numberTwo;
		std::cout << "+ " << numberOne << " " << numberTwo;
		break;
	case '-':						//case '-'
		answer = numberOne - numberTwo;
		std::cout << "- " << numberOne << " " << numberTwo;
		break;
	case '':
	case '*':						//case '*'
		answer = numberOne * numberTwo;
		std::cout << "* " << numberOne << " " << numberTwo;
		break;
	case '/':						//case '/'
		if (numberTwo != 0){ //check to make sure the universe didnt implode
			answer = numberOne / numberTwo;
			std::cout << "/ " << numberOne << " " << numberTwo;
		}//end if
		else{
			answer = 12358132134;				//just saved the universe
			std::cout << "Can not divide by zero." << endl;
		}//end else
		break;
	case '%':						//case '%'
		answer = static_cast<int>(numberOne) % static_cast<int>(numberTwo);
		std::cout << "% " << numberOne << " " << numberTwo;
		break;
	case '^':						//case '^'
		std::cout << "^ " << numberOne << " " << numberTwo;
		answer = pow(numberOne, numberTwo);
		break;
	default:						//default, just ouput 0
		answer = 0;
		break;
	}//end switch
	if (answer != 12358132134)		//do not want to print 0.00 when divide by 0
		std::cout << "\t" << answer << endl;
}//end arthmetic Function

//-------------------------------------------------------------------------------------------------
//trigFunction:  This function will view the char holding the value that stands for the operation
//				 needed to be performed. Using a switch statement, the function will match this
//				 char with 'S', 'C', and 'T' and after finding the matching char, that trig
//				 function will be selected. The function will then call stringToDouble to determine
//				 the degree value that is within the cstring array. After recieving the value,
//				 double is then converted from degree to radians using the following formula:
//										PI(number)/180.
//				 The function will then do the trig operation on the radian and finally output the
//				 solution. 
//
//Precondition:  The function requires the cstring, first char in the cstring and the current
//				 index of the cstring array to be sent to it.
//Postcondition: The function will not return anything, but will change the value of the index
//				 for the calling function.
//-------------------------------------------------------------------------------------------------
void trigFunction(const char readLine[MAX_LENGTH], char operation, int& index) {
	double numArray[1];						    //array to hold the converted double
	stringToDouble(readLine, numArray, index);  //find the number still in the cstring
	double number = numArray[0];			    //retrieve that double
	double radian = (number * PI / 180);		//convert from degrees to radians
	double answer;								//holds the solution to the trig operation
	switch (operation) {
	case 'S':									//Sine
		answer = sin(radian);
		std::cout << "S " << number;
		break;
	case 'C':									//Cosine
		answer = cos(radian);
		std::cout << "C " << number;
		break;
	case 'T':									//Tangent
		answer = tan(radian);
		std::cout << "T " << number;
		break;
	default:
		answer = 0;
		break;
	}//end switch
	std::cout << "\t" << answer << endl;
}//end trigFunction Function

//-------------------------------------------------------------------------------------------------
//modeToPrint:   This function will change the way decimal values are represented. A switch 
//				 statement will check the char sent from readOperation and determine which decimal
//			     structure should be used to print doubles. If an 'e' or 'E' is found, decimals
//				 will be displayed in scientific notation. If a 'f' or 'F' is found, decimals will
//				 be displayed with a fixed number of digits.
//
//Precondition:  The function requires the char read from the first index of the 
//				 cstring. If ch isn't 'e' 'E' 'f' or 'F' the method will default
//				 to fixed point notation.
//
//Postcondition: The function will not return anything. It will however, change the way all other
//				 functions will print double variables.
//-------------------------------------------------------------------------------------------------
void modeToPrint(char ch) {
	switch (ch) {
	case 'e':
	case 'E':	//Change the print mode to scientific notation
		std::cout.unsetf(ios::fixed);
		std::cout << "E" << std::scientific << endl;
		break;
	case 'f':
	case 'F':	//Change the print mode to fixed point notation
	default:
		std::cout.unsetf(ios::scientific);
		std::fixed;
		std::cout.setf(ios::showpoint);
		std::cout.precision(2);
		std::cout << "F" << endl;
	}//end switch
}//end modeToPrint function


//-------------------------------------------------------------------------------------------------
//cleanToNext:	the function returns  the index of the next operand or operation
//				the function cleans all the white spaces, and returns the index where the 
//				next operand or operator starts 
//
//Precondition: Index must be within the bounds of str[]. str[] must contain a non-whitespace
//				char or the method will create an array out of bounds error.
//
//Postcondition:Changes the index value to the index of the next non-whitespace character.
//-------------------------------------------------------------------------------------------------
void cleanToNext(const char str[], int& index){
	while (isspace(str[index])){ index++; }
}
