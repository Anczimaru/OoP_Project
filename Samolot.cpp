#include <iostream>
#include <vector>


using namespace std;

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
        Samolot(int dest=1,int src=2,int capacity=80,int passengers=60,int status = 1,double fuel_state=0.8,double tech_state=0.8,int index=1):
            m_dest(dest), m_src(src), m_capacity(capacity), m_passengers(passengers), m_status(status), m_fuel(fuel_state), m_tech_state(tech_state), m_index(index)
            {
                cout<<"Im plane with no:"<<m_index<<endl;
                fly_to_airport(m_dest);
            }
        ~Samolot()
            {
                //cout<<"destroyed plane"<<endl;
            }
        void fly_to_airport(int airport_index)
            {
                cout<<"Im flying to: "<<m_dest<<endl;
            }
        int get_dest()
            {
                return m_dest;
            }
        void set_dest(int dest) 
            {m_dest = dest;}
        int get_plane_index()
            {
            return m_index;
            }
        int get_capacity() 
            {return m_capacity;}
        int get_passengers()
            {return m_passengers;}
        void set_passengers(int passengers)
            {m_passengers = passengers;}

    };

class Airport
    {
    private:
        int m_index_ap; //index of airport
        int m_waiting_ppl;

        vector <Samolot> samoloty;
        Samolot m_plane;

    public:
        Airport(int index = 1) : m_index_ap(index)
            {
                cout<<"Airport created with index no: "<< m_index_ap<<endl;
            }
        ~Airport()
            {
                cout<<"Airport with index: "<<m_index_ap <<" was destroyed" <<endl;
            }
        void register_plane(Samolot plane)
            {
                samoloty.push_back(plane);
                cout<<"Airport: "<<m_index_ap<<" registered plane with index: "<<samoloty.back().get_plane_index()<<endl;
            }
        
        void do_routine_on_plane()
            {
                m_plane = samoloty.back();
                loading();
            }
        
        double loading() //not sure bout type
            {
                int cap {m_plane.get_capacity()};
                int ppl_to_load;
                (cap >= m_waiting_ppl)? (ppl_to_load = cap) : (ppl_to_load = m_waiting_ppl);
                m_plane.set_passengers(ppl_to_load);
                cout<<"Loaded : "<<m_plane.get_passengers()<<" passengers"<<endl;
            }
        double unload(int arr_passangers, int gate) //not sure bout type
            {
                //unload passangers
            }
        double refuel(double m_fuel) //not sure bout type
            {
                //refuel airplane
            }
        int service(double m_tech_state)  //not sure bout type
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



int main(int argc, char* argv[])
{
    Airport Los_Angles;
    Samolot r1;
    Los_Angles.register_plane(r1);
    Los_Angles.do_routine_on_plane();
    Samolot r2();
    Los_Angles.register_plane(r2);
    Los_Angles.do_routine_on_plane();
    //samoloty.back().introduce();

    return 0;
}
