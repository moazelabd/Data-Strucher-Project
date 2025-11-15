#include "classes.h"
#include <fstream>
#include <vector>
#include <string>

int main() {
    string filename;
    cout << "Enter file name: ";
    cin >> filename;

    ifstream infile(filename);
    if (!infile) return 1;

    vector<Order> orders;
    string line;

    while (getline(infile, line)) {
        if (line.empty()) continue;
        Order o;
        o.readFromString(line);
        orders.push_back(o);
    }

    for (const auto& o : orders) o.print();

    return 0;
}
