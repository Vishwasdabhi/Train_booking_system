#include "frontend.cpp"
int main()
{

    cout << "           o x o x o x o . . ." << endl;
    cout << "         o      _____            _______________ ___=====__T___" << endl;
    cout << "       .][__n_n_|DD[  ====_____  |    |.\\/.|   | |   |_|     |_" << endl;
    cout << "      >(________|__|_[_________]_|____|_/\\_|___|_|___________|_|" << endl;
    cout << "      _/oo OOOOO oo`  ooo   ooo   o^o       o^o   o^o     o^o" << endl;
    cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
    char ch;
    cin >> ch;
    seed();
    loadDataFromFile();
    loginPanel();
    saveDataToFile();
    delete passengers;
    delete stations;
    delete travelClasses;
    delete trains;
    delete tickets;
    return 0;
}