#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class User;
class Station;
class TravelClass;
class Train;
class Ticket;
class Guest;
class Passenger;
class AdminPanel;
class Date;

AdminPanel adminPanel;
class User
{
protected:
    string username, password;

public:
    User(string uname = "", string pass = "") : username(uname), password(pass) {}
    virtual bool login(string uname, string pass);
    virtual bool changePassword(string newPass);
    ~User() {}
};

class UserGuest : public User
{
protected:
public:
    UserGuest(string uname = "", string pass = "") : User(uname, pass) {}
    virtual void viewStations();
    virtual vector<Train *> viewAvailability(string &from, string &to, Date &date);
    virtual void logout();
    ~UserGuest() {}
};

class Passenger : public UserGuest
{
private:
    string fullName;
    string email;
    string phone;
    vector<Ticket> myTickets;

public:
    Passenger(string uname = "", string pass = "", string name = "", string email = "", string phone = "")
        : UserGuest(uname, pass), fullName(name), email(email), phone(phone) {}
    string getUsername() { return username; }
    void bookTicket(Station &from, Station &to, TravelClass &travelClass, Date &date);
    void cancelTicket();
    void viewMyTickets();
    ~Passenger() {}
};

class Station
{
private:
    int stationId;
    string name;

public:
    Station(int id = 0, string name = "") : stationId(id), name(name) {}
    int getId();
    string getName();
    void viewStation();
    ~Station() {}
};

class TravelClass
{
private:
    string className; // e.g., "AC", "Sleeper"
    int totalSeats;
    int bookedSeats;
    float fare;

public:
    TravelClass(string name = "", int total = 0, int booked = 0, float fare = 0.0) : className(name), totalSeats(total), bookedSeats(booked), fare(fare) {}

    string getClassName();
    int getAvailableSeats();
    int getBookedSeats();
    int getSeatNumber() {};
    float getFare();
    float setFare(float newFare);
    void setTotalSeats(int newTotalSeats);
    ~TravelClass() {}
};

class Train
{
private:
    int trainId;
    string name;
    vector<int> route;
    vector<TravelClass> classes;

public:
    Train(int id = 0, string name = "") : trainId(id), name(name) {}
    int getId();
    string getName();
    float getFare(string &className);
    vector<int> getRoute();
    vector<TravelClass> getClasses();
    void setroute(vector<int> &newRoute);
    void addClass(TravelClass &newClass);

    void viewTrain();
};

class Ticket
{
    int ticketNo;
    string pnr;
    Passenger &passenger;
    Train &train;
    Station &origin;
    Station &destination;
    int seatNumber;
    float fare;
    TravelClass &travelClass;
    Date &date;

public:
    Ticket(int ticketNo, string &pnr, Passenger &passenger, Train &train, Station &origin,
           Station &destination, int seatNumber, float fare, TravelClass &travelClass, Date &date)
        : ticketNo(ticketNo), pnr(pnr), passenger(passenger), train(train), origin(origin), destination(destination),
          seatNumber(seatNumber), fare(fare), travelClass(travelClass), date(date) {}
    int getTicketNo();
    string getPNR();
    int getSeatNumber();
    Train &getTrain();
    Station &getOrigin();
    Station &getDestination();
    Date &getDate();
    float getFare();
    TravelClass &getTravelClass();

    void printTicket();
    void viewTicket();
    ~Ticket() {}
};

class AdminPanel
{
    vector<Train> trains;
    vector<Station> stations;

public:
    AdminPanel() {}
    int generateTicketNo();
    string generatePNR();

    void addTrain();
    void addStation();

    vector<Train *> getTrains();
    vector<Station *> getStations();

    void viewAllTrains();
    void viewAllStations();

    void updateTrainRoute(int trainId);
    void updateTrainFare(int trainId, string &className, float newFare);
    void updateTrainSeats(int trainId, string &className, int newTotalSeats);

    void addStationObject(const Station &s)
    {
        stations.push_back(s);
    }
    void addTrainObject(const Train &t)
    {
        trains.push_back(t);
    }

    ~AdminPanel() {}
};

class Date
{
    int day;
    int month;
    int year;

public:
    Date(int day = 0, int month = 0, int year = 0) : day(day), month(month), year(year) {}
    int Calculate_days(Date Start_date, Date End_date);
    string show_date();
};

bool User::login(string uname, string pass)
{
    return (username == uname && password == pass);
}

bool User::changePassword(string newPass)
{
    if (!newPass.empty())
    {
        password = newPass;
        return true;
    }
    return false;
}

void UserGuest::viewStations()
{
    adminPanel.viewAllStations();
}

vector<Train *> UserGuest::viewAvailability(string &from, string &to, Date &date)
{
    vector<Station *> stations = adminPanel.getStations();
    int fromId = -1, toId = -1;
    for (auto &&station : stations)
    {
        if (station->getName() == from)
            fromId = station->getId();
        if (station->getName() == to)
            toId = station->getId();
    }
    vector<Train *> trains = adminPanel.getTrains();
    Date travelDate;
    vector<Train *> availableTrains;
    for (auto &&train : trains)
    {
        vector<int> route = train->getRoute();
        bool fromFound = false, toFound = false;
        for (auto &&stationId : route)
        {
            if (stationId == fromId)
                fromFound = true;
            if (stationId == toId)
                toFound = true;
            if (fromFound && toFound)
                break;
        }
        if (fromFound && toFound)
        {
            vector<TravelClass> classes = train->getClasses();
            for (auto &&travelclass : classes)
            {
                bool flag = false;
                if (travelclass.getAvailableSeats() > 0)
                {
                    cout << availableTrains.size() + 1 << ". Train ID: " << train->getId() << ", Name: " << train->getName() << endl;
                    cout << "Available Classes: " << endl;
                    cout << travelclass.getClassName() << " - Available Seats: " << travelclass.getAvailableSeats() << ", Fare: " << travelclass.getFare() << endl;
                    if (!flag)
                    {
                        availableTrains.push_back(train);
                        flag = true;
                    }
                }
            }
        }
    }
    return availableTrains;
}

void UserGuest::logout()
{
    cout << "Logged out successfully." << endl;
}

void Passenger ::bookTicket(Station &from, Station &to, TravelClass &travelClass, Date &date)
{
    string from_station = from.getName();
    string to_station = to.getName();
    vector<Train *> availableTrains = viewAvailability(from_station, to_station, date);
    if (availableTrains.empty())
    {
        cout << "No trains available for the selected route." << endl;
        return;
    }
    cout << "Enter the serial number of the train you want to book: ";
    int trainIndex;
    cin >> trainIndex;
    while (trainIndex < 1 || trainIndex > availableTrains.size())
    {
        cout << "Invalid train selection. Enter correct index" << endl;
        cin >> trainIndex;
    }
    Train *selectedTrain = availableTrains[trainIndex - 1];
    int ticketNo = adminPanel.generateTicketNo();
    int seatNumber = travelClass.getSeatNumber();
    if (seatNumber == -1)
    {
        cout << "No seats available." << endl;
        return;
    }
    string pnr = adminPanel.generatePNR();
    Ticket newTicket(
        ticketNo,
        pnr,
        *this,
        *selectedTrain,
        from,
        to,
        travelClass.getAvailableSeats() - travelClass.getBookedSeats() + 1,
        travelClass.getFare(),
        travelClass,
        date);
    myTickets.push_back(newTicket);
    cout << "Ticket booked successfully!" << endl;
    cout << "Ticket No: " << ticketNo << ", PNR: " << pnr << endl;
    newTicket.printTicket();
}

void Passenger::cancelTicket()
{
    for (int i = 0; i < myTickets.size(); i++)
    {
        cout << i + 1 << ". Ticket No: " << myTickets[i].getPNR() << endl;
    }
    cout << "Enter the serial number of the ticket you want to cancel: ";
    int ticketIndex;
    cin >> ticketIndex;
    while (ticketIndex < 1 || ticketIndex > myTickets.size())
    {
        cout << "Invalid ticket selection. Enter correct index" << endl;
        cin >> ticketIndex;
    }
    myTickets.erase(myTickets.begin() + ticketIndex - 1);
    cout << "Ticket cancelled successfully!" << endl;
}

void Passenger::viewMyTickets()
{
    if (myTickets.empty())
    {
        cout << "No tickets booked yet." << endl;
        return;
    }
    for (int i = 0; i < myTickets.size(); i++)
    {
        cout << i + 1 << ' ';
        myTickets[i].viewTicket();
    }
}

int Station::getId()
{
    return stationId;
}
string Station::getName()
{
    return name;
}
void Station::viewStation()
{
    cout << "Station ID: " << stationId << ", Name: " << name << endl;
}

string TravelClass::getClassName()
{
    return className;
}
int TravelClass::getAvailableSeats()
{
    return totalSeats - bookedSeats;
}
int TravelClass::getBookedSeats()
{
    return bookedSeats;
}
int TravelClass::getSeatNumber()
{
    if (getAvailableSeats() > 0)
    {
        bookedSeats++;
        return totalSeats - bookedSeats + 1;
    }
    return -1;
}
float TravelClass::getFare()
{
    return fare;
}
float TravelClass::setFare(float newFare)
{
    fare = newFare;
    return fare;
}

void TravelClass::setTotalSeats(int newTotalSeats)
{
    totalSeats = newTotalSeats;
}

int Train::getId()
{
    return trainId;
}
string Train::getName()
{
    return name;
}
float Train::getFare(string &className)
{
    for (auto &&travelClass : classes)
    {
        if (travelClass.getClassName() == className)
        {
            return travelClass.getFare();
        }
    }
    return 0.0;
}
vector<int> Train::getRoute()
{
    return route;
}

vector<TravelClass> Train::getClasses()
{
    return classes;
}
void Train ::setroute(vector<int> &newRoute)
{
    route = newRoute;
}
void Train::addClass(TravelClass &newClass)
{
    classes.push_back(newClass);
}
void Train::viewTrain()
{
    cout << "Train ID: " << trainId << ", Name: " << name << endl;
    cout << "Route: ";
    for (auto &&stationId : route)
    {
        cout << stationId << " ";
    }
    cout << endl;
    cout << "Classes: " << endl;
    for (auto &&travelClass : classes)
    {
        cout << travelClass.getClassName() << " - Total Seats: " << travelClass.getAvailableSeats() + travelClass.getBookedSeats()
             << ", Available Seats: " << travelClass.getAvailableSeats() << ", Fare: " << travelClass.getFare() << endl;
    }
}
int Ticket::getTicketNo()
{
    return ticketNo;
}

string Ticket::getPNR()
{
    return pnr;
}

int Ticket ::getSeatNumber()
{
    return seatNumber;
}

Train &Ticket::getTrain()
{
    return train;
}
Station &Ticket::getOrigin()
{
    return origin;
}
Station &Ticket::getDestination()
{
    return destination;
}
Date &Ticket::getDate()
{
    return date;
}
float Ticket::getFare()
{
    return fare;
}
TravelClass &Ticket::getTravelClass()
{
    return travelClass;
}
void Ticket::printTicket()
{
    // print ticket in HTML file
}

void Ticket ::viewTicket()
{
    cout << "Ticket No: " << ticketNo << endl;
    cout << "PNR: " << pnr << endl;
    cout << "Passenger: " << passenger.getUsername() << endl;
    cout << "Train: " << train.getName() << endl;
    cout << "From: " << origin.getName() << " To: " << destination.getName() << endl;
    cout << "Date: " << date.show_date() << endl;
    cout << "Travel Class: " << travelClass.getClassName() << endl;
    cout << "Seat Number: " << seatNumber << endl;
    cout << "Fare: " << fare << endl;
}

int AdminPanel ::generateTicketNo()
{
    static int ticketNo = 10000;
    return ticketNo++;
}
string AdminPanel ::generatePNR()
{
    vector<char> numbers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    string pnr = "";
    while (pnr.length() < 10)
    {
        pnr += numbers[rand() % numbers.size()];
    }
    return pnr;
}

void AdminPanel::addTrain()
{
    int id;
    string name;
    cout << "Enter Train ID: ";
    cin >> id;
    cout << "Enter Train Name: ";
    cin.ignore();
    getline(cin, name);
    Train newTrain(id, name);
    trains.push_back(newTrain);
    vector<int> route;
    vector<Station *> stations = getStations();
    viewAllStations();
    cout << "Enter the number of stations in the route: ";
    int numStations;
    cin >> numStations;
    cout << "Enter the route (serial numbers of stations, separated by spaces): ";
    int stationInd;
    for (int i = 0; i < numStations; i++)
    {
        cin >> stationInd;
        while (stationInd < 1 || stationInd > stations.size())
        {
            cout << "Invalid station index. Please try again." << endl;
            cin >> stationInd;
        }
        route.push_back(stations[stationInd - 1]->getId());
    }
    newTrain.setroute(route);
    int numClasses;
    cout << "Enter the number of travel classes: ";
    cin >> numClasses;
    for (int i = 0; i < numClasses; i++)
    {
        string className;
        cout << "Enter Class Name: ";
        cin >> className;
        int totalSeats;
        cout << "Enter Total Seats: ";
        cin >> totalSeats;
        float fare;
        cout << "Enter Fare: ";
        cin >> fare;
        TravelClass newClass(className, totalSeats, 0, fare);
        newTrain.addClass(newClass);
    }
    cout << "Train added successfully!" << endl;
}

void AdminPanel::addStation()
{
    int id;
    string name;
    cout << "Enter Station ID: ";
    cin >> id;
    cout << "Enter Station Name: ";
    cin.ignore();
    getline(cin, name);
    Station newStation(id, name);
    stations.push_back(newStation);
    cout << "Station added successfully!" << endl;
}
vector<Train *> AdminPanel::getTrains()
{
    vector<Train *> trainPointers;
    for (auto &&train : trains)
    {
        trainPointers.push_back(&train);
    }
    return trainPointers;
}
vector<Station *> AdminPanel::getStations()
{
    vector<Station *> stationPointers;
    for (auto &&station : stations)
    {
        stationPointers.push_back(&station);
    }
    return stationPointers;
}

void AdminPanel::viewAllTrains()
{
    if (trains.empty())
    {
        cout << "No trains available." << endl;
        return;
    }
    for (int i = 0; i < trains.size(); i++)
    {
        cout << i + 1 << ". ";
        trains[i].viewTrain();
    }
}
void AdminPanel::viewAllStations()
{
    if (stations.empty())
    {
        cout << "No stations available." << endl;
        return;
    }
    for (int i = 0; i < stations.size(); i++)
    {
        cout << i + 1 << ". ";
        stations[i].viewStation();
    }
}

void AdminPanel ::updateTrainRoute(int trainId)
{
    for (auto &&train : trains)
    {
        if (train.getId() == trainId)
        {
            vector<int> newRoute;
            vector<Station *> stations = getStations();
            viewAllStations();
            cout << "Enter the number of stations in the new route: ";
            int numStations;
            cin >> numStations;
            cout << "Enter the new route (serial numbers of stations, separated by spaces): ";
            int stationInd;
            for (int i = 0; i < numStations; i++)
            {
                cin >> stationInd;
                while (stationInd < 1 || stationInd > stations.size())
                {
                    cout << "Invalid station index. Please try again." << endl;
                    cin >> stationInd;
                }
                newRoute.push_back(stations[stationInd - 1]->getId());
            }
            train.setroute(newRoute);
            cout << "Train route updated successfully!" << endl;
            return;
        }
    }
    cout << "Train not found." << endl;
}

void AdminPanel ::updateTrainFare(int trainId, string &className, float newFare)
{
    for (auto &&train : trains)
    {
        if (train.getId() == trainId)
        {
            vector<TravelClass> classes = train.getClasses();
            for (auto &&travelClass : classes)
            {
                if (travelClass.getClassName() == className)
                {
                    travelClass.setFare(newFare);
                    cout << "Fare updated successfully!" << endl;
                    return;
                }
            }
            cout << "Travel class not found." << endl;
            return;
        }
    }
    cout << "Train not found." << endl;
}

void AdminPanel ::updateTrainSeats(int trainId, string &className, int newTotalSeats)
{
    for (auto &&train : trains)
    {
        if (train.getId() == trainId)
        {
            vector<TravelClass> classes = train.getClasses();
            for (auto &&travelClass : classes)
            {
                if (travelClass.getClassName() == className)
                {
                    travelClass.setTotalSeats(newTotalSeats);
                    cout << "Total seats updated successfully!" << endl;
                    return;
                }
            }
            cout << "Travel class not found." << endl;
            return;
        }
    }
    cout << "Train not found." << endl;
}

int Date ::Calculate_days(Date Start_date, Date End_date)
{
    int days = 0;
    vector<int> days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int day1 = Start_date.day, day2 = End_date.day;
    int month1 = Start_date.month, month2 = End_date.month;
    int year1 = Start_date.year, year2 = End_date.year;
    if (year1 > year2 || (year1 == year2 && month1 > month2) || (year1 == year2 && month1 == month2 && day1 > day2))
    {
        cout << "Invalid date range." << endl;
        return -1;
    }
    if (year1 == year2)
    {
        if (month1 == month2)
        {
            days = day2 - day1;
        }
        else
        {
            days += days_in_month[month1 - 1] - day1;
            for (int i = month1; i < month2 - 1; i++)
            {
                days += days_in_month[i];
            }
            days += day2;
        }
    }
    else
    {
        days += days_in_month[month1 - 1] - day1;
        for (int i = month1; i < 12; i++)
        {
            days += days_in_month[i];
        }
        for (int i = 0; i < month2 - 1; i++)
        {
            days += days_in_month[i];
        }
        days += day2;
        for (int i = year1 + 1; i < year2; i++)
        {
            if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
                days += 366;
            else
                days += 365;
        }
        return days;
    }
}

string Date::show_date()
{
    string date = "";
    if (day < 10)
        date += "0";
    date += to_string(day) + "/";
    if (month < 10)
        date += "0";
    date += to_string(month) + "/";
    date += to_string(year);
    return date;
}
int main()
{

    return 0;
}