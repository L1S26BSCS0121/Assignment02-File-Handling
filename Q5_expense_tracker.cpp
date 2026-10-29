/*
 * Name       : Fahad Maqbool
 * Reg No     : L1S26BSCS0121
 * Assignment : 02 - File Handling
 * Question   : Q5 - Expense Tracker
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int main() {
    int choice = 0;

    do {
        cout << "===== Expense Tracker =====" << endl;
        cout << "1. Add an expense" << endl;
        cout << "2. Show all expenses" << endl;
        cout << "3. Show total of a category" << endl;
        cout << "4. Clear all expenses" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            char cat[20];
            int amt;
            cout << "Enter category: ";
            cin >> cat;
            cout << "Enter amount: ";
            cin >> amt;

            if (amt <= 0) {
                cout << "Invalid amount!" << endl;
            }
            else {
                ofstream outfile("expenses.txt", ios::app);
                outfile << cat << " " << amt << endl;
                outfile.close();
                cout << "Expense saved." << endl;
            }
        }
        else if (choice == 2) {
            ifstream infile("expenses.txt");
            if (!infile) {
                cout << "No expenses yet." << endl;
            }
            else {
                char cat[20];
                int amt;
                int count = 0;
                int totalspent = 0;
                int largestamt = -1;
                char largestcat[20] = "";
                bool empty = true;

                while (count < 100 && infile >> cat >> amt) {
                    empty = false;
                    count++;
                    cout << count << ". " << cat << " " << amt << endl;
                    totalspent += amt;
                    if (amt > largestamt) {
                        largestamt = amt;
                        strcpy(largestcat, cat);
                    }
                }
                infile.close();

                if (empty) {
                    cout << "No expenses yet." << endl;
                }
                else {
                    cout << "Total spent: " << totalspent << endl;
                    cout << "Largest expense: " << largestcat << " (" << largestamt << ")" << endl;
                }
            }
        }
        else if (choice == 3) {
            char searchcat[20];
            cout << "Enter category: ";
            cin >> searchcat;

            ifstream infile("expenses.txt");
            if (!infile) {
                cout << "No expenses found for " << searchcat << endl;
            }
            else {
                char cat[20];
                int amt;
                int count = 0;
                int total = 0;

                while (infile >> cat >> amt) {
                    if (strcmp(cat, searchcat) == 0) {
                        count++;
                        total += amt;
                    }
                }
                infile.close();

                if (count == 0) {
                    cout << "No expenses found for " << searchcat << endl;
                }
                else {
                    cout << "Expenses in " << searchcat << ": " << count << endl;
                    cout << "Total for " << searchcat << ": " << total << endl;
                }
            }
        }
        else if (choice == 4) {
            ofstream outfile("expenses.txt");
            outfile.close();
            cout << "All expenses cleared." << endl;
        }
        else if (choice == 5) {
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 5);

    return 0;
}