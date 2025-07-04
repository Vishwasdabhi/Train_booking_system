#include "backend.hpp"

void loginPanel();
void adminPanel();
void userGuestPanel();
void passengerPanel(Passenger *passenger);

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";

void loginPanel()
{
    system("cls");
    cout << "╔════════════════════════════════════════════════════╗" << endl;
    cout << "║        Welcome to the Train Management System      ║" << endl;
    cout << "╠════════════════════════════════════════════════════╣" << endl;
    cout << "║  Log in as:                                        ║" << endl;
    cout << "║    1. Admin                                        ║" << endl;
    cout << "║    2. User Guest                                   ║" << endl;
    cout << "║    3. Passenger                                    ║" << endl;
    cout << "║    4. New User                                     ║" << endl;
    cout << "║    5. Exit                                         ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
    cout << "Enter your choice: ";
    bool flag = false;
    fflush(stdin);
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        system("cls");
        string username, password;
        cout << "╔═══════════════════════════════╗" << endl;
        cout << "║         Admin Login           ║" << endl;
        cout << "╚═══════════════════════════════╝" << endl;
        cout << "Enter Admin Username: ";
        cin >> username;
        cout << "Enter Admin Password: ";
        // cin >> password;
        password = inputPassword();
        if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD)
        {
            cout << "Login successful!" << endl;
            fflush(stdin);
            cout << "Press any key to continue...";
            _getch();
            adminPanel();
            return;
        }
        else
        {
            cout << "Invalid credentials. Please try again." << endl;
            fflush(stdin);
            cout << "Press any key to continue...";
            _getch();
            loginPanel();
            return;
        }
    }
    case 2:
    {
        userGuestPanel();
        return;
    }
    case 3:
    {
        system("cls");
        string username, password;
        cout << "╔══════════════════════════════════╗" << endl;
        cout << "║       Passenger Login Panel      ║" << endl;
        cout << "╚══════════════════════════════════╝" << endl;
        cout << "Enter Passenger Username: ";
        cin >> username;
        cout << "Enter Passenger Password: ";
        // cin >> password;
        password = inputPassword();
        bool found = false;
        for (auto &&passenger : *passengers)
        {
            if (passenger.getPassengerUsername() == username && passenger.getPassengerPassword() == password)
            {
                found = true;
                cout << "Login successful!" << endl;
                fflush(stdin);
                cout << "Press any key to continue...";
                _getch();
                passengerPanel(&passenger);
                return;
            }
        }
        cout << "You entered : " << password << endl;
        cout << "Invalid credentials. Please try again." << endl;
        break;
    }
    case 4:
    {
        Adminpanel.addNewUser();
        break;
    }
    case 5:
    {
        system("cls");
        cout << "╔════════════════════════════════════════════════════╗" << endl;
        cout << "║  Thank you for using the Train Management System!  ║" << endl;
        cout << "╚════════════════════════════════════════════════════╝" << endl;
        cout << endl;
        cout << "___________   _______________________________________^__" << endl;
        cout << " ___   ___ |||  ___   ___   ___    ___ ___  |   __  ,----\\" << endl;
        cout << "|   | |   |||| |   | |   | |   |  |   |   | |  |  | |_____\\ " << endl;
        cout << "|___| |___|||| |___| |___| |___|  | O | O | |  |  |       \\" << endl;
        cout << "           |||                    |___|___| |  |__|        )" << endl;
        cout << "___________|||______________________________|_____________/" << endl;
        cout << "           |||                                        /--------" << endl;
        cout << "-----------'''----------------------------------------'" << endl;
        flag = true;
        break;
    }
    default:
    {
        cout << "Invalid choice. Please try again." << endl;
        fflush(stdin);
        cout << "Press any key to continue...";
        _getch();
        loginPanel();
        return;
    }
    }
    if (!flag)
    {
        fflush(stdin);
        cout << "Press any key to continue...";
        _getch();
        loginPanel();
    }
}

void adminPanel()
{
    system("cls");
    cout << "╔════════════════════════════════════════════════════╗" << endl;
    cout << "║               Welcome to Admin Panel               ║" << endl;
    cout << "╠════════════════════════════════════════════════════╣" << endl;
    cout << "║  1. View All Trains                                ║" << endl;
    cout << "║  2. View All Stations                              ║" << endl;
    cout << "║  3. Add Train                                      ║" << endl;
    cout << "║  4. Add Station                                    ║" << endl;
    cout << "║  5. Update Train Route                             ║" << endl;
    cout << "║  6. Update Train Fare                              ║" << endl;
    cout << "║  7. Update Train Seats                             ║" << endl;
    cout << "║  8. Logout                                         ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;
    cout << "Enter your choice: ";
    int choice;
    bool flag = false;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        system("cls");
        Adminpanel.viewAllTrains();
        break;
    }
    case 2:
    {
        system("cls");
        Adminpanel.viewAllStations();
        break;
    }
    case 3:
    {
        system("cls");
        Adminpanel.addNewTrain();
        break;
    }
    case 4:
    {
        system("cls");
        Adminpanel.addNewStation();
        break;
    }
    case 5:
    {
        set<int> TrainIds;
        vector<Train *> trains = Adminpanel.getAllTrainPointers();
        for (auto &&train : trains)
        {
            TrainIds.insert(train->getTrainId());
        }
        system("cls");
        Adminpanel.viewAllTrains();
        cout << "Enter the Train ID to update its route: ";
        int trainId;
        cin >> trainId;
        while (TrainIds.find(trainId) == TrainIds.end())
        {
            cout << "Invalid Train ID. Please try again: ";
            cin >> trainId;
        }
        Adminpanel.updateTrainRoute(trainId);
        break;
    }
    case 6:
    {
        set<int> TrainIds;
        vector<Train *> trains = Adminpanel.getAllTrainPointers();
        for (auto &&train : trains)
        {
            TrainIds.insert(train->getTrainId());
        }
        system("cls");
        Adminpanel.viewAllTrains();
        cout << "Enter the Train ID to update its fare: ";
        int trainId;
        cin >> trainId;
        while (TrainIds.find(trainId) == TrainIds.end())
        {
            cout << "Invalid Train ID. Please try again: ";
            fflush(stdin);
            cin >> trainId;
        }
        for (int i = 0; i < travelClasses->size(); i++)
        {
            cout << i + 1 << ". " << travelClasses->at(i).getTravelClassName() << endl;
        }
        cout << "Enter the class index to update fare: ";
        int classIndex;
        cin >> classIndex;
        while (classIndex < 1 || classIndex > travelClasses->size())
        {
            cout << "Invalid class index. Please try again: ";
            fflush(stdin);
            cin >> classIndex;
        }
        string className = travelClasses->at(classIndex - 1).getTravelClassName();
        float newFare;
        cout << "Enter new fare: ";
        cin >> newFare;
        Adminpanel.updateTrainFare(trainId, className, newFare);
        break;
    }
    case 7:
    {
        set<int> TrainIds;
        vector<Train *> trains = Adminpanel.getAllTrainPointers();
        for (auto &&train : trains)
        {
            TrainIds.insert(train->getTrainId());
        }
        system("cls");
        Adminpanel.viewAllTrains();
        cout << "Enter the Train ID to update its seats: ";
        int trainId;
        cin >> trainId;
        while (TrainIds.find(trainId) == TrainIds.end())
        {
            cout << "Invalid Train ID. Please try again: ";
            cin >> trainId;
        }
        for (int i = 0; i < travelClasses->size(); i++)
        {
            cout << i + 1 << ". " << travelClasses->at(i).getTravelClassName() << endl;
        }
        cout << "Enter the class index to update fare: ";
        int classIndex;
        cin >> classIndex;
        while (classIndex < 1 || classIndex > travelClasses->size())
        {
            cout << "Invalid class index. Please try again: ";
            fflush(stdin);
            cin >> classIndex;
        }
        string className = travelClasses->at(classIndex - 1).getTravelClassName();
        int newTotalSeats;
        cout << "Enter new total seats: ";
        cin >> newTotalSeats;
        Adminpanel.updateTrainSeats(trainId, className, newTotalSeats);
        break;
    }
    case 8:
    {
        system("cls");
        cout << "╔════════════════════════════════════════════════════╗" << endl;
        cout << "║        You have been logged out successfully.      ║" << endl;
        cout << "╚════════════════════════════════════════════════════╝" << endl;
        fflush(stdin);
        cout << "Press any key to continue...";
        _getch();
        flag = true;
        loginPanel();
        return;
    }
    default:
    {
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
    }
    if (!flag)
    {
        fflush(stdin);
        cout << "Press any key to continue...";
        _getch();
        adminPanel();
    }
}

void userGuestPanel()
{
    system("cls");
    cout << "╔════════════════════════════════════════════════════╗" << endl;
    cout << "║              Welcome to User Guest Panel           ║" << endl;
    cout << "╠════════════════════════════════════════════════════╣" << endl;
    cout << "║  1. View Stations                                  ║" << endl;
    cout << "║  2. View Train Availability                        ║" << endl;
    cout << "║  3. Logout                                         ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;

    bool flag = false;
    UserGuest guest = UserGuest();
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        system("cls");
        Adminpanel.viewAllStations();
        break;
    }
    case 2:
    {
        system("cls");
        string from, to;
        Date date;
        cout << "Enter departure station: ";
        cin >> from;
        cout << "Enter destination station: ";
        cin >> to;
        cout << "Enter travel date (DD MM YYYY): ";
        int day, month, year;
        cin >> day >> month >> year;
        date = Date(day, month, year);
        guest.viewAvailability(from, to, date);
        break;
    }
    case 3:
    {
        system("cls");
        guest.logout();
        fflush(stdin);
        cout << "Press any key to continue...";
        _getch();
        flag = true;
        loginPanel();
        return;
    }
    }
    if (!flag)
    {
        fflush(stdin);
        cout << "Press any key to continue...";
        _getch();
        userGuestPanel();
    }
}
void passengerPanel(Passenger *passenger)
{
    system("cls");
    cout << "╔════════════════════════════════════════════════════╗" << endl;
    cout << "║              Welcome to Passenger Panel            ║" << endl;
    cout << "╠════════════════════════════════════════════════════╣" << endl;
    cout << "║  1. View Stations                                  ║" << endl;
    cout << "║  2. View Train Availability                        ║" << endl;
    cout << "║  3. Book Ticket                                    ║" << endl;
    cout << "║  4. Cancel Ticket                                  ║" << endl;
    cout << "║  5. View My Tickets                                ║" << endl;
    cout << "║  6. Change Password                                ║" << endl;
    cout << "║  7. Logout                                         ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << endl;

    bool flag = false;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        system("cls");
        Adminpanel.viewAllStations();
        break;
    }
    case 2:
    {
        system("cls");
        string from, to;
        Date date;
        cout << "Enter departure station: ";
        cin >> from;
        cout << "Enter destination station: ";
        cin >> to;
        cout << "Enter travel date (DD MM YYYY): ";
        int day, month, year;
        cin >> day >> month >> year;
        date = Date(day, month, year);
        passenger->viewAvailability(from, to, date);
        break;
    }
    case 3:
    {
        system("cls");
        cout << "╔════════════════════════════════════════════════════╗" << endl;
        cout << "║                Train Ticket Booking                ║" << endl;
        cout << "╚════════════════════════════════════════════════════╝" << endl;
        string from, to;
        Date date;
        cout << "Enter departure station: ";
        cin >> from;
        cout << "Enter destination station: ";
        cin >> to;
        cout << "Enter travel date (DD MM YYYY): ";
        int day, month, year;
        cin >> day >> month >> year;
        date = Date(day, month, year);
        vector<Train *> availableTrains = passenger->viewAvailability(from, to, date);
        if (availableTrains.size() == 0)
        {
            break;
        }
        cout << "Select a train by entering its index: ";
        int trainIndex;
        fflush(stdin);
        cin >> trainIndex;
        while (trainIndex < 1 || trainIndex > availableTrains.size())
        {
            cout << "Invalid train selection. Enter correct index: ";
            cin >> trainIndex;
        }
        Train *selectedTrain = availableTrains[trainIndex - 1];
        cout << "╔════════════════════════════════════════════════════╗" << endl;
        cout << "║              Available Travel Classes              ║" << endl;
        cout << "╚════════════════════════════════════════════════════╝" << endl;

        int cnt = 1;
        for (auto &&travelClass : selectedTrain->getTravelClasses())
        {
            cout << cnt++ << ". " << travelClass.getTravelClassName()
                 << " | Seats: " << travelClass.getAvailableSeats()
                 << " | Fare: " << travelClass.getFare() << endl;
        }
        cout << "Select a class by entering its index: ";
        int classIndex;
        cin >> classIndex;
        while (classIndex < 1 || classIndex > selectedTrain->getTravelClasses().size())
        {
            cout << "Invalid class selection. Enter correct index: ";
            cin >> classIndex;
        }
        TravelClass *selectedClass = &selectedTrain->getTravelClasses()[classIndex - 1];
        Station *fromStation = Adminpanel.getStationByName(from);
        Station *toStation = Adminpanel.getStationByName(to);
        passenger->bookPassengerTicket(selectedTrain, *fromStation, *toStation, *selectedClass, date);
        break;
    }
    case 4:
    {
        system("cls");
        passenger->cancelPassengerTicket();
        break;
    }
    case 5:
    {
        system("cls");
        passenger->viewPassengerTickets();
        break;
    }
    case 6:
    {
        system("cls");
        cout << "╔══════════════════════════════════════════════╗" << endl;
        cout << "║          Change Passenger Password           ║" << endl;
        cout << "╚══════════════════════════════════════════════╝" << endl;
        string currentPassword;
        cout << "Enter current password: ";
        // cin >> currentPassword;
        currentPassword = inputPassword();
        if (currentPassword != passenger->getPassengerPassword())
        {
            cout << "╔═════════════════════════════════════════╗" << endl;
            cout << "║     Incorrect password. Try again.      ║" << endl;
            cout << "╚═════════════════════════════════════════╝" << endl;
            fflush(stdin);
            cout << "Press any key to continue...";
            _getch();
            passengerPanel(passenger);
            return;
        }
        string newPassword;
        cout << "Enter new password: ";
        // cin >> newPassword;
        newPassword = inputPassword();
        string confirmPassword;
        cout << "Confirm new password: ";
        // cin >> confirmPassword;
        confirmPassword = inputPassword();
        while (newPassword != confirmPassword)
        {
            cout << "╔═════════════════════════════════════════════╗" << endl;
            cout << "║        Passwords do not match. Retry.       ║" << endl;
            cout << "╚═════════════════════════════════════════════╝" << endl;
            cout << "Enter new password: ";
            // cin >> newPassword;
            newPassword = inputPassword();
            cout << "Confirm new password: ";
            // cin >> confirmPassword;
            confirmPassword = inputPassword();
        }
        if (passenger->changePassword(newPassword))
        {
            cout << "╔═════════════════════════════════════════════╗" << endl;
            cout << "║         Password changed successfully       ║" << endl;
            cout << "╚═════════════════════════════════════════════╝" << endl;
        }
        else
        {
            cout << "╔═════════════════════════════════════════════╗" << endl;
            cout << "║       Failed to change the password.        ║" << endl;
            cout << "╚═════════════════════════════════════════════╝" << endl;
            fflush(stdin);
            cout << "Press any key to continue...";
            _getch();
            passengerPanel(passenger);
            return;
        }

        break;
    }
    case 7:
    {
        system("cls");
        passenger->logout();
        fflush(stdin);
        cout << "Press any key to continue...";
        _getch();
        flag = true;
        loginPanel();
        return;
    }
    default:
    {
        system("cls");
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
    }
    if (!flag)
    {
        fflush(stdin);
        cout << "Press any key to continue...";
        _getch();
        passengerPanel(passenger);
    }
}