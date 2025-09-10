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
            cout << "No bookings till now.\n";
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

            }
        }
    }

    bool ticketcancel(int ticketid) {
        for (auto it = bookedtickets.begin(); it != bookedtickets.end(); ++it) {
            if (it->getid() == ticketid) {
                bookedtickets.erase(it);
                return true;
            }
        }
        return false;
    }
};
class bookingsystem {
private:
    vector<movie> movies;
    vector<showtime> showtimes;
public:
    void addmovie(movie m) { movies.push_back(m); }
    void addshowtime(showtime s) { showtimes.push_back(s); }

    void showallmovies() {
        cout << "\nMovies Available:\n";
        if (movies.empty()) { cout << "No movies available.\n"; return; }
        for (int i=0; i<movies.size(); i++) movies[i].displayDetails(i+1);
    }

    void showallshowtimes() {
        cout << "\nShowtimes Available:\n";
        if (showtimes.empty()) { cout << "No showtimes available.\n"; return; }
        for (int i=0; i<showtimes.size(); i++) showtimes[i].showDetails(i+1);
    }

    string getmovietitle(int index) {
        if (index < 1 || index > movies.size()) 
            throw out_of_range("Invalid movie selection!");
        return movies[index-1].gettitle();
    }

    showtime* getshowtime(int index) {
        if (index < 1 || index > showtimes.size()) 
            throw out_of_range("Invalid showtime selection!");
        return &showtimes[index-1];
    }
};
int main() {
    BookingSystem system;

    // Add Movies
    system.addMovie(movie("Inception", "Sci-Fi", 148));
    system.addMovie(movie("Avengers", "Action", 180));
    system.addMovie(movie("Interstellar", "Sci-Fi", 169));

    // Add Showtimes
    system.addShowtime(showtime("10:00 AM", "2025-09-12", 1, 5));
    system.addShowtime(showtime("2:00 PM", "2025-09-12", 2, 3));
    system.addShowtime(showtime("7:00 PM", "2025-09-12", 3, 2));

    // Create User
    User u1("Rudraksha", "rudra@example.com");

    int choice;
      while(choice != 6){
    cout << "\n========= movie Ticket Booking =========\n";
    cout << "1. View Movies\n";
    cout << "2. View Showtimes\n";
    cout << "3. Book Ticket\n";
    cout << "4. View My Bookings\n";
    cout << "5. Cancel Ticket\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";

    if(!(cin >> choice)){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! Please enter a number.\n";
        continue;
    }

    try{
        switch(choice){
            case 1:
                system.showAllMovies();
                break;
            case 2:
                system.showAllShowtimes();
                break;
            case 3:{
                system.showAllMovies();
                cout << "Select a movie number: ";
                int mChoice; 
                cin >> mChoice;
                string selectedMovie = system.getmovietitle(mChoice);

                system.showAllShowtimes();
                cout << "Select a showtime number: ";
                int sChoice; 
                cin >> sChoice;
                showtime* selectedShow = system.getShowtime(sChoice);

                if(selectedShow->bookSeat()){
                    Ticket t(selectedMovie, selectedShow->getTime());
                    u1.bookticket(t);
                } else{
                    throw runtime_error("No seats available for this showtime!");
                }
                break;
            }
            case 4:
                u1.viewbooking();
                break;
            case 5:{
                u1.viewbooking();
                cout << "Enter Ticket ID to cancel: ";
                int tID; cin >> tID;
                if(u1.ticketcancel(tID)){
                    cout << "Ticket cancelled successfully.\n";
                    // Optional: Restore seat in showtime if mapping is added
                } 
                else{
                    throw runtime_error("Invalid Ticket ID! Cannot cancel.");
                }
                break;
            }
            case 6:
                cout << "Thank you for using movie Ticket Booking System!\n";
                break;
            default:
                cout << "Invalid choice, try again!\n";
        }
    } catch (exception &e){
        cout << "Error: " << e.what() << endl;
    }
}
    return 0;
}
