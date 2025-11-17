#include <iostream>
#include <sstream>
#include <fstream>
#include "classes.h"
using namespace std;
/*


order class


*/
// Constructor
Order::Order() : type(NORMAL), OrderSize(0), OrderPrice(0.0), ID(0),
    ArraivalTime(0.0), waitingTime(0.0), serviceTime(0.0),
    finishTime(0.0), deadline(0.0), Status(waiting) {}


// Destructor
Order::~Order() {}

// Setters
void Order::setArrivalTime(double t) { ArraivalTime = t; }
void Order::setOrderType(OrderType t) { type = t; }
void Order::setOrderSize(int size) { OrderSize = size; }
void Order::setOrderPrice(double price) { OrderPrice = price; }
void Order::setID(int id) { ID = id; }
void Order::setWaitingTime(double wt) { waitingTime = wt; }
void Order::setServiceTime(double st) { serviceTime = st; }
void Order::setFinishTime(double ft) { finishTime = ft; }
void Order::setDeadline(double d) { deadline = d; }
void Order::setStatus(Orderstatus s) { Status = s; }

// Getters
double Order::getArraivalTime() const { return ArraivalTime; }
OrderType Order::getType() const { return type; }
int Order::getOrderSize() const { return OrderSize; }
double Order::getOrderPrice() const { return OrderPrice; }
int Order::getID() const { return ID; }
double Order::getWaitingTime() const { return waitingTime; }
double Order::getServiceTime() const { return serviceTime; }
double Order::getFinishTime() const { return finishTime; }
double Order::getDeadline() const { return deadline; }
Orderstatus Order::getStatus() const { return Status; }

// Print order data
void Order::print() const {
    cout << "Type: " << (type == NORMAL ? "Normal" : type == VEGAN ? "Vegan" : "VIP")
        << ", Size: " << OrderSize
        << ", Price: " << OrderPrice
        << ", ID: " << ID
        << ", ArrivalTime: " << ArraivalTime
        << ", Waiting: " << waitingTime
        << ", Service: " << serviceTime
        << ", Finish: " << finishTime
        << ", Deadline: " << deadline
        << ", Status: " << Status
        << endl;
}
/*


cooks class


*/
// Constructor
Cook::Cook()
    : specialization(NORMAL), baseSpeed(0), currentSpeed(0), ordersBeforeBreak(0), breakDuration(0),
    status(AVAILABLE), handledNormalOrders(0), handledVeganOrders(0), handledVIPOrders(0),
    busyTime(0), idleTime(0), breakTime(0), injuryTime(0) {
}

// Destructor
Cook::~Cook() {}

// Setters
void Cook::setSpecialization(OrderType spec) { specialization = spec; }
void Cook::setBreakDuration(int duration) { breakDuration = duration; }
void Cook::setBaseSpeed(int speed) { baseSpeed = speed; }
void Cook::setCurrentSpeed(int speed) { currentSpeed = speed; }
void Cook::setOrdersBeforeBreak(int orders) { ordersBeforeBreak = orders; }
void Cook::setStatus(CookStatus s) { status = s; }
void Cook::setHandledNormalOrders(int n) { handledNormalOrders = n; }
void Cook::setHandledVeganOrders(int v) { handledVeganOrders = v; }
void Cook::setHandledVIPOrders(int vip) { handledVIPOrders = vip; }
void Cook::setBusyTime(int t) { busyTime = t; }
void Cook::setIdleTime(int t) { idleTime = t; }
void Cook::setBreakTime(int t) { breakTime = t; }
void Cook::setInjuryTime(int t) { injuryTime = t; }

// Getters
OrderType Cook::getSpecialization() const { return specialization; }
int Cook::getBreakDuration() const { return breakDuration; }
int Cook::getBaseSpeed() const { return baseSpeed; }
int Cook::getCurrentSpeed() const { return currentSpeed; }
int Cook::getOrdersBeforeBreak() const { return ordersBeforeBreak; }
CookStatus Cook::getStatus() const { return status; }
int Cook::getHandledNormalOrders() const { return handledNormalOrders; }
int Cook::getHandledVeganOrders() const { return handledVeganOrders; }
int Cook::getHandledVIPOrders() const { return handledVIPOrders; }
int Cook::getBusyTime() const { return busyTime; }
int Cook::getIdleTime() const { return idleTime; }
int Cook::getBreakTime() const { return breakTime; }
int Cook::getInjuryTime() const { return injuryTime; }
/*


event class


*/

// Constructor
Event::Event(EventType t, int ts, Order* o, int id, double m)
    : type(t), TimeStep(ts), order(o), OrderID(id), ExtraMoney(m) {
}

// Destructor
Event::~Event() {}

// Setters
void Event::setType(EventType t) { type = t; }
void Event::setTimeStep(int ts) { TimeStep = ts; }
void Event::setOrder(Order* o) { order = o; }
void Event::setOrderID(int id) { OrderID = id; }
void Event::setExtraMoney(double m) { ExtraMoney = m; }

// Getters
EventType Event::getType() const { return type; }
int Event::getTimeStep() const { return TimeStep; }
Order* Event::getOrder() const { return order; }
int Event::getOrderID() const { return OrderID; }
double Event::getExtraMoney() const { return ExtraMoney; }

// Print event details
void Event::print() const {
          cout << "Event Type: " << (type == ARRIVAL ? "Arrival" : type == CANCELLATION ? "Cancellation" : "Promotion")
        << ", TimeStep: " << TimeStep
        << ", OrderID: " << OrderID
        << ", ExtraMoney: " << ExtraMoney
        << endl;
}


/*


resturant class


*/


// Constructor
Restaurant::Restaurant() : AutoPromotionLimit(0), CurrentTimeStep(0) {}

// LoadFile Implementation
void Restaurant::LoadFile(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string type;
        ss >> type;

        if (type == "Cook") {
            string spec; int speed, breakDur, ordersBeforeBreak;
            ss >> spec >> speed >> breakDur >> ordersBeforeBreak;

            Cook* c = new Cook();
            if (spec == "Normal") c->setSpecialization(NORMAL);
            else if (spec == "Vegan") c->setSpecialization(VEGAN);
            else if (spec == "VIP") c->setSpecialization(VIP);

            c->setBaseSpeed(speed); // Use setBaseSpeed for baseSpeed
            c->setBreakDuration(breakDur);
            c->setOrdersBeforeBreak(ordersBeforeBreak);

            if (spec == "Normal") normalCooks.InsertEnd(c);
            else if (spec == "Vegan") veganCooks.InsertEnd(c);
            else if (spec == "VIP") vipCooks.InsertEnd(c);
        }
        else if (type == "Event") {
            string evtType; int ts, id, size; string orderType; double price;
            ss >> evtType >> ts;

            if (evtType == "Arrival") {
                ss >> orderType >> size >> price >> id;
                Order* o = new Order();
                if (orderType == "Normal") o->setOrderType(NORMAL);
                else if (orderType == "Vegan") o->setOrderType(VEGAN);
                else if (orderType == "VIP") o->setOrderType(VIP);
                o->setOrderSize(size);
                o->setOrderPrice(price);
                o->setID(id);

                Event* e = new Event(ARRIVAL, ts, o);
                events.enqueue(e);
            }
            else if (evtType == "Promotion") {
                double extraMoney;
                ss >> id >> extraMoney;
                Event* e = new Event(PROMOTION, ts, nullptr, id, extraMoney);
                events.enqueue(e);
            }
            else if (evtType == "Cancellation") {
                ss >> id;
                Event* e = new Event(CANCELLATION, ts, nullptr, id);
                events.enqueue(e);
            }
        }
        else if (type == "AutoPromotionLimit") {
            ss >> AutoPromotionLimit;
        }
    }

    fin.close();
    cout << "File loaded successfully.\n";
}

// SimpleSimulator Implementation
void Restaurant::SimpleSimulator() {
    CurrentTimeStep = 0;

    while (
        !events.isEmpty() ||
        !normalOrders.isEmpty() ||
        !veganOrders.isEmpty() ||
        !vipOrders.isEmpty() ||
        !inServiceOrders.isEmpty())
    {
        cout << "\nTime Step: " << CurrentTimeStep << endl;

        Event* e;
        while (events.peek(e) && e->getTimeStep() == CurrentTimeStep) {
            events.dequeue(e);

            if (e->getType() == ARRIVAL) {
                Order* o = e->getOrder();
                if (o->getType() == NORMAL) normalOrders.enqueue(o);
                else if (o->getType() == VEGAN) veganOrders.enqueue(o);
                else if (o->getType() == VIP) vipOrders.enqueue(o);
            }
            else if (e->getType() == CANCELLATION) {
                int cancelID = e->getOrderID();
                LinkedQueue<Order*> tempQ;
                Order* tempO;
                while (normalOrders.dequeue(tempO)) {
                    if (tempO->getID() != cancelID) tempQ.enqueue(tempO);
                    else delete tempO;
                }
                normalOrders = tempQ;
            }
        }

        Order* o1; Order* o2; Order* o3;
        if (normalOrders.dequeue(o1)) inServiceOrders.InsertEnd(o1);
        if (veganOrders.dequeue(o2)) inServiceOrders.InsertEnd(o2);
        if (vipOrders.dequeue(o3)) inServiceOrders.InsertEnd(o3);

        if (CurrentTimeStep % 5 == 0) {
            if (!inServiceOrders.isEmpty()) {
                Order* finishedO;
                inServiceOrders.DeleteFirst(finishedO);
                finishedOrders.InsertEnd(finishedO);
            }
        }

        cout << "Normal Orders waiting: " << normalOrders.GetCount() << endl;
        cout << "Vegan Orders waiting: " << veganOrders.GetCount() << endl;
        cout << "VIP Orders waiting: " << vipOrders.GetCount() << endl;
        cout << "In-Service Orders: " << inServiceOrders.GetCount() << endl;
        cout << "Finished Orders: " << finishedOrders.GetCount() << endl;

        CurrentTimeStep++;
    }

    cout << "\nSimulation finished." << endl;
}

