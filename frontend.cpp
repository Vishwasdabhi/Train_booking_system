#include "backend.cpp"

void loginPanel();
void adminPanel();
void userGuestPanel();
void passengerPanel(Passenger *passenger);

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";

void loginPanel()
{
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "Welcome to the Train management system." << endl;
    cout << "Log in as :" << endl;
    cout << "1. Admin" << endl;
    cout << "2. User Guest" << endl;
    cout << "3. Passenger" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        system("cls");
        string username, password;
        cout << "Enter Admin Username: ";
        cin >> username;
        cout << "Enter Admin Password: ";
        cin >> password;
        if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD)
        {
            cout << "Login successful!" << endl;
            char ch;
            cout << "Press any key to continue...";
            cin >> ch;
            adminPanel();
        }
        else
        {
            cout << "Invalid credentials. Please try again." << endl;
            char ch;
            cout << "Press any key to continue...";
            cin >> ch;
            loginPanel();
        }
        break;
        adminPanel();
        break;
    }
    case 2:
    {
        userGuestPanel();
        break;
    }
    case 3:
    {
        system("cls");
        string username, password;
        cout << "Enter Passenger Username: ";
        cin >> username;
        cout << "Enter Passenger Password: ";
        cin >> password;
        bool found = false;
        for (auto &&passenger : *passengers)
        {
            if (passenger.getUsername() == username && passenger.getPassword() == password)
            {
                found = true;
                cout << "Login successful!" << endl;
                char ch;
                cout << "Press any key to continue...";
                cin >> ch;
                passengerPanel(&passenger);
                break;
            }
        }

        break;
    }
    case 4:
    {
        system("cls");
        cout << "Thank you for using the Train Management System!" << endl;
        cout << endl;
        cout << "___________   _______________________________________^__" << endl;
        cout << " ___   ___ |||  ___   ___   ___    ___ ___  |   __  ,----\\" << endl;
        cout << "|   | |   |||| |   | |   | |   |  |   |   | |  |  | |_____\\" << endl;
        cout << "|___| |___|||| |___| |___| |___|  | O | O | |  |  |        \\" << endl;
        cout << "           |||                    |___|___| |  |__|         )" << endl;
        cout << "___________|||______________________________|______________/" << endl;
        cout << "           |||                                        /--------" << endl;
        cout << "-----------'''---------------------------------------'" << endl;
        return;
    }
    default:
    {

        cout << "Invalid choice. Please try again." << endl;
        char ch;
        cout << "Press any key to continue...";
        cin >> ch;
        loginPanel();
        break;
    }
    }
    char ch;
    cout << "Press any key to continue...";
    cin >> ch;
    loginPanel();
}

void adminPanel()
{
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "Welcome to the Admin Panel!" << endl;
    cout << "\n--- Admin Panel ---" << endl;
    cout << "1. View All Trains" << endl;
    cout << "2. View All Stations" << endl;
    cout << "3. Add Train" << endl;
    cout << "4. Add Station" << endl;
    cout << "5. Update Train Route" << endl;
    cout << "6. Update Train Fare" << endl;
    cout << "7. Update Train Seats" << endl;
    cout << "8. Logout" << endl;

    cout << "Enter your choice: ";
    int choice;
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
        Adminpanel.addTrain();
        char ch;
        cout << "Press any key to continue...";
        cin >> ch;
        break;
    }
    case 4:
    {
        system("cls");
        Adminpanel.addStation();

        break;
    }
    case 5:
    {
        set<int> TrainIds;
        vector<Train *> trains = Adminpanel.getTrains();
        for (auto &&train : trains)
        {
            TrainIds.insert(train->getId());
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
        vector<Train *> trains = Adminpanel.getTrains();
        for (auto &&train : trains)
        {
            TrainIds.insert(train->getId());
        }
        system("cls");
        Adminpanel.viewAllTrains();
        cout << "Enter the Train ID to update its fare: ";
        int trainId;
        cin >> trainId;
        while (TrainIds.find(trainId) == TrainIds.end())
        {
            cout << "Invalid Train ID. Please try again: ";
            cin >> trainId;
        }
        string className;
        cout << "Enter class name: ";
        cin >> className;
        float newFare;
        cout << "Enter new fare: ";
        cin >> newFare;
        Adminpanel.updateTrainFare(trainId, className, newFare);
        break;
    }
    case 7:
    {
        set<int> TrainIds;
        vector<Train *> trains = Adminpanel.getTrains();
        for (auto &&train : trains)
        {
            TrainIds.insert(train->getId());
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
        string className;
        cout << "Enter class name: ";
        cin >> className;
        int newTotalSeats;
        cout << "Enter new total seats: ";
        cin >> newTotalSeats;
        Adminpanel.updateTrainSeats(trainId, className, newTotalSeats);
        break;
    }
    case 8:
    {
        system("cls");
        cout << "Logged out successfully." << endl;
        char ch;
        cout << "Press any key to continue...";
        cin >> ch;
        loginPanel();
        break;
    }
    default:
    {
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
    }
    char ch;
    cout << "Press any key to continue...";
    cin >> ch;
    adminPanel();
}

void userGuestPanel()
{
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "Welcome to the User Guest Panel!" << endl;
    cout << "\n--- User Guest Panel ---" << endl;
    cout << "1. View Stations" << endl;
    cout << "2. View Train Availability" << endl;
    cout << "3. Logout" << endl;

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
        char ch;
        cout << "Press any key to continue...";
        cin >> ch;
        loginPanel();
        break;
    }
    }
    char ch;
    cout << "Press any key to continue...";
    cin >> ch;
    userGuestPanel();
}
void passengerPanel(Passenger *passenger)
{
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "Welcome to the Passenger Panel!" << endl;
    cout << "\n--- Passenger Panel ---" << endl;

    cout << "1. View Stations" << endl;
    cout << "2. View Train Availability" << endl;
    cout << "3. Book Ticket" << endl;
    cout << "4. Cancel Ticket" << endl;
    cout << "5. View My Tickets" << endl;
    cout << "6. Change Password" << endl;
    cout << "7. Logout" << endl;
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
        cout << "Select a train by entering its index: ";
        int trainIndex;
        cin >> trainIndex;
        while (trainIndex < 1 || trainIndex > availableTrains.size())
        {
            cout << "Invalid train selection. Enter correct index: ";
            cin >> trainIndex;
            break;
        }
        Train *selectedTrain = availableTrains[trainIndex - 1];
        cout << "Enter class name: ";
        string className;
        cin >> className;
        TravelClass *selectedClass = nullptr;
        for (auto &&travelClass : selectedTrain->getClasses())
        {
            if (travelClass.getClassName() == className)
            {
                selectedClass = &travelClass;
                break;
            }
        }
        Station *fromStation = Adminpanel.getStationByName(from);
        Station *toStation = Adminpanel.getStationByName(to);
        passenger->bookTicket(*fromStation, *toStation, *selectedClass, date);
       
        break;
    }
    case 4:
    {
        system("cls");
        passenger->cancelTicket();
        
        break;
    }
    case 5:
    {
        system("cls");
        passenger->viewMyTickets();
        
        break;
    }
    case 6:
    {
        system("cls");
        string currentPassword;
        cout << "Enter current password: ";
        cin >> currentPassword;
        if (currentPassword != passenger->getPassword())
        {
            cout << "Incorrect current password. Please try again." << endl;
            passengerPanel(passenger);
            return;
        }
        string newPassword;
        cout << "Enter new password: ";
        cin >> newPassword;
        string confirmPassword;
        cout << "Confirm new password: ";
        cin >> confirmPassword;
        while (newPassword != confirmPassword)
        {
            cout << "Passwords do not match. Please try again." << endl;
            cout << "Enter new password: ";
            cin >> newPassword;
            cout << "Confirm new password: ";
            cin >> confirmPassword;
        }
        if (passenger->changePassword(newPassword))
        {
            cout << "Password changed successfully!" << endl;
        }
        else
        {
            cout << "Failed to change password. Please try again." << endl;
            char ch;
            cout << "Press any key to continue...";
            cin >> ch;
            passengerPanel(passenger);
        }
       
        break;
    }
    case 7:
    {
        system("cls");
        passenger->logout();
        char ch;
        cout << "Press any key to continue...";
        cin >> ch;
        loginPanel();
        break;
    }
    default:
    {
        system("cls");
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
    }
    char ch;
    cout << "Press any key to continue...";
    cin >> ch;
    passengerPanel(passenger);
}