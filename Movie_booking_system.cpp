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
