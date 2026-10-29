/*
 * Name       : Fahad Maqbool
 * Reg No     : L1S26BSCS0121
 * Assignment : 02 - File Handling
 * Question   : Q4 - Heart Rate Cleaner
 */

#include <iostream>
#include <fstream>
using namespace std;
int main() {
    ifstream infile("heart_rate.txt");
    if (!infile) {
        cout << "heart_rate.txt not found!" << endl;
        return 1;
    }

    int rate[100];
    int count = 0;
    int bad = 0;
    int x;
    char junk[50];
    int reason = 0;

    while (true) {
        if (count == 100) {
            reason = 3;
            break;
        }
        if (infile >> x) {
            if (x == -1) {
                reason = 1;
                break;
            }
            rate[count] = x;
            count++;
        }
        else if (infile.eof()) {
            reason = 2;
            break;
        }
        else {
            infile.clear();
            infile >> junk;
            bad++;
        }
    }
    infile.close();

    ofstream outfile("clean_heart_rate.txt");
    for (int i = 0; i < count; i++) {
        outfile << rate[i] << endl;
    }
    outfile.close();

    cout << "Valid readings: " << count << endl;
    cout << "Junk skipped: " << bad << endl;

    if (count == 0) {
        cout << "No valid readings!" << endl;
    }
    else {
        int total = 0;
        int highest = rate[0];
        int alerts = 0;

        for (int i = 0; i < count; i++) {
            total += rate[i];
            if (rate[i] > highest) {
                highest = rate[i];
            }
            if (rate[i] > 100) {
                alerts++;
            }
        }

        double avg = (double)total / count;

        int aboveavg = 0;
        for (int i = 0; i < count; i++) {
            if (rate[i] > avg) {
                aboveavg++;
            }
        }

        cout << "Average: " << avg << endl;
        cout << "Highest: " << highest << endl;
        cout << "Above average: " << aboveavg << endl;
        cout << "Alerts (above 100): " << alerts << endl;
    }

    cout << "Stopped because: ";
    if (reason == 1) {
        cout << "sentinel found" << endl;
    }
    else if (reason == 2) {
        cout << "end of file" << endl;
    }
    else if (reason == 3) {
        cout << "array full" << endl;
    }

    return 0;
}