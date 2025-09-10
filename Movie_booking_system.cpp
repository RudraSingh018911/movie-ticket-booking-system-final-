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
