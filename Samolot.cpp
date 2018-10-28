#include <iostream>

class Samolot
{
private:
    int m_dest, m_src; //indexes of airports
    int m_passenger; //no of passengers
    int m_capacity; // capacity of num of passengers
    int m_gate; //index of m_gate
    int m_status; //
    /*
    1 - flying, 2 - waiting, 3 - landing, 4 - unloading, 5 - maintenance, 6 - repairs, 7 - refueling, 8 - loading, 9 - departing, 10 - hangar
    yoloyloyloylyoyylyoyl
    */
    int m_airline; //index of airline
    int m_airstrip // index of airstrip
    double m_fuel; // percentage of fuel in airplane
    double tech_state //percentage of airplane maintenance

public:
    int greet_airport()
    {
        //przywitaj lotnisko, zapytaj czy możesz u nich ladować, jesli nie to zapytaj się gdzie lecieć
        return 0;
    }
    void fly_to_airport(int airport_index)
    {
        //change m_src, airtport_index ->m_dest;

    }
    double loading(int dep_passangers, int gate) //not sure bout type
    {
        //load passangers <= capacity, track percentage
    }
    double unload(int arr_passangers, int gate) //not sure bout type
    {
        //unload passangers
    }
    double refuel(double fuel_state) //not sure bout type
    {
        //refuel airplane
    }
    int service(tech_state)  //not sure bout type
    {
        // jeśli stan tech < 90 -> wyślij do naprawy
    }
    bool repair(double tech_state)
    {
        //napraw samolot
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
