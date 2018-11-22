#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

// CLASSES DECLARATION
class Samolot;
class Airport;

// GLOBAL VARS
int new_plane_index = 1; // those are initial indeces when creating objects, incrementation after creation :) 
int new_airport = 1;

//GLOBAL VECTORS DECLARATION
vector <Samolot> samoloty;
vector <Airport> lotniska;


//ENUM FOR PLANE STATUS
enum status_t 
    {  
        /*
        1 - flying, 2 - waiting, 3 - landing, 4 - unloading, 5 - repairs, 6 - refueling, 7 - loading, 8 - departing, 9 - hangar
        */
        flying =1,
        waiting =2,
        landing =3,
        unloading =4,
        repairing =5,
        refueling =6,
        loading =7,
        departing =8,
        flying_away =9
    };

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
        int m_index; //index of airplane
        int m_airline; //index of airline
        int m_airstrip; // index of airstrip
        double m_fuel; // percentage of fuel in airplane
        double m_tech_state; //percentage of airplane maintenance
        status_t m_status; // TO DO CHANGE TO ENUM

    public:
       /* Samolot(int dest=1,int src=2,int capacity=80,int passengers=60,int status = 2,double fuel_state=0.8,double tech_state=0.8,int index=1):
            m_dest(dest), m_src(src), m_capacity(capacity), m_passengers(passengers), m_status((status_t)status), m_fuel(fuel_state), m_tech_state(tech_state), m_index(index)
            {
                // cout<<"Im plane with no:"<<m_index<<endl;
            } */
    //CONSTR AND DECONSTR
        Samolot(status_t status = flying) :m_dest(1), m_src(2), m_capacity(80), m_passengers(60), m_status((status_t)status), m_fuel(0.78), m_tech_state(0.99), m_index(new_plane_index)
            {
                
                cout <<	"Im plane with no:"<<m_index<<endl;
                new_plane_index++;
                
            }
        ~Samolot()
            {
                cout<<"   destroyed plane no: "<<m_index<<endl;
            }
    //FUNCTIONS
        void fly_to_airport()
            {
                cout << "Hi, Im plane number: "<<m_index<<"\tIm flying to: " << m_dest << "\tfrom: "<<m_src<< endl;
            }
    // SETTERS AND GETTERS
    //DESTINATION
        int get_dest()
            { return m_dest; }
        void set_dest(int target_dest) 
            { m_dest = target_dest; }
    //SRC
        void set_src(int src)
            { m_src = src; }
        int get_src()
            { return m_src; }
        void whereAmI()
            {
                //Do testów
                cout << "Im located at: " << m_src << endl;
            }
    //INDEX
        int get_plane_index()
            { return m_index; }
    //PASSENGERS
        int get_capacity() 
            { return m_capacity; }
        int get_passengers()
            { return m_passengers; }
        void set_passengers(int target_passengers)
            { m_passengers = target_passengers; }
    //FUEL AND TECH STATE
        double get_fuel()
            { return m_fuel; }
        void set_fuel(double target_fuel)
            { m_fuel = target_fuel; }
        double get_tech_state()
            { return m_tech_state; }
        void set_tech_state(double target_state)
            { m_tech_state = target_state; }
    //STATUS OF PLANE
        status_t get_status()
            { return m_status; }
        void set_status(status_t tmp_status)
            {m_status = tmp_status;}
        void set_status(int i)
            {m_status = (status_t)i;}
        void increment_status()
            {
            int x = (int) m_status;
            x++;
            m_status = (status_t) x;
            cout<<"changed status to: "<<x<<endl;
            if (x>=10) x=1;
            }
    };


class Airport
    {
    private:
        int m_index_ap; //index of airport
        int m_waiting_ppl;

        vector <Samolot*> przypisane_samoloty;

    public:
    //CONSTR AND DECONSTR
        Airport(int index = 1) : m_index_ap(new_airport), m_waiting_ppl(200)
            {
                lotniska.push_back(*this);
                cout << "Airport created with index no: " << m_index_ap << endl;
                new_airport++;
            }

        Airport(const Airport &lotnisko):m_index_ap(lotnisko.m_index_ap), m_waiting_ppl(lotnisko.m_waiting_ppl)
            {
                // cout<<"copying glorius airport"<<endl;
            }
        ~Airport()
            {
                // cout<<"Airport with index: "<<m_index_ap <<" was destroyed" <<endl;
            }
    //FUNCTIONS
        void register_plane(Samolot &plane)
            {
                samoloty.push_back(plane);
                samoloty.back().set_dest(m_index_ap);
                
                
                cout << "Airport: " << m_index_ap << " registered plane with index: " << samoloty.back().get_plane_index() << endl;
                samoloty.back().fly_to_airport();
            }
        
        Samolot* reassign_plane(Samolot &plane)
            {
                plane.get_plane_index();

            }
    //ROUTINES
        void do_routine_on_plane(Samolot &m_tmp_plane)
            {
                //HEART OF ACTION IF DOES APRIOPRIATE ACTIONS DEPENDING ON STATUS OF PLANE
                //iterate over converted int status
                //taking apriopriate actions
                switch(m_tmp_plane.get_status())
                    {
                    case status_t::flying:
                        m_tmp_plane.set_status(waiting);
                        cout<<"     plane no: "<<m_tmp_plane.get_plane_index()<<" is flying"<<endl;
                        break;  
                    case status_t::waiting:
                        m_tmp_plane.set_status(landing);
                        cout<<"     plane no: "<<m_tmp_plane.get_plane_index()<<" is waiting for landing"<<endl;
                        break; 
                    case status_t::landing:
                        land(m_tmp_plane);
                        m_tmp_plane.set_status(unloading);
                        cout<<"     plane no: "<<m_tmp_plane.get_plane_index()<<" landed"<<endl;
                        break;   
                    case status_t::unloading:
                        unload(m_tmp_plane);
                        m_tmp_plane.set_status(repairing);
                        cout<<"     plane no: "<<m_tmp_plane.get_plane_index()<<" was unloaded"<<endl;
                        break; 
                    case status_t::repairing:
                        repair(m_tmp_plane);
                        m_tmp_plane.set_status(refueling);
                        cout<<"     plane no: "<<m_tmp_plane.get_plane_index()<<" repaired"<<endl;
                        break; 
                    case status_t::refueling:
                        refuel(m_tmp_plane);
                        m_tmp_plane.set_status(loading);
                        cout<<"     plane no: "<<m_tmp_plane.get_plane_index()<<" refeueled"<<endl;
                        break; 
                    case status_t::loading:
                        load(m_tmp_plane);
                        m_tmp_plane.set_status(departing);
                        cout<<"     plane no: "<<m_tmp_plane.get_plane_index()<<" loaded"<<endl;
                        break; 
                    case status_t::departing:
                        m_tmp_plane.set_status(flying_away);
                        cout<<"     plane no: "<<m_tmp_plane.get_plane_index()<<" is leaving"<<endl;
                        break;
                    }
            }
        void do_routine()
            {
                do
                {
                    for (int i =0;i<samoloty.size();i++)
                    {
                        do_routine_on_plane(samoloty[i]);
                        if(samoloty[i].get_status()==flying_away)
                            {
                                samoloty.erase(samoloty.begin()+i);    
                            }
                    }


                }while(samoloty.size()>0);


            }
    //ROUTINE SUB FUNCTIONS
        void load(Samolot &m_tmp_plane) 
            {   
                //load people to plane
                int cap {m_tmp_plane.get_capacity()};
                cout << cap<<endl;
                int ppl_to_load;
                (cap >= m_waiting_ppl)? (ppl_to_load = cap) : (ppl_to_load = m_waiting_ppl);
                cout <<ppl_to_load <<endl; 
                m_tmp_plane.set_passengers(ppl_to_load);
                cout<<"         Loaded : "<<m_tmp_plane.get_passengers()<<" passengers"<<endl;
            }
        void unload(Samolot &m_tmp_plane)
            {
                //unload ppl from plane
                int tmp_ppl_unloaded = m_tmp_plane.get_passengers();
                m_tmp_plane.set_passengers(0);
                cout<<"         Unloaded: "<<tmp_ppl_unloaded<<" passengers"<<endl;
            }
        void refuel(Samolot &m_tmp_plane)
            {
                m_tmp_plane.set_fuel(1.00);
                cout<<"         Refueled plane with index: "<<m_tmp_plane.get_plane_index()<<endl;
            }
        void repair(Samolot &m_tmp_plane)  //if plane maintenance below 80% repair it
            {
                if (m_tmp_plane.get_tech_state() < 0.8)
                    {
                        m_tmp_plane.set_tech_state(1.00);
                        cout<<"         Repaired plane with index: "<<m_tmp_plane.get_plane_index()<<endl;
                    }
                else
                    {
                        cout<<"         No maintenance needed for plane: "<<m_tmp_plane.get_plane_index()<<endl;
                    }
            }
        int wait_in_hangar(int how_long, int how_long_left)
            {
                //sleep for x ticks, x1 - trackers of sleept time
            }
        void land(Samolot &m_tmp_plane)
            {
                do
                {
                    samoloty.back().set_dest(gibMe());

                } while (samoloty.back().get_dest() == m_index_ap);

                m_tmp_plane.set_src(m_index_ap);
                m_tmp_plane.fly_to_airport();
                //wyladuje samolot

            }
        bool take_off(int airstrip)
            {
                //wystatuj samolot z lotniska
            }
        void check_out()
            {


            }


    };



int main(int argc, char* argv[])
{
    srand(time(NULL));
	Airport Los_Angles,Katowice, London;
	Samolot p1;   
	Los_Angles.register_plane(p1);
	
    // Los_Angles.register_plane(r2);
    // Los_Angles.register_plane(r3);

    Los_Angles.do_routine();

   /* Samolot r2(2);
    Los_Angles.register_plane(r2);
    Los_Angles.do_routine_on_plane();
    */
   return 0;
}
