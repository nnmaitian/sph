#pragma once
#include<string>
#include<iostream>

using namespace std;

class Nodes
{
public:
	void write_num(int num1)
	{
		num = num1;
	}
	void write_x(int x1)
	{
		x = x1;
	}
	void write_y(int y1)
	{
		y = y1;
	}
	void readN()
	{
		cout << "num:" << num << endl;
		cout << "x" << x << endl;
		cout << "y" << y << endl<<endl;
	}

private:
	int num;
	int x;
	int y;
};
