//============================================================================
// Name        : Project2.cpp
// Author      : Drew Heard
// Version     : 1.0
// Description : Project 2
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>


using namespace std;

//structure to hold course information
struct Course {
    string name; //course name
    string number; //course number 
    vector<string> preqs; // vector that hold all the prerequisites
    Course() {
        number = "0"; // create with empty variables, functions will check for these specific values
        name = "";
    }

};

bool operator<(const Course& a, const Course& b) {   // overloaded operator for course comparison. Source: https://stackoverflow.com/questions/4892680/sorting-a-vector-of-structs
    return a.number < b.number;
}

Course search(vector<Course> vect, string number) { // search vector for number
    Course temp;
    for (int i = 0; i < vect.size(); i++) { //vector loop
        if (vect.at(i).number == number) { //if vector i number equals number
            temp = vect.at(i);
            return temp; //return it
        }
    }
    if (temp.number == "0") {
        cout << "Course not found." << endl; // empty search
    }
    return temp; //return empty course
}

void printer(Course course) { //print course info
    if (course.number != "0" && course.name != "") { // check for valid course info
        cout << course.number << ": " << course.name << '.';
        if (course.preqs.size() > 0) { // if it has any preqs
            cout << " Prerequisites: ";
            for (int j = 0; j < course.preqs.size(); j++) { //preqs loop
                cout << course.preqs.at(j) << " ";
            }
        }
        cout << endl;
    }
    else {
        cout << "Print failed." << endl; //error message
    }
}



vector<Course> loadFile(string path) { //load vector from given file path
    vector<Course> courses; //new vector
    string temp;

    cout << "Loading file " << path << endl;
    std::ifstream info(path);
    //ifile.open();
    if (info.is_open()) {
        while (!info.eof()) {
            Course course; // temp course
            getline(info, temp); //getline
            course.number = temp.substr(0, temp.find(','));//add number to course structure 
            temp.erase(0, course.number.size() + 1); //erase number from the getline
            //
            if (temp.size() > 0) { //the getline still has info

                course.name = temp.substr(0, temp.find(','));//add name to course structure 
                temp.erase(0, course.name.size() + 1);//erase name from the getline

                //int i = 0; //test counter
                while (temp.size() > 0) { //the getline still has info

                    string temppreq = temp.substr(0, temp.find(',')); //add preq to course structure 
                    course.preqs.push_back(temppreq);

                    temp.erase(0, temppreq.size() + 1); //erase preq from the getline
                  //  i += 1;
                }

                if ((course.number == "0") || (course.name == "")) { // check for valid entry
                    // do nothing
                }
                else {
                    courses.push_back(course); // add to vector
                } 
             //
            }
        }
    }
    else {
        cout << "File Error." << endl; //fail message
    }
    //prerequisite check
    for (int i = 0; i < courses.size(); i++) {   //vector loop
        for (int j = 0; j < courses.at(i).preqs.size(); j++) { //preqs loop
            Course tester = search(courses, courses.at(i).preqs.at(j));   //temp course = the current preq in preqs                   
            if (tester.number == "0") { //if course is null, if the search for the preq comes back empty
                courses.at(i).preqs.erase(courses.at(i).preqs.begin()+j); //erase it
            }
        }
    }
    std::sort(courses.begin(), courses.end()); //sort by number
    return courses;
}




int main() {

    vector<Course> vect;

    int uin=0; // user input
    string path; // file path
    string targetCourse; // desired course
    int size = 1; //not used
    cout << "Welcome to the SNHU Course Databse." << endl;
    cout << "Please enter your file path." << endl;
    cin >> path;
    //path = "test.txt"; //tester
    cout << endl;
    


    while (uin != 9) { //menu loop

        cout << "Please make a selection." << endl;
        cout << "Press 1 to load your file." << endl;
        cout << "Press 2 to list all courses." << endl;
        cout << "Press 3 to list your desired course information." << endl;
        cout << "Press 9 to exit." << endl;
        cin >> uin; //get user input
        cout << endl;

        switch (uin) { 

        case 1: //load file
            vect = loadFile(path);
           // int size = vect.size();
            cout << "Loaded courses." << endl;
            cout << endl;

            break;


        case 2: //print all in order
            cout << "Displaying all courses." << endl;
            for (int i = 0; i < vect.size(); i++) {   //vector loop
                printer(vect.at(i));
            }
            cout << endl;

            break;



        case 3: //print course info
            cout << "Please enter your desired course number" << endl;
            cin >> targetCourse;
            transform(targetCourse.begin(), targetCourse.end(), targetCourse.begin(), ::toupper); // transform user input to uppercase
            //targetCourse = "CSCI100";   //tester
            cout << endl;
            printer(search(vect, targetCourse)); // search and print
            cout << endl;

            break;


 
        default:
            cout << "Try again." << endl;
            break;
        }


    }
    cout << "Goodbye." << endl;
    return 0;
  
