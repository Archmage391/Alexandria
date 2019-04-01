/*
	File Name: DynamicStack.h
	Author: Reece Wienandt
	Course: CSC 402
	Date: 10/12/18
*/

#pragma once
#include <iostream>
using namespace std;

class DynamicStack
{
public:
	//Constructors
	DynamicStack(int c = 10)
	{
		data = new double[c];
		cap = c;
		s = 0;
	};

	DynamicStack(double a[], int length)
	{
		data = new double[length];
		for (int i = 0; i < length; i++)
		{
			data[i] = a[i];
		}
		s = length;
		cap = length;
		top = &data[length - 1];
	};

	//Member Functions
	//Accessors
	int size() const;
	int capacity() const;
	bool empty() const;
	double peek() const;
	
	//Mutators
	void push(double);
	double pop();
	void clear();


	//Destructor
	~DynamicStack()
	{
		delete[] data;
		cout << "Destuctor Called" << endl;
	}

	//Copy Constructor
	explicit DynamicStack(const DynamicStack& i) : cap{ i.cap }, s{ i.s }
	{
		data = new double[i.s];
		for (int j = 0; j < i.s; j++)
		{
			data[j] = i.data[j];
		}
		top = &data[s - 1];
		cout << "Copy Constructor Called" << endl;
	}

	//Move Constructor
	DynamicStack(DynamicStack&& arg) : cap{ arg.cap }, s{ arg.s }
	{
		data = new double[cap];
		for (int i = 0; i < s; i++)
		{
			data[i] = arg.data[i];
		}
		top = &data[s - 1];
		arg.top = nullptr;
		arg.s = 0;
		arg.cap = 0;
		cout << "Move Constructor Called" << endl;
	}

	//Copy Assignment Operator  
	const DynamicStack& operator=(const DynamicStack &rhs);

	//Move Assignment Constructor
	DynamicStack& operator=(DynamicStack&& arg);

	//[] Operator
	double operator[] (int) const;

	//<< Operator
	friend ostream & operator<<(ostream &a, const DynamicStack&b);

private:
	double *data;
	double *top;
	int cap;
	int s;


};
