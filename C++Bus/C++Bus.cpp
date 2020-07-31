// C++Bus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

#define BUSCAPACITY 30

void addBus();
void clearAll();
int show(bool);     //Returns bus count
void printReservations(int);
void reserve();
std::string seatDisplay(int);
char* fileChar(std::string);
void availBus();

class Bus {
    public:
        virtual int getId() = 0;
        int id;
        std::string driver;
};

class busInfo : public Bus {
public:
    busInfo() {
        destFrom = "";
        destTo = "";
        id = NULL;
        driver = "";
    }

    busInfo(std::string c, std::string d, int i, std::string drive/*, tm* a, tm* b*/) {
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
        file.open("C:\\Temp\\tmp\\BusInfo.txt", std::ios::app);
        file << id << std::endl;
        file << driver << std::endl;
        file << destFrom << std::endl;
        file << destTo << std::endl;
        /*file << asctime(aTime) << endl;
        file << asctime(dTime) << endl;*/
        file << "END" << std::endl;

        file.close();
    }

    tm* aTime;   //Accurate to MM/DD/YY
    tm* dTime;
    std::string destFrom;
    std::string destTo;
    
private:
    std::fstream file;
};

class Reservation : Bus {
public:
    Reservation(int s, std::string p, int i) {
        seatNum = s;
        passenger = p;
        id = i;
    }
    int getId() {
        return id;
    }

    int seatNum;
    std::string passenger;
};

int main()
{
    int choice;
    bool goAgain = true;
    while (goAgain == true) {
        std::cout << "1. Install" << std::endl;
        std::cout << "2. Reservation" << std::endl;
        std::cout << "3. Show reservation information" << std::endl;
        std::cout << "4. Buses available" << std::endl;
        std::cout << "5. Clear all Info" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cin >> choice;

        switch (choice) {
        case 1: addBus();
            break;
        case 2: reserve();
            break;
        case 3:show(true);
            break;
        case 4: availBus();
            break;
        case 5: clearAll();
            std::cout << "All bus info deleted" << std::endl;
            break;
        case 6: goAgain = false;
            break;
        }
        std::cout << std::endl;
    }
}

int show(bool getRes) {
    std::ifstream infile;
    infile.open("C:\\Temp\\tmp\\BusInfo.txt");
    std::string str;
    int count = 1;
    std::string temp;
    int busCount = 1;
    bool hasBus = false;

    while (getline(infile, str)) {
        hasBus = true;
        if (str != "END") {
            switch (count) {
            case 1: std::cout << "\nBus " << busCount << std::endl;
                std::cout << "ID: ";
                temp = str;
                break;
            case 2: std::cout << "Driver's Name: ";
                break;
            case 3: std::cout << "Departure location: ";
                break;
            case 4: std::cout << "Destination: ";
                break;
            }
            count++;
            std::cout << str << std::endl;
        }
        else {
            if (getRes == true) {
                std::cout << "\nBus reservation Info\n" << std::endl;
                printReservations(stoi(temp));
            }
            count = 1;
            busCount++;
        }
        
    }
    if (hasBus == true) {
        return --busCount;
    }
    else {
        return 0;
    }
}

void printReservations(int busId) {
    std::string fileName = "C:\\Temp\\tmp\\R";
    fileName += std::to_string(busId);
    fileName += ".txt";
    
    std::ifstream file;
    file.open(fileName);
    std::string str;
    while (getline(file, str)) {
        std::cout << str << std::endl;
    }
}

void addBus() {
    busInfo temp;
    std::cout << "Enter a bus ID" << std::endl;
    std::cin >> temp.id, 20;
    std::cin.ignore();
    std::cout << "Enter driver's full name" << std::endl;
    getline(std::cin, temp.driver);
    /*cout << "Enter the departure date" << endl;
    cin >> temp.dTime->tm_mday;
    cout << "Enter the arrival date" << endl;
    cin >> temp.aTime;*/
    std::cout << "Enter departure location" << std::endl;
    getline(std::cin, temp.destFrom);
    std::cout << "Enter destination" << std::endl;
    getline(std::cin, temp.destTo);

    temp.writeIn();

    std::string fileName = "C:\\Temp\\tmp\\R";
    fileName += std::to_string(temp.id);
    fileName += ".txt";

    std::ofstream fileCreate (fileName);
    fileCreate << "" << std::endl;
    fileCreate.close();
    
    std::ofstream file;

    char* writable = new char[fileName.size() + 1];
    std::copy(fileName.begin(), fileName.end(), writable);
    writable[fileName.size()] = '\0'; // don't forget the terminating 0

    file.open(writable); //Name files based off bus id
    for (int x = 1; x <= BUSCAPACITY; x++) {
        file << x << ". EMPTY" << std::endl;
    }

    delete[] writable;
    file.close();
}

void clearAll() {
    std::ifstream file;

    std::string fileName;
    char* pFileName;
    bool isId = true;
    std::string str;
    file.open("C:\\Temp\\tmp\\BusInfo.txt");
    while (getline(file, str)) {
        if (isId == true) {
            fileName = "C:\\Temp\\tmp\\R";
            fileName += str;
            fileName += ".txt";

            char* writable = new char[fileName.size() + 1];
            std::copy(fileName.begin(), fileName.end(), writable);
            writable[fileName.size()] = '\0'; // don't forget the terminating 0

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
    file.open("C:\\Temp\\tmp\\BusInfo.txt", std::ios::out);
    file.close();
}

void reserve() {
    std::cout << "Enter a bus number for reservation" << std::endl;
    std::string str;
    int busCount = show(false);
    if (busCount == 0) {
        std::cout << "No buses installed" << std::endl;
        return;
    }

    int choice;
    int count = 1;
    for (;;) {
        std::cin >> choice;
        if (choice < 1 || choice > busCount) {
            std::cout << "Bus number request is out of range, input a valid bus number" << std::endl;
        }
        else { break; }
    }

    std::ifstream infile;
    infile.open("C:\\Temp\\tmp\\BusInfo.txt");

    std::string rFile;

    while (getline(infile, str)) {
        if (count == choice) {
            rFile = seatDisplay(stoi(str));
            break;
        }
        
        if (str == "END") {
            count++;
        }
    }
    infile.close();

    std::string passenger;

    std::cin >> choice;
    std::cout << "Enter the passenger name to reserve the seat" << std::endl;
    std::cin.ignore();
    std::getline(std::cin, passenger);

    int lineCounter = 1;
    std::ifstream fileRead;
    std::ofstream fileIn;

    fileIn.open("C:\\Temp\\tmp\\temp.txt");
    fileRead.open(rFile);

    while (getline(fileRead, str)) {
        if (lineCounter != choice)
        {
            fileIn << str << std::endl;
        }
        else {
            fileIn << choice << ". " << passenger << std::endl;
        }
        lineCounter++;
    }
    fileRead.close();
    fileIn.close();

    char* writable = new char[rFile.size() + 1];
    std::copy(rFile.begin(), rFile.end(), writable);
    writable[rFile.size()] = '\0'; // don't forget the terminating 0

    remove(writable);
    rename("C:\\Temp\\tmp\\temp.txt", writable);

    delete[] writable;
}

std::string seatDisplay(int id) {
    std::string fileName = "C:\\Temp\\tmp\\R";
    fileName += std::to_string(id);
    fileName += ".txt";

    char* writable = new char[fileName.size() + 1];
    std::copy(fileName.begin(), fileName.end(), writable);
    writable[fileName.size()] = '\0'; // don't forget the terminating 0

    std::string str;

    std::ifstream file;
    file.open(writable); //Name files based off bus id
    while(getline(file, str)){
        std::cout << str << std::endl;
    }

    std::cout << "From the above, pick an available seat" << std::endl;

    delete[] writable;

    file.close();

    return fileName;
}

void availBus() {
    std::ifstream fileRead;
    std::ifstream reserveRead;
    std::string str;
    std::string str2;
    fileRead.open("C:\\Temp\\tmp\\BusInfo.txt");
    bool nextId = true;
    bool showBus = false;
    std::string temp;
    int counter = 1;
    int count = 1;

    while (getline(fileRead, str)) {
        if (nextId == true) {
            std::string fileName = "C:\\Temp\\tmp\\R";
            fileName += str;
            fileName += ".txt";

            char* a = new char[fileName.size() + 1];
            std::copy(fileName.begin(), fileName.end(), a);
            a[fileName.size()] = '\0'; // don't forget the terminating 0

            reserveRead.open(a);
            while (getline(reserveRead, str2)) {
                temp = std::to_string(counter) + ". EMPTY";
                if (temp != str2){
                    showBus = true;
                    std::cout << temp << std::endl;
                    std::cout << str2 << std::endl;
                    break;
                }
                counter++;
            }
            counter = 1;
            nextId = false;
            reserveRead.close();
        }

        if (showBus == true) {
            switch (count) {
            case 1: std::cout << "\nBus" << std::endl;
                std::cout << "ID: ";
                break;
            case 2: std::cout << "Driver's Name: ";
                break;
            case 3: std::cout << "Departure location: ";
                break;
            case 4: std::cout << "Destination: ";
                break;
            }
            if (count != 5) {
                std::cout << str << std::endl;
            }
            count++;
        }

        if (str == "END") {
            nextId = true;
            showBus = false;
            count = 1;
        }
    }
    fileRead.close();
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
