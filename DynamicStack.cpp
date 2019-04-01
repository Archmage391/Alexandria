
/*
	File Name: DynamicStack.cpp
	Author: Reece Wienandt
	Course: CSC 402
	Date: 10/12/18
*/

#include "DynamicStack.h"
#include <iostream>

using namespace std;


//Accessor Functions
int DynamicStack::size() const
{
	return s;
}
int DynamicStack::capacity() const
{
	return cap;
}
bool DynamicStack::empty() const
{
	if (s == 0)
	{
		return true;
	}
	return false;
}
double DynamicStack::peek() const
{
	if (s == 0)
	{
		return static_cast<double>(-INT_MAX);
	}
	return *top;
}


//Mutator Functions
void DynamicStack::push(double dat)
{
	if (s == cap)
	{
		if (cap == 0)
		{
			cap = 1;
			s = 1;
			data = new double[1];
			data[0] = dat;
			top = &data[0];
		}
		else if (cap == 1)
		{
			cap = 2;
			s = 2;
			data = new double[2];
			data[1] = dat;
			top = &data[1];
		}
		else
		{
			cap = (int)(cap * 1.5);
			double *temp = new double[s];
			for (int i = 0; i < s; i++)
			{
				temp[i] = data[i];
			}
			data = new double[cap];
			for (int i = 0; i < s; i++)
			{
				data[i] = temp[i];
			}
			delete[] temp;
			data[s] = dat;
			top = &data[s];
			s++;
		}
	}
	else
	{
		data[s] = dat;
		top = &data[s];
		s++;
	}
}

double DynamicStack::pop()
{
	if (s == 0)
	{
		return static_cast<double>(-INT_MAX);
	}
	double ret = *top;
	data[s - 1] = 0;
	s--;
	top = &data[s - 1];
	return ret;
}

void DynamicStack::clear()
{
	for (int i = 0; i < s; i++)
	{
		data[i] = 0;
	}
	s = 0;
	cap = 10;
	delete[] data;
	data = new double[cap];
}


//Operator Overloading
//Copy Assignment Operator
const DynamicStack & DynamicStack::operator=(const DynamicStack & rhs)
{
	if (this != &rhs)
	{
		data = new double[rhs.cap];
		for (int j = 0; j < rhs.s; j++)
		{
			data[j] = rhs.data[j];
		}
		top = &data[rhs.s] - 1;
		cap = rhs.cap;
		s = rhs.s;
	}
	cout << "Copy Assignment Operator Called" << endl;
	return *this;
}

//Movement Assignment Operator
DynamicStack & DynamicStack::operator=(DynamicStack && arg)
{
	data = new double[arg.cap];
	for (int j = 0; j < arg.s; j++)
	{
		data[j] = arg.data[j];
	}
	top = &data[arg.s - 1];
	cap = arg.cap;
	s = arg.s;
	arg.top = nullptr;
	arg.s = 0;
	arg.cap = 0;

	cout << "Move Assignment Constructor Called" << endl;
	return *this;
}

double DynamicStack::operator[](int ind) const
{
	if (ind >= DynamicStack::s)
	{
		cout << "Array out of bounds" << endl;
		throw out_of_range("Oops");
	}
	return DynamicStack::data[ind];
}

ostream& operator<<(ostream & o, const DynamicStack & arg)
{
	for (int i = arg.s - 1; i >= 0; i--)
	{
		o << arg.data[i] << " ";
	}
	o << endl;
	return o;
}
