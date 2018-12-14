#ifndef COUNTRY_MANAGER_H
#define COUNTRY_MANAGER_H

#include "stdafx.h"

class CountryManager
{
	using size_t = std::size_t;

private:
	struct Product;

	//key - child product_name, value - amount
	typedef std::map<std::string, size_t>				child_products_t;	

	// products amounts list type
	typedef std::list<std::pair<Product, size_t>>		products_list_t;
	
	//key - year, value - products amounts list
	typedef std::map<std::string, products_list_t>		year_products_list_t;

private:
	struct Product
	{
		std::string			product_name;
		child_products_t	child_products;
	};

	struct ProductYearsInfo
	{
		std::string	product_name;
		size_t	first_balance;
		size_t	last_balance;
	};

	struct Country
	{
		std::string		country_name;
		year_products_list_t	produced_products;
		year_products_list_t	products_for_consumers;
		year_products_list_t	export_products;
		year_products_list_t	import_products;
	};
public:
	enum product_t { ProducedProduct, ProductForConsumers, ExportProduct, ImportProduct };
public:
	void addCountry(std::string countryName);
	void addProduct(std::string countryName, std::string Year, std::string ProductName, size_t ProductAmount, product_t type);
	void addChildProduct(std::string countryName, std::string Year, std::string MainProductName, std::string ChildProductName, size_t Amount);
public:
	std::list<std::string> getAllCountriesName();
	std::list<std::string> getInfo(std::string countryName);
	std::list<std::string> getCountriesBalance(std::string Countries);
private:
	Country*			find_country(std::string const& countryName, std::list<Country>&& Countries);
	Product*			find_product(std::string const& ProductName, products_list_t&& Products);
	products_list_t*	find_year(std::string const& Year, Country* country, year_products_list_t&& products);
	year_products_list_t*	get_products(Country * country, product_t type);
private:
	void get_info(std::list<std::string>&& buffer, year_products_list_t const& products);
	void get_balance(std::list<std::string>&& buffer, year_products_list_t const& products);
private:
	std::list<ProductYearsInfo> get_product_years_info(year_products_list_t const& products);
private:
	std::list<Country> ListOfCountries;
};

#endif