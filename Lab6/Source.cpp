//-------------------------------------------------------------------------------------------------
//Author: Jason McMullen and Arthur Lunn
//Due Date: 4/1/14
//Program: Lab6
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
static const int MAX_LENGTH = 30;
//-------------------------------------------------------------------------------------------------
void readOperation(const char readLine[MAX_LENGTH], ifstream& input);
void arithmetic(const char readLine[MAX_LENGTH], char operation, int& index);
int getTotalWords(const char currentLine[MAX_LENGTH]);
void readNumber(const char readLine[MAX_LENGTH], double numArray[2], int& index);
void trigFunction(const char readLine[MAX_LENGTH], char operation, int& index);
void modeToPrint(const char readLine[MAX_LENGTH], char next);
void cleanToNext(const char readLine[MAX_LENGTH], char currentLine[MAX_LENGTH]);

int main(){
	char readLine[MAX_LENGTH];
	int index = 0;

	ifstream input;
	input.open("PFN.txt");
	if (input.fail())	//check to see if the input file is there, if it isnt then
		exit(1);	//close this program instantly

	while (!(input.eof())){
		input.getline(readLine, MAX_LENGTH);
		readOperation(readLine, input);
	}//end while loop

	input.close();
	system("pause");
	return 0;
}//end main

void readOperation(const char readLine[MAX_LENGTH], ifstream& input){
	int doContinue = 0;
	int index = 0;
	char next = readLine[index];

	while (doContinue != 1){
		std::cout << index;
		if (isalpha(next)){
			if (next == 'S' || next == 'T' || next == 'C'){
				trigFunction(readLine, next, index);
				doContinue = 1;
			}
			else{
				modeToPrint(readLine, next);
				doContinue = 1;
			}
		}
		else if (isprint(next) || (next == '•')){
			arithmetic(readLine, next, index);
			doContinue = 1;
		}
		index++;
		next = readLine[index];
	}
}

void readNumber(const char readLine[MAX_LENGTH], double numArray[2], int& index){
	double answer = 0;
	int j = 0, i = 0;
	string digits = "";
	for (unsigned int k = 0; (j != 2) && (k < (strlen(readLine) - 1)); k++){
		if (isdigit(readLine[k]) || (readLine[k] == '.')){
			digits += readLine[k];
			if (!(isdigit(readLine[k + 1]) || (readLine[k + 1] == '.'))){
				std::cout << digits << endl;
				answer = atof(digits.c_str());
				numArray[j++] = answer;
				digits = "";
			}
		}//end if
	}//end for
}//end readNumber Function

void arithmetic(const char readLine[MAX_LENGTH], char operation, int& index) {
	double numArray[2];
	readNumber(readLine, numArray, index);
	double numberOne = numArray[0];
	double numberTwo = numArray[1];
	std::cout << numArray[0] << " " << numArray[1] << endl;
	double answer;
	switch (operation) {
	case '+':
		answer = numberOne + numberTwo;
		std::cout << "+ " << numberOne << " " << numberTwo;
		break;
	case '-':
		answer = numberOne - numberTwo;
		std::cout << "- " << numberOne << " " << numberTwo;
		break;
	case '•':
	case '*':
		answer = numberOne * numberTwo;
		std::cout << "* " << numberOne << " " << numberTwo;
		break;
	case '/':
		answer = numberOne / numberTwo;
		std::cout << "/ " << numberOne << " " << numberTwo;
		break;
	case '%':
		answer = static_cast<int>(numberOne) % static_cast<int>(numberTwo);
		std::cout << "% " << numberOne << " " << numberTwo;
		break;
	case '^':
		std::cout << "^ " << numberOne << " " << numberTwo;
		answer = pow(numberOne, numberTwo);
		break;
	default:
		answer = 0;
		break;
	}//end switch
	std::cout << " " << answer << endl;
}//end arthmetic Function

void trigFunction(const char readLine[MAX_LENGTH], char operation, int& index) {
	double numArray[1];
	readNumber(readLine, numArray, index);
	double number = numArray[0];
	double answer;
	switch (operation) {
	case 'S':
		answer = sin(PI*number / 180);
		std::cout << "S" << number;
		break;
	case 'C':
		answer = cos(PI*number / 180);
		std::cout << "C" << number;
		break;
	case 'T':
		answer = tan(PI*number / 180);
		std::cout << "T" << number;
		break;
	default:
		answer = 0;
		break;
	}//end switch
	std::cout << " " << answer << endl;
}//end trigFunction Function

void modeToPrint(const char readLine[MAX_LENGTH], char next) {
	switch (next) {
	case 'e':
	case 'E':
		std::cout << "E" << std::scientific << endl;
		break;
	case 'f':
	case 'F':
	default:
		std::cout << "F" << std::fixed << endl;
	}//end switch
}//end modeToPrint function