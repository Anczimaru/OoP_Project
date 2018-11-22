#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int our_index = 1; // those are initial indeces when creating objects, incrementation after creation :) 
int new_airport = 1;

int gibMe() // funckja do losowania indeksu lotniska. Generalnie program mamy mało idioto-odporny. Musimy pamiętać, żeby najpierw inicjalizować wszystkie lotniska
			// i pojedynczo rejestrujemy samoloty (zobacz main() ) 
{
	int gib;
	do {
		gib = rand() % new_airport;
	} while (gib == 0);
	return gib;
	
}

class Samolot
{
private:
	int m_dest, m_src; //indexes of airports
	int m_passengers; //no of passengers
	int m_capacity; // capacity of num of passengers
	int m_gate; //index of m_gate
	int m_status; // TO DO CHANGE TO ENUM
	int m_index; //index of airplane
	/*
	1 - flying, 2 - waiting, 3 - landing, 4 - unloading, 5 - maintenance, 6 - repairs, 7 - refueling, 8 - loading, 9 - departing, 10 - hangar
	*/
	int m_airline; //index of airline
	int m_airstrip; // index of airstrip
	double m_fuel; // percentage of fuel in airplane
	double m_tech_state; //percentage of airplane maintenance

public:
	/*Samolot(int dest=1,int src=2,int capacity=80,int passengers=60,int status = 1,double fuel_state=0.8,double tech_state=0.8,int index=1):
		m_dest(dest), m_src(src), m_capacity(capacity), m_passengers(passengers), m_status(status), m_fuel(fuel_state), m_tech_state(tech_state), m_index(index)
		{
			cout<<"Im plane with no:"<<m_index<<endl;
			fly_to_airport(m_dest);
		} */

	Samolot() :m_dest(1), m_src(2), m_capacity(80), m_passengers(60), m_status(0), m_fuel(0.78), m_tech_state(0.99), m_index(our_index)
	{
		
		//cout <<	"Im plane with no:"<<m_index<<endl;
		
		
		
	}
	~Samolot()
	{
		//cout<<"   destroyed plane no: "<<m_index<<endl;
	}
	void fly_to_airport()
	{
		cout << "Hi, Im plane number: "<<m_index<<"\tIm flying to: " << m_dest << "\tfrom: "<<m_src<< endl;
	}
	int get_dest()
	{
		return m_dest;
	}
	void set_dest(int target_dest)
	{
		m_dest = target_dest;
	}
	void set_src(int src)
	{
		m_src = src;
	}
	int get_src()
	{
		return m_src;
	}
	int get_plane_index()
	{
		return m_index;
	}
	int get_capacity()
	{
		return m_capacity;
	}
	int get_passengers()
	{
		return m_passengers;
	}
	void set_passengers(int target_passengers)
	{
		m_passengers = target_passengers;
	}
	double get_fuel()
	{
		return m_fuel;
	}
	void set_fuel(double target_fuel)
	{
		m_fuel = target_fuel;
	}
	double get_tech_state()
	{
		return m_tech_state;
	}
	void set_tech_state(double target_state)
	{
		m_tech_state = target_state;
	}
	void whereAmI()
	{
		//Do testów
		cout << "Im located at: " << m_src << endl;
	}
	int getIndex()
	{
		return m_index;
	}

};

class Airport
{
private:
	int m_index_ap; //index of airport
	int m_waiting_ppl;
	

	vector <Samolot> samoloty;
	Samolot m_tmp_plane; // to do change to pointer

public:
	Airport(int index = 1) : m_index_ap(new_airport)
	{

		cout << "Airport created with index no: " << m_index_ap << endl;
		new_airport++;
	}
	~Airport()
	{
		cout << "Airport with index: " << m_index_ap << " was destroyed" << endl;
	}
	void register_plane(Samolot plane) // wydaje mi się że jest cool, ale coś się pierniczy
										// To Do later!!
	{
		samoloty.push_back(plane);
		samoloty.back().set_src(m_index_ap);
		do
		{
			samoloty.back().set_dest(gibMe());
		} while (samoloty.back().get_dest() == m_index_ap);
		cout << "Airport: " << m_index_ap << " registered plane with index: " << samoloty.back().get_plane_index() << endl;
		samoloty.back().fly_to_airport();
		our_index++;
		
	}

	void do_routine_on_plane()
	{
		m_tmp_plane = samoloty.back();
		unload();
		repair();
		refuel();
		load();
		cout << "\n" << endl;
	}

	void load() //not sure bout type
	{
		int cap{ m_tmp_plane.get_capacity() };
		int ppl_to_load;
		(cap >= m_waiting_ppl) ? (ppl_to_load = cap) : (ppl_to_load = m_waiting_ppl);
		m_tmp_plane.set_passengers(ppl_to_load);
		cout << "Loaded : " << m_tmp_plane.get_passengers() << " passengers" << endl;
	}
	void unload() //not sure bout type
	{
		int tmp_ppl_unloaded = m_tmp_plane.get_passengers();
		m_tmp_plane.set_passengers(0);
		cout << "Unloaded: " << tmp_ppl_unloaded << " passengers" << endl;
	}
	void refuel() //not sure bout type
	{
		m_tmp_plane.set_fuel(1.00);
		cout << "Refueled plane with index: " << m_tmp_plane.get_plane_index() << endl;
	}
	void repair()  //not sure bout type
	{
		if (m_tmp_plane.get_tech_state() < 0.8)
		{
			m_tmp_plane.set_tech_state(1.00);
			cout << "Repaired plane with index: " << m_tmp_plane.get_plane_index() << endl;
		}
		else
		{
			cout << "No maintenance needed for plane: " << m_tmp_plane.get_plane_index() << endl;
		}
	}
	int wait_in_hangar(int how_long, int how_long_left)
	{
		//sleep for x ticks, x1 - trackers of sleept time
	}
	bool landing(int airport_index, int airstrip)
	{
		//wyladuje samolot

	}
	bool taking_off(int airstrip)
	{
		//wystatuj samolot z lotniska
	}



};

//OLEK


int main(int argc, char* argv[])
{
	srand(time(NULL));
	Airport Los_Angles,Katowice;
	Samolot p1;
	Los_Angles.register_plane(p1);
	

	
	
	//samoloty.back().introduce();

	return 0;
}