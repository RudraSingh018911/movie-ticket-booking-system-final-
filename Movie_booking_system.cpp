#include <iostream>
#include <vector>
#include <string>
using namespace std;
class movie {
private:
    string title;
    string genre;
    int duration;
public:
    movie(string title, string genre, int duration){
        this->title = title;
        this->genre = genre;
        this->duration = duration;
    }
    void displayDetails(int index) {
        cout << index << ". " << title << " | Genre: " << genre 
             << " | Duration: " << duration << " mins" << endl;
    }
    string gettitle(){
         return title;
         }
};
class showtime {
private:
    string time;
    string date;
    int hallnumber;
    int avseats;
public:
    showtime(string time, string date, int hall=1, int seats=50) {
                this->time = time;
                this->date = date;
                this->hallnumber = hall;
                avseats = seats;
        }

    void showdetails(int index) {
        cout << index << ". Date: " << date << " | Time: " << time 
             << " | Hall: " << hallnumber 
             << " | Available Seats: " << avseats << endl;
    }

    bool bookseat() {
        if (avseats > 0) {
            avseats--;
            return true;
        }
        return false;
    }

    void cancelseat() { 
        avseats++; 
    }

    string gettime() {
         return time; 
        }
    string getdate() {
         return date; 
        }
    int getavailableseats() {
         return avseats;
         }
};
class Ticket {
private:
    static int count;
    int ticketid;
    string movietitle;
    string showtime;
public:
    ticket(string m, string s) {
        ticketid = count++;
        movietitle = m;
        showtime = s;
    }
    int getid() {
         return ticketid; 
        }
    string getshowtime() {
         return showtime; 
        }
    string getmovietitle() { 
        return movietitle;
     }
    void displayticket() {
        cout << "Ticket ID: " << ticketid 
             << " | movie: " << movietitle 
             << " | Show: " << showtime << endl;
    }
};
int Ticket::count = 0;
class User {
private:
    string name;
    string email;
    vector<Ticket> bookedtickets;
public:
    User(string n, string e){
        name = n;
        email = e;
    }

    void bookticket(Ticket t) {
        bookedtickets.push_back(t);
        cout << "Ticket booked successfully for " << name << endl;
    }

    void viewbooking(){
        cout << "\nBookings for " << name << ":\n";
        if (bookedtickets.empty()) {
            cout << "No bookings yet.\n";
        } else {
            for(int i = 0; i<bookedtickets.size(); i++){
                bookedtickets[i].displayticket();
            }
        }
    }

    bool ticketcancel(int ticketid) {
        for(int i=0; i< bookedtickets.size(); i++){
            if(bookedtickets[i].getid() == ticketid ){
                for(int j = i; j< bookedtickets.size()- 1; j++){
                    bookedtickets[j] = bookedtickets[j+1];
                }
                bookedtickets.pop_back();
                return true;
            }
        }
    return false;
 }
};
