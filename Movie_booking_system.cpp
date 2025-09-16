//contributors : 202411083, 202411084, 202411036, 202411059
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;
class movie{
private:
    string title,genre;
    int duration;
public:
    movie(string title,string genre,int duration){
        this->title=title;
        this->genre=genre;
        this->duration=duration;
    }
    void displaydetails(int index){
        cout<<index<<". "<<title<<" | Genre: "<<genre<<" | Duration: "<<duration<<" mins\n";
    }
    string gettitle(){
         return title; 
        }
    ~movie(){
        cout<<"movie destructor called"<<endl;
    }
};

class showtime{
private:
    string time,date;
    int hallnumber,avseats;
public:
    showtime(string time,string date,int hall=1,int seats=50){
        this->time=time;
        this->date=date;
        hallnumber=hall;
        avseats=seats;
    }
    void showdetails(int index){
        cout<<index<<". Date: "<<date<<" | Time: "<<time<<" | Hall: "<<hallnumber<<" | Available Seats: "<<avseats<<endl;
    }
    bool bookseat(){
        if (avseats > 0){
            avseats--;
            return true;
        }
        return false;
    }
    void cancelseat(){
         avseats++; 
        }
    string gettime(){ 
        return time;
     }
    string getdate(){ 
        return date;
     }
    int getavailableseats(){
         return avseats; 
        }
~showtime(){
cout<<"showtime destructor has been called"<<endl;
}
};
class ticket{
private:
    static int count;
    int ticketid;
    string movietitle,showtime;
public:
    ticket(string m,string s){
        ticketid=count++;
        movietitle=m;
        showtime=s;
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
        cout<<"Ticket ID: "<<ticketid<<" | Movie: "<<movietitle<<" | Show: "<<showtime<<endl;
    }
    ~ticket(){
        cout<<"ticket destructor is called"<<endl;
    }
};
int ticket::count=0;
class user{
private:
    string name, email;
    vector<ticket*> bookedtickets;
public:
    user(string n, string e){
        name=n;
        email=e;
    }
    void quicksignup(string n, string e){
        name=n;
        email=e;
        cout<<"Quick signup done for "<<name<<" with email: "<<email<<endl;
    }

    string getname()const{
        return name; 
    }
    string getmail()const{ 
        return email;
    }
    void bookticket(ticket* t){
        bookedtickets.push_back(t);
        cout <<"Ticket booked successfully for"<<name<< endl;
    }
    void viewbooking(){
    cout<<"\nBookings for "<<name<<":\n";
    if (bookedtickets.empty()){
        cout<<"No bookings yet.\n";
    } 
    else{
        for(int i=0; i<bookedtickets.size();i++){
            bookedtickets[i]->displayticket();
        }
    }
}

    bool ticketcancel(int ticketid){
        for (int i=0;i<bookedtickets.size();i++){
            if (bookedtickets[i]->getid() == ticketid){
                delete bookedtickets[i];
                bookedtickets.erase(bookedtickets.begin() + i);
                return true;
            }
        }
        return false;}
    friend void showUserDetails(const user &u);
    ~user(){
        for (int i=0;i<bookedtickets.size();i++){
        delete bookedtickets[i];
    }
     cout<<"user destructor has been called"<<endl;
    }
};

void showUserDetails(const user &u) {
    cout << "\n*** User Details ***\n";
    cout << "Name: " << u.name << endl;
    cout << "Email: " << u.email << endl;
    cout << "Booked Tickets Count: " << u.bookedtickets.size() << endl;
}

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
        cout<<"\nMovies Available:\n";
        if(movies.empty()){
            cout<<"No movies available.\n"; 
            return; 
        }
        for(int i=0;i< movies.size();i++){
            movies[i].displaydetails(i+1);
        } 
    }
    void showallshowtimes(){
        cout<<"\nShowtimes Available:\n";
        if(showtimes.empty()){ 
            cout<<"No showtimes available.\n"; 
            return;
         }
        for(int i=0;i<showtimes.size();i++){
            showtimes[i].showdetails(i+1);
        } 
    }
    string getmovietitle(int index){
        if(index<1||index>movies.size())
            throw out_of_range("Invalid movie selection!");
        return movies[index-1].gettitle();
    }
    showtime* getshowtime(int index){
        if(index<1||index>showtimes.size()){
            throw out_of_range("Invalid showtime selection!");
        }
        return &showtimes[index-1];
    }
    ~bookingsystem(){
        cout<<"booking system destructor has been called"<<endl;
    }
};
int selectuser(const vector<user>& users){
    if(users.empty())throw runtime_error("No users available! Please sign up first.");
    cout<<"\nAvailable Users:\n";
    for(int i=0;i<users.size();i++){
        cout<<(i+1)<<"."<<users[i].getname()<<endl;
    }
    cout<<"Select user number:";
    int uchoice; 
    cin>>uchoice;
    if(uchoice<1||uchoice>users.size()){
        throw out_of_range("Invalid user selection!");
    } 
    return uchoice - 1;
}
int main(){
    bookingsystem system;
    vector<user> users;
    string uname,uemail;
    cout<<"Welcome to Movie Ticket Booking System!\n";
    cout<<"Please sign up first.\n";
    cout<<"Enter your name: ";
    cin>>uname;
    cout<<"Enter your email: "; 
    cin>>uemail;
    users.push_back(user(uname,uemail));
    system.addmovie(movie("Inception","Sci-Fi",148));
    system.addmovie(movie("Avengers","Action",180));
    system.addmovie(movie("Interstellar","Sci-Fi",169));
    system.addshowtime(showtime("10:00 AM","2025-09-12",1,5));
    system.addshowtime(showtime("2:00 PM","2025-09-12",2,3));
    system.addshowtime(showtime("7:00 PM","2025-09-12",3,2));
    int choice=0;
    while (choice!=8){
        cout<<"\n========= Movie Ticket Booking =========\n";
        cout<<"1. View Movies\n2. View Showtimes\n3. Book Ticket\n4. View My Bookings\n";
        cout<<"5. Cancel Ticket\n6. Add New User (Sign Up)\n";
         cout << "7. Show User Details\n8. Exit\n";
        cout<<"Enter your choice: ";
        if(!(cin>>choice)){
            cin.clear();
            cin.ignore(10000,'\n');
            cout<<"Invalid input! Please enter a number.\n";
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
                    int uindex=selectuser(users);
                    system.showallmovies();
                    cout<<"Select a movie number: ";
                    int mchoice;
                    cin>>mchoice;
                    string selectedmovie=system.getmovietitle(mchoice);
                    system.showallshowtimes();
                    cout<<"Select a showtime number: ";
                    int schoice;
                    cin>>schoice;
                    showtime* selectedshow=system.getshowtime(schoice);
                    if(selectedshow->bookseat()){
                        ticket* t = new ticket(selectedmovie, selectedshow->gettime());
                         users[uindex].bookticket(t);
                    }
                    else throw runtime_error("No seats available for this showtime!");
                    break;
                }
                case 4:{
                    int uindex=selectuser(users);
                    users[uindex].viewbooking();
                    break;
                }
                case 5:{
                    int uindex=selectuser(users);
                    users[uindex].viewbooking();
                    cout<<"Enter Ticket ID to cancel: ";
                    int tid;
                    cin>>tid;
                    if(users[uindex].ticketcancel(tid))
                        cout<<"Ticket cancelled successfully.\n";
                    else throw runtime_error("Invalid Ticket ID! Cannot cancel.");
                    break;
                }
                case 6:{
                    cout << "Enter new user name: ";
                    cin>>uname;
                    cout<<"Enter new user email: "; 
                    cin>>uemail;
                    users.push_back(user(uname,uemail));
                    cout<<"New user added: "<<uname<<endl;
                    break;
                }
                case 7: {
                    int uindex = selectuser(users);
                    showUserDetails(users[uindex]);  
                    break;
                }
                case 8:
                  cout << "Thank you for using Movie Ticket Booking System!\n";
                  break;
                default:
                    cout<<"Invalid choice, try again!\n";
            }
        }catch(exception &e){
            cout<<"Error: "<<e.what()<<endl;
        }
    }
return 0;
}
