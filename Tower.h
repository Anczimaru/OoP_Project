#include "pch.h"
#include "Samolot.h"
#include "Airport.h"
#include <vector>
#include <iostream>
#include <memory>
#include <ctime>
//////////// LINE STATUS /////
//occupied --> number representing the index of plane
//free = 0
using namespace std;
#pragma once
class Tower
{
private:
	int m_tower_index;
	int ** m_lines;
	bool m_line_status;
	int lines;
	
public:
	Tower(Airport* tmp_airport);
	~Tower();
	void set_line_status(int status);
	//int get_line_status();
	int get_tower_index();
	void reserve_line(Airport* tmp_airport,Samolot* tmp_plane);
	void show_occupancy();
};

