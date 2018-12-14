#include "stdafx.h"
#include "CountryManager.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

void init ( CountryManager & manager )
{
	manager.addCountry ( "Ukraine" );
	manager.addCountry ( "Russia" );
	manager.addCountry ( "England" );
	manager.addCountry ( "Poland" );

	manager.addProduct ( "Ukraine", "1988", "Milk", 1000, CountryManager::product_t::ProducedProduct );
	manager.addProduct ( "Ukraine", "2018", "Milk", 7000, CountryManager::product_t::ProducedProduct );

	manager.addChildProduct ( "Ukraine", "1988", "Milk", "Cow", 100 );
	manager.addChildProduct ( "Ukraine", "2018", "Milk", "Cow", 700 );

	manager.addProduct ( "Ukraine", "1988", "Milk", 1000, CountryManager::product_t::ExportProduct );
	manager.addProduct ( "Ukraine", "2018", "Milk", 7000, CountryManager::product_t::ExportProduct );
	manager.addProduct ( "Ukraine", "1988", "Milk", 1000, CountryManager::product_t::ImportProduct );
	manager.addProduct ( "Ukraine", "2018", "Milk", 7000, CountryManager::product_t::ImportProduct );
	manager.addProduct ( "Ukraine", "1988", "Milk", 1000, CountryManager::product_t::ProductForConsumers );
	manager.addProduct ( "Ukraine", "2018", "Milk", 7000, CountryManager::product_t::ProductForConsumers );


	manager.addProduct ( "Russia", "1988", "Cakes", 8000, CountryManager::product_t::ProducedProduct );
	manager.addProduct ( "Russia", "2018", "Cakes", 18000, CountryManager::product_t::ProducedProduct );

	manager.addChildProduct ( "Russia", "1988", "Cakes", "Sugar", 10000 );
	manager.addChildProduct ( "Russia", "1988", "Cakes", "Milk", 5000 );
	manager.addChildProduct ( "Russia", "2018", "Cakes", "Sugar", 30000 );
	manager.addChildProduct ( "Russia", "2018", "Cakes", "Milk", 9000 );

	manager.addProduct ( "Russia", "1988", "Sugar", 10000, CountryManager::product_t::ExportProduct );
	manager.addProduct ( "Russia", "2018", "Sugar", 30000, CountryManager::product_t::ExportProduct );
	manager.addProduct ( "Russia", "1988", "Milk", 2000, CountryManager::product_t::ImportProduct );
	manager.addProduct ( "Russia", "2018", "Milk", 7000, CountryManager::product_t::ImportProduct );
	manager.addProduct ( "Russia", "1988", "Cakes", 8000, CountryManager::product_t::ProductForConsumers );
	manager.addProduct ( "Russia", "2018", "Cakes", 18000, CountryManager::product_t::ProductForConsumers );


	manager.addProduct ( "England", "1988", "Bread", 18000, CountryManager::product_t::ProducedProduct );
	manager.addProduct ( "England", "2018", "Bread", 38000, CountryManager::product_t::ProducedProduct );

	manager.addChildProduct ( "England", "1988", "Bread", "Flour", 20000 );
	manager.addChildProduct ( "England", "2018", "Bread", "Flour", 40000 );

	manager.addProduct ( "England", "1988", "Bread", 5000, CountryManager::product_t::ExportProduct );
	manager.addProduct ( "England", "2018", "Bread", 12000, CountryManager::product_t::ExportProduct );
	manager.addProduct ( "England", "1988", "Flour", 10000, CountryManager::product_t::ImportProduct );
	manager.addProduct ( "England", "2018", "Flour", 15000, CountryManager::product_t::ImportProduct );
	manager.addProduct ( "England", "1988", "Bread", 13000, CountryManager::product_t::ProductForConsumers );
	manager.addProduct ( "England", "2018", "Bread", 26000, CountryManager::product_t::ProductForConsumers );

	manager.addProduct ( "Poland", "1988", "Apple", 10000, CountryManager::product_t::ProducedProduct );
	manager.addProduct ( "Poland", "1988", "Tomato", 15000, CountryManager::product_t::ProducedProduct );
	manager.addProduct ( "Poland", "2018", "Tomato", 55000, CountryManager::product_t::ProducedProduct );

	manager.addProduct ( "Poland", "1988", "Apple", 5000, CountryManager::product_t::ExportProduct );
	manager.addProduct ( "Poland", "1988", "Tomato", 4000, CountryManager::product_t::ExportProduct );
	manager.addProduct ( "Poland", "2018", "Tomato", 7000, CountryManager::product_t::ExportProduct );
	manager.addProduct ( "Poland", "1988", "Apple", 3000, CountryManager::product_t::ImportProduct );
	manager.addProduct ( "Poland", "1988", "Tomato", 10000, CountryManager::product_t::ImportProduct );
	manager.addProduct ( "Poland", "2018", "Tomato", 15000, CountryManager::product_t::ImportProduct );
	manager.addProduct ( "Poland", "1988", "Apple", 5500, CountryManager::product_t::ProductForConsumers );
	manager.addProduct ( "Poland", "1988", "Tomato", 13000, CountryManager::product_t::ProductForConsumers );
	manager.addProduct ( "Poland", "2018", "Tomato", 26000, CountryManager::product_t::ProductForConsumers );

}

int main()
{
	CountryManager manager;

	init ( manager );

	uint32_t input = 0;
	string buf;

	while (input != 4)
	{
		system("cls");
		cout << "1. Look up all countries." << endl;
		cout << "2. Look up countries information." << endl;
		cout << "3. Get balance of products." << endl;
		cout << "4. Exit." << endl;

		cin >> input;

		switch (input)
		{
		case 1:

			for (auto const& i : manager.getAllCountriesName())
				cout << i << endl;
			break;
		case 2:
			cin.ignore(cin.rdbuf()->in_avail());

			cout << "Enter country name: ";
			getline(cin, buf);

			for (auto const& i : manager.getInfo(buf))
				cout << i << endl;

			break;
		case 3:
			cin.ignore(cin.rdbuf()->in_avail());

			cout << "Enter countries list: ";
			getline(cin, buf);

			for (auto const& i : manager.getCountriesBalance(buf))
				cout << i << endl;

			break;
		default:
			break;
		}
		cout << endl;
		cout << "Press any key" << endl;
		_getch();
	}

	return 0;
}