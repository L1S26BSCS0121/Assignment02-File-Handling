/*
 * Name       : Fahad Maqbool
 * Reg No     : L1S26BSCS0121
 * Assignment : 02 - File Handling
 * Question   : Q2 - Parking Report
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int main() {
    ifstream infile("parking.txt");
    if (!infile) {
        cout << "parking.txt not found!" << endl;
        return 1;
    }

    int d, m, y;
    char slash;
    infile >> d >> slash >> m >> slash >> y;

    infile.ignore(100, '\n');
    infile.ignore(100, '\n');

    ofstream outfile("receipts.txt");
    outfile << "Receipts for " << d << "/" << m << "/" << y << endl;

    char plate[15];
    char type;
    int inh, inm, outh, outm;
    char colon;

    int totalvehicles = 0;
    int carcount = 0;
    int bikecount = 0;
    int totalfee = 0;
    int longestmin = -1;
    char longestplate[15] = "";
    int longesth = 0;
    int longestm = 0;

    cout << "Parking report for " << d << "/" << m << "/" << y << endl;

    while (infile >> plate >> type >> inh >> colon >> inm >> outh >> colon >> outm) {
        int inmin = inh * 60 + inm;
        int outmin = outh * 60 + outm;
        int parkedmin = outmin - inmin;

        int hourscharged = (parkedmin + 59) / 60;
        if (parkedmin == 0) {
            hourscharged = 1;
        }

        int fee = 0;
        if (type == 'C') {
            fee = hourscharged * 100;
            carcount++;
        }
        else if (type == 'B') {
            fee = hourscharged * 40;
            bikecount++;
        }

        int h = parkedmin / 60;
        int min = parkedmin % 60;

        if (type == 'C') {
            cout << plate << " Car " << h << " h " << min << " min Fee: " << fee << endl;
        }
        else {
            cout << plate << " Bike " << h << " h " << min << " min Fee: " << fee << endl;
        }

        outfile << plate << " " << fee << endl;

        totalvehicles++;
        totalfee += fee;

        if (parkedmin > longestmin) {
            longestmin = parkedmin;
            strcpy(longestplate, plate);
            longesth = h;
            longestm = min;
        }
    }

    infile.close();
    outfile.close();

    if (totalvehicles == 0) {
        cout << "No vehicles found!" << endl;
    }
    else {
        cout << "Vehicles: " << totalvehicles << endl;
        cout << "Cars: " << carcount << " Bikes: " << bikecount << endl;
        cout << "Total collected: " << totalfee << endl;
        cout << "Longest stay: " << longestplate << " (" << longesth << " h " << longestm << " min)" << endl;
    }

    return 0;
}