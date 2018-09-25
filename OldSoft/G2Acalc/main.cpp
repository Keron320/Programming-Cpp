#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>

using namespace std;

int main()
{
	char loop = 'y';
	string name;
	int keys;
	int tenner;
	float price;
	float tprice;
	float fee;
	float total = 0;
	ofstream myfile;
	myfile.open("test.txt");


	while (loop == 'y')
	{
	//fixed fees
	float fee15 = 0.15;
	float fee35 = 0.35;

	cout << "Name of the game?" << endl;
	cin >> name;
	cout << "Price of the game at G2A?" << endl;
	cin >> price;
	cout << "Amount of keys?" << endl << endl;
	cin >> keys;
	cout << keys << " copyies of " << name << " priced at " << price << "$" << endl;
	tprice = keys * price;
	cout << "Total price is: " << tprice << "$" << endl;

	fee = (tprice / 100 * 10.8);

	// If there's only one key of the game
	if (keys == 1)
	{
		tprice = tprice - fee15 - fee35;	
	}
	// If there are 2 to 9 games
	else if (keys > 1 && keys <= 10)
	{
		fee35 = keys * fee35;
		tprice = tprice - fee15 - fee35;
	}

	//// If there are more than 10 games	
		else {
			tenner = keys / 10;
		fee35 = keys * fee35;
		fee15 = tenner * fee15;

		tprice = tprice - fee15 - fee35;
	}
	cout << "After fees your games are worth: " << tprice - fee << "$";


	//Saves data to the text file
	myfile << keys << " copyies of " << name << " priced at " << price << "$" << " Total price: " << price * keys
		<< endl << " Worth after fees: " << tprice - fee << "$" << endl;
	total = total + (tprice - fee);
	//Asks user if he wants to add a new game or quit
	// Resets all values
	fee35 = 0;
	fee15 = 0;
	fee = 0;
	keys = 0;
	price = 0;
	tenner = 0;
	tprice = 0;

	cout << "\nDo you want to add another game? (y/n)";
	//Record y/n decision
	cin >> loop;
	}


	myfile << "\n\nTotal value after fees: " << total << endl;


	myfile.close();

	_getch();
	return 0;
}