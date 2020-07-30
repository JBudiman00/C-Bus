// C++Bus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

#define BUSCAPACITY 30

using namespace std;

void addBus();
void clearAll();
void show();
void printReservations(int);
void reserve();
void seatDisplay(int);

class Bus {
    public:
        virtual int getId() = 0;
        int id;
        string driver;
};

class busInfo : public Bus {
public:
    busInfo() {
        destFrom = "";
        destTo = "";
        id = NULL;
        driver = "";
    }

    busInfo(string c, string d, int i, string drive/*, tm* a, tm* b*/) {
        /*aTime = a;
        dTime = b;*/
        destFrom = c;
        destTo = d;
        id = i;
        driver = drive;
    }

    int getId() {
        return id;
    }

    void writeIn() {
        file.open("C:\\Temp\\tmp\\BusInfo.txt", ios::app);
        file << id << endl;
        file << driver << endl;
        file << destFrom << endl;
        file << destTo << endl;
        /*file << asctime(aTime) << endl;
        file << asctime(dTime) << endl;*/
        file << "END" << endl;

        file.close();
    }

    tm* aTime;   //Accurate to MM/DD/YY
    tm* dTime;
    string destFrom;
    string destTo;
    
private:
    fstream file;
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

    int seatNum;
    string passenger;
};

int main()
{
    int choice;
    bool goAgain = true;
    while (goAgain == true) {
        cout << "1. Install" << endl;
        cout << "2. Reservation" << endl;
        cout << "3. Show reservation information" << endl;
        cout << "4. Buses available" << endl;
        cout << "5. Clear all Info" << endl;
        cout << "6. Exit" << endl;
        cin >> choice;

        switch (choice) {
        case 1: addBus();
            break;
        case 2: reserve();
            break;
        case 3:show();
            break;
        case 5: clearAll();
            cout << "All bus info deleted" << endl;
            break;
        case 6: goAgain = false;
            break;
        }
        cout << endl;
    }
}

void show() {
    ifstream infile;
    infile.open("C:\\Temp\\tmp\\BusInfo.txt");
    string str;
    int count = 1;
    string temp;

    while (getline(infile, str)) {
        if (str != "END") {
            switch (count) {
            case 1: cout << "ID: ";
                temp = str;
                break;
            case 2: cout << "Driver's Name: ";
                break;
            case 3: cout << "Departure location: ";
                break;
            case 4: cout << "Destination: ";
                break;
            }
            count++;
            cout << str << endl;
        }
        else {
            cout << "\nBus reservation Info\n" << endl;
            printReservations(stoi(temp));
            count = 1;
            cout << endl << "Next bus";
        }
        
    }
    
}

void printReservations(int busId) {
    string fileName = "C:\\Temp\\tmp\\R";
    fileName += to_string(busId);
    fileName += ".txt";
    
    ifstream file;
    file.open(fileName);
    string str;
    while (getline(file, str)) {
        cout << str << endl;
    }
}

void addBus() {
    busInfo temp;
    cout << "Enter a bus ID" << endl;
    cin >> temp.id, 20;
    cin.ignore();
    cout << "Enter driver's full name" << endl;
    getline(cin, temp.driver);
    /*cout << "Enter the departure date" << endl;
    cin >> temp.dTime->tm_mday;
    cout << "Enter the arrival date" << endl;
    cin >> temp.aTime;*/
    cout << "Enter departure location" << endl;
    getline(cin, temp.destFrom);
    cout << "Enter destination" << endl;
    getline(cin, temp.destTo);

    temp.writeIn();

    string fileName = "C:\\Temp\\tmp\\R";
    fileName += to_string(temp.id);
    fileName += ".txt";

    ofstream fileCreate (fileName);
    fileCreate << "" << endl;
    fileCreate.close();
    
    fstream file;
    file.open(fileName, ios::out); //Name files based off bus id
    for (int x = 1; x <= BUSCAPACITY; x++) {
        file << x << ". EMPTY" << endl;
    }

    file.close();
}

void clearAll() {
    ifstream file;  

    string fileName;
    char* pFileName;
    bool isId = true;
    string str;
    file.open("C:\\Temp\\tmp\\BusInfo.txt");
    while (getline(file, str)) {
        if (isId == true) {
            fileName = "C:\\Temp\\tmp\\R";
            fileName += str;
            fileName += ".txt";

            //char* writable = new char[fileName.size() + 1];
            //copy(fileName.begin(), fileName.end(), writable);
            //writable[fileName.size()] = '\0'; // don't forget the terminating 0

            remove(writable);

            delete[] writable;

            isId = false;
        }

        if (str == "END") {
            isId = true;
        }
    }
    file.close();

    remove("C:\\Temp\\tmp\\BusInfo.txt");
    file.open("C:\\Temp\\tmp\\BusInfo.txt", ios::out);
    file.close();
}

void reserve() {
    cout << "Enter a bus number for reservation\n" << endl;
    ifstream infile;
    infile.open("C:\\Temp\\tmp\\BusInfo.txt");
    string str;
    int count = 1;
    int busCount = 1;
    while (getline(infile, str)) {
        if (str != "END") {
            switch (count) {
            case 1: cout << "Bus " << busCount << endl;
                cout << "ID: ";
                break;
            case 2: cout << "Driver's Name: ";
                break;
            case 3: cout << "Departure location: ";
                break;
            case 4: cout << "Destination: ";
                break;
            }
            count++;
            cout << str << endl;
        }
        else {
            cout << endl;
            count = 1;
            busCount++;
        }
    }

    infile.close();

    int choice;
    count = 1;
    cin >> choice;

    infile.open("C:\\Temp\\tmp\\BusInfo.txt");

    while (getline(infile, str)) {
        if (count == choice) {
            seatDisplay(stoi(str));
            break;
        }
        
        if (str == "END") {
            count++;
        }
    }

    infile.close();
}

void seatDisplay(int id) {
    string fileName = "C:\\Temp\\tmp\\R";
    fileName += to_string(id);
    fileName += ".txt";

    string str;

    fstream file;
    file.open(fileName, ios::out); //Name files based off bus id
    while(getline(file, str)){
        cout << str << endl;
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
