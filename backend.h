#include "classes.h"


void saveDataToFile()
{
    trains->clear();
    stations->clear();
    *trains = Adminpanel.getAllTrainsObj();
    *stations = Adminpanel.getAllStationsObj();
    tickets->clear();
    for (auto &&passenger : *passengers)
    {
        for (auto &&ticket : passenger.getPassengerTicketsObj())
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
        credentials_file << passenger.getPassengerUsername() << "," << passenger.getPassengerPassword() << endl;
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
        passenger_file << passenger.getPassengerUsername() << "," << passenger.getPassengerFullName() << "," << passenger.getPassengerEmail() << "," << passenger.getPassengerPhone() << "," << passenger.getPassengerTickets() << endl;
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
        stations_file << station.getStationId() << "," << station.getStationName() << endl;
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
        travel_classes_file << travelClass.getTravelClassId() << "," << travelClass.getTravelClassName() << "," << travelClass.getTotalSeats() << ","
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
        trains_file << train.getTrainId() << "," << train.getTrainName() << "," << train.getTrainRouteStr() << "," << train.getTravelClassesStr() << endl;
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
        tickets_file << ticket.getTicketNo() << "," << ticket.getPNR() << "," << ticket.getPassengerUserNameFromTicket() << ","
                     << ticket.getTrainIdFromObj() << "," << ticket.getOriginIdFromObj() << "," << ticket.getDestinationIdFromObj() << ","
                     << ticket.getTicketSeatNumber() << "," << ticket.getTicketFare() << "," << ticket.getTravelClassIdFromObj() << ","
                     << ticket.getDayFromObj() << "," << ticket.getMonthFromObj() << "," << ticket.getYearFromObj() << endl;
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
                it->addPassengerTicket(stoi(ticketId));
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
            if (passenger.getPassengerUsername() == username)
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
                newTrain.addTrainRoute(stoi(stationId));
            }
        }

        // Parse classes
        stringstream classesStream(classesStr);
        string classId;
        while (getline(classesStream, classId, ' '))
        {
            if (!classId.empty())
            {
                newTrain.addTravelClassId(stoi(classId));
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
        passengerMap[passenger.getPassengerUsername()] = &passenger;
    }
    unordered_map<int, TravelClass *> travelClassMap;
    for (auto &&travelClass : *travelClasses)
    {
        travelClassMap[travelClass.getTravelClassId()] = &travelClass;
    }
    unordered_map<int, Train *> trainMap;
    for (auto &&train : *trains)
    {
        trainMap[train.getTrainId()] = &train;
    }

    unordered_map<int, Station *> stationMap;
    for (auto &&station : *stations)
    {
        stationMap[station.getStationId()] = &station;
    }
    for (auto &&train : *trains)
    {
        for (auto &&classid : train.getTravelClassIds())
        {
            if (travelClassMap.count(classid))
            {
                trainMap[train.getTrainId()]->addTravelClassObject(*(travelClassMap[classid]));
            }
        }
    }

    for (auto &ticket : *tickets)
    {
        if (trainMap.count(ticket.getTrainIdFromTicket()))
        {
            Train *train = (trainMap[ticket.getTrainIdFromTicket()]);
            ticket.setTrainInTicket(*train);
        }
        if (stationMap.count(ticket.getOriginIdFromTicket()))
        {
            Station *origin = (stationMap[ticket.getOriginIdFromTicket()]);
            ticket.setOriginInTicket(*origin);
        }
        if (stationMap.count(ticket.getDestinationIdFromTicket()))
        {
            Station *destination = (stationMap[ticket.getDestinationIdFromTicket()]);
            ticket.setDestinationInTicket(*destination);
        }
        if (travelClassMap.count(ticket.getTravelClassIdFromTicket()))
        {
            TravelClass *travelClass = (travelClassMap[ticket.getTravelClassIdFromTicket()]);
            ticket.setTravelClassInTicket(*travelClass);
        }
        if (passengerMap.count(ticket.getPassengerUserNameFromTicket()))
        {
            Passenger *p = passengerMap[ticket.getPassengerUserNameFromTicket()];
            p->addPassengerTicketObject(ticket);
        }
        int day = ticket.getDayFromTicket(), month = ticket.getMonthFromTicket(), year = ticket.getYearFromTicket();
        Date date(day, month, year);
        ticket.setDateInTicket(date);
    }
    Adminpanel.setTrains(*trains);
    Adminpanel.setStations(*stations);
    // cout << "Data loaded successfully!" << endl;
}
