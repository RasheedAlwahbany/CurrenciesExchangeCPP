
// include input/output streams library
#include <iostream>	 
// include string library for dealing with strings
#include "string"
// include reading/writing files streams library
#include "fstream"	 
// include stdc++ library to transforming from string to uppercase/lowercase
#include "../stdc++.h"	 
// for making input/output streams easy to use instead of using std::cout
using namespace std; 
/*
DCurrenciesExchanges => the list of exchanges currencies
Size => the size of the all arrays
DSize => the size of the displayed DCurrencies
currencyValues => the Currencies values
*/
string *DCurrencies,*DCurrenciesExchanges;
float *currencyValues;
int Size, DSize;
// Checking if the value is exists in the array or not
bool exist(string value, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (DCurrencies[i] == value)
			return true;
	}
	return false;
}
/*
ifstream line for reading from the file
All arrays initialized with the size and values
exist() function to make sure the currency values is not repeated

getCurrencies() function for reading all currencies from the ExchangeRate.txt and append the values to the arrays
*/
void getCurrencies()
{
	string filename="ExchageRate.txt";
	string line, word, name_from, name_to;
	float value_from, value_to;
	Size = 1;
	ifstream reader(filename.c_str());
	ifstream readerCounter(filename.c_str());
	// File lines count
	while (readerCounter >> word)
	{
		Size = Size + 1;
	}
	int i = 0;
	DSize = 0;
	DCurrencies = new string[Size];
	currencyValues = new float[Size];
	DCurrenciesExchanges = new string[Size];
	while (reader >> value_from >> name_from >> value_to >> name_to)
	{
		DCurrenciesExchanges[i] = name_from+"<=>"+name_to;
		currencyValues[i] = value_to;
		i = i + 1;
		if (!exist(name_to, DSize))
		{
			DCurrencies[DSize] = name_to;
			DSize = DSize + 1;
		}else if (!exist(name_from, DSize))
		{
			DCurrencies[DSize] = name_from;
			DSize = DSize + 1;
		}
	}
}


int main()
{
	// Main function
	/*
	Here all variables
	exchange_amount variable was entered by the user hime self to make currency exchange with its amount
	The variables (from/to) is referenced to the currency value that came up from the user inputs
	the variable total is the returned value from currency exchange process
	*/
	// This is while for re-running the app again
	string name_from, name_to;
	float total, exchange_amount;
	while(true){
	// The function getCurrencies() called to get all the currencies from the file and initialize the arrays values
	getCurrencies();
	cout << "The list of the currencies available are:" << endl;
	// Displaying all the currencies names to the end user
	for (int i = 0; i < DSize; i++)
	{
		cout <<"* " << DCurrencies[i]<< "\t|\t";
		if (i % 4 == 0 && i > 3)
		cout<<endl;
	}
	cout<<endl;
	// transform() Convert the string to uppercase
	// Checked the name of the currency that entered by the user to re-asking the user for entering the currency name again if its not exist
	do 
	{
		cout << "Enter the currency name you want to exchange:" << endl;
		cin >> name_from;
		transform(name_from.begin(), name_from.end(), name_from.begin(), ::toupper);
	}while (!exist(name_from, DSize));

	do 
	{
		cout << "Enter the currency name you want to exchange into:" << endl;
		cin >> name_to;
		transform(name_to.begin(), name_to.end(), name_to.begin(), ::toupper);
	}while(!exist(name_to, DSize));

	cout << "Enter the amount you want to exchange:" << endl;
	cin >> exchange_amount;
	// Get the currencies exchanges total value
	total=0;
	for (int i = 0; i < Size; i++)
	{
		if (DCurrenciesExchanges[i] == (name_from+"<=>"+name_to)){
			total = exchange_amount * currencyValues[i];
		}else if (DCurrenciesExchanges[i] == (name_to+"<=>"+name_from)){
			total = exchange_amount / currencyValues[i];
		}
	}
	if (total != 0)
	{
		cout << "Exchanging  ( " << name_from << "  =>  " << name_to << " ) process total: ( " << total << " )" << endl;
	}
	else
	{
		cout << "Error.\nThere is an error in the currency exchanging\nTry again:" << endl;
	}
	// Making the window waiting to any key press from the user
	system("pause");
	// To empty the terminal window output
	system("cls");
	}

	return 0;
}
