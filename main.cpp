
#include <iostream>	 // for input/output streams
#include "fstream"	 // for reading/writing files streams
#include "string"	 // for dealing with strings
#include "stdc++.h"	 // for transforming from string to std::uppercase/std::lowercase
using namespace std; // for compatibility with all input/output streams functions
// Declaring the app main arrays
/*
arraySize => the size of the all arrays
displayArraySizeFrom => the size of the currencies_from array
displayArraySizeTo => the size of the currencies_to array
currency_value => the currency_to values
*/
int arraySize, displayArraySizeFrom, displayArraySizeTo;
string *currencies_from, *currencies_to;
float *currency_value,*currency_value_from;
// this method for checking if the element value is in the array returned true if the value exists in the array
bool in_array(string *array, string value, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] == value)
			return true;
	}
	return false;
}
// this method for returning the currency_to exchange value its returned 0.0 if the value is not in the array
float getCurrencyPrice(string *array, string value, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] == value)
			return currency_value[i];
	}
	for (int i = 0; i < displayArraySizeFrom; i++)
	{
		if (currencies_from[i] == value)
			return (-1*currency_value[i]);
	}

	return 0.0;
}
// this method for reading all currencies from the file.txt and append the values to the arrays in orderd way
/*
Here we can see all arrays associated with the app functionality is initialized with the size and values
ifstream for reading from the file

*/
void convertCurrencies(string filename)
{
	ifstream file(filename.c_str());
	ifstream file2(filename.c_str());
	string line, word, from_currency, to_currency;
	float from, to;
	arraySize = 1;
	// To get the real file rows count to initailize the arrays size
	while (getline(file2, word))
	{
		arraySize = arraySize + 1;
	}
	currencies_from = new string[arraySize];
	currencies_to = new string[arraySize];
	currency_value = new float[arraySize];
	currency_value_from = new float[arraySize];
	int i0 = 0, i = 0;
	displayArraySizeFrom = 0;
	while (file >> from >> from_currency >> to >> to_currency)
	{
		// To make sure the currency_from values is not repeated
		if (!in_array(currencies_from, from_currency, displayArraySizeFrom))
		{

			currencies_from[displayArraySizeFrom] = from_currency;
			displayArraySizeFrom = displayArraySizeFrom + 1;
			currency_value_from[displayArraySizeFrom] = from;

		}
		// To make sure the currency_to values is not repeated
		if (!in_array(currencies_to, to_currency, displayArraySizeTo))
		{

			currencies_to[displayArraySizeTo] = to_currency;
			currency_value[displayArraySizeTo] = to;
			displayArraySizeTo = displayArraySizeTo + 1;
		}

		i = i + 1;
	}
}

int main()
{
	// this is the main function
	/*
	from/to variables is referenced to the currency_from/currency_to value the came up from the user
	mony variable is referenced to the mony the was entered by the user hime self to make currency exchange with it
	result is the returned value as currency exchange process result
	*/
	string from, to;
	float result, mony;
	// here we called the convertCurrencies() function to get all the currencies from the file and initialize the arrays
	convertCurrencies("ExchageRate.txt");
	cout << "Welcome to Currencies Exchanger ^_^" << endl;
	cout << "The currencies we have exchange from are:" << endl;
	// this is block for displaying the currencies_from names to the user
	for (int i = 0; i < displayArraySizeFrom; i++)
	{
		if (i % 2 == 0)
			cout << endl;
		else
			cout << "\t|\t";
		cout << i << "- " << currencies_from[i];
	}
	cout << endl
		 << "The currencies we have exchange to are:" << endl;
	// this is block for displaying the currencies_to names to the user
	for (int i = 0; i < displayArraySizeTo; i++)
	{
		if (i % 2 == 0)
			cout << endl;
		else
			cout << "\t|\t";
		cout << i << "- " << currencies_to[i];
	}
	cout << endl;
// x: its point for relunching the user choices if the result is 0.0 its just for make exception if there is any error in the result
x:
	cout << "Please enter the currency you want to exchange from:" << endl;
	cin >> from;
	// this is function is for convert the string to uppercase to facilitate the currency names entering by the user
	transform(from.begin(), from.end(), from.begin(), ::toupper);
	// here we checked the name of the currency that entered by the user if its not found this block will re-asking the user for the currency name again
	while (!in_array(currencies_from, from, displayArraySizeFrom)&&!in_array(currencies_to, from, displayArraySizeTo))
	{
		cout<<!in_array(currencies_from, from, displayArraySizeFrom)<<"="<<!in_array(currencies_to, to, displayArraySizeTo)<<endl;
		cout << "Please enter the correct currency you want to exchange from:" << endl;
		cin >> from;
		transform(from.begin(), from.end(), from.begin(), ::toupper);
	}

	cout << "Please enter the currency you want to exchange to:" << endl;
	cin >> to;
	transform(to.begin(), to.end(), to.begin(), ::toupper);
	while (!in_array(currencies_to, to, displayArraySizeTo) && !in_array(currencies_from, to, displayArraySizeFrom))
	{
		cout << "Please enter the correct currency you want to exchange to:" << endl;
		cin >> to;
		transform(to.begin(), to.end(), to.begin(), ::toupper);
	}

	cout << "Please enter the currency amount you want to exchange:" << endl;
	cin >> mony;
	// this is line is to return the currency_to value for exchanging
	result = getCurrencyPrice(currencies_to, to, displayArraySizeTo);
	if (result != 0.0)
	{
		// here we are compute the currency exchange price result
		result = result * mony;
		cout << "The result of exchanging from ( " << from << " ) currency to ( " << to << " ) was = " << result << endl;
	}
	else
	{
		cout << "operation error.\nPlease try again:" << endl;
		// this line is responsible for moving the window to the x: point which we descussed above
		goto x;
	}

	cout << endl;
	// this is line to make the window waiting the user to close the window and not closing by itself
	system("pause");

	return 0;
}
