#include "CountryManager.h"

using namespace std;

void CountryManager::addCountry(string countryName)
{
	ListOfCountries.push_back({ countryName });
}

void CountryManager::addProduct(string countryName, string year, string productName, size_t productAmount, product_t type)
{
	Country* found_country = find_country(move(countryName), move(ListOfCountries)); 
	//find found_country in database and return pointer to this found_country

	if (!found_country)
		return;
	
	year_products_list_t* main_products = get_products(found_country, type); 
	//return address to Product type
	products_list_t* products_list = find_year(move(year), found_country, move(*main_products)); 
	//find year in array of years and return address to Product list of this year
	
	if (!products_list)
		main_products->emplace(year, products_list_t({ make_pair(Product{ productName }, productAmount) }));
	else
		products_list->push_back(make_pair(Product{ productName }, productAmount));

	//if year exist we insert our Product to list of products in this year 
	//else if year isn't exist we create this year and insert Product to this year
}

void CountryManager::addChildProduct(string countryName, string year, string mainProductName, string childProductName, size_t amount)
{
	Country* country = find_country(move(countryName), move(ListOfCountries)); 
	//find found_country in database and return pointer to this found_country

	if (!country)
		return;

	products_list_t* found_product_list = find_year(move(year), country, move(country->produced_products)); 

	if (!found_product_list)
		return;

	Product* product = find_product(move(mainProductName), move(*found_product_list)); 

	if (!product)
		return;

	product->child_products.emplace(childProductName, amount); 
}

list<string> CountryManager::getAllCountriesName()
{
	list<string> countries;

	for (auto&& i : ListOfCountries)
		countries.push_back(i.country_name);

	//get name of all countries in our database , and push to list of names
	return countries;
}

list<string> CountryManager::getInfo(string countryName)
{
	//find found_country in database and return pointer to this found_country
	Country* country = find_country(move(countryName), move(ListOfCountries));

	if (!country)
		return { "Invalid country value!" };

	
	list<string> info;

	//get all info about produced products
	if (!country->produced_products.empty())
	{
		info.push_back("Produced products: ");
		get_info(move(info), move(country->produced_products));
	}

	//get all info about export products
	if (!country->export_products.empty())
	{
		info.push_back("Export products: ");
		get_info(move(info), move(country->export_products));
	}

	//get all info about import products
	if (!country->import_products.empty())
	{
		info.push_back("Import products: ");
		get_info(move(info), move(country->import_products));
	}

	//get all info about products for consumers
	if (!country->products_for_consumers.empty())
	{
		info.push_back("Products for consumers: ");
		get_info(move(info), move(country->products_for_consumers));
	}

	return info;
}

list<string> CountryManager::getCountriesBalance(string Countries)
{
	auto first_letter = Countries.begin();
	//get pointer to first letter of our string

	list<string> info;
	Country* found_country;

	while (first_letter != Countries.end())
	{
		first_letter = find_if(first_letter, Countries.end(), [](const char& symbol)
		{
			return isalpha(symbol);
		});
		//find first letter-type symbol

		if (first_letter == Countries.end())
			break;

		auto last_letter = find_if_not(first_letter, Countries.end(), [](const char& symbol)
		{
			return isalpha(symbol);
		});
		//find first not letter-type symbol after letter-type symbol

		found_country = find_country(move(string(first_letter, last_letter)), move(ListOfCountries));
		//find found_country in database and return pointer to this found_country

		if (!found_country)
			break;

		info.push_back(found_country->country_name);
		//insert counry name to info-list

		get_balance(move(info), move(found_country->produced_products));
		//get balance of every year about every Product

		first_letter = last_letter;
	}
	
	return info;
}

CountryManager::Country* CountryManager::find_country(string const& countryName, list<Country>&& Countries)
{
	auto res = find_if(Countries.begin(), Countries.end(), [countryName](const Country& country)
	{
		return countryName == country.country_name;
	});
	//find found_country pointer by name

	return res != Countries.end() ? &(*res) : nullptr;
	//if our found_country name exists in database , we return address to this found_country
}

CountryManager::Product* CountryManager::find_product(string const& ProductName, products_list_t&& Products)
{
	auto res = find_if(Products.begin(), Products.end(), [ProductName](const pair<Product, size_t>& products)
	{
		return ProductName == products.first.product_name;
	});
	//find Product pointer by name

	return res != Products.end() ? &((*res).first) : nullptr;
	//if our Product name exist in database , we return address to this Product
}

CountryManager::products_list_t* CountryManager::find_year(string const& Year, Country* country, year_products_list_t&& products)
{
	auto res = products.find(Year);

	return res != products.end() ? &((*res).second) : nullptr;
	//if our year exist in database , we return address to Product list from this year
}

CountryManager::year_products_list_t* CountryManager::get_products(Country * country, product_t type)
{
	return type == ProducedProduct ? &country->produced_products : type == ProductForConsumers ? &country->products_for_consumers
		: type == ExportProduct ? &country->export_products : &country->import_products;
}

void CountryManager::get_info(list<string>&& buffer, year_products_list_t const& products)
{
	for (auto&& i : products)
	{
		buffer.push_back("  Year: " + i.first);

		for (auto&& k : i.second)
		{
			buffer.push_back("\t" + k.first.product_name + "\t" + to_string(k.second));

			if (!k.first.child_products.empty())
			{
				buffer.push_back("\t\tChild Prod**--ucts: ");

				for (auto&& c : k.first.child_products)
					buffer.push_back("\t\t  " + c.first + "\t" + to_string(c.second));
			}
		}
	}
}

void CountryManager::get_balance(list<string>&& buffer, year_products_list_t const& products)
{
	int min_year = atoi((*products.begin()).first.c_str());
	int max_year = atoi((*prev(products.end())).first.c_str());

	auto not_changed_products = get_product_years_info(products);

	for (int i = min_year; i <= max_year; ++i)
	{
		for (auto&& k : not_changed_products)
		{
			int balance = k.first_balance + (((k.last_balance - k.first_balance) / (max_year - min_year)) * (i - min_year));

			buffer.push_back("\tYear: " + to_string(i) + "\tproduct: " + k.product_name + "\tbalance: " + to_string(balance));
		}
	}
}

list<CountryManager::ProductYearsInfo> CountryManager::get_product_years_info(year_products_list_t const& products)
{
	list<ProductYearsInfo> years_info;

	auto last_year = prev(products.end())->second;
	
	for (auto const& i : products.begin()->second)
	{
		auto res = find_if(last_year.begin(), last_year.end(), [i](const pair<Product, size_t>& e_product)
		{
			return e_product.first.product_name == i.first.product_name;
		});
		//try to find Product name from first year, in array of Product names from last year

		if (res != last_year.end())
			years_info.push_back({ i.first.product_name, i.second, (*res).second });
	}

	return years_info;
}
