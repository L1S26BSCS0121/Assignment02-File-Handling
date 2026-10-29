/*
 * Name       : Fahad Maqbool
 * Reg No     : L1S26BSCS0121
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

 // FIX 1: <fstream> header was missing
#include <fstream>
#include <iostream>
using namespace std;
int main() {
    // FIX 2: Added exclamation mark to check if the file fails to open
    ifstream inFile("stock.txt");
    if (!inFile) {
        cout << "stock.txt not found!" << endl;
        return 1;
    }

    // FIX 3: Added ios::app so that existing lines in reorder.txt are not deleted
    ofstream reorder("reorder.txt", ios::app);

    char code[10];
    int qty, count = 0, low = 0;
    double price;
    // FIX 4: Changed total from int to double for decimal multiplication 
    double total = 0;

    // FIX 5: Added ignore to skip the first header line of stock.txt before reading items
    inFile.ignore(100, '\n');

    while (count < 50 && inFile >> code >> qty >> price) {
        count++;
        total = total + qty * price;
        if (qty < 10) {
            // FIX 6: Added endl so low stock items are added in new line 
            reorder << code << " " << qty << endl;
            low++;
        }
    }
    inFile.close();
    reorder.close();

    cout << "Items: " << count << endl;
    cout << "Total stock value: " << total << endl;
    cout << "Low stock items: " << low << endl;
    return 0;
}