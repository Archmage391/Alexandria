/*
  File Name: Project5.cpp
  Author: Reece Wienandt
  Course: CSC 402
  Date: 11/29/2018
*/

#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;

struct ItemInfo
{
	ItemInfo(string a = "Default", double b = 0, double c = 0) : description{ a }, unitPrice{ b }, shippingWeight{ c }
	{

	}

	string description;
	double unitPrice, shippingWeight;

	void print()
	{
		cout << description << ", " << unitPrice << ", " << shippingWeight << endl;
	}
};

typedef map<string, ItemInfo> Catalog;
typedef map<string, int> Order;



void readCatalog(Catalog& catalog, const string& fileName);
// reads the input file and creates the catalog; throws a 
// runtime_error if the file cannot be opened


void printCatalog(const Catalog& catalog);
// prints the SKU, description, price, and weight of every item in 
// the catalog 


ItemInfo getItemData(const Catalog& catalog, const string& sku);
// finds a single item by SKU and returns the details as a struct;
// returns a dummy struct with the description "Item not found", 
// price 0.00, and weight 0.00 if the SKU is not in the catalog


void displayOrderItems(const Order& order, const Catalog& catalog);
// Lists the SKU, description, and quantity of each type of order item

void addItem(Order& order, const Catalog& catalog, const string& sku, int quantity);
// adds item(s) to the order; throws a logic_error if the item cannot
// be found in the catalog 

void removeItem(Order& order, const string& sku, int quantity);
// removes items(s) from the order; throws a logic_error if the item 
// cannot be found in the order 

void displayOrderSummary(const Order& order, const Catalog& catalog);
// displays the number of unique item types, the total number of 
// items, the total cost, and the total shipping weight 




int main()
{
	Catalog catalog;
	Order order;
	try
	{
		readCatalog(catalog, "CatalogDa.txt");
	}
	catch (exception &e)
	{
		cout << "Error! " << e.what() << endl << endl;
	}
	try
	{
		readCatalog(catalog, "CatalogData.txt");
	}
	catch (exception &e)
	{
		throw runtime_error("");
	}
	printCatalog(catalog);
	/*
	cout << endl;
	catalog.find("4123RED")->second;
	catalog.find("93456D")->second;
	catalog.find("9356D")->second;
	*/
	cout << endl;
	getItemData(catalog, "93456B");
	getItemData(catalog, "4123RED");
	getItemData(catalog, "4123BLU");
	getItemData(catalog, "93456D");
	getItemData(catalog, "9356D");
	cout << endl;
	try
	{
		//dItem(order, catalog, "4123BL", 12);
		addItem(order, catalog, "93456D", 3);
		addItem(order, catalog, "576361B", 1);
		addItem(order, catalog, "576361A", 1);
		addItem(order, catalog, "4123GRE", 5);
		addItem(order, catalog, "4123BLU", 12);
		addItem(order, catalog, "4123BL", 12);
	}
	catch (exception &e)
	{
		cout << "Error! " << e.what() << "\n\n";
	}
	displayOrderItems(order, catalog);

	try
	{
		//removeItem(order, "4123BL", 6);
		removeItem(order, "4123BLU", 6);
	}
	catch (exception &e)
	{
		cout << "Error! " << e.what() << "\n\n";
	}
	cout << "\n\n";
	displayOrderItems(order, catalog);
	cout << "\n\n";
	displayOrderSummary(order, catalog);
	cin.get();
	return 0;
}


void readCatalog(Catalog& catalog, const string& fileName)
{
	string tmp;
	stringstream ss;
	vector<string> tokens;

	ifstream file;
	file.open(fileName);
	if (file.is_open() != true) 
	{
		throw runtime_error("File Cannot be Opened");
	}
	else
	{
		while (getline(file, tmp))
		{
			ss.clear();
			ss.str(tmp);
			while (getline(ss, tmp, ':'))
			{
				tokens.push_back(tmp);
			}
			catalog.insert(pair<string, ItemInfo>(tokens[0], { tokens[1], stod(tokens[2]), stod(tokens[3]) }));
			tokens.clear();
		}
		ss.clear();
	}
	file.close();
}
// reads the input file and creates the catalog; throws a 
// runtime_error if the file cannot be opened


void printCatalog(const Catalog& catalog)
{
	cout << left << setw(10) << "SKU" << setw(60) << "Description" << setw(10) << "UnitPrice" << setw(10) << "Shipping Wt. (lbs.)" << endl;
	cout << "================================================================================" << endl;
	
	for (Catalog::const_iterator itr = catalog.begin(); itr != catalog.end(); itr++)
	{
		cout << left << setw(10) << itr->first << setw(60) << itr->second.description << setw(10) << itr->second.unitPrice << setw(10) << itr->second.shippingWeight << endl;
	}

}
// prints the SKU, description, price, and weight of every item in 
// the catalog 


ItemInfo getItemData(const Catalog& catalog, const string& sku)
{
	ItemInfo inf("Item not found", 0.00, 0.00);
	if (catalog.find(sku) != catalog.end())
	{
		cout << "Product description for sku " << sku << ": " << setw(60) << catalog.find(sku)->second.description << endl;
		return catalog.find(sku)->second;
	}
	else
	{
		cout << "Product descrption for sku " << sku << ": Item not found" << endl;
		return inf;
	}
}
// finds a single item by SKU and returns the details as a struct;
// returns a dummy struct with the description "Item not found", 
// price 0.00, and weight 0.00 if the SKU is not in the catalog


void displayOrderItems(const Order& order, const Catalog& catalog)
{
	cout << left << setw(10) << "SKU" << setw(60) << "Description" << setw(10) << "Quantity" << endl;
	cout << "===============================================================================" << endl;

	Order::const_iterator itr;
	for (Order::const_iterator itr = order.begin(); itr != order.end(); itr++)
	{
		cout << left << setw(10) << itr->first;
		cout << left << setw(60) << catalog.find(itr->first)->second.description << setw(10) << itr->second << " \t" << endl;
	}
}
// Lists the SKU, description, and quantity of each type of order item

void addItem(Order& order, const Catalog& catalog, const string& sku, int quantity)
{
	int nquantity;
	if (catalog.find(sku) != catalog.end())
	{
		if (order.find(sku) != order.end())
		{
			nquantity = order.find(sku)->second + quantity;
			order[sku] = nquantity;
		}
		else
		{
			order.insert(pair<string, int>(sku, quantity));
		}
	}
	else
	{
		throw logic_error("Item cannot be found");
	}
}
// adds item(s) to the order; throws a logic_error if the item cannot
// be found in the catalog 

void removeItem(Order& order, const string& sku, int quantity)
{
	int nquantity;
	if (order.find(sku) != order.end())
	{
		if ((order.find(sku)->second - quantity) >= 1)
		{
			nquantity = order.find(sku)->second - quantity;
			order[sku] = nquantity;
		}
		else
		{
			order.erase(order.find(sku));
		}
	}
	else
	{
		throw logic_error("Item cannot be found");
	}
}
// removes items(s) from the order; throws a logic_error if the item 
// cannot be found in the order 

void displayOrderSummary(const Order& order, const Catalog& catalog)
{
	cout << "Order Summary" << endl;
	cout << "===============================================================================" << endl;
	cout << "Distinct item types: " << order.size() << endl;

	int itemCount = 0;
	for (Order::const_iterator itr = order.begin(); itr != order.end(); itr++)
	{
		itemCount = itemCount + itr->second;
	}

	cout << "Total number of items: " << itemCount << endl;

	double itemCost = 0;
	double itemWeight = 0;
	for (Order::const_iterator itr = order.begin(); itr != order.end(); itr++)
	{
		itemCost = itemCost + (catalog.find(itr->first)->second.unitPrice * itr->second);
	}

	cout << "Total cost: $" << itemCost << endl;


	for (auto itr = order.begin(); itr != order.end(); itr++)
	{
		itemWeight = itemWeight + (catalog.find(itr->first)->second.shippingWeight * itr->second);
	}

	cout << "Total weight: " << itemWeight << "lbs." << endl;
}
// displays the number of unique item types, the total number of 
// items, the total cost, and the total shipping weight 


