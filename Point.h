#pragma once
class Point
{
public:
	double x;
	double y;
	Point();
	Point(double x,double y);
	void print();
	double operator-(Point tmp_pt);
	~Point();
};

