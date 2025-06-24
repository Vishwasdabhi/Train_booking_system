#include <bits/stdc++.h>
#include <conio.h>

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

void seed()
{
    srand(time(0));
}
class User
{
protected:
    string username, password;

public:
    User(string uname = "", string pass = "") : username(uname), password(pass) {}
    virtual bool login(string uname, string pass);
    virtual bool changePassword(string newPass);
    virtual void setPassword(string newPass)
    {
        password = newPass;
    }
    virtual void logout();
    ~User() {}
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
    int getday() { return day; }
    int getmonth() { return month; }
    int getyear() { return year; }
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
    int classId;
    string className; // e.g., "AC", "Sleeper"
    int totalSeats;
    int bookedSeats;
    float fare;
    map<string, int> classIds = {
        {"AC", 1},
        {"Sleeper", 2},
        {"General", 3},
        {"First Class", 4},
        {"Second Class", 5},
        {"Third Class", 6}};

public:
    TravelClass(int id = 0, string name = "", int total = 0, int booked = 0, float fare = 0.0) : classId(id), className(name), totalSeats(total), bookedSeats(booked), fare(fare)
    {
        classId = classIds[name];
    }

    string getClassName();
    int getId() { return classId; }
    int getTotalSeats() { return totalSeats; }
    int getAvailableSeats();
    int getBookedSeats();
    int getseatNumber();
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
    vector<int> classId; // to save & retrieve TravelClass objects from file

public:
    Train(int id = 0, string name = "") : trainId(id), name(name) {}
    int getId();
    string getName();
    float getFare(string &className);
    vector<int> getRoute();
    vector<TravelClass> &getClasses();
    void setroute(vector<int> &newRoute);
    void addClass(TravelClass &newClass);
    string getroutestr()
    {
        string routeStr = "";
        for (auto &&stationId : route)
        {
            routeStr += to_string(stationId) + " ";
        }
        return routeStr;
    }
    void addroute(int stationId)
    {
        route.push_back(stationId);
    }
    void addclassid(int classId)
    {
        this->classId.push_back(classId);
    }
    string getClassesStr()
    {
        string classesStr = "";
        for (auto &&travelClass : classes)
        {
            classesStr += to_string(travelClass.getId()) + " ";
        }
        return classesStr;
    }
    void addClassObject(TravelClass &c)
    {
        classes.push_back(c);
    }
    vector<int> getClassIds()
    {
        return classId;
    }
    void viewTrain();
};

class Ticket
{
    int ticketNo;
    string pnr;
    string passengerUsername; // to save & retrieve Passenger objects from file
    Train train;
    int trainId; // this also
    Station origin;
    int originId; // this also
    Station destination;
    int destinationId; // this also
    int seatNumber;
    float fare;
    TravelClass travelClass;
    int travelClassId; // this also
    Date date;
    int day, month, year; // this also

public:
    Ticket(int ticketNo = 0, string pnr = "", string passengerusername = "", Train train = Train(), Station origin = Station(), Station destination = Station(), int seatNumber = 0, float fare = 0.0, TravelClass travelClass = TravelClass(), Date date = Date())
        : ticketNo(ticketNo), pnr(pnr), train(train), origin(origin), destination(destination),
          seatNumber(seatNumber), fare(fare), travelClass(travelClass), date(date), passengerUsername(passengerusername)
    {
        trainId = train.getId();
        originId = origin.getId();
        destinationId = destination.getId();
        travelClassId = travelClass.getId();
        day = date.getday();
        month = date.getmonth();
        year = date.getyear();
    }
    Ticket(int ticketNo = 0, string pnr = "", string passengerusername = "", int trainId = 0, int originId = 0, int destinationId = 0, int seatNumber = 0, float fare = 0, int travelClassId = 0, int day = 0, int month = 0, int year = 0) : ticketNo(ticketNo), pnr(pnr), passengerUsername(passengerusername), seatNumber(seatNumber), fare(fare), trainId(trainId), originId(originId), destinationId(destinationId), travelClassId(travelClassId), day(day), month(month), year(year)
    {
        date = Date(day, month, year);
        train = Train();
        origin = Station();
        destination = Station();
        travelClass = TravelClass();
    }
    int getTicketNo();
    string getPNR();
    int getSeatNumber();
    Train &getTrain();
    Station &getOrigin();
    Station &getDestination();
    Date getDate();
    float getFare();
    TravelClass &getTravelClass();
    int gettrainIdfromObj()
    {
        return train.getId();
    }
    int getoriginIdfromObj()
    {
        return origin.getId();
    }
    int getdestinationIdfromObj()
    {
        return destination.getId();
    }
    int gettravelClassIdfromObj()
    {
        return travelClass.getId();
    }
    int getdayfromObj()
    {
        return date.getday();
    }
    int getmonthFromObj()
    {
        return date.getmonth();
    }
    int getyearFromObj()
    {
        return date.getyear();
    }

    string getpassengerUserName()
    {
        return passengerUsername;
    }
    int getTrainId()
    {
        return trainId;
    }
    int getOriginId()
    {
        return originId;
    }
    int getDestinationId()
    {
        return destinationId;
    }
    int getTravelClassId()
    {
        return travelClassId;
    }
    int getday()
    {
        return day;
    }
    int getmonth()
    {
        return month;
    }
    int getyear()
    {
        return year;
    }

    void setPassenger(string newPassenger)
    {
        passengerUsername = newPassenger;
    }
    void setTrain(Train &newTrain)
    {
        train = newTrain;
        trainId = train.getId();
    }
    void setOrigin(Station &newOrigin)
    {
        origin = newOrigin;
        originId = origin.getId();
    }
    void setDestination(Station &newDestination)
    {
        destination = newDestination;
        destinationId = destination.getId();
    }
    void setTravelClass(TravelClass &newTravelClass)
    {
        travelClass = newTravelClass;
        travelClassId = travelClass.getId();
    }
    void setDate(Date &newDate)
    {
        date = newDate;
        day = date.getday();
        month = date.getmonth();
        year = date.getyear();
    }
    void printTicket();
    void viewTicket();
    ~Ticket() {}
};

class UserGuest : public User
{
protected:
public:
    UserGuest(string uname = "", string pass = "") : User(uname, pass) {}
    virtual void viewStations();
    virtual vector<Train *> viewAvailability(string &from, string &to, Date &date);

    ~UserGuest() {}
};

class Passenger : public UserGuest
{
private:
    string fullName;
    string email;
    string phone;
    vector<Ticket> myTickets;
    vector<int> Tickets; // to save & retrive Ticket objects from file

public:
    Passenger(string uname = "", string pass = "", string name = "", string email = "", string phone = "")
        : UserGuest(uname, pass), fullName(name), email(email), phone(phone) {}

    string getUsername() { return username; }
    string getPassword() { return password; }
    string getFullName() { return fullName; }
    string getEmail() { return email; }
    string getPhone() { return phone; }
    string getMyTickets()
    {
        string ticketsList = "";
        for (auto &ticket : myTickets)
        {
            ticketsList += to_string(ticket.getTicketNo()) + " ";
        }
        return ticketsList;
    }
    vector<int> &getMyTicketsvec()
    {
        return Tickets;
    }
    vector<Ticket> &getMyTicketsObj()
    {
        return myTickets;
    }
    void addMyTicket(int ticketNo)
    {
        Tickets.push_back(ticketNo);
    }
    void bookTicket(Train *selectedTrain, Station &from, Station &to, TravelClass &travelClass, Date &date);
    void cancelTicket();
    void viewMyTickets();
    void addTicketObject(Ticket &t)
    {
        myTickets.push_back(t);
    }
    ~Passenger() {}
};

class AdminPanel
{
    vector<Train> trains_admin;
    vector<Station> stations_admin;
    int max_ticket_number = 1000;

public:
    AdminPanel() {}
    AdminPanel(vector<Train> &trains, vector<Station> &stations) : trains_admin(trains), stations_admin(stations) {}
    int generateTicketNo();
    string generatePNR();
    int getMaxTicketNumber()
    {
        return max_ticket_number;
    }
    void setMaxTicketNumber(int newMaxTicketNumber)
    {
        max_ticket_number = newMaxTicketNumber;
    }
    void setTrains(vector<Train> &newTrains)
    {
        trains_admin = newTrains;
    }
    void setStations(vector<Station> &newStations)
    {
        stations_admin = newStations;
    }

    void addTrain();
    void addStation();

    vector<Train *> getTrains();
    vector<Station *> getStations();

    vector<Train> &getTrainsObj()
    {
        return trains_admin;
    }
    vector<Station> &getStationsObj()
    {
        return stations_admin;
    }
    map<int, Station *> getStationsMap()
    {
        map<int, Station *> stationMap;
        for (auto &&station : stations_admin)
        {
            stationMap[station.getId()] = &station;
        }
        return stationMap;
    }
    map<int, Train *> getTrainsMap()
    {
        map<int, Train *> trainMap;
        for (auto &&train : trains_admin)
        {
            trainMap[train.getId()] = &train;
        }
        return trainMap;
    }

    Station *getStationById(int id)
    {
        for (auto &&station : stations_admin)
        {
            if (station.getId() == id)
                return &station;
        }
        return nullptr;
    }

    Station *getStationByName(string &name)
    {
        for (auto &&station : stations_admin)
        {
            if (station.getName() == name)
                return &station;
        }
        return nullptr;
    }

    Train *getTrainById(int id)
    {
        for (auto &&train : trains_admin)
        {
            if (train.getId() == id)
                return &train;
        }
        return nullptr;
    }
    Train *getTrainByName(string &name)
    {
        for (auto &&train : trains_admin)
        {
            if (train.getName() == name)
                return &train;
        }
        return nullptr;
    }

    void viewAllTrains();
    void viewAllStations();

    void updateTrainRoute(int trainId);
    void updateTrainFare(int trainId, string &className, float newFare);
    void updateTrainSeats(int trainId, string &className, int newTotalSeats);

    void addStationObject(const Station &s)
    {
        stations_admin.push_back(s);
    }
    void addTrainObject(const Train &t)
    {
        trains_admin.push_back(t);
    }
    void addNewUser();
    ~AdminPanel() {}
};

vector<Passenger> *passengers = new vector<Passenger>;
vector<Station> *stations = new vector<Station>;
vector<TravelClass> *travelClasses = new vector<TravelClass>;
vector<Train> *trains = new vector<Train>;
vector<Ticket> *tickets = new vector<Ticket>;

AdminPanel Adminpanel = AdminPanel();

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
void User::logout()
{
    cout << "╔════════════════════════════════════════════════════╗" << endl;
    cout << "║        You have been logged out successfully.      ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
}

void UserGuest::viewStations()
{
    Adminpanel.viewAllStations();
}

vector<Train *> UserGuest::viewAvailability(string &from, string &to, Date &date)
{
    system("cls");
    cout << "╔════════════════════════════════════════════════════╗" << endl;
    cout << "║             Train Availability Search              ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
    vector<Station *> stations = Adminpanel.getStations();
    int fromId = -1, toId = -1;
    for (auto &&station : stations)
    {
        if (station->getName() == from)
            fromId = station->getId();
        if (station->getName() == to)
            toId = station->getId();
    }
    if (fromId == -1 || toId == -1)
    {
        cout << "Invalid station names provided." << endl;
        return {};
    }
    vector<Train *> trains = Adminpanel.getTrains();
    Date travelDate;
    // vector<Train *> availableTrains;
    set<Train *> availableTrains;
    vector<Train *> availableTrainsVec;
    for (auto &&train : trains)
    {
        if (availableTrains.find(train) != availableTrains.end())
            continue;
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
            cout << "----------------------------------------------------" << endl;
            cout << availableTrains.size() + 1 << ". Train ID: " << train->getId() << ", Name: " << train->getName() << endl;
            cout << "Available Classes: " << endl;
            cout << "----------------------------------------------------" << endl;
            for (auto &&travelclass : classes)
            {
                if (travelclass.getAvailableSeats() > 0)
                {
                    cout << " - " << travelclass.getClassName()
                         << " | Seats: " << travelclass.getAvailableSeats()
                         << " | Fare: " << travelclass.getFare() << endl;
                }
            }
            cout << "----------------------------------------------------" << endl;
            availableTrains.insert(train);
            availableTrainsVec.push_back(train);
        }
    }
    if (availableTrainsVec.empty())
    {
        cout << "No trains available for the selected route." << endl;
        return {};
    }
    return availableTrainsVec;
}

void Passenger ::bookTicket(Train *selectedTrain, Station &from, Station &to, TravelClass &travelClass, Date &date)
{
    int ticketNo = Adminpanel.generateTicketNo();
    int seatNumber = travelClass.getseatNumber();
    if (seatNumber == -1)
    {
        cout << "No seats available." << endl;
        return;
    }
    string pnr = Adminpanel.generatePNR();
    Ticket newTicket(ticketNo, pnr, this->getUsername(), *selectedTrain, from, to, seatNumber, travelClass.getFare(), travelClass, date);
    myTickets.push_back(newTicket);
    Tickets.push_back(ticketNo);
    cout << "Ticket No: " << ticketNo << ", PNR: " << pnr << endl;
    cout << "           o x o x o x o . . ." << endl;
    cout << "         o      _____            _______________ ___=====__T___" << endl;
    cout << "       .][__n_n_|DD[  ====_____  |    |.\\/.|   | |   |_|     |_" << endl;
    cout << "      >(________|__|_[_________]_|____|_/\\_|___|_|___________|_|" << endl;
    cout << "      _/oo OOOOO oo`  ooo   ooo   o^o       o^o   o^o     o^o" << endl;
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
    cout << "Ticket booked successfully!" << endl;

    newTicket.printTicket();
}

void Passenger::cancelTicket()
{
    system("cls");
    if (myTickets.empty())
    {
        cout << "╔════════════════════════════════════════════════════╗" << endl;
        cout << "║               Ticket Cancellation Panel            ║" << endl;
        cout << "╠════════════════════════════════════════════════════╣" << endl;
        cout << "║               No tickets booked yet.               ║" << endl;
        cout << "╚════════════════════════════════════════════════════╝" << endl;
        return;
    }

    cout << "╔═══════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                 Ticket Cancellation Panel                         ║" << endl;
    cout << "╠══════╦════════════╦════════════════════════════════╦══════════════╣" << endl;
    cout << "║ S.No ║ Ticket No  ║ Train Name                     ║ Travel Date  ║" << endl;
    cout << "╠══════╬════════════╬════════════════════════════════╬══════════════╣" << endl;

    for (int i = 0; i < myTickets.size(); i++)
    {
        string trainName = myTickets[i].getTrain().getName();
        if (trainName.length() > 30)
            trainName = trainName.substr(0, 27) + "...";
        printf("║ %-4d ║ %-10d ║ %-30s ║ %-12s ║\n",
               i + 1,
               myTickets[i].getTicketNo(),
               trainName.c_str(),
               myTickets[i].getDate().show_date().c_str());
    }

    cout << "╚══════╩════════════╩════════════════════════════════╩══════════════╝" << endl;
    cout << "Enter the serial number of the ticket you want to cancel: ";

    int ticketIndex;
    cin >> ticketIndex;
    while (ticketIndex < 1 || ticketIndex > myTickets.size())
    {
        cout << "Invalid ticket selection. Enter correct index" << endl;
        cin >> ticketIndex;
    }
    myTickets.erase(myTickets.begin() + ticketIndex - 1);
    cout << "╔════════════════════════════════════════════════════╗" << endl;
    cout << "║        Ticket cancelled successfully!              ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
}

void Passenger::viewMyTickets()
{
    system("cls");
    if (myTickets.empty())
    {
        cout << "╔══════════════════════════════════════════════╗" << endl;
        cout << "║         No tickets booked yet.               ║" << endl;
        cout << "╚══════════════════════════════════════════════╝" << endl;
        return;
    }

    cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                   My Booked Tickets                                                                  ║" << endl;
    cout << "╠════╦════════════╦════════════════════════════╦══════════════╦══════════════════════╦══════════════╦══════════════════╣" << endl;
    cout << "║ No ║ Ticket No  ║ Train Name                 ║ Travel Date  ║ From → To            ║ Seat Number  ║ Class            ║" << endl;
    cout << "╠════╬════════════╬════════════════════════════╬══════════════╬══════════════════════╬══════════════╬══════════════════╣" << endl;

    for (int i = 0; i < myTickets.size(); i++)
    {
        Ticket &t = myTickets[i];
        string trainName = t.getTrain().getName();
        if (trainName.length() > 26)
            trainName = trainName.substr(0, 23) + "...";

        string date = t.getDate().show_date();
        string from = t.getOrigin().getName();
        string to = t.getDestination().getName();
        string fromTo = from + " → " + to;
        if (fromTo.length() > 22)
            fromTo = fromTo.substr(0, 19) + "...";

        string travelClass = t.getTravelClass().getClassName();

        printf("║ %-2d ║ %-10d ║ %-26s ║ %-12s ║ %-22s ║ %-12d ║ %-16s ║\n",
               i + 1,
               t.getTicketNo(),
               trainName.c_str(),
               date.c_str(),
               fromTo.c_str(),
               t.getSeatNumber(),
               travelClass.c_str());
    }

    cout << "╚════╩════════════╩════════════════════════════╩══════════════╩══════════════════════╩══════════════╩══════════════════╝" << endl;
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
    cout << "╔════════════════════════════════════════╗" << endl;

    string idLine = "║ Station ID : " + to_string(stationId);
    cout << idLine << string(42 - idLine.length() - 1, ' ') << "║" << endl;

    string nameLine = "║ Name       : " + name;
    cout << nameLine << string(42 - nameLine.length() - 1, ' ') << "║" << endl;

    cout << "╚════════════════════════════════════════╝" << endl;
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
int TravelClass::getseatNumber()
{
    if (totalSeats - bookedSeats > 0)
    {
        bookedSeats++;
        return bookedSeats;
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

vector<TravelClass> &Train::getClasses()
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
    classId.push_back(newClass.getId());
}
void Train::viewTrain()
{
    cout << "Train ID     : " << trainId << endl;
    cout << "Train Name   : " << name << endl;

    cout << "Route        : ";
    for (size_t i = 0; i < route.size(); ++i)
    {
        cout << route[i];
        if (i != route.size() - 1)
            cout << " → ";
    }
    cout << endl;

    cout << "Classes      :\n";
    for (auto &travelClass : classes)
    {
        int totalSeats = travelClass.getAvailableSeats() + travelClass.getBookedSeats();
        cout << "  - " << travelClass.getClassName()
             << " | Total: " << totalSeats
             << " | Available: " << travelClass.getAvailableSeats()
             << " | Fare: " << travelClass.getFare() << endl;
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
Date Ticket::getDate()
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

void Ticket::viewTicket()
{
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║               Ticket Details                 ║" << endl;
    cout << "╠══════════════════════════════════════════════╣" << endl;
    printf("║ %-20s : %-20d ║\n", "Ticket No", ticketNo);
    printf("║ %-20s : %-20s ║\n", "PNR", pnr.c_str());
    printf("║ %-20s : %-20s ║\n", "Passenger", passengerUsername.c_str());
    printf("║ %-20s : %-20s ║\n", "Train", train.getName().c_str());
    printf("║ %-20s : %-20s ║\n", "From", origin.getName().c_str());
    printf("║ %-20s : %-20s ║\n", "To", destination.getName().c_str());
    printf("║ %-20s : %-20s ║\n", "Date", date.show_date().c_str());
    printf("║ %-20s : %-20s ║\n", "Travel Class", travelClass.getClassName().c_str());
    printf("║ %-20s : %-20d ║\n", "Seat Number", seatNumber);
    printf("║ %-20s : %-20.2f ║\n", "Fare", fare);
    cout << "╚══════════════════════════════════════════════╝" << endl;
}

int AdminPanel ::generateTicketNo()
{
    static int ticketNo = max_ticket_number + 1;
    return ticketNo++;
}
string AdminPanel ::generatePNR()
{
    vector<char> numbers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100);
    string pnr = "";
    while (pnr.length() < 10)
    {
        int RandomNumber = dist(gen);
        pnr += numbers[RandomNumber % numbers.size()];
    }
    return pnr;
}

void AdminPanel::addTrain()
{
    system("cls");
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║         Add New Train Details        ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;

    int id;
    string name;
    cout << "\nEnter Train ID        : ";
    cin >> id;
    cout << "Enter Train Name      : ";
    cin.ignore();
    getline(cin, name);

    Train newTrain(id, name);
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

    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║      Available Travel Classes        ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;
    int numClasses;
    cout << "Enter the number of travel classes: ";
    cin >> numClasses;
    for (int i = 0; i < travelClasses->size(); i++)
    {
        cout << i + 1 << ". " << travelClasses->at(i).getClassName() << endl;
    }
    cout << "Enter class indices to add (space separated): ";
    int classIndex;
    for (int i = 0; i < numClasses; i++)
    {
        cin >> classIndex;
        while (classIndex < 1 || classIndex > travelClasses->size())
        {
            cout << "Invalid class index. Please try again." << endl;
            cin >> classIndex;
        }
        newTrain.addClass(travelClasses->at(classIndex - 1));
    }

    trains_admin.push_back(newTrain);
    trains->push_back(newTrain);
    cout << "Train added successfully!" << endl;
}

void AdminPanel::addStation()
{
    system("cls");
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║         Add New Station              ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;

    int id;
    string name;

    cout << "\nEnter Station ID     : ";
    cin >> id;
    cout << "Enter Station Name   : ";
    cin.ignore();
    getline(cin, name);

    Station newStation(id, name);
    stations_admin.push_back(newStation);
    stations->push_back(newStation);
    cout << "Station added successfully!" << endl;
}
vector<Train *> AdminPanel::getTrains()
{
    vector<Train *> trainPointers;
    for (auto &&train : trains_admin)
    {
        trainPointers.push_back(&train);
    }
    return trainPointers;
}
vector<Station *> AdminPanel::getStations()
{
    vector<Station *> stationPointers;
    for (auto &&station : stations_admin)
    {
        stationPointers.push_back(&station);
    }
    return stationPointers;
}
void AdminPanel::viewAllTrains()
{
    if (trains_admin.empty())
    {
        cout << "╔════════════════════════════════════════════════════╗" << endl;
        cout << "║              No trains available                   ║" << endl;
        cout << "╚════════════════════════════════════════════════════╝" << endl;
        return;
    }

    for (int i = 0; i < trains_admin.size(); i++)
    {
        cout << "═════════════════════════════════════════════════════════════════" << endl;
        cout << "Train #" << i + 1 << endl;
        cout << "═════════════════════════════════════════════════════════════════" << endl;
        trains_admin[i].viewTrain();
    }
}
void AdminPanel::viewAllStations()
{
    if (stations_admin.empty())
    {
        cout << "╔════════════════════════════════════════════════════╗" << endl;
        cout << "║              No stations available                 ║" << endl;
        cout << "╚════════════════════════════════════════════════════╝" << endl;
        return;
    }

    cout << "╔════════════════════════════════════════════════════╗" << endl;
    cout << "║                List of Stations                    ║" << endl;
    cout << "╠════╦════════════╦══════════════════════════════════╣" << endl;
    cout << "║ No ║ Station ID ║ Name                             ║" << endl;
    cout << "╠════╬════════════╬══════════════════════════════════╣" << endl;

    for (int i = 0; i < stations_admin.size(); i++)
    {
        cout << "║ ";
        cout.width(2);
        cout << left << i + 1 << " ║ ";
        cout.width(10);
        cout << left << stations_admin[i].getId() << " ║ ";
        cout.width(32);
        cout << left << stations_admin[i].getName() << " ║" << endl;
    }

    cout << "╚════╩════════════╩══════════════════════════════════╝" << endl;
}

void AdminPanel ::updateTrainRoute(int trainId)
{
    system("cls");
    cout << "╔════════════════════════════════════════════════════╗" << endl;
    cout << "║              Update Train Route                    ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
    for (auto &&train : trains_admin)
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
    for (auto &&train : trains_admin)
    {
        if (train.getId() == trainId)
        {
            vector<TravelClass> &classes = train.getClasses();
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
    for (auto &&train : trains_admin)
    {
        if (train.getId() == trainId)
        {
            vector<TravelClass> &classes = train.getClasses();
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
    if ((year1 % 4 == 0 && year1 % 100 != 0) || (year1 % 400 == 0))
        days_in_month[1] = 29;
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
    stringstream ss;
    if (day < 10)
        ss << '0';
    ss << day << '/';
    if (month < 10)
        ss << '0';
    ss << month << '/';
    ss << year;
    return ss.str();
}

void AdminPanel ::addNewUser()
{
    system("cls");
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║           Register New Passenger             ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cin.ignore();
    string fullName, email, phone;
    cout << "Enter full name: ";
    getline(cin, fullName);
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter phone: ";
    cin >> phone;
    bool flag = false;
    while (!flag)
    {
        flag = true;
        if (phone.size() != 10)
            flag = false;
        for (auto &&ch : phone)
        {
            if (ch < '0' || ch > '9')
            {
                flag = false;
                break;
            }
        }
        if (!flag)
        {
            cout << "Invalid phone number, please enter a 10-digit phone number:" << endl;
            cin >> phone;
        }
    }
    Passenger newPassenger(username, password, fullName, email, phone);
    passengers->push_back(newPassenger);
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║            User added successfully!          ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
}