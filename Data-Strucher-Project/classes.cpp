#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/*


order class


*/
class Order {
	double ArraivalTime;
	string OrderType;       //(vip , normal,veg)
	int OrderSize;
	double OrderPrice;
	int ID;


public:
	//constractor
	Order() : ArraivalTime(0), OrderType("Normal"), OrderSize(0), OrderPrice(0.0) ,ID(1){}
	//destractor
	~Order() {}
	//setters
	void setArrivalTime(double t) { 
		ArraivalTime = t;
	}

	void setOrderType(string type) {
		OrderType = type;
	}
	void setOrderSize(int size) {
		OrderSize = size;
	}
	void setOrderPrice(double price) {
		OrderPrice = price;
	}
	void setID(int id) {
		ID = id;
	}
	//getters
	double getArraivalTime() const {
		return ArraivalTime;
	}
	string getOrderType() const {
		return OrderType;
	}
	int getOrderSize() const {
		return OrderSize;
	}
	double getOrderPrice() const {
		return OrderPrice;
	}	
	
	int getID() const {
		return ID;
	}
	


};

/*


cooks class


*/
class cook{
	string specialization;   //(vip , normal,veg)
	int breakDuration;      //break time
	int speed;              //dishes per time step
	int ordersBeforeBreak;  //number of orders have benn cooked before break


public:
	//constractor
	cook() : specialization("Normal"), breakDuration(0), speed(0), ordersBeforeBreak(0) {}
	//destractor
	~cook() {}
	//setters
	void setSpecialization(string spec) {
		specialization = spec;
	}
	void setBreakDuration(int duration) {
		breakDuration = duration;
	}
	void setSpeed(int spd) {
		speed = spd;
	}
	void setOrdersBeforeBreak(int orders) {
		ordersBeforeBreak = orders;
	}
	//getters
	string getSpecialization() const {
		return specialization;
	}
	int getBreakDuration() const {
		return breakDuration;
	}
	int getSpeed() const {
		return speed;
	}
	int getOrdersBeforeBreak() const {
		return ordersBeforeBreak;
	}
	



};

/*


resturant class


*/
template<typename T>
class Restaurant {
        // lists of cooks
        LinkedList<Cook*> normalCooks;
        LinkedList<Cook*> veganCooks;
        LinkedList<Cook*> vipCooks;

        // waiting orders
        Queue<Order*> normalOrders;
        Queue<Order*> veganOrders;
        PriorityQueue<Order*> vipOrders;

        // in_service and finished
        LinkedList<Order*> inServiceOrders;
        LinkedList<Order*> finishedOrders;

        // events
        Queue<Event*> events;

        int AutoPromotionLimit;
        int CurrentTimeStep;

    public:

        void LoadFile(string filename) {
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
                    c->setSpecialization(spec);
                    c->setSpeed(speed);
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
                        o->setOrderType(orderType);
                        o->setOrderSize(size);
                        o->setOrderPrice(price);
                        o->setID(id);

                        Event* e = new Event(ARRIVAL, ts, o);
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

        void SimpleSimulator() {
            CurrentTimeStep = 0;

            while (!events.isEmpty() || !normalOrders.isEmpty() || !veganOrders.isEmpty() || !vipOrders.isEmpty() || !inServiceOrders.IsEmpty()) {
                cout << "\nTime Step: " << CurrentTimeStep << endl;

                // execute events for current time step
                Event* e;
                while (events.peek(e) && e->getTimeStep() == CurrentTimeStep) {
                    events.dequeue(e);

                    if (e->getType() == ARRIVAL) {
                        Order* o = e->getOrder();
                        if (o->getOrderType() == "Normal") normalOrders.enqueue(o);
                        else if (o->getOrderType() == "Vegan") veganOrders.enqueue(o);
                        else if (o->getOrderType() == "VIP") vipOrders.enqueue(o);
                    }
                    else if (e->getType() == CANCELLATION) {
                        int cancelID = e->getOrderID();
                        // search and delete from normalOrders
                        Queue<Order*> tempQ;
                        Order* tempO;
                        while (normalOrders.dequeue(tempO)) {
                            if (tempO->getID() != cancelID) tempQ.enqueue(tempO);
                            else delete tempO; // removed
                        }
                        normalOrders = tempQ;
                    }
                }

                // Pick first order of each type and move to inServiceOrders
                Order* o1; Order* o2; Order* o3;
                if (normalOrders.dequeue(o1)) inServiceOrders.InsertEnd(o1);
                if (veganOrders.dequeue(o2)) inServiceOrders.InsertEnd(o2);
                if (vipOrders.dequeue(o3)) inServiceOrders.InsertEnd(o3);

                // Every 5 time steps, move one order from inServiceOrders to finishedOrders
                if (CurrentTimeStep % 5 == 0) {
                    if (!inServiceOrders.IsEmpty()) {
                        Order* finishedO = inServiceOrders.GetFirstAndRemove();
                        finishedOrders.InsertEnd(finishedO);
                    }
                }

                // Display system state
                cout << "Normal Orders waiting: " << normalOrders.GetCount() << endl;
                cout << "Vegan Orders waiting: " << veganOrders.GetCount() << endl;
                cout << "VIP Orders waiting: " << vipOrders.GetCount() << endl;

                CurrentTimeStep++;

            }

            cout << "\nSimulation finished." << endl;
        }
    };
/*


event class


*/
enum EventType { 
	ARRIVAL, 
	CANCELLATION 
};

class Event {
	EventType type;
	int TimeStep;           // Time Step
	Order* order;     //  only for Arrival
	int OrderID;      // only for Cancellation

public:
	Event(EventType t, int ts, Order* o = nullptr, int id = -1)
		: type(t), TimeStep(ts), order(o), OrderID(id) {
	}
	//getters
	EventType getType() const { return type; }
	int getTimeStep() const { return TimeStep; }
	Order* getOrder() const { return order; }
	int getOrderID() const { return OrderID; }
	//setters
	void setType(EventType t) { type = t; }	
	void setTimeStep(int ts) { TimeStep = ts; }
	void setOrder(Order* o) { order = o; }
	void setOrderID(int id) { OrderID = id; }

};
