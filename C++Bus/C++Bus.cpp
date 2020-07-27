// C++Bus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

class Bus {
    public:
        virtual int getId() = 0;
    protected:
        int id;
        string driver;
};

class busInfo : public Bus {
public:
    busInfo(tm a, tm b, string c, string d, int i, string drive) {
        aTime = a;
        dTime = b;
        destFrom = c;
        destTo = d;
        int id = i;
        string driver = drive;
    }

    int getId() {
        return id;
    }

    void writeIn() {
        file.open("C:\\Temp\\tmp\\BusInfo.txt", ios::out);
    }
    
private:
    fstream file;
    tm aTime;
    tm dTime;
    string destFrom;
    string destTo;
};

class Reservation : Bus {
public:
    Reservation(int s, string p, int i) {
        seatNum = s;
        passenger = p;
        id = i;
    }
    int getId() {
        return id;
    }
private:
    int seatNum;
    string passenger;
};

int main()
{
    int choice;
    cout << "1. Install" << endl;
    cout << "2. Reservation" << endl;
    cout << "3. Show reservation information" << endl;
    cout << "4. Buses available" << endl;
    cout << "5. Exit" << endl;
    cin >> choice; 

    switch (choice) {
    case 1: 
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
