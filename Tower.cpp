#include "pch.h"
#include "Tower.h"
#include "Airport.h"
#include <iostream>

using namespace std;
class Airport;

Tower::Tower()
	: m_tower_index(1), lines(2)
{
	m_lines = new int*[lines];
	for (int i = 0; i < lines; i++)
	{
		m_lines[i] = new int[2];

	}

	for (int i = 0; i < lines; i++)
	{
		m_lines[i][0] = i + 1;
		m_lines[i][1] = 0;
	}

	//cout << "Constructing tower nr: " << m_tower_index << endl;

	//cout << '\n';
}
Tower::Tower(Airport* tmp_air)
{
	m_tower_index = tmp_air->get_airport_index();
	lines = tmp_air->get_airport_size();
	m_lines = new int*[lines];
	for (int i = 0; i < lines; i++)
	{
		m_lines[i] = new int[2];

	}

	for (int i = 0; i < lines; i++)
	{
		m_lines[i][0] = i + 1;
		m_lines[i][1] = 0;
	}

	//cout << "Constructing tower nr: " << m_tower_index << endl;

	//cout << '\n';
}

Tower::~Tower()
{
	//cout << "Deleting tower nr: " << get_tower_index() << endl;
	delete[] * m_lines;

}
