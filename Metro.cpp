#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
using namespace std;

typedef struct Station
{
    Station *previous;
    string stationname;
    int traveltime;
    Station *next;
}Station;

Station* generate_metro_line(int linenumber, int mstationnumber)
{
    Station * prev = NULL;
    Station * n;
    Station * pStation;
    for(int i = 0; i < mstationnumber;i++)
    {
        n = new Station;//Station A
        if(i != 0)
            prev->next = n;
        else
            pStation = n;
        n->previous = prev;
        n->stationname = "line " + to_string(linenumber) + " station " + to_string(i + 1);
        n->traveltime = rand() % 5 + 1;
        n->next = NULL;
        prev = n;
        
    }

    return pStation;
}

void output(Station s)
{
    cout << s.stationname << endl;
    if(s.next == NULL)
    {
        cout << "end station" << endl << endl;
    }
    else
    {
        cout << "Time to next station: " + to_string(s.traveltime) << endl << endl;
    }
};

void output_line(Station * s_head)
{
    while(s_head->next != NULL)
    {
        output(*s_head);
        s_head = s_head->next;
    }
    cout << "end station" << endl;
}

typedef struct Train
{
    string name;
    int timeleft;
    bool direction;
    Station * nextstation;
}Train;

void init(Train * train1, string name, Station * first_station)
{
    train1->name = name;
    train1->timeleft = first_station->next->traveltime;
    train1->direction = 1;
    train1->nextstation = first_station->next;
}

void output(Train train1)
{
    if(train1.timeleft == 0)
    {
        cout << train1.name << ": stop at "  << train1.nextstation->stationname;
    }
    else
    {
        cout << train1.name << ": " << train1.timeleft << " minute(s) to " << train1.nextstation->stationname;
    }
    if(!train1.direction)
    {
        cout << "(way back)" << endl;
    }
    else
    {
        cout << endl;
    }
} 

void output_all_train(int simtime, Train * train_array[], int array_length)
{
    cout << "\ntime simulation: " << simtime << " min" << endl;
    for(int a = 0; a < array_length;a++)
    {
        output(*train_array[a]);
    }
}

void judge(Train * t1)
{
    if(t1->timeleft == 0)
    {
        if(t1->direction == 1)
        {
            if(t1->nextstation->next == nullptr)
            {
                t1->nextstation = t1->nextstation->previous;
                t1->direction = 0;
            }
            else
            t1->nextstation = t1->nextstation->next;
        }
        else
        {
            if (t1->nextstation->previous == nullptr)
            {
                t1->nextstation = t1->nextstation->next;
                t1->direction = 1;
            }
            else
                t1->nextstation = t1->nextstation->previous;
        }
        t1->timeleft = t1->nextstation->traveltime;
    }
}

int run()
{

    int simtime = 0;
    int station_number1, station_number2;
    while(true)
    {
        cout << "input number of stations of line 1:" << endl;
        cin >> station_number1;
        cout << "input number of stations of line 2:" << endl;
        cin >> station_number2;
        if(station_number1 < 2 || station_number2 < 2)
        {
            cout << "Station number must more than 1!" << endl;
            continue;
        }
        break;
    }

    Station * metro_line1 = generate_metro_line(1, station_number1);
    Station * metro_line2 = generate_metro_line(2, station_number2);
    
    Train t1, t2;
    init(&t1, "train 1", metro_line1);
    init(&t2, "train 2", metro_line2);
    Train * train_array[2] = {&t1, &t2};

    char choice = 'e';
    do
    {
        cout << "\ne for end\nl for line output\nt for train output\n1 for simulate 1 minute" << endl;
        cin >> choice;
        switch (choice)
        {
            case 'e':
                cout << "System exit." << endl;
                break;

            case 'l':
                int line;
                while(true)
                {
                    cout << "which line?" << endl;
                    cin >> line;

                    if(line == 1)
                        output_line(metro_line1);
                    else if(line == 2)
                        output_line(metro_line2);
                    else
                    {
                        cout << "Invalid input.";
                        continue;
                    }
                    break;
                }
                break;

            case 't':
                output_all_train(simtime, train_array, 2);
                break;
                
            case '1':
                output_all_train(simtime, train_array, 2);
                judge(&t1);
                judge(&t2);
                t1.timeleft--;
                t2.timeleft--;
                simtime++;
                break;

            default:
                cout << "Invalid enter." << endl;
                choice = '\0';
                break;
        }
    } while (choice !='e');

    return 0;
}

int main()
{
    run();

    return 0;
}