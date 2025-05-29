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

class User
{
protected:
    string username, password;

public:
    User(string uname = "", string pass = "") : username(uname), password(pass) {}
    virtual bool login(string uname, string pass) = 0;
    virtual void changePassword(string newPass) = 0;
    virtual ~User() {}
};

class UserGuest : public User
{
protected:
public:
    UserGuest(string uname = "", string pass = "") : User(uname, pass) {}
    virtual void viewStations(const vector<Station> &stations);
    virtual void viewAvailability(const vector<Train> &trains, const string &from, const string &to, const string &date);
    virtual void logout();
    virtual ~UserGuest();
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
    void bookTicket(vector<Train> &trains, vector<Station> &stations);
    void cancelTicket(Ticket &myticket);
    void viewMyTickets();
};

class Station
{
private:
    int stationId;
    string name;

public:
    Station(int id = 0, string name = "") : stationId(id), name(name) {}
    int getId() const;
    string getName() const;
    void viewStation() const;
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

    string getClassName() const;
    int getAvailableSeats() const;
    float getFare() const;
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
    void viewTrain() const;
    bool checkAvailability(int fromStationId, int toStationId, const Date &date, const string &className) const;
    float getFare(const string &className) const;
    void addClass(const TravelClass &travelClass);
    void setRoute(const vector<int> &route);
    int getId() const;
    string getName() const;
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
    Ticket(int ticketNo, const string &pnr, Passenger &passenger, Train &train, Station &origin,
           Station &destination, int seatNumber, float fare, TravelClass &travelClass, Date &date)
        : ticketNo(ticketNo), pnr(pnr), passenger(passenger), train(train), origin(origin), destination(destination),
          seatNumber(seatNumber), fare(fare), travelClass(travelClass), date(date) {}
    void printTicket() const;
    string getPNR() const;
};

class AdminPanel
{
public:
    static void addTrain(vector<Train> &trains, const Train &newTrain);
    static void updateTrainRoute(Train &train, const vector<int> &newRoute);
    static void updateTrainFare(Train &train, const string &className, float newFare);
    static void updateTrainSeats(Train &train, const string &className, int newTotalSeats);
    static void addStation(vector<Station> &stations, const Station &newStation);
    static void removeStation(vector<Station> &stations, int stationId);
    static void viewAllTrains(const vector<Train> &trains);
    static void viewAllStations(const vector<Station> &stations);
};

class Date
{
    int day;
    int month;
    int year;

public:
    Date(int day = 0, int month = 0, int year = 0) : day(day), month(month), year(year) {}
    int Calculate_days(Date Start_date, Date End_date);
};

int main()
{

    return 0;
}