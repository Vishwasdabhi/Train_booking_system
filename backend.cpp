#include "classes.cpp"
#include <windows.h>
#include <fstream>

vector<Passenger> *passengers = new vector<Passenger>;
vector<Station> *stations = new vector<Station>;
vector<TravelClass> *travelClasses = new vector<TravelClass>;
vector<Train> *trains = new vector<Train>;
vector<Ticket> *tickets = new vector<Ticket>;

void saveDataToFile()
{
    // Save passengers to file
    ofstream passenger_file("passengers.csv");
    if (!passenger_file.is_open())
    {
        cout << "Error opening student information file for writing." << endl;
        return;
    }
    for (auto &&passenger : *passengers)
    {
        passenger_file << passenger.getUsername() << "," << passenger.getFullName() << "," << passenger.getEmail() << "," << passenger.getPhone() << "," << passenger.getMyTickets() << endl;
    }
    passenger_file.close();
    // Save stations to file
    ofstream stations_file("stations.csv");
    if (!stations_file.is_open())
    {
        cout << "Error opening station information file for writing." << endl;
        return;
    }
    for (auto &&station : *stations)
    {
        stations_file << station.getId() << "," << station.getName() << endl;
    }
    stations_file.close();
    // Save travel classes to file
    ofstream travel_classes_file("travel_classes.csv");
    if (!travel_classes_file.is_open())
    {
        cout << "Error opening travel class information file for writing." << endl;
        return;
    }
    for (auto &&travelClass : *travelClasses)
    {
        travel_classes_file << travelClass.getId() << "," << travelClass.getClassName() << "," << travelClass.getTotalSeats() << ","
                            << travelClass.getBookedSeats() << "," << travelClass.getFare() << endl;
    }
    travel_classes_file.close();

    // Save trains to file
    ofstream trains_file("trains.csv");
    if (!trains_file.is_open())
    {
        cout << "Error opening train information file for writing." << endl;
        return;
    }
    for (auto &&train : *trains)
    {
        trains_file << train.getId() << "," << train.getName() << "," << train.getroutestr() << "," << train.getClassesStr() << endl;
    }
    trains_file.close();

    // Save tickets to file
    ofstream tickets_file("tickets.csv");
    if (!tickets_file.is_open())
    {
        cout << "Error opening ticket information file for writing." << endl;
        return;
    }
    for (auto &ticket : *tickets)
    {
        tickets_file << ticket.getTicketNo() << "," << ticket.getPNR() << "," << ticket.getUserName() << ","
                     << ticket.gettrainIdfromObj() << "," << ticket.getoriginIdfromObj() << "," << ticket.getdestinationIdfromObj() << ","
                     << ticket.getSeatNumber() << "," << ticket.getFare() << "," << ticket.gettravelClassIdfromObj() << ","
                     << ticket.getday() << "," << ticket.getmonth() << "," << ticket.getyear() << endl;
    }
    tickets_file.close();
    cout << "Data saved successfully!" << endl;
}

void loadDataFromFile()
{
    // Load passengers from file
    ifstream passengers_file("passengers.csv");
    if (!passengers_file.is_open())
    {
        cout << "Error opening student information file for reading." << endl;
        return;
    }
    string line;
    while (getline(passengers_file, line))
    {
        stringstream ss(line);
        string username, fullName, email, phone, myTickets;
        getline(ss, username, ',');
        getline(ss, fullName, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');
        getline(ss, myTickets);
        Passenger *passenger = new Passenger(username, "", fullName, email, phone);
        stringstream ticketsStream(myTickets);
        string ticketId;
        while (getline(ticketsStream, ticketId, ' '))
        {
            if (!ticketId.empty())
            {
                passenger->addMyTicket(stoi(ticketId));
            }
        }
    }
    passengers_file.close();

    // Load stations from file
    ifstream stations_file("stations.csv");
    if (!stations_file.is_open())
    {
        cout << "Error opening station information file for reading." << endl;
        return;
    }
    while (getline(stations_file, line))
    {
        stringstream ss(line);
        int id;
        string name;
        ss >> id;
        ss.ignore(1); // Ignore the comma
        getline(ss, name);
        stations->emplace_back(id, name);
    }
    stations_file.close();

    // Load travel classes from file
    ifstream travel_classes_file("travel_classes.csv");
    if (!travel_classes_file.is_open())
    {
        cout << "Error opening travel class information file for reading." << endl;
    }
    while (getline(travel_classes_file, line))
    {
        stringstream ss(line);
        int id, totalSeats, bookedSeats;
        string className;
        float fare;
        ss >> id;
        ss.ignore(1); // Ignore the comma
        getline(ss, className, ',');
        ss >> totalSeats;
        ss.ignore(1); // Ignore the comma
        ss >> bookedSeats;
        ss.ignore(1); // Ignore the comma
        ss >> fare;
        travelClasses->emplace_back(id, className, totalSeats, bookedSeats, fare);
    }
    travel_classes_file.close();
    // Load trains from file
    ifstream trains_file("trains.csv");
    if (!trains_file.is_open())
    {
        cout << "Error opening train information file for reading." << endl;
        return;
    }
    while (getline(trains_file, line))
    {
        stringstream ss(line);
        int id;
        string name, routeStr, classesStr;
        ss >> id;
        ss.ignore(1); // Ignore the comma
        getline(ss, name, ',');
        getline(ss, routeStr, ',');
        getline(ss, classesStr, ',');
        Train newTrain(id, name);

        // Parse route
        stringstream routeStream(routeStr);
        string stationId;
        while (getline(routeStream, stationId, ' '))
        {
            if (!stationId.empty())
            {
                newTrain.addroute(stoi(stationId));
            }
        }

        // Parse classes
        stringstream classesStream(classesStr);
        string classId;
        while (getline(classesStream, classId, ' '))
        {
            if (!classId.empty())
            {
                newTrain.addclassid(stoi(classId));
            }
        }

        trains->push_back(newTrain);
    }
    trains_file.close();
    // Load tickets from file
    ifstream tickets_file("tickets.csv");
    if (!tickets_file.is_open())
    {
        cout << "Error opening ticket information file for reading." << endl;
        return;
    }
    while (getline(tickets_file, line))
    {
        stringstream ss(line);
        int ticketNo, passengerId, trainId, originId, destinationId, seatNumber, travelClassId, day, month, year;
        string pnr;
        ss >> ticketNo;
        ss.ignore(1); // Ignore the comma
        getline(ss, pnr, ',');
        ss >> passengerId;
        ss.ignore(1); // Ignore the comma
        ss >> trainId;
        ss.ignore(1); // Ignore the comma
        ss >> originId;
        ss.ignore(1); // Ignore the comma
        ss >> destinationId;
        ss.ignore(1); // Ignore the comma
        ss >> seatNumber;
        ss.ignore(1); // Ignore the comma
        float fare;
        ss >> fare;
        ss.ignore(1); // Ignore the comma
        ss >> travelClassId;
        ss.ignore(1); // Ignore the comma
        ss >> day;
        ss.ignore(1); // Ignore the comma
        ss >> month;
        ss.ignore(1); // Ignore the comma
        ss >> year;

        tickets->emplace_back(ticketNo, pnr, passengerId, trainId, originId, destinationId, seatNumber, fare, travelClassId, day, month, year);
    }
    tickets_file.close();
    cout << "Data loaded successfully!" << endl;

    unordered_map<int, Ticket *> ticketMap;
    for (auto &ticket : *tickets)
        ticketMap[ticket.getTicketNo()] = &ticket;

    for (auto &passenger : *passengers)
    {
        for (int id : passenger.getMyTicketsvec())
        {
            if (ticketMap.count(id))
                passenger.addTicketObject(*ticketMap[id]);
        }
    }
    unordered_map<int, TravelClass *> travelClassMap;
    for (auto &travelClass : *travelClasses)
    {
        travelClassMap[travelClass.getId()] = &travelClass;
    }
    for (auto &train : *trains)
    {
        for (auto &classid : train.getClassIds())
        {
            if (travelClassMap.count(classid))
            {
                train.addClassObject(*(travelClassMap[classid]));
            }
        }
    }
    unordered_map<string, Passenger *> passengerMap;
    for (auto &passenger : *passengers)
    {
        passengerMap[passenger.getUsername()] = &passenger;
    }

    unordered_map<int, Train *> trainMap;
    for (auto &train : *trains)
    {
        trainMap[train.getId()] = &train;
    }

    unordered_map<int, Station *> stationMap;
    for (auto &station : *stations)
    {
        stationMap[station.getId()] = &station;
    }

    for (auto &&ticket : *tickets)
    {
        if (passengerMap.count(ticket.getUserName()))
        {
            ticket.setPassenger(*(passengerMap[ticket.getUserName()]));
        }
        if (trainMap.count(ticket.getTrainId()))
        {
            ticket.setTrain(*(trainMap[ticket.getTrainId()]));
        }
        if (stationMap.count(ticket.getOriginId()))
        {
            ticket.setOrigin(*(stationMap[ticket.getOriginId()]));
        }
        if (stationMap.count(ticket.getDestinationId()))
        {
            ticket.setDestination(*(stationMap[ticket.getDestinationId()]));
        }
        if (travelClassMap.count(ticket.getTravelClassId()))
        {
            ticket.setTravelClass(*(travelClassMap[ticket.getTravelClassId()]));
        }
        int day = ticket.getday(), month = ticket.getmonth(), year = ticket.getyear();
        Date date(day, month, year);
        ticket.setDate(date);
    }
}
AdminPanel adminPanel(*trains, *stations);