#ifndef TOWER_H
#define TOWER_H
#include "pch.h"
#include <iostream>

using namespace std;
class Airport;

class Tower
{
public:
	int m_tower_index;
	int ** m_lines;
	int lines;
	Tower();
	Tower(Airport* tmp_airport);
	~Tower();
};

#endif // !TOWER_H