// COMSC-210 | Lab 28 | Mamadou Sissoko
// IDE used: Visual Studio Code
// Adding more goat menu options to previous solution

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 11) {
        switch (sel) {
            case 1: // Adds goat
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2: // Removes goat
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3: // Displays list of goat
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4: // Goats sorted by name
                trip.sort();
                cout << "Goats sorted by alphabetical order.\n";
                break;
            case 5: // Goats sorted in reverse
                trip.reverse();
                cout << "Goats order is now reversed.\n";
                break;
            case 6: // Displays first goat in trip
              if (!trip.empty()) {
                 Goat g = trip.front();
                 cout << "First goat in the trip:\n";
                 cout << "\t" << g.get_name() 
                      << " (" << g.get_age() 
                      << ", " << g.get_color() << ")\n";
              } else {
                 cout << "The trip has no goats.\n";
                      }
                    break;  
            case 7: // Displays last goat in trip
              if (!trip.empty()) {
                 Goat g = trip.back();
                 cout << "Last goat in the trip:\n";
                 cout << "\t" << g.get_name() 
                      << " (" << g.get_age() 
                      << ", " << g.get_color() << ")\n";
              } else {
                 cout << "The trip has no goats.\n";
                      }
                    break;  
            default:
                cout << "Invalid selection.\n";
                break;
            case 8: // Displays # of goats on trip
                cout << "There are currently " << trip.size() << " goats in the trip.\n";
                break;
            case 9: // Displays a random goat
              if (!trip.empty()) {
                 int randomIndex = rand() % trip.size();
                 auto it = trip.begin();
                 advance(it, randomIndex);
                 Goat g = *it;
                 cout << "Random goat selected:\n";
                 cout << "\t" << g.get_name()
                      << " (" << g.get_age()
                      << ", " << g.get_color() << ")\n";
              } else { 
                  cout << "No goats in the trip.\n";
              }
              break;
            case 10: // Clears the list of goats present
             if (!trip.empty()) {
             trip.clear();
            cout << "All goats have been removed from the trip.\n";
         } else {
             cout << "There are no goats to remove.\n";
              }
             break;
        }

        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Sorts goats in alphabetical order\n";
    cout << "[5] Sorts goats in reverse order\n";
    cout << "[6] Display the first goat\n";
    cout << "[7] Display the last goat\n";
    cout << "[8] Display goat total in list\n";
    cout << "[9] Display a random goat\n";
    cout << "[10] Clears list of goats\n";
    cout << "[11] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 11) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}