//-------------------------------------------------------------------------------------------------
//Author:	   Jason McMullen
//Due Date:    3/25/14
//Program:	   Lab6
//Description: 
//-------------------------------------------------------------------------------------------------
#include <fstream>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <math.h>
#include <cmath>
#include <string>
using namespace std;

static const double PI = 3.14159;
static const int MAX_LENGTH = 20;
//-------------------------------------------------------------------------------------------------
void readOperation(const char readLine[MAX_LENGTH], int& index, ifstream& input, 
	ofstream& output);
void arithmetic(const char readLine[MAX_LENGTH], char operation, int& index, ifstream& input, ofstream& output);
int getTotalWords(const char currentLine[MAX_LENGTH]);
void readNumber(const char readLine[MAX_LENGTH], double numArray[2], int& index, ifstream& input);
void trigFunction(const char readLine[MAX_LENGTH], char operation, int& index, ifstream& input, ofstream& output);
void modeToPrint(const char readLine[MAX_LENGTH], char next, ofstream& output);
void cleanToNext(const char readLine[MAX_LENGTH], char currentLine[MAX_LENGTH], ifstream& input);

int main(){
	char readLine[MAX_LENGTH];
	int index = 0;
	
	ifstream input;
	input.open("PFN.txt");
	if (input.fail())	//check to see if the input file is there, if it isnt then
		exit(1);		//close this program instantly
	ofstream output;
	output.open("Output.txt");
	
	while (input.getline(readLine, MAX_LENGTH)){
		readOperation(readLine, index, input, output);
	}//end while loop
	
	input.close();
	output.close();
	system("pause");
	return 0;
}//end main

void readOperation(const char readLine[MAX_LENGTH], int& index, ifstream& input, ofstream& output){
	char next = readLine[0];
	
	while (next != '\n'){
		if (isalpha(next)){
			if (next == 'S' || next == 'T' || next == 'C'){
				trigFunction(readLine, next, index, input, output);
				index = 1;
			}
			else
				modeToPrint(readLine, next, output);
		}
		else if (isprint(next)){
			arithmetic(readLine, next, index, input, output);
			index = 1;
		}
		input.get(next);
	}
}

void readNumber(const char readLine[MAX_LENGTH], double numArray[2], int& index, ifstream& input){
	double answer = 0;
	int i = 0, j = 0;
	char digit[MAX_LENGTH];
	char next;
	input.get(next);
	input.get(next);

	for (int k = 1; k < (strlen(readLine) - 1); k++){
		if (isdigit(next) || ispunct(next)){
			digit[i] = next;
			cout << digit[i] << " " << endl;
			i++;
			input.get(next);
		}//end if
		else if (isspace(next)){
			digit[i] = '\0';
			answer = atof(digit);
			numArray[j] = answer;
			j++;
			while (isspace(next)){
				input.get(next);
				i = 0;
			}//end while
		}//end else if
	}//end for
}//end readNumber Function

void arithmetic(const char readLine[MAX_LENGTH], char operation, int& index, ifstream& input, ofstream& output) {
	double numArray[2];
	readNumber(readLine, numArray, index, input);
	double numberOne = numArray[0];
	double numberTwo = numArray[1];
	cout << numArray[0] << " " << numArray[1] << endl;
	double answer;
	switch (operation) {
		case '+':
			answer = numberOne + numberTwo;
			output << "+ " << numberOne << " " << numberTwo;
			break;
		case '-':
			answer = numberOne - numberTwo;
			output << "- " << numberOne << " " << numberTwo;
			break;
		case '*':
			answer = numberOne * numberTwo;
			output << "* " << numberOne << " " << numberTwo;
			break;
		case '/':
			answer = numberOne / numberTwo;
			output << "/ " << numberOne << " " << numberTwo;
			break;
		case '%':
			answer = static_cast<int>(numberOne) % static_cast<int>(numberTwo);
			break;
		case '^':
			answer = pow(numberOne, numberTwo);
			break;
		default:
			answer = 0;
			break;
	}//end switch
	output << "      " << answer << endl;
}//end arthmetic Function

void trigFunction(const char readLine[MAX_LENGTH], char operation, int& index, ifstream& input, ofstream& output) {
	double numArray[1];
	readNumber(readLine, numArray, index, input);
	double number = numArray[0];
	double answer;
	switch (operation) {
		case 'S':
			answer = sin(PI*number/180);
			cout << "S" << number;
			break;
		case 'C':
			answer = cos(PI*number/180);
			cout << "C" << number;
			break;
		case 'T':
			answer = tan(PI*number/180);
			output << "T" << number;
			break;
		default:
			answer = 0;
			break;
	}//end switch
	output << "     " << answer << endl;
}//end trigFunction Function

void modeToPrint(const char readLine[MAX_LENGTH], char next, ofstream& output) {
	switch (next) {
		case 'e':
		case 'E':
			output << "E" << std::scientific << endl;
			break;
		case 'f':
		case 'F':
		default:
			output << "F" << std::fixed << endl;
	}//end switch
}//end modeToPrint function