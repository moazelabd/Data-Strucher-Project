
#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Order {
private:
    string type;      
    int size;         
    double price;     
    int ID;           
    double arrivalTime;

public:
  
    Order() : type(""), size(0), price(0), ID(0), arrivalTime(0.0) {}

    // Constructor 
    Order(string t, int s, double p, int id, double at)
        : type(t), size(s), price(p), ID(id), arrivalTime(at) {
    }

    // Setters
    void setType(string t) { type = t; }
    void setSize(int s) { size = s; }
    void setPrice(double p) { price = p; }
    void setID(int id) { ID = id; }
    void setArrivalTime(double at) { arrivalTime = at; }

    // Getters
    string getType() const { return type; }
    int getSize() const { return size; }
    double getPrice() const { return price; }
    int getID() const { return ID; }
    double getArrivalTime() const { return arrivalTime; }


    void readFromString(const string& line) {
        stringstream ss(line);
        ss >> type >> size >> price >> ID >> arrivalTime;
    }


    void print() const {
        cout << "Type: " << type
            << ", Size: " << size
            << ", Price: " << price
            << ", ID: " << ID
            << ", ArrivalTime: " << arrivalTime
            << endl;
    }
};

#endif
