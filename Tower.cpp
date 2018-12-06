#include "pch.h"
#include "Tower.h"
#include "Samolot.h"
#include "Airport.h"
#include <iostream>
#include <vector>


Tower::Tower(Airport * tmp_airport)
{
	m_tower_index = tmp_airport->get_airport_index();
	lines = tmp_airport->get_airport_size();
	m_lines = new int*[lines];
	for(int i=0; i< lines; i++)
	{
		m_lines[i] = new int[2];
	
	}

	for (int i = 0; i < lines; i++)
	{
		m_lines[i][0] = i + 1;
		m_lines[i][1] = 0;
	}

	cout << "Constructing tower nr: " << get_tower_index() << endl;
	
	cout << '\n';
}


Tower::~Tower()
{
	cout << "Deleting tower nr: " << get_tower_index() << endl;
	delete[] *m_lines;

}

void Tower::set_line_status(int stat)
{
	m_line_status = stat;
}
int Tower::get_tower_index()
{
	return m_tower_index;
}

void Tower::reserve_line(Airport* tmp_air,Samolot* tmp_plane)
{
	int i = tmp_air->get_airport_size();
	cout << "NUMBER OF LINES: " << i << endl;
	int out = 0;
	do
	{
		if (i <= 0)
		{
			cout << "We cannot reserve a line for you\n";
		}
		else if (m_lines[i-1][1] == 0)
		{
			m_lines[i-1][1] = tmp_plane->get_plane_index();
			out = 1;
			cout << "Reservation of line nr: " << m_lines[i - 1][0] << " for plane nr: " << tmp_plane->get_plane_index() << endl;
		}
		
		i--;
		
		
	} while((out==0)&&(i>=0));
}
void Tower::show_occupancy()
{
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < 1; j++) {
			cout << m_lines[i][j] << " " << m_lines[i][j + 1] << '\n';
		}
	}
}
