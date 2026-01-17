#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm> 
using namespace std;

// ----------------------
// Base User Class
// ----------------------
class User {
protected:
    string username;
    string password;
public:
    User() {}
    User(string u, string p) : username(u), password(p) {}
    virtual bool login(string u, string p) { return (username == u && password == p); }
    string getUsername() { return username; }
};

// ----------------------
// Admin Class
// ----------------------
class Admin : public User {
public:
    Admin(string u, string p) : User(u, p) {}
};

// ----------------------
// Passenger Class
// ----------------------
class Passenger : public User {
public:
    Passenger(string u, string p) : User(u, p) {}
};

// ----------------------
// Flight Class
// ----------------------
class Flight {
public:
    string flightNumber;
    string source;
    string destination;
    string date;
    string time;
    int totalSeats;
    int availableSeats;

    Flight() {}
    Flight(string fn, string s, string d, string dt, string t, int ts)
        : flightNumber(fn), source(s), destination(d), date(dt), time(t), totalSeats(ts), availableSeats(ts) {}

    void displayInfo() {
        cout << "Flight: " << flightNumber << " | " << source << " -> " << destination
             << " | Date: " << date << " | Time: " << time
             << " | Seats: " << availableSeats << "/" << totalSeats << endl;
    }
};

// ----------------------
// Booking Class
// ----------------------
class Booking {
public:
    string bookingID;
    string flightNumber;
    string passengerName;
    int seatNumber;

    void displayBooking() {
        cout << "Booking ID: " << bookingID << " | Passenger: " << passengerName
             << " | Flight: " << flightNumber << " | Seat: " << seatNumber << endl;
    }
};

// ----------------------
// Flight Manager Class
// ----------------------
class FlightManager {
public:
    vector<Flight> flights;

    void addFlight(Flight f) {
        flights.push_back(f);
        cout << "Flight added successfully!" << endl;
    }

    void removeFlight(string flightNum) {
        for (auto it = flights.begin(); it != flights.end(); ++it) {
            if (it->flightNumber == flightNum) {
                flights.erase(it);
                cout << "Flight removed successfully!" << endl;
                return;
            }
        }
        cout << "Flight not found!" << endl;
    }

    void updateFlight(string flightNum) {
        Flight* f = searchFlightByNumber(flightNum);
        if (f != nullptr) {
            cout << "Update flight details:\n";
            cout << "New source: "; cin >> f->source;
            cout << "New destination: "; cin >> f->destination;
            cout << "New date (YYYY-MM-DD): "; cin >> f->date;
            cout << "New time (HH:MM): "; cin >> f->time;
            cout << "New total seats: "; cin >> f->totalSeats;
            f->availableSeats = f->totalSeats; // reset seats
            cout << "Flight updated successfully!\n";
        } else {
            cout << "Flight not found!\n";
        }
    }

    void displayAllFlights() {
        for (auto &f : flights) f.displayInfo();
    }

    Flight* searchFlightByNumber(string flightNum) {
        for (auto &f : flights) {
            if (f.flightNumber == flightNum)
                return &f;
        }
        return nullptr;
    }

    // File persistence
    void saveFlightsToFile() {
        ofstream file("flights.txt");
        for (auto &f : flights) {
            file << f.flightNumber << " " << f.source << " " << f.destination << " "
                 << f.date << " " << f.time << " " << f.totalSeats << " " << f.availableSeats << "\n";
        }
        file.close();
    }

    void loadFlightsFromFile() {
        ifstream file("flights.txt");
        if (!file.is_open()) return;
        flights.clear();
        string fn, s, d, dt, t;
        int ts, avail;
        while (file >> fn >> s >> d >> dt >> t >> ts >> avail) {
            Flight f(fn, s, d, dt, t, ts);
            f.availableSeats = avail;
            flights.push_back(f);
        }
        file.close();
    }
};

// ----------------------
// Booking Manager Class
// ----------------------
class BookingManager {
public:
    vector<Booking> bookings;
    queue<string> waitingList; // for full flights

    void addBooking(Booking b) {
        bookings.push_back(b);
        cout << "Booking successful! Booking ID: " << b.bookingID << endl;
    }

    void displayAllBookings() {
        for (auto &b : bookings) b.displayBooking();
    }

    Booking* searchBooking(string bookingID) {
        for (auto &b : bookings) {
            if (b.bookingID == bookingID)
                return &b;
        }
        return nullptr;
    }

    void bookTicket(FlightManager &fm, string passengerName) {
        string flightNum;
        cout << "Enter flight number to book: ";
        cin >> flightNum;
        Flight* f = fm.searchFlightByNumber(flightNum);
        if (f != nullptr) {
            if (f->availableSeats > 0) {
                Booking b;
                b.flightNumber = flightNum;
                b.passengerName = passengerName;
                b.seatNumber = f->totalSeats - f->availableSeats + 1;
                b.bookingID = flightNum + to_string(b.seatNumber); // simple unique ID
                addBooking(b);
                f->availableSeats--;
            } else {
                cout << "No seats available! Added to waiting list.\n";
                waitingList.push(passengerName + " " + flightNum);
            }
        } else {
            cout << "Flight not found.\n";
        }
    }

    void cancelTicket(FlightManager &fm) {
        string bookingID;
        cout << "Enter Booking ID to cancel: ";
        cin >> bookingID;
        Booking* b = searchBooking(bookingID);
        if (b != nullptr) {
            Flight* f = fm.searchFlightByNumber(b->flightNumber);
            if (f != nullptr) f->availableSeats++;
            bookings.erase(remove_if(bookings.begin(), bookings.end(),
                                     [&](Booking x){ return x.bookingID == bookingID; }), bookings.end());
            cout << "Booking cancelled successfully!\n";

            // Assign seat to first in waiting list if any
            if (!waitingList.empty()) {
                string w = waitingList.front();
                waitingList.pop();
                string pname = w.substr(0, w.find(" "));
                string fnum = w.substr(w.find(" ") + 1);
                Flight* wf = fm.searchFlightByNumber(fnum);
                if (wf && wf->availableSeats > 0) {
                    Booking nb;
                    nb.passengerName = pname;
                    nb.flightNumber = fnum;
                    nb.seatNumber = wf->totalSeats - wf->availableSeats + 1;
                    nb.bookingID = fnum + to_string(nb.seatNumber);
                    addBooking(nb);
                    wf->availableSeats--;
                    cout << pname << " from waiting list got a seat!\n";
                }
            }
        } else {
            cout << "Booking ID not found!\n";
        }
    }

    void saveBookingsToFile() {
        ofstream file("bookings.txt");
        for (auto &b : bookings) {
            file << b.bookingID << " " << b.passengerName << " " << b.flightNumber << " " << b.seatNumber << "\n";
        }
        file.close();
    }

    void loadBookingsFromFile() {
        ifstream file("bookings.txt");
        if (!file.is_open()) return;
        bookings.clear();
        string id, pname, fnum;
        int seat;
        while (file >> id >> pname >> fnum >> seat) {
            Booking b;
            b.bookingID = id;
            b.passengerName = pname;
            b.flightNumber = fnum;
            b.seatNumber = seat;
            bookings.push_back(b);
        }
        file.close();
    }
};

// ----------------------
// Main Function
// ----------------------
int main() {
    FlightManager flightManager;
    BookingManager bookingManager;

    // Load existing data
    flightManager.loadFlightsFromFile();
    bookingManager.loadBookingsFromFile();

    Admin admin("admin", "1234");

    int choice;
    string username;

    while (true) {
        cout << "\n--- SkyBook Airline Reservation ---\n";
        cout << "1. Admin Login\n2. Passenger Login\n3. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            string uname, pass;
            cout << "Username: "; cin >> uname;
            cout << "Password: "; cin >> pass;
            if (admin.login(uname, pass)) {
                cout << "Admin logged in!\n";
                int aChoice;
                do {
                    cout << "\n1. Add Flight\n2. Remove Flight\n3. Update Flight\n4. Display Flights\n5. Logout\nChoice: ";
                    cin >> aChoice;
                    if (aChoice == 1) {
                        string fn, s, d, dt, t; int seats;
                        cout << "Flight Number: "; cin >> fn;
                        cout << "Source: "; cin >> s;
                        cout << "Destination: "; cin >> d;
                        cout << "Date: "; cin >> dt;
                        cout << "Time: "; cin >> t;
                        cout << "Total Seats: "; cin >> seats;
                        flightManager.addFlight(Flight(fn, s, d, dt, t, seats));
                    } else if (aChoice == 2) {
                        string fn; cout << "Flight Number to remove: "; cin >> fn;
                        flightManager.removeFlight(fn);
                    } else if (aChoice == 3) {
                        string fn; cout << "Flight Number to update: "; cin >> fn;
                        flightManager.updateFlight(fn);
                    } else if (aChoice == 4) {
                        flightManager.displayAllFlights();
                    }
                } while (aChoice != 5);
            } else {
                cout << "Invalid credentials!\n";
            }
        } else if (choice == 2) {
            string passengerName;
            cout << "Enter your name: ";
            cin >> passengerName;
            int pChoice;
            do {
                cout << "\n1. View Flights\n2. Book Ticket\n3. Cancel Ticket\n4. View My Bookings\n5. Logout\nChoice: ";
                cin >> pChoice;
                if (pChoice == 1) flightManager.displayAllFlights();
                else if (pChoice == 2) bookingManager.bookTicket(flightManager, passengerName);
                else if (pChoice == 3) bookingManager.cancelTicket(flightManager);
                else if (pChoice == 4) {
                    cout << "Your Bookings:\n";
                    for (auto &b : bookingManager.bookings) {
                        if (b.passengerName == passengerName) b.displayBooking();
                    }
                }
            } while (pChoice != 5);
        } else break;
    }

    // Save data
    flightManager.saveFlightsToFile();
    bookingManager.saveBookingsToFile();

    cout << "Thank you for using SkyBook!\n";
    return 0;
}
