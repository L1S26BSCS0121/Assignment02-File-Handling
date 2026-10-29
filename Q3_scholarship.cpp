/*
 * Name       : Fahad Maqbool
 * Reg No     : L1S26BSCS0121
 * Assignment : 02 - File Handling
 * Question   : Q3 - Scholarship List
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int main() {
    char path[100];
    cout << "Enter the file name: ";
    cin.getline(path, 100);

    ifstream infile(path);
    if (!infile.is_open()) {
        cout << "Could not open " << path << "!" << endl;
        return 1;
    }

    int n;
    if (!(infile >> n)) {
        infile.close();
        cout << "No students found!" << endl;
        return 0;
    }

    if (n > 30) {
        cout << "Too many students!" << endl;
        infile.close();
        return 0;
    }

    infile.ignore(100, '\n');

    ofstream outfile("scholarship.txt");

    char name[30];
    double cgpa;
    int count = 0;
    double totalcgpa = 0;
    int eligiblecount = 0;
    double topcgpa = -1.0;
    char topname[30] = "";

    while (count < n && infile.getline(name, 30, ',')) {
        if (!(infile >> cgpa)) {
            break;
        }
        infile.ignore(100, '\n');

        cout << "[" << name << "] CGPA: " << cgpa << endl;

        if (cgpa >= 3.50) {
            outfile << name << "," << cgpa << endl;
            eligiblecount++;
        }

        totalcgpa += cgpa;

        if (cgpa > topcgpa) {
            topcgpa = cgpa;
            strcpy(topname, name);
        }

        count++;
    }

    infile.close();
    outfile.close();

    if (count < n) {
        cout << "Warning: only " << count << " of " << n << " records found." << endl;
    }

    if (count == 0) {
        cout << "No students found!" << endl;
        return 0;
    }

    double avgcgpa = totalcgpa / count;

    cout << "Students: " << count << endl;
    cout << "Average CGPA: " << avgcgpa << endl;
    cout << "Eligible for scholarship: " << eligiblecount << endl;
    cout << "Top student: " << topname << " (" << topcgpa << ")" << endl;

    return 0;
}