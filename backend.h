#include "classes.h"

void saveDataToFile()
{
    trains->clear();
    stations->clear();
    *trains = Adminpanel.getTrainsObj();
    *stations = Adminpanel.getStationsObj();
    tickets->clear();
    for (auto &&passenger : *passengers)
    {
        for (auto &&ticket : passenger.getMyTicketsObj())
        {
            tickets->push_back(ticket);
        }
    }
    ofstream credentials_file("credentials.csv");
    if (!credentials_file.is_open())
    {
        cout << "Error opening credentials file for writing." << endl;
        return;
    }
    credentials_file.clear();
    // Save credentials to file
    for (auto &&passenger : *passengers)
    {
        credentials_file << passenger.getUsername() << "," << passenger.getPassword() << endl;
    }
    credentials_file.close();

    // Save passengers to file
    ofstream passenger_file("passengers.csv");
    passenger_file.clear();
    if (!passenger_file.is_open())
    {
        cout << "Error opening passenger file for writing." << endl;
        return;
    }
    for (auto &&passenger : *passengers)
    {
        passenger_file << passenger.getUsername() << "," << passenger.getFullName() << "," << passenger.getEmail() << "," << passenger.getPhone() << "," << passenger.getMyTickets() << endl;
    }
    passenger_file.close();
    // Save stations to file
    ofstream stations_file("stations.csv");
    stations_file.clear();
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
    travel_classes_file.clear();
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
    trains_file.clear();
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
    tickets_file.clear();
    if (!tickets_file.is_open())
    {
        cout << "Error opening ticket information file for writing." << endl;
        fflush(stdin);
        _getch();
        return;
    }
    for (auto &ticket : *tickets)
    {
        tickets_file << ticket.getTicketNo() << "," << ticket.getPNR() << "," << ticket.getpassengerUserName() << ","
                     << ticket.gettrainIdfromObj() << "," << ticket.getoriginIdfromObj() << "," << ticket.getdestinationIdfromObj() << ","
                     << ticket.getSeatNumber() << "," << ticket.getFare() << "," << ticket.gettravelClassIdfromObj() << ","
                     << ticket.getday() << "," << ticket.getmonth() << "," << ticket.getyear() << endl;
    }
    tickets_file.close();
    // cout << "Data saved successfully!" << endl;
}

void loadDataFromFile()
{
    // Load passengers from file
    ifstream passengers_file("passengers.csv");
    if (!passengers_file.is_open())
    {
        cout << "Error opening passenger information file for reading." << endl;
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
        // Passenger *passenger = new Passenger(username, "", fullName, email, phone);
        passengers->emplace_back(username, "", fullName, email, phone);
        stringstream ticketsStream(myTickets);
        string ticketId;
        while (getline(ticketsStream, ticketId, ' '))
        {
            if (!ticketId.empty())
            {
                // passenger->addMyTicket(stoi(ticketId));
                auto it = passengers->end();
                it--;
                it->addMyTicket(stoi(ticketId));
            }
        }
        // passengers->push_back(*passenger);
        // delete passenger;
    }
    passengers_file.close();

    // Load credentials from file
    ifstream credentials_file("credentials.csv");
    if (!credentials_file.is_open())
    {
        cout << "Error opening credentials file for reading." << endl;
        return;
    }
    while (getline(credentials_file, line))
    {
        stringstream ss(line);
        string username, password;
        getline(ss, username, ',');
        getline(ss, password);
        for (auto &&passenger : *passengers)
        {
            if (passenger.getUsername() == username)
            {
                passenger.setPassword(password);
                break;
            }
        }
    }
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
        // Train newTrain(id, name);
        trains->emplace_back(id, name);
        Train &newTrain = trains->back();

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

        // trains->push_back(newTrain);
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
        int ticketNo, trainId, originId, destinationId, seatNumber, travelClassId, day, month, year;
        string pnr, passengerUsername;
        float fare;
        ss >> ticketNo;
        ss.ignore(1); // Ignore the comma
        getline(ss, pnr, ',');
        getline(ss, passengerUsername, ',');
        ss >> trainId;
        ss.ignore(1); // Ignore the comma
        ss >> originId;
        ss.ignore(1); // Ignore the comma
        ss >> destinationId;
        ss.ignore(1); // Ignore the comma
        ss >> seatNumber;
        ss.ignore(1); // Ignore the comma
        ss >> fare;
        ss.ignore(1); // Ignore the comma
        ss >> travelClassId;
        ss.ignore(1); // Ignore the comma
        ss >> day;
        ss.ignore(1); // Ignore the comma
        ss >> month;
        ss.ignore(1); // Ignore the comma
        ss >> year;
        int mximumTicketNumber = Adminpanel.getMaxTicketNumber();
        if (ticketNo > mximumTicketNumber)
        {
            Adminpanel.setMaxTicketNumber(ticketNo);
        }
        tickets->emplace_back(ticketNo, pnr, passengerUsername, trainId, originId, destinationId, seatNumber, fare, travelClassId, day, month, year);
    }
    tickets_file.close();
    
    unordered_map<int, Ticket *> ticketMap;
    for (auto &&ticket : *tickets)
    ticketMap[ticket.getTicketNo()] = &ticket;

    unordered_map<string, Passenger *> passengerMap;
    for (auto &&passenger : *passengers)
    {
        passengerMap[passenger.getUsername()] = &passenger;
    }
    unordered_map<int, TravelClass *> travelClassMap;
    for (auto &&travelClass : *travelClasses)
    {
        travelClassMap[travelClass.getId()] = &travelClass;
    }
    unordered_map<int, Train *> trainMap;
    for (auto &&train : *trains)
    {
        trainMap[train.getId()] = &train;
    }

    unordered_map<int, Station *> stationMap;
    for (auto &&station : *stations)
    {
        stationMap[station.getId()] = &station;
    }
    for (auto &&train : *trains)
    {
        for (auto &&classid : train.getClassIds())
        {
            if (travelClassMap.count(classid))
            {
                trainMap[train.getId()]->addClassObject(*(travelClassMap[classid]));
            }
        }
    }

    for (auto &ticket : *tickets)
    {
        if (trainMap.count(ticket.getTrainId()))
        {
            Train *train = (trainMap[ticket.getTrainId()]);
            ticket.setTrain(*train);
        }
        if (stationMap.count(ticket.getOriginId()))
        {
            Station *origin = (stationMap[ticket.getOriginId()]);
            ticket.setOrigin(*origin);
        }
        if (stationMap.count(ticket.getDestinationId()))
        {
            Station *destination = (stationMap[ticket.getDestinationId()]);
            ticket.setDestination(*destination);
        }
        if (travelClassMap.count(ticket.getTravelClassId()))
        {
            TravelClass *travelClass = (travelClassMap[ticket.getTravelClassId()]);
            ticket.setTravelClass(*travelClass);
        }
        if (passengerMap.count(ticket.getpassengerUserName()))
        {
            Passenger *p = passengerMap[ticket.getpassengerUserName()];
            p->addTicketObject(ticket);
        }
        int day = ticket.getday(), month = ticket.getmonth(), year = ticket.getyear();
        Date date(day, month, year);
        ticket.setDate(date);
    }
    Adminpanel.setTrains(*trains);
    Adminpanel.setStations(*stations);
    // cout << "Data loaded successfully!" << endl;
}

