#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

class Activity {
    private:
        string name, location;
        int day, month, year, hour, minute;

    public:
        void setName(string n){ name = n; }
        string getName(){ return name; }

        void setLocation(string l){ location = l; }
        string getLocation(){ return location; }

        void setDay(int d){ day = d; }
        int getDay(){ return day; }

        void setMonth(int m){ month = m; }
        int getMonth(){ return month; }

        void setYear(int y){ year = y; }
        int getYear(){ return year; }

        void setHour(int h){ hour = h; }
        int getHour(){ return hour; }

        void setMinute(int m){ minute = m; }
        int getMinute(){ return minute; }
};

int addActivity() {
    Activity activity;
    string name_, location_;
    int day_, month_, year_, hour_, minute_;

    // Enter in information
    cout << "\nEnter name of activity: ";
    cin >> name_;
    activity.setName(name_);

    cout << "Enter date of activity (dd[\\n]mm[\\n]yyyy): ";
    cin >> day_ >> month_ >> year_;
    activity.setDay(day_);
    activity.setMonth(month_);
    activity.setYear(year_);

    cout << "Enter time of activity (hh[\\n]mm): ";
    cin >> hour_ >> minute_;
    activity.setHour(hour_);
    activity.setMinute(minute_);

    cout << "Enter location of activity (no spaces): ";
    cin >> location_;
    activity.setLocation(location_);

    // Get year
    time_t t = time(NULL);
    tm *timePointer = localtime(&t);
    int year = timePointer -> tm_year + 1900;

    // Write to file
    if(activity.getDay() <= 31 && activity.getMonth() <= 12 && activity.getYear() >= year
        && activity.getHour() <= 24 && activity.getMinute() <= 60) {
        ofstream file;
        file.open("tasks.txt", ios::app);
        
        file << "\n" << activity.getName() << "," << activity.getDay() << "," << activity.getMonth()
        << "," << activity.getYear() << "," << activity.getHour() << "," << activity.getMinute()
        << "," << activity.getLocation();

        file.close();
    }

    return 0;
}

int removeActivity() {
    string compStr;
    cout << "Enter name of activity to remove: ";
    cin >> compStr;

    vector<string> lines;
    string text;
    string substring = ",";
    ifstream file("tasks.txt");

    while(getline(file, text)) {
        // Get location of first comma
        size_t found = text.find(substring);

        if(found != string::npos) {
            string newText = text.substr(0, found); // Start of line to the first comma

            // Add to list only if inputed name isn't equal to name in file
            if(newText == compStr) {
                continue;
            }else{
                lines.push_back(text);
            }
        }
    }

    file.close();

    // Reopen and add the lines back into the file
    ofstream file_;
    file_.open("tasks.txt", ios::trunc);

    for(int i = 0; i < lines.size(); i++) {
        file_ << "\n" + lines[i];
    }

    file_.close();

    return 0;
}

int displayTasks() {
    int i = 0;
    string text;
    ifstream file("tasks.txt");

    while(getline(file, text)) {
        cout << "\nTask number " << i << ": " << text;
        i++;
    }

    file.close();

    return 0;
}

int addRemoveActivity() {
    string choice;
    
    cout << "\n>>> ";
    cin >> choice;
    std::transform(choice.begin(), choice.end(), choice.begin(),
    [](unsigned char c){ return std::tolower(c); });

    if(choice == "add") {
        addActivity();
    }else if(choice == "remove") {
        removeActivity();
    }else if(choice == "tasks") {
        displayTasks();
    }else if(choice == "quit") {
        exit(0);
    }else if(choice == "cleanup") {
        return 0;
    }else {
        addRemoveActivity();
    }

    return 0;
}

int welcome() {
    // Get current date and time
    time_t today;
    time(&today);

    cout << "Task Scheduler by Fransk\t\t" << asctime(localtime(&today)) << "\n";

    return 0;
}

int main() {
    string pause;

    welcome();
    
    do {
        addRemoveActivity();
    }while(true);

    return 0;
}