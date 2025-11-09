#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <ctime>
#include <random>
using namespace std;

bool isValidEmail(const string &email){
    size_t atPos = email.find("@");
    if(atPos == string::npos) return false;
    string domain = email.substr(atPos);
    if(domain.rfind("@gmail.", 0) == 0 || domain == "@gmail.com") return true;
    if(domain == "@yahoo.com") return true;
    if(domain == "@rediffmail.com") return true;
    if(domain == "@diu.iiitvadodara.ac.in") return true;
    return false;
}

bool isValidCardNumber(const string &cardNumber) {
    
    string cleaned = cardNumber;
    cleaned.erase(remove(cleaned.begin(), cleaned.end(), ' '), cleaned.end());
    cleaned.erase(remove(cleaned.begin(), cleaned.end(), '-'), cleaned.end());
    
    if (cleaned.length() < 13 || cleaned.length() > 19) return false;
    if (!all_of(cleaned.begin(), cleaned.end(), ::isdigit)) return false;
    
    int sum = 0;
    bool alternate = false;
    for (int i = cleaned.length() - 1; i >= 0; i--) {
        int digit = cleaned[i] - '0';
        if (alternate) {
            digit *= 2;
            if (digit > 9) digit -= 9;
        }
        sum += digit;
        alternate = !alternate;
    }
    return (sum % 10 == 0);
}

bool isValidExpiryDate(const string &expiryDate) {
    if (expiryDate.size() != 5 || expiryDate[2] != '/')
        return false;

    string mm = expiryDate.substr(0, 2);
    string yy = expiryDate.substr(3, 2);

    if (!isdigit(mm[0]) || !isdigit(mm[1]) || !isdigit(yy[0]) || !isdigit(yy[1]))
        return false;

    int month = stoi(mm);
    int year = stoi(yy);

    if (month < 1 || month > 12)
        return false;


    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentYear = (ltm->tm_year + 1900) % 100; 
    int currentMonth = ltm->tm_mon + 1;

    if (year < currentYear || (year == currentYear && month < currentMonth))
        return false;

    return true;
}


bool isValidCVV(const string &cvv) {
    if (cvv.length() < 3 || cvv.length() > 4) return false;
    return all_of(cvv.begin(), cvv.end(), ::isdigit);
}

bool isValidUPI(const string &upiId) {
    size_t atPos = upiId.find('@');
    if (atPos == string::npos) return false; // must contain '@'
    if (atPos == 0 || atPos == upiId.size() - 1) return false; // '@' not first or last

    string user = upiId.substr(0, atPos);
    string provider = upiId.substr(atPos + 1);

    for (char c : user) {
        if (!(isalnum(c) || c == '.' || c == '-' || c == '_'))
            return false;
    }
    if (provider.empty()) return false;
    for (char c : provider) {
        if (!isalpha(c)) return false;
    }

    return true;
}

bool isValidMobileNumber(const string &mobile) {
    if (mobile.length() != 10) return false;
    return all_of(mobile.begin(), mobile.end(), ::isdigit);
}

bool isValidName(const string &name) {
    return !name.empty() && name.length() >= 2 && name.length() <= 50;
}

class movie{
private:
    string title,genre;
    int duration;
    double imdbRating;
    int rottenTomatoes;
    double boxOffice;
    double userRatingSum;
    int userRatingCount;
public:
    movie(string title,string genre,int duration,double imdb=0,int rotten=0,double box=0){
        this->title=title;
        this->genre=genre;
        this->duration=duration;
        imdbRating=imdb;
        rottenTomatoes=rotten;
        boxOffice=box;
        userRatingSum=0;
        userRatingCount=0;
    }
    
    void displaydetails(int index){
        double avgUser = (userRatingCount==0)?0:(userRatingSum/userRatingCount);
        cout<<index<<". "<<title<<" | Genre: "<<genre<<" | Duration: "<<duration<<" mins\n";
        cout<<"   IMDb: "<<imdbRating<<"/10 | Rotten Tomatoes: "<<rottenTomatoes<<"% | Box Office: $"<<boxOffice<<"M\n";
        cout<<"   User Rating: "<<avgUser<<"/10 ("<<userRatingCount<<" votes)\n";
    }
    string gettitle() const { return title; }
    string getgenre() const { return genre; }
    void addrating(double rating){
        if(rating>=0 && rating<=10){
            userRatingSum+=rating;
            userRatingCount++;
        }
        else throw invalid_argument("Rating must be between 0 and 10.");
    }
    friend ostream& operator<<(ostream &out, const movie &m){
        cout<<"<< Operator is overloaded"<<endl;
        out<<m.title<<" | Genre: "<<m.genre<<" | Duration: "<<m.duration<<" mins | IMDb: "<<m.imdbRating<<"/10";
        return out;
    }
    ~movie(){}
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
                cout<<s<<" (Rs."<<price<<")  "<<endl;
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
    string gettime(){ return time; }
    string getdate(){ return date; }
    int getseatprice(const string &seatid){
        if(seatid[0]=='1') return 200;
        if(seatid[0]=='2') return 500;
        if(seatid[0]=='3') return 1000;
        return 0;
    }
    ~showtime(){}
};

class ticket{
private:
    static int count;
    int ticketid;
    string movietitle,showtime,seatid;
    int price;
    double discount;
public:
    ticket(string m,string s,string seat,int p, double disc=0.0){
        ticketid=count++;
        movietitle=m;
        showtime=s;
        seatid=seat;
        price=p;
        discount=disc;
    }
    int getid(){ return ticketid; }
    string getshowtime(){ return showtime; }
    string getmovietitle(){ return movietitle; }
    string getseat(){ return seatid; }
    int getprice(){ return price; }
    double getdiscount(){ return discount; }
    int getfinalprice() const { 
        return price - (price * discount); 
    }
    void displayticket(){
        cout<<"Ticket ID: "<<ticketid<<" | Movie: "<<movietitle<<" | Show: "<<showtime
            <<" | Seat: "<<seatid<<" | Original Price: Rs."<<price;
        if(discount > 0){
            cout<<" | Discount: "<<(discount*100)<<"% | Final Price: Rs."<<getfinalprice();
        }
        cout<<endl;
    }
    friend ostream& operator<<(ostream &out, const ticket &t){
        out<<"Ticket ID: "<<t.ticketid
           <<" | Movie: "<<t.movietitle
           <<" | Show: "<<t.showtime
           <<" | Seat: "<<t.seatid
           <<" | Price: Rs."<<t.getfinalprice();
        return out;
    }
    ~ticket(){}
};
int ticket::count=0;

class Payment {
protected:
    string paymentId;
    double amount;
    string timestamp;
    string status;
    
    string generateTimestamp() {
        time_t now = time(0);
        char* dt = ctime(&now);
        return string(dt);
    }
    
    string generatePaymentId() {
        string id = "PAY";
        for(int i = 0; i < 8; i++) {
            id += to_string(rand() % 10);
        }
        return id;
    }

public:
    Payment(double amt) : amount(amt) {
        paymentId = generatePaymentId();
        timestamp = generateTimestamp();
        status = "Pending";
    }
    
    virtual bool processPayment() = 0;
    virtual string getPaymentMethod() const = 0;
    
    double getAmount() const { return amount; }
    
    string getPaymentDetails() const {
        return "ID: " + paymentId + " | Amount: Rs." + to_string((int)amount) + 
               " | Method: " + getPaymentMethod() + " | Status: " + status;
    }
    
    virtual ~Payment() {}
};

class CreditDebitCard : public Payment {
private:
    string cardNumber;
    string expiryDate;
    string cvv;
    string cardHolderName;

public:
    CreditDebitCard(double amt, string card, string exp, string cv, string name) 
        : Payment(amt), cardNumber(card), expiryDate(exp), cvv(cv), cardHolderName(name) {}
    
    bool processPayment() override {
        cout << "Processing card payment for Rs." << amount << "..." << endl;
        cout << "Card: **** **** **** " << cardNumber.substr(cardNumber.length()-4) << endl;
        
        // Validate all inputs before processing
        if (!isValidCardNumber(cardNumber)) {
            cout << "ERROR: Invalid card number format!" << endl;
            status = "Failed - Invalid Card";
            return false;
        }
        
        if (!isValidExpiryDate(expiryDate)) {
            cout << "ERROR: Invalid or expired card!" << endl;
            status = "Failed - Invalid Expiry";
            return false;
        }
        
        if (!isValidCVV(cvv)) {
            cout << "ERROR: Invalid CVV! CVV must be 3 or 4 digits." << endl;
            status = "Failed - Invalid CVV";
            return false;
        }
        
        if (!isValidName(cardHolderName)) {
            cout << "ERROR: Invalid cardholder name!" << endl;
            status = "Failed - Invalid Name";
            return false;
        }
        
        bool success = (rand() % 10) != 0;
        status = success ? "Success" : "Failed";
        
        if(success) {
            cout << "Card payment processed successfully!" << endl;
        } else {
            cout << "Card payment failed. Please try again." << endl;
        }
        return success;
    }
    
    string getPaymentMethod() const override { return "Credit/Debit Card"; }
};

class UPI : public Payment {
private:
    string upiId;

public:
    UPI(double amt, string id) : Payment(amt), upiId(id) {}
    
    bool processPayment() override {
        cout << "Initiating UPI payment for Rs." << amount << "..." << endl;
        cout << "UPI ID: " << upiId << endl;
        
        if (!isValidUPI(upiId)) {
            cout << "ERROR: Invalid UPI ID format! Should be like name@provider" << endl;
            status = "Failed - Invalid UPI";
            return false;
        }
        
        bool success = (rand() % 10) != 0;
        status = success ? "Success" : "Failed";
        
        if(success) {
            cout << "UPI payment processed successfully!" << endl;
        } else {
            cout << "UPI payment failed. Please try again." << endl;
        }
        return success;
    }
    
    string getPaymentMethod() const override { return "UPI"; }
};

class DigitalWallet : public Payment {
private:
    string walletType;
    string mobileNumber;

public:
    DigitalWallet(double amt, string type, string mobile) 
        : Payment(amt), walletType(type), mobileNumber(mobile) {}
    
    bool processPayment() override {
        cout << "Processing " << walletType << " payment for Rs." << amount << "..." << endl;
        cout << "Mobile: " << mobileNumber << endl;
        
        if (!isValidMobileNumber(mobileNumber)) {
            cout << "ERROR: Invalid mobile number! Must be 10 digits." << endl;
            status = "Failed - Invalid Mobile";
            return false;
        }
        
        bool success = (rand() % 10) != 0;
        status = success ? "Success" : "Failed";
        
        if(success) {
            cout << walletType << " payment processed successfully!" << endl;
        } else {
            cout << walletType << " payment failed. Please try again." << endl;
        }
        return success;
    }
    
    string getPaymentMethod() const override { return walletType; }
};

class NetBanking : public Payment {
private:
    string bankName;
    string userId;

public:
    NetBanking(double amt, string bank, string user) 
        : Payment(amt), bankName(bank), userId(user) {}
    
    bool processPayment() override {
        cout << "Processing Net Banking payment for Rs." << amount << "..." << endl;
        cout << "Bank: " << bankName << " | User: " << userId << endl;
        
        if (bankName.empty() || userId.empty()) {
            cout << "ERROR: Bank name and user ID cannot be empty!" << endl;
            status = "Failed - Invalid Input";
            return false;
        }
        
        bool success = (rand() % 10) != 0;
        status = success ? "Success" : "Failed";
        
        if(success) {
            cout << "Net Banking payment processed successfully!" << endl;
        } else {
            cout << "Net Banking payment failed. Please try again." << endl;
        }
        return success;
    }
    
    string getPaymentMethod() const override { return "Net Banking (" + bankName + ")"; }
};

class QRCodePayment : public Payment {
private:
    string qrCodeImagePath;
    string upiId;

public:
    QRCodePayment(double amt, string imagePath, string upi) 
        : Payment(amt), qrCodeImagePath(imagePath), upiId(upi) {}
    
    bool processPayment() override {
        cout << "\nQR Code Payment Initiated for Rs." << amount << endl;
        cout << "==========================================" << endl;
        cout << "UPI ID: " << upiId << endl;
        cout << "QR Code Image: " << qrCodeImagePath << endl;
        cout << "Please scan the QR code using any UPI app" << endl;
        cout << "==========================================" << endl;
        
        // Check if QR code file exists
        ifstream qrFile(qrCodeImagePath);
        if(!qrFile.good()) {
            cout << "Warning: QR code image file '" << qrCodeImagePath << "' not found!" << endl;
            cout << "Please ensure the QR code image is in the program directory." << endl;
        }
        qrFile.close();
        
        cout << "\nWaiting for payment confirmation..." << endl;
        cout << "1. Confirm Payment" << endl;
        cout << "2. Payment Failed" << endl;
        cout << "Choose option (1-2): ";
        
        int confirmation;
        cin >> confirmation;
        
        bool success = (confirmation == 1);
        status = success ? "Success" : "Failed";
        
        if(success) {
            cout << "QR Code payment confirmed successfully!" << endl;
        } else {
            cout << "QR Code payment failed or was cancelled." << endl;
        }
        return success;
    }
    
    string getPaymentMethod() const override { 
        return "QR Code UPI (Image: " + qrCodeImagePath + ")"; 
    }
};

class RecommendationSystem {
private:
    map<string, vector<string>> userWatchHistory;
    map<string, string> userFavoriteGenres;
    
public:
    void addToWatchHistory(const string& userEmail, const string& movieTitle, const string& genre) {
        userWatchHistory[userEmail].push_back(movieTitle);
        userFavoriteGenres[userEmail] = genre;
    }
    
    vector<string> getPersonalizedRecommendations(const string& userEmail, const vector<movie>& allMovies) {
        vector<string> recommendations;
        vector<string> watchedMovies = userWatchHistory[userEmail];
        string favGenre = userFavoriteGenres[userEmail];
        
        if(watchedMovies.empty()) {
            return getTrendingMovies(allMovies);
        }
        
        if(!watchedMovies.empty()) {
            string lastWatched = watchedMovies.back();
            recommendations.push_back("Because you watched \"" + lastWatched + "\", you might like:");
            
            for(const auto& mov : allMovies) {
                if(mov.gettitle() != lastWatched && 
                   find(watchedMovies.begin(), watchedMovies.end(), mov.gettitle()) == watchedMovies.end()) {
                    if(recommendations.size() < 3) {
                        recommendations.push_back("   - " + mov.gettitle());
                    }
                }
            }
        }
        
        if(!favGenre.empty()) {
            recommendations.push_back("\nTop picks in your favorite genre (" + favGenre + "):");
            int count = 0;
            for(const auto& mov : allMovies) {
                if(count < 2) {
                    recommendations.push_back("   - " + mov.gettitle());
                    count++;
                }
            }
        }
        
        vector<string> trending = getTrendingMovies(allMovies);
        recommendations.push_back("\nTrending Now:");
        for(int i = 0; i < min(2, (int)trending.size()); i++) {
            recommendations.push_back("   - " + trending[i]);
        }
        
        return recommendations;
    }
    
    vector<string> getTrendingMovies(const vector<movie>& allMovies) {
        vector<string> trending;
        for(int i = 0; i < min(3, (int)allMovies.size()); i++) {
            trending.push_back(allMovies[i].gettitle());
        }
        return trending;
    }
    
    void displayRecommendations(const string& userEmail, const vector<movie>& allMovies) {
        vector<string> recommendations = getPersonalizedRecommendations(userEmail, allMovies);
        
        cout << "\nPersonalized Recommendations for You:" << endl;
        cout << "==========================================" << endl;
        
        if(recommendations.empty()) {
            cout << "Start watching movies to get personalized recommendations!" << endl;
            return;
        }
        
        for(const auto& rec : recommendations) {
            cout << rec << endl;
        }
    }
};

class user {
private:
    string name, email,password;   
    vector<ticket*> bookedtickets;
    bool isFirstBooking;
    vector<Payment*> paymentHistory;

public:
    user(string n, string e,string p){
        name=n;
        if(!isValidEmail(e)){
            throw invalid_argument("Invalid email! Only gmail, yahoo, rediffmail, diu.iiitvadodara.ac.in allowed.");
        }
        email=e;
        password=p;
        isFirstBooking = true;
    }
    
    void quicksignup(string n, string e){
        if(!isValidEmail(e)){
            throw invalid_argument("Invalid email! Only gmail, yahoo, rediffmail, diu.iiitvadodara.ac.in allowed.");
        }
        name=n;
        email=e;
        isFirstBooking = true;
        cout<<"Quick signup done for "<<name<<" with email: "<<email<<endl;
    }
    string getname()const{ return name; }
    string getmail()const{ return email; }
    bool getIsFirstBooking()const{ return isFirstBooking; }
    
    bool processPayment(double amount, RecommendationSystem& recommender) {
        cout << "\nPayment Options:" << endl;
        cout << "1. Credit/Debit Card" << endl;
        cout << "2. UPI" << endl;
        cout << "3. Digital Wallet (Paytm/Google Pay)" << endl;
        cout << "4. Net Banking" << endl;
        cout << "5. QR Code Payment" << endl;
        cout << "Choose payment method (1-5): ";
        
        int choice;
        cin >> choice;
        
        Payment* payment = nullptr;
        
        switch(choice) {
            case 1: {
                string card, exp, cvv, name;
                cout << "Enter card number: ";
                cin >> card;
                cout << "Enter expiry date (MM/YY): ";
                cin >> exp;
                cout << "Enter CVV: ";
                cin >> cvv;
                cin.ignore();
                cout << "Enter cardholder name: ";
                getline(cin, name);
                
                // Validate inputs before creating payment object
                if (!isValidCardNumber(card)) {
                    cout << "ERROR: Invalid card number! Must be 13-19 digits and pass Luhn check." << endl;
                    return false;
                }
                if (!isValidExpiryDate(exp)) {
                    cout << "ERROR: Invalid expiry date! Format: MM/YY, must be in future." << endl;
                    return false;
                }
                if (!isValidCVV(cvv)) {
                    cout << "ERROR: Invalid CVV! Must be 3 or 4 digits." << endl;
                    return false;
                }
                if (!isValidName(name)) {
                    cout << "ERROR: Invalid cardholder name! Must be 2-50 characters." << endl;
                    return false;
                }
                
                payment = new CreditDebitCard(amount, card, exp, cvv, name);
                break;
            }
            case 2: {
                string upiId;
                cout << "Enter UPI ID (e.g., name@upi): ";
                cin >> upiId;
                
                if (!isValidUPI(upiId)) {
                    cout << "ERROR: Invalid UPI ID! Format: name@provider" << endl;
                    return false;
                }
                
                payment = new UPI(amount, upiId);
                break;
            }
            case 3: {
                string walletType, mobile;
                cout << "Choose wallet:\n1. Paytm\n2. Google Pay\nChoice: ";
                int walletChoice;
                cin >> walletChoice;
                walletType = (walletChoice == 1) ? "Paytm" : "Google Pay";
                cout << "Enter mobile number: ";
                cin >> mobile;
                
                if (!isValidMobileNumber(mobile)) {
                    cout << "ERROR: Invalid mobile number! Must be 10 digits." << endl;
                    return false;
                }
                
                payment = new DigitalWallet(amount, walletType, mobile);
                break;
            }
            case 4: {
                string bank, userId;
                cout << "Enter bank name: ";
                cin >> bank;
                cout << "Enter user ID: ";
                cin >> userId;
                
                if (bank.empty() || userId.empty()) {
                    cout << "ERROR: Bank name and user ID cannot be empty!" << endl;
                    return false;
                }
                
                payment = new NetBanking(amount, bank, userId);
                break;
            }
            case 5: {
                string upiId = "movietickets@upi";
                string qrImagePath = "qrcode.jpeg";
                
                // Check if QR code file exists
                ifstream qrFile(qrImagePath);
                if(!qrFile.good()) {
                    cout << "Warning: QR code image file '" << qrImagePath << "' not found!" << endl;
                    cout << "Please ensure the QR code image is in the program directory." << endl;
                }
                qrFile.close();
                
                payment = new QRCodePayment(amount, qrImagePath, upiId);
                break;
            }
            default:
                cout << "Invalid payment method!" << endl;
                return false;
        }
        
        bool success = payment->processPayment();
        if(success) {
            paymentHistory.push_back(payment);
            if(!bookedtickets.empty()) {
                string lastMovie = bookedtickets.back()->getmovietitle();
                recommender.addToWatchHistory(email, lastMovie, "Action");
            }
        } else {
            delete payment;
        }
        
        return success;
    }
    
    void viewPaymentHistory() {
        cout << "\nPayment History for " << name << ":" << endl;
        cout << "==========================================" << endl;
        
        if(paymentHistory.empty()) {
            cout << "No payment history found." << endl;
            return;
        }
        
        double totalSpent = 0;
        for(int i = 0; i < paymentHistory.size(); i++) {
            cout << (i+1) << ". " << paymentHistory[i]->getPaymentDetails() << endl;
            totalSpent += paymentHistory[i]->getAmount();
        }
        cout << "Total Amount Spent: Rs." << totalSpent << endl;
    }
    
    void confirmTicketWithCashier(int ticketId) {
        for(auto& ticket : bookedtickets) {
            if(ticket->getid() == ticketId) {
                cout << "\n=== TICKET CONFIRMATION REQUIRED ===" << endl;
                cout << "Ticket ID: " << ticketId << endl;
                cout << "Movie: " << ticket->getmovietitle() << endl;
                cout << "Showtime: " << ticket->getshowtime() << endl;
                cout << "Seat: " << ticket->getseat() << endl;
                cout << "Amount: Rs." << ticket->getfinalprice() << endl;
                cout << "====================================" << endl;
                
                cout << "Cashier, please confirm payment (1-Confirm, 0-Reject): ";
                int confirmation;
                cin >> confirmation;
                
                if(confirmation == 1) {
                    cout << "Ticket CONFIRMED by cashier!" << endl;
                    cout << "Ticket has been allocated to customer: " << name << endl;
                    
                    // Generate ticket file
                    ofstream ticketFile("ticket_" + to_string(ticketId) + ".txt");
                    if(ticketFile.is_open()) {
                        ticketFile << "=== MOVIE TICKET ===" << endl;
                        ticketFile << "Ticket ID: " << ticketId << endl;
                        ticketFile << "Customer: " << name << endl;
                        ticketFile << "Movie: " << ticket->getmovietitle() << endl;
                        ticketFile << "Showtime: " << ticket->getshowtime() << endl;
                        ticketFile << "Seat: " << ticket->getseat() << endl;
                        ticketFile << "Amount Paid: Rs." << ticket->getfinalprice() << endl;
                        ticketFile << "Payment Method: QR Code" << endl;
                        ticketFile << "Status: CONFIRMED" << endl;
                        ticketFile << "=====================" << endl;
                        ticketFile.close();
                        cout << "Ticket details saved to: ticket_" << ticketId << ".txt" << endl;
                    }
                } else {
                    cout << "Ticket REJECTED by cashier!" << endl;
                }
                return;
            }
        }
        cout << "Ticket ID not found!" << endl;
    }
    
    void bookticket(ticket* t, RecommendationSystem& recommender) {
        double finalAmount = t->getfinalprice();
        
        cout << "\nProceeding to payment for Rs." << finalAmount << "..." << endl;
        
        if(processPayment(finalAmount, recommender)) {
            bookedtickets.push_back(t);
            if(isFirstBooking){
                cout << "\n Thank you for registering with us, " << name << "!" << endl;
                cout << "As a welcome gift, you get 20% discount on your first booking!" << endl;
                isFirstBooking = false;
            }
            
            // If payment was via QR code, require cashier confirmation
            if(!paymentHistory.empty() && 
               paymentHistory.back()->getPaymentMethod().find("QR Code") != string::npos) {
                cout << "\nNOTE: QR Code payment requires cashier confirmation." << endl;
                cout << "Please proceed to the counter with Ticket ID: " << t->getid() << endl;
                cout << "Your ticket will be allocated after cashier verification." << endl;
            } else {
                cout << "Ticket booked successfully for " << name << endl;
            }
            
            ofstream fout("bookings.txt", ios::app);
            if(fout.is_open()){
                fout << "Customer: " << name << " | Email: " << email
                     << " | Movie: " << t->getmovietitle()
                     << " | Showtime: " << t->getshowtime()
                     << " | Seat: " << t->getseat()
                     << " | Original Price: Rs." << t->getprice()
                     << " | Discount: " << (t->getdiscount()*100) << "%"
                     << " | Final Price: Rs." << t->getfinalprice() 
                     << " | Status: " << (paymentHistory.back()->getPaymentMethod().find("QR Code") != string::npos ? "Pending Confirmation" : "Confirmed")
                     << endl;
                fout.close();
            }
            else{
                cerr << "Error: Unable to open bookings.txt file!" << endl;
            }
        } else {
            cout << "Booking failed due to payment issue." << endl;
            delete t;
        }
    }
    
    void bookticket(showtime* st, const string &seatid, const string &movietitle, RecommendationSystem& recommender) {
        if(st->bookseat(seatid)){
            int price = st->getseatprice(seatid);
            double discount = 0.0;
            if(isFirstBooking) discount = 0.2;
            ticket* t = new ticket(movietitle, st->getdate()+" "+st->gettime(), seatid, price, discount);
            bookticket(t, recommender);
        }
        else throw runtime_error("Seat not available!");
    }
    
    void bookMultipleTickets(vector<ticket*>& tickets, RecommendationSystem& recommender, showtime* st) {
        double totalDiscount = 0.0;
        if(isFirstBooking){
            totalDiscount = 0.20;
            cout << "\n Thank you for registering with us, " << name << "!" << endl;
            cout << "As a welcome gift, you get 20% discount on your first booking!" << endl;
            isFirstBooking = false;
        }
        if(tickets.size() >= 3){
            if(totalDiscount < 0.10){
                totalDiscount = 0.10;
                cout << " You get 10% discount for booking " << tickets.size() << " tickets together!" << endl;
            }
        }
        
        int totalOriginalPrice = 0;
        int totalFinalPrice = 0;
        vector<ticket*> finalTickets;
        
        for(auto& t : tickets){
            ticket* discountedTicket = new ticket(t->getmovietitle(), t->getshowtime(), t->getseat(), t->getprice(), totalDiscount);
            finalTickets.push_back(discountedTicket);
            totalOriginalPrice += t->getprice();
            totalFinalPrice += discountedTicket->getfinalprice();
            delete t;
        }
        tickets.clear();
        
        cout << "Total Amount: Rs." << totalFinalPrice << endl;
        cout << "Proceeding to payment..." << endl;
        
        if(processPayment(totalFinalPrice, recommender)) {
            for(auto& t : finalTickets) {
                bookedtickets.push_back(t);
            }
            
            cout << "Successfully booked " << bookedtickets.size() << " tickets for " << name << endl;
            cout << "Total Original Price: Rs." << totalOriginalPrice << endl;
            if(totalDiscount > 0){
                cout << "Discount Applied: " << (totalDiscount*100) << "%" << endl;
                cout << "Total Final Price: Rs." << totalFinalPrice << endl;
                cout << "You saved: Rs." << (totalOriginalPrice - totalFinalPrice) << endl;
            }
            
            ofstream fout("bookings.txt", ios::app);
            if(fout.is_open()){
                fout << "Bulk Booking - Customer: " << name << " | Email: " << email
                     << " | Tickets: " << bookedtickets.size() 
                     << " | Total Original: Rs." << totalOriginalPrice
                     << " | Discount: " << (totalDiscount*100) << "%"
                     << " | Total Final: Rs." << totalFinalPrice << endl;
                fout.close();
            }
        } else {
            cout << "Booking failed due to payment issue." << endl;
            for(auto& t : finalTickets) {
                st->cancelseat(t->getseat());
                delete t;
            }
        }
    }
    
    void viewbooking(){
        cout<<"\nBookings for "<<name<<":"<<endl;
        if (bookedtickets.empty()){
            cout<<"No bookings yet."<<endl;
        } 
        else{
            int totalSpent = 0;
            int totalSaved = 0;
            for(int i=0; i<bookedtickets.size();i++){
                cout<<*bookedtickets[i]<<endl;
                totalSpent += bookedtickets[i]->getfinalprice();
                totalSaved += (bookedtickets[i]->getprice() - bookedtickets[i]->getfinalprice());
            }
            cout << "Total Amount Spent: Rs." << totalSpent << endl;
            if(totalSaved > 0){
                cout << "Total Savings: Rs." << totalSaved << endl;
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
        return false;
    }
    friend void showUserDetails(const user &u);
    ~user(){
        for (int i=0;i<bookedtickets.size();i++){
            delete bookedtickets[i];
        }
        for (int i=0;i<paymentHistory.size();i++){
            delete paymentHistory[i];
        }
    }
};

void showUserDetails(const user &u) {
    cout << "\n*** User Details ***" << endl;
    cout << "Name: " << u.name << endl;
    cout << "Email: " << u.email << endl;
    cout << "Booked Tickets Count: " << u.bookedtickets.size() << endl;
    cout << "First Booking Bonus Available: " << (u.isFirstBooking ? "Yes" : "No") << endl;
}

class bookingsystem{
private:
    vector<movie> movies;
    vector<showtime> showtimes;
public:
    void addmovie(movie m){ movies.push_back(m); }
    void addshowtime(showtime s){ showtimes.push_back(s); }
    void showallmovies(){
        cout<<"\nMovies Available:"<<endl;
        if(movies.empty()){
            cout<<"No movies available."<<endl; 
            return; 
        }
        for(int i=0;i< movies.size();i++){
            movies[i].displaydetails(i+1);
        } 
    }
    void showallshowtimes(){
        cout<<"\nShowtimes Available:"<<endl;
        if(showtimes.empty()){ 
            cout<<"No showtimes available."<<endl; 
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
    void addrating(int index,double rating){
        if(index<1||index>movies.size()) throw out_of_range("Invalid movie selection!");
        movies[index-1].addrating(rating);
    }
    vector<movie> getallmovies() { return movies; }
    ~bookingsystem(){}
};

int selectuser(const vector<user>& users){
    if(users.empty())throw runtime_error("No users available! Please sign up first.");
    cout<<"\nAvailable Users:"<<endl;
    for(int i=0;i<users.size();i++){
        cout<<(i+1)<<"."<<users[i].getname();
        if(users[i].getIsFirstBooking()){
            cout << "  (First booking discount available!)";
        }
        cout << endl;
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
    RecommendationSystem recommender;
    
    string uname,uemail,upass;
    cout<<"Welcome to Movie Ticket Booking System!"<<endl;
    cout<<"Please sign up first."<<endl;
    cout<<"Enter your name: ";
    cin>>uname;
    cout<<"Enter your email: "; 
    cin>>uemail;
    cout<<"Create a password: ";
    cin>>upass;
    try{
        users.push_back(user(uname,uemail,upass));
    }catch(exception &e){
        cout<<"Error: "<<e.what()<<endl;
        return 0;
    }
    
    system.addmovie(movie("Inception","Sci-Fi",148,8.8,87,830));
    system.addmovie(movie("Avengers","Action",180,8.0,91,1518));
    system.addmovie(movie("Interstellar","Sci-Fi",169,8.6,93,677));
    system.addmovie(movie("The Dark Knight","Action",152,9.0,94,1006));
    system.addmovie(movie("Pulp Fiction","Crime",154,8.9,92,214));
    
    system.addshowtime(showtime("10:00 AM","2025-09-12",1));
    system.addshowtime(showtime("2:00 PM","2025-09-12",2));
    system.addshowtime(showtime("7:00 PM","2025-09-12",3));
    
    int choice=0;
    while (choice!=13){
        cout<<"\n========= Movie Ticket Booking ========="<<endl;
        cout<<"1. View Movies"<<endl;
        cout<<"2. View Showtimes"<<endl;
        cout<<"3. Book Single Ticket"<<endl;
        cout<<"4. Book Multiple Tickets"<<endl;
        cout<<"5. View My Bookings"<<endl;
        cout<<"6. Cancel Ticket"<<endl;
        cout<<"7. Add New User (Sign Up)"<<endl;
        cout<<"8. Show User Details"<<endl;
        cout<<"9. Rate a Movie"<<endl;
        cout<<"10. View Payment History"<<endl;
        cout<<"11. Get Recommendations"<<endl;
        cout<<"12. Cashier Confirm Ticket"<<endl;
        cout<<"131. Exit"<<endl;
        cout<<"Enter your choice: ";
        
        if(!(cin>>choice)){
            cin.clear();
            cin.ignore(10000,'\n');
            cout<<"Invalid input! Please enter a number."<<endl;
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
                    users[uindex].bookticket(selectedshow, seatid, selectedmovie, recommender);
                    break;
                }
                case 4:{
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
                    cout<<"How many tickets do you want to book? (Minimum 1): ";
                    int ticketCount;
                    cin>>ticketCount;
                    if(ticketCount < 1){
                        throw invalid_argument("Please book at least 1 ticket.");
                    }
                    vector<ticket*> tickets;
                    vector<string> bookedSeats;
                    for(int i=0; i<ticketCount; i++){
                        cout<<"Enter seat ID for ticket " << (i+1) << " (e.g., 2B): ";
                        string seatid;
                        cin>>seatid;
                        if(find(bookedSeats.begin(), bookedSeats.end(), seatid) != bookedSeats.end()){
                            throw runtime_error("Seat " + seatid + " is already selected in this booking!");
                        }
                        if(selectedshow->bookseat(seatid)){
                            int price=selectedshow->getseatprice(seatid);
                            ticket* t = new ticket(selectedmovie, selectedshow->getdate() + " " + selectedshow->gettime(), seatid, price);
                            tickets.push_back(t);
                            bookedSeats.push_back(seatid);
                        }
                        else{
                            for(auto& t : tickets){
                                selectedshow->cancelseat(t->getseat());
                                delete t;
                            }
                            throw runtime_error("Seat " + seatid + " not available!");
                        }
                    }
                    users[uindex].bookMultipleTickets(tickets, recommender, selectedshow);
                    break;
                }
                case 5:{
                    int uindex=selectuser(users);
                    users[uindex].viewbooking();
                    break;
                }
                case 6:{
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
                        cout<<"Ticket cancelled successfully."<<endl;
                    else throw runtime_error("Invalid Ticket ID! Cannot cancel.");
                    break;
                }
                case 7:{
                    cout << "Enter new user name: ";
                    cin>>uname;
                    cout<<"Enter new user email: "; 
                    cin>>uemail;
                    cout<<"Create a password: ";
                    cin>>upass;
                    try{
                        users.push_back(user(uname,uemail,upass));
                        cout<<"New user added: "<<uname<<endl;
                    }catch(exception &e){
                        cout<<"Error: "<<e.what()<<endl;
                    }
                    break;
                }
                case 8: {
                    int uindex = selectuser(users);
                    showUserDetails(users[uindex]);  
                    break;
                }
                case 9: {
                    system.showallmovies();
                    cout<<"Select a movie to rate: ";
                    int mchoice;
                    cin>>mchoice;
                    cout<<"Enter rating (0-10): ";
                    double r;
                    cin>>r;
                    system.addrating(mchoice,r);
                    cout<<"Rating added!"<<endl;
                    break;
                }
                case 10: {
                    int uindex = selectuser(users);
                    users[uindex].viewPaymentHistory();
                    break;
                }
                case 11: {
                    int uindex = selectuser(users);
                    vector<movie> allMovies = system.getallmovies();
                    recommender.displayRecommendations(users[uindex].getmail(), allMovies);
                    break;
                }
                 case 12: {
                    int uindex = selectuser(users);
                    users[uindex].viewbooking();
                    cout << "Enter Ticket ID for cashier confirmation: ";
                    int tid;
                    cin >> tid;
                    users[uindex].confirmTicketWithCashier(tid);
                    break;
                }
             
                case 13:
                    cout << "Thank you for using Movie Ticket Booking System!" << endl;
                    break;
                default:
                    cout<<"Invalid choice, try again!"<<endl;
            }
        }catch(exception &e){
            cout<<"Error: "<<e.what()<<endl;
        }
    }
    return 0;
}
