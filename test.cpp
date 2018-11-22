#include <iostream>
#include <vector>
using namespace std;



/*
ZAPYTAJ PAWŁA:
-KAZ IM SIĘ PRZY TWORZENIU PRZYPISYWAĆ DO WEKTORA PRZYPISANEGO ODGÓRNIE
-JAK KOPIOWAĆ

*/
class Samolot;
class Airport;

// GLOBAL VARS
int new_plane_index = 1; // those are initial indeces when creating objects, incrementation after creation :) 
int new_airport = 1;

vector <Samolot> samoloty;
vector <Airport> lotniska;


class Samolot
    {
    private:
        int m_dest, m_src; //indexes of airports
        int m_index;
       

    public:
    //CONSTR AND DECONSTR
        Samolot() :m_dest(1), m_src(2), m_index(new_plane_index)
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

    };

class Airport
    {
    private:
        int m_index_ap; //index of airport
        int m_waiting_ppl;

        vector <Samolot*> przypisane_samoloty;

    public:
    //CONSTR AND DECONSTR
        Airport(int index = 1) : m_index_ap(new_airport)
            {
                lotniska.push_back(*this);
                cout << "Airport created with index no: " << m_index_ap << endl;
                new_airport++;
            }
        Airport(const Airport &lotnisko):m_index_ap(lotnisko.m_index_ap)
        {

            /////////////////////////// JAK KOPIOWAĆ !!!!!!!!!!!!!!!!!!!
            cout<<"copying glorius airport"<<endl;
        }
        ~Airport()
            {
                 cout<<"Airport with index: "<<m_index_ap <<" was destroyed" <<endl;
            }
        void Say()
            {

               cout << "Airport  with index no: " << m_index_ap << endl; 
            }


    };


int main(int argc, char* argv[])
{
    srand(time(NULL));



    Airport Los_Angles,Katowice, London;
    Samolot p1,p2;


    lotniska[0].Say();
    lotniska[1].Say();
    lotniska[2].Say();

    return 0;
}



