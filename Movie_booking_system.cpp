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
    void displaydetails(int index) {
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
    string getdate(){
         return date; 
    }
    int getavailableseats(){ 
        return avseats; 
    }
};

class Ticket{
private:
    static int count;
    int ticketid;
    string movietitle;
    string showtime;
public:
    Ticket(string m, string s){   
        ticketid = count++;
        movietitle = m;
        showtime = s;
    }
    int getid(){ 
        return ticketid; 
    }
    string getshowtime(){ 
        return showtime; 
    }
    string getmovietitle(){
        return movietitle; 
    }
    void displayticket(){
        cout << "Ticket ID: " << ticketid 
             << " | Movie: " << movietitle 
             << " | Show: " << showtime << endl;
    }
};
int Ticket::count = 0;   

class User{
private:
    string name;
    string email;
    vector<Ticket> bookedtickets;
public:
    User(string n, string e){
        name = n;
        email = e;
    }

    string getname(){
        return name;
    }

    void bookticket(Ticket t){
        bookedtickets.push_back(t);
        cout << "Ticket booked successfully for " << name << endl;
    }

    void viewbooking(){
        cout << "\nBookings for " << name << ":\n";
        if (bookedtickets.empty()){
            cout << "No bookings yet.\n";
        } else{
            for(int i = 0; i < bookedtickets.size(); i++){
                bookedtickets[i].displayticket();  
            }
        }
    }

    bool ticketcancel(int ticketid){
        for (auto it = bookedtickets.begin(); it != bookedtickets.end(); ++it){
            if (it->getid() == ticketid){
                bookedtickets.erase(it);
                return true;
            }
        }
        return false;
    }
};

class bookingsystem{
private:
    vector<movie> movies;
    vector<showtime> showtimes;
public:
    void addmovie(movie m){ 
        movies.push_back(m); 
    }
    void addshowtime(showtime s){
         showtimes.push_back(s); 
        }

    void showallmovies(){
        cout << "\nMovies Available:\n";
        if(movies.empty()){
             cout << "No movies available.\n";
              return; 
            }
        for(int i=0; i<movies.size(); i++){
             movies[i].displaydetails(i+1);
        }
    }

    void showallshowtimes(){
        cout << "\nShowtimes Available:\n";
        if(showtimes.empty()){ 
            cout << "No showtimes available.\n"; return;
         }
        for (int i=0; i<showtimes.size(); i++){
            showtimes[i].showdetails(i+1);
        }
    }

    string getmovietitle(int index){
        if(index < 1 || index > movies.size()){
            throw out_of_range("Invalid movie selection!");
        }
        return movies[index-1].gettitle();
    }

    showtime* getshowtime(int index){
        if (index < 1 || index > showtimes.size()) 
            throw out_of_range("Invalid showtime selection!");
        return &showtimes[index-1];
    }
};

int main() {
    bookingsystem system;
    vector<User> users;

    // Add Movies
    system.addmovie(movie("Inception", "Sci-Fi", 148));
    system.addmovie(movie("Avengers", "Action", 180));
    system.addmovie(movie("Interstellar", "Sci-Fi", 169));

    // Add Showtimes
    system.addshowtime(showtime("10:00 AM", "2025-09-12", 1, 5));
    system.addshowtime(showtime("2:00 PM", "2025-09-12", 2, 3));
    system.addshowtime(showtime("7:00 PM", "2025-09-12", 3, 2));

    // Add default user
    users.push_back(User("Rudraksha", "rudra@gmail.com"));

    int choice = 0;
    int currentUserIndex = 0; // Default user is logged in

    while(choice != 7){
        cout << "\n========= Movie Ticket Booking =========\n";
        cout << "1. View Movies\n";
        cout << "2. View Showtimes\n";
        cout << "3. Book Ticket\n";
        cout << "4. View My Bookings\n";
        cout << "5. Cancel Ticket\n";
        cout << "6. Add New User (Ticket Manager)\n";
        cout << "7. Exit\n";
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
                    system.showallmovies();
                    break;
                case 2:
                    system.showallshowtimes();
                    break;
                case 3:{
                    system.showallmovies();
                    cout << "Select a movie number: ";
                    int mChoice; 
                    cin >> mChoice;
                    string selectedmovie = system.getmovietitle(mChoice);

                    system.showallshowtimes();
                    cout << "Select a showtime number: ";
                    int sChoice; 
                    cin >> sChoice;
                    showtime* selectedShow = system.getshowtime(sChoice);

                    if(selectedShow->bookseat()){
                        Ticket t(selectedmovie, selectedShow->gettime());
                        users[currentUserIndex].bookticket(t);
                    } else{
                        throw runtime_error("No seats available for this showtime!");
                    }
                    break;
                }
                case 4:
                    users[currentUserIndex].viewbooking();
                    break;
                case 5:{
                    users[currentUserIndex].viewbooking();
                    cout << "Enter Ticket ID to cancel: ";
                    int tID; cin >> tID;
                    if(users[currentUserIndex].ticketcancel(tID)){
                        cout << "Ticket cancelled successfully.\n";
                    } 
                    else{
                        throw runtime_error("Invalid Ticket ID! Cannot cancel.");
                    }
                    break;
                }
                case 6:{
                    string uname, uemail;
                    cout << "Enter new user name: ";
                    cin >> uname;
                    cout << "Enter new user email: ";
                    cin >> uemail;
                    users.push_back(User(uname, uemail));
                    currentUserIndex = users.size() - 1; // Switch to new user
                    cout << "New user added and logged in: " << uname << endl;
                    break;
                }
                case 7:
                    cout << "Thank you for using Movie Ticket Booking System!\n";
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
