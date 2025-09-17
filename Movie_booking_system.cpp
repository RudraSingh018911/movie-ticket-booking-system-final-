//contributors : 202411083, 202411084, 202411036, 202411059
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include<fstream>
#include<sstream>
#include<map>
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
    }
};

class showtime{
private:
    string time,date;
    int hallnumber;
    vector<string> seats;
    map<string,bool> seatstatus;
public:
    showtime(string time,string date,int hall=1){
        this->time=time;
        this->date=date;
        hallnumber=hall;
        for(int r=1;r<=3;r++){
            for(char c='A';c<='E';c++){
                string seat=to_string(r)+c;
                seats.push_back(seat);
                seatstatus[seat]=true;
            }
        }
    }
    void showdetails(int index){
        cout<<index<<". Date: "<<date<<" | Time: "<<time<<" | Hall: "<<hallnumber<<endl;
    }
    void displayavailableseats(){
        cout<<"\nAvailable seats for "<<date<<" "<<time<<":\n";
        for(auto &s:seats){
            if(seatstatus[s]){
                int price=getseatprice(s);
                cout<<s<<" (Rs."<<price<<")  ";
            }
        }
        cout<<"\n";
    }
    bool bookseat(const string &seatid){
        if(seatstatus.find(seatid)!=seatstatus.end() && seatstatus[seatid]){
            seatstatus[seatid]=false;
            return true;
        }
        return false;
    }
    void cancelseat(const string &seatid){
        if(seatstatus.find(seatid)!=seatstatus.end()){
            seatstatus[seatid]=true;
        }
    }
    string gettime(){ 
        return time;
     }
    string getdate(){ 
        return date;
     }
    int getseatprice(const string &seatid){
        if(seatid[0]=='1') return 200;
        if(seatid[0]=='2') return 500;
        if(seatid[0]=='3') return 1000;
        return 0;
    }
~showtime(){
}
};
class ticket{
private:
    static int count;
    int ticketid;
    string movietitle,showtime,seatid;
    int price;
public:
    ticket(string m,string s,string seat,int p){
        ticketid=count++;
        movietitle=m;
        showtime=s;
        seatid=seat;
        price=p;
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
    string getseat(){
        return seatid;
    }
    int getprice(){
        return price;
    }
    void displayticket(){
        cout<<"Ticket ID: "<<ticketid<<" | Movie: "<<movietitle<<" | Show: "<<showtime
        <<" | Seat: "<<seatid<<" | Price: Rs."<<price<<endl;
    }
    ~ticket(){
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
        cout <<"Ticket booked successfully for "<<name<< endl;
        ofstream fout("bookings.txt", ios::app);
        if(fout.is_open()){
            fout << "Customer: " << name << " | Email: " << email
                 << " | Movie: " << t->getmovietitle()
                 << " | Showtime: " << t->getshowtime()
                 << " | Seat: " << t->getseat()
                 << " | Price: Rs." << t->getprice() << "\n";
            fout.close();
        }
        else{
            cerr << "Error: Unable to open bookings.txt file!\n";
        }
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

    bool ticketcancel(int ticketid,showtime* st){
        for (int i=0;i<bookedtickets.size();i++){
            if (bookedtickets[i]->getid() == ticketid){
                st->cancelseat(bookedtickets[i]->getseat());
                delete bookedtickets[i];
                bookedtickets.erase(bookedtickets.begin() + i);
                return true;
            }
        }
        return false;}
    friend bool hasBookedSameMovie(const user &u1, const user &u2);
    ~user(){
        for (int i=0;i<bookedtickets.size();i++){
        delete bookedtickets[i];
    }
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
    system.addshowtime(showtime("10:00 AM","2025-09-12",1));
    system.addshowtime(showtime("2:00 PM","2025-09-12",2));
    system.addshowtime(showtime("7:00 PM","2025-09-12",3));
    int choice=0;
    while (choice!=7){
        cout<<"\n========= Movie Ticket Booking =========\n";
        cout<<"1. View Movies\n2. View Showtimes\n3. Book Ticket\n4. View My Bookings\n";
        cout<<"5. Cancel Ticket\n6. Add New User (Sign Up)\n7. Exit\n";
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
                    selectedshow->displayavailableseats();
                    cout<<"Enter seat ID to book (e.g., 2B): ";
                    string seatid;
                    cin>>seatid;
                    if(selectedshow->bookseat(seatid)){
                        int price=selectedshow->getseatprice(seatid);
                        ticket* t = new ticket(selectedmovie, selectedshow->getdate() + " " + selectedshow->gettime(), seatid, price);
                        users[uindex].bookticket(t);
                    }
                    else throw runtime_error("Seat not available!");
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
                    system.showallshowtimes();
                    cout<<"Enter showtime number for the ticket: ";
                    int schoice;
                    cin>>schoice;
                    showtime* st=system.getshowtime(schoice);
                    if(users[uindex].ticketcancel(tid,st))
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
                case 7:
                    cout<<"Thank you for using Movie Ticket Booking System!\n";
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
