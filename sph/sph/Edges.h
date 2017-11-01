#pragma once
#include<string>
#include<iostream>

using namespace std;

class Edges
{
private:
	int num;
	int a;
	int b;
	int value;
public:
	void write_a(int a1)
	{
		a = a1; 
	}
	void write_b(int b1)
	{
		b = b1;
	}
	void write_value(int c)
	{
		value = c;
	}
	void write_num(int num1)
	{
		num = num1;
	}
	void readE()
	{
		cout << "num:" << num << endl;
		cout << "a" << a << endl;
		cout << "b" << b << endl;
		cout << "value" << value << endl<<endl;
	}
	int reada()
	{
		return a;
	}
	int readb()
	{
		return b;
	}
	int readnum()
	{
		return num;
	}
	int readvalue()
	{
		return value;
	}
};