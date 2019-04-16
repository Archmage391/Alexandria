/*
	File Name: IComparable.h
	Author: Reece Wienandt
	Course: CSC 402
	Date: 11/01/2018
*/


#pragma once
#include <iostream>
#include <string.h>

using namespace std;

class IComparable
{
public:

	// the key to being "comparable" is this pure virtual function
	virtual int compare(const IComparable& icmp) const = 0;

	// Using the compare function, implement the == operator in the base class
	virtual bool operator==  (const IComparable& rhs) const {
		return (compare(rhs) == 0);
	}

	virtual bool operator< (const IComparable& rhs) const {
		return (compare(rhs) < 0);
	}

	virtual bool operator> (const IComparable& rhs) const {
		return (compare(rhs) > 0);
	}

	virtual bool operator!= (const IComparable& rhs) const {
		return (compare(rhs) != 0);
	}

	virtual bool operator<= (const IComparable& rhs) const {
		return (compare(rhs) <= 0);
	}

	virtual bool operator>= (const IComparable& rhs) const {
		return (compare(rhs) >= 0);
	}
	// TODO: Implement the remaining 5 relational operators
	// (<, >, !=, <=, and >=)  similarly within the IComparable class

	// Accessor to facilitate implementation of the << operator; also pure virtual
	virtual void print(ostream & out = cout) const = 0;

	// Given the pure virtual funcion below, you will need two operator= 
	// member functions in each concrete derived class--one that 
	// provides an implementation with this exact signature and one that provides a 
	// concrete implementation for derived classes with a signature such as: 
	// const Integer& operator= (const Integer& rhs) 
	virtual const IComparable& operator= (const IComparable & rhs) = 0;




	// TODO:  Implement a 'proper' destructor for an abstract class
	virtual ~IComparable() {}

};


ostream& operator<< (ostream& cout, IComparable& rhs)
{
	rhs.print(cout);
	return cout;
}


class Integer : public IComparable
{
public:

	// default and single-arg constructor is trivial 
	Integer(const int i = 0) : value{ i } { }

	// copy constructor for stack-based Integers is trivial and 
	// actually may be left out if you prefer.
	// Test it with the compiler-generated default to see if you need it.
	Integer(const Integer& rhs) : value{ rhs.value }  { }


	// copy assignment operator for stack-based Integers
	const Integer& operator= (const Integer& rhs) {  
		value = rhs.value;
		return  value;
	}


	// copy constructor for IComparable references
	// Note the strange syntax 
	Integer(const IComparable& rhs) : value{ dynamic_cast<const Integer&>(rhs).value } {   }

	// copy assignment operator for IComparable references
	const IComparable& operator= (const IComparable& rhs) { 
		value = dynamic_cast<const Integer&>(rhs).value;
		return Integer(value);
	}

	// As per the contract, compare must accept an IComparable reference 
	// return -1 if this object < icmp, 0 if this ojbect == icmp, 1 if icmp > 
	// this object (see hints below)
	int compare(const IComparable& rhs) const {  
		if (value < dynamic_cast<const Integer&>(rhs).value)
		{
			return -1;
		}
		else if (value == dynamic_cast<const Integer&>(rhs).value)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	// print is likewise trivial
	void print(ostream& out = cout) const { out << value; }

private:
	int value;
};   // end of class Integer



class Double : public IComparable
{
public:

	// default and single-arg constructor is trivial 
	Double(const double i = 1.1) : value{ i } { }

	// copy constructor for stack-based Integers is trivial and 
	// actually may be left out if you prefer.
	// Test it with the compiler-generated default to see if you need it.
	Double(const Double& rhs) : value{ rhs.value } { }


	// copy assignment operator for stack-based Integers
	const Double& operator= (const Double& rhs) {
		value = rhs.value;
		return  value;
	}


	// copy constructor for IComparable references
	// Note the strange syntax 
	Double(const IComparable& rhs) : value{ dynamic_cast<const Double&>(rhs).value } {   }

	// copy assignment operator for IComparable references
	const IComparable& operator= (const IComparable& rhs) {
		value = dynamic_cast<const Double&>(rhs).value;
		return Double(value);
	}

	// As per the contract, compare must accept an IComparable reference 
	// return -1 if this object < icmp, 0 if this ojbect == icmp, 1 if icmp > 
	// this object (see hints below)
	int compare(const IComparable& rhs) const {
		if (value < dynamic_cast<const Double&>(rhs).value)
		{
			return -1;
		}
		else if (value == dynamic_cast<const Double&>(rhs).value)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	// print is likewise trivial
	void print(ostream& out = cout) const { out << value; }

private:
	double value;
};   // end of class Double


class Character : public IComparable
{
public:

	// default and single-arg constructor is trivial 
	Character(const char i = '?') : value{ i } { }

	// copy constructor for stack-based Integers is trivial and 
	// actually may be left out if you prefer.
	// Test it with the compiler-generated default to see if you need it.
	Character(const Character& rhs) : value{ rhs.value } { }


	// copy assignment operator for stack-based Integers
	const Character& operator= (const Character& rhs) {
		value = rhs.value;
		return  value;
	}


	// copy constructor for IComparable references
	// Note the strange syntax 
	Character(const IComparable& rhs) : value{ dynamic_cast<const Character&>(rhs).value } {   }

	// copy assignment operator for IComparable references
	const IComparable& operator= (const IComparable& rhs) {
		value = dynamic_cast<const Character&>(rhs).value;
		return Character(value);
	}

	// As per the contract, compare must accept an IComparable reference 
	// return -1 if this object < icmp, 0 if this ojbect == icmp, 1 if icmp > 
	// this object (see hints below)
	int compare(const IComparable& rhs) const {
		if (value < dynamic_cast<const Character&>(rhs).value)
		{
			return -1;
		}
		else if (value == dynamic_cast<const Character&>(rhs).value)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	// print is likewise trivial
	void print(ostream& out = cout) const { out << value; }

private:
	char value;
};   // end of class Character