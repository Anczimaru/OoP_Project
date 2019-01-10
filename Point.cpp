#include "pch.h"
#include "Point.h"
#include <iostream>
#include <cmath>

using namespace std;


Point::Point() :x(0), y(0)
{

}
Point::Point(double xi = 0.0, double yi = 0.0)
{
	x = xi;
	y = yi;
}
void Point::print()
{
	cout << "x: " << x << "y: " << y << endl;
}

double Point::operator-(Point tmp_pt)
{
	double distance = sqrt(pow(x - tmp_pt.x, 2) + pow(y - tmp_pt.y, 2));
	return distance;
}
Point::~Point()
{
}
