#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
//enum for orders types
enum OrderType { NORMAL, VEGAN, VIP };
//enum for status
enum Orderstatus{ finished, in_service, waiting};
/*


order class


*/
class Order {
	double ArraivalTime;
    OrderType type;       //(vip , normal,veg)
	int OrderSize;
	double OrderPrice;
	int ID;
    double waitingTime;
    double serviceTime;
    double finishTime;
    double deadline;
    Orderstatus Status; //(finished, in_service, waiting)
public:
	//constractor
    Order() : type(NORMAL), OrderSize(0), OrderPrice(0.0), ID(0),
        ArraivalTime(0.0), waitingTime(0.0), serviceTime(0.0),
        finishTime(0.0), deadline(0.0), Status(waiting) {
    }
	//destractor
	~Order() {}
	//setters
	void setArrivalTime(double t) { 
		ArraivalTime = t;
	}

	void setOrderType(OrderType t) {
		type = t;
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
    void setWaitingTime(double wt) { 
        waitingTime = wt; 
    }
    void setServiceTime(double st) {
        serviceTime = st; 
    }
    void setFinishTime(double ft) { 
        finishTime = ft;
    }
    void setDeadline(double d) {
        deadline = d;
    }
    void setStatus(Orderstatus s) {
        Status = s;
    }
	//getters
	double getArraivalTime() const {
		return ArraivalTime;
	}
    OrderType getType() const {
        return type; 
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
    double getWaitingTime() const { 
        return waitingTime; 
    }
    double getServiceTime() const {
        return serviceTime;
    }
    double getFinishTime() const { 
        return finishTime; 
    }
    double getDeadline() const { 
        return deadline; 
    }
    Orderstatus getStatus() const {
        return Status; 
    }
    //print the order data
    void print() const {
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

	


};
//enum for cookers statue
enum CookStatus { AVAILABLE, ON_BREAK, INJURED, BUSY };
/*


cooks class


*/
class Cook{
    OrderType specialization;   //(vip , normal,veg)
	int breakDuration;      //break time
    int baseSpeed;
    int currentSpeed;        
	int ordersBeforeBreak;  //number of orders have benn cooked before break
    CookStatus status;
    int handledNormalOrders;
    int handledVeganOrders;
    int handledVIPOrders;
    int busyTime;
    int idleTime;
    int breakTime;
    int injuryTime;
  
public:
	//constractor
    Cook()
        : specialization(NORMAL), baseSpeed(0), currentSpeed(0), ordersBeforeBreak(0), breakDuration(0),
        status(AVAILABLE), handledNormalOrders(0), handledVeganOrders(0), handledVIPOrders(0),
        busyTime(0), idleTime(0), breakTime(0), injuryTime(0) {
    }
	//destractor
	~Cook() {}
    // setters
    void setSpecialization(OrderType spec) {
        specialization = spec; 
    }
    void setBreakDuration(int duration) {
        breakDuration = duration;
    }
    void setBaseSpeed(int speed) { 
        baseSpeed = speed;
    }
    void setCurrentSpeed(int speed) {
        currentSpeed = speed;
    }
    void setOrdersBeforeBreak(int orders) {
        ordersBeforeBreak = orders; 
    }
    void setStatus(CookStatus s) { 
        status = s;
    }
    void setHandledNormalOrders(int n) { 
        handledNormalOrders = n;
    }
    void setHandledVeganOrders(int v) { 
        handledVeganOrders = v;
    }
    void setHandledVIPOrders(int vip) { 
        handledVIPOrders = vip;
    }
    void setBusyTime(int t) { 
        busyTime = t;
    }
    void setIdleTime(int t) {
        idleTime = t;
    }
    void setBreakTime(int t) {
        breakTime = t;
    }
    void setInjuryTime(int t) { 
        injuryTime = t;
    }

    // getters
    OrderType getSpecialization() const {
        return specialization;
    }
    int getBreakDuration() const {
        return breakDuration;
    }
    int getBaseSpeed() const {
        return baseSpeed; 
    }
    int getCurrentSpeed() const {
        return currentSpeed;
    }
    int getOrdersBeforeBreak() const {
        return ordersBeforeBreak;
    }
    CookStatus getStatus() const {
        return status; 
    }
    int getHandledNormalOrders() const {
        return handledNormalOrders; 
    }
    int getHandledVeganOrders() const {
        return handledVeganOrders; 
    }
    int getHandledVIPOrders() const {
        return handledVIPOrders; 
    }
    int getBusyTime() const {
        return busyTime;
    }
    int getIdleTime() const { 
        return idleTime; 
    }
    int getBreakTime() const { 
        return breakTime;
    }
    int getInjuryTime() const {
        return injuryTime;
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
        Restaurant() : AutoPromotionLimit(0), CurrentTimeStep(0) {}

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
                    if (spec == "Normal") c->setSpecialization(NORMAL);
                    else if (spec == "Vegan") c->setSpecialization(VEGAN);
                    else if (spec == "VIP") c->setSpecialization(VIP);

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
                        double extraMony;
                        ss >> id >> extraMony;
                        Event* e = new Event(PROMOTION, ts, nullptr, id, extraMony);
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

            while (
                !events.isEmpty() ||
                !normalOrders.isEmpty() ||
                !veganOrders.isEmpty() ||
                !vipOrders.isEmpty() ||
                !inServiceOrders.isEmpty())
            {
                cout << "\nTime Step: " << CurrentTimeStep << endl;

                // تنفيذ الأحداث لهذه الـTime Step فقط
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
                        // حذف الطلب من قائمة الانتظار الخاصة بالـNormal فقط
                        LinkedQueue<Order*> tempQ;
                        Order* tempO;
                        while (normalOrders.dequeue(tempO)) {
                            if (tempO->getID() != cancelID) tempQ.enqueue(tempO);
                            else delete tempO; // إزالة نهائية من الذاكرة
                        }
                        normalOrders = tempQ;
                    }
                    // يمكنك إضافة حالات Promotion لاحقاً إذا وجدت في ملف الإدخال
                }

                // نقل أول طلب من كل قائمة للـinServiceOrders
                Order* o1; Order* o2; Order* o3;
                if (normalOrders.dequeue(o1)) inServiceOrders.InsertEnd(o1);
                if (veganOrders.dequeue(o2)) inServiceOrders.InsertEnd(o2);
                if (vipOrders.dequeue(o3)) inServiceOrders.InsertEnd(o3);

                // كل 5 خطوات زمنية، يتم نقل أول طلب في الخدمة لقائمة "انتهى"
                if (CurrentTimeStep % 5 == 0) {
                    if (!inServiceOrders.isEmpty()) {
                        // يجب تنفيذ دالة ترتب إزالة أول عنصر
                        Order* finishedO;
                        inServiceOrders.DeleteFirst(finishedO); // بناء على دالة حذف أول عنصر في LinkedList
                        finishedOrders.InsertEnd(finishedO);
                    }
                }

                // display system statu in every step
                cout << "Normal Orders waiting: " << normalOrders.GetCount() << endl;
                cout << "Vegan Orders waiting: " << veganOrders.GetCount() << endl;
                cout << "VIP Orders waiting: " << vipOrders.GetCount() << endl;
                cout << "In-Service Orders: " << inServiceOrders.GetCount() << endl;
                cout << "Finished Orders: " << finishedOrders.GetCount() << endl;

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
	CANCELLATION,
    PROMOTION
};

class Event {
	EventType type;
	int TimeStep;           // Time Step
	Order* order;     //  only for Arrival
	int OrderID;      // only for Cancellation
    double ExtraMoney;
public:
	Event(EventType t, int ts, Order* o = nullptr, int id = -1,double m)
		: type(t), TimeStep(ts), order(o), OrderID(id),ExtraMoney(m) {
	}
    ~Event() {};
	//setters
	void setType(EventType t) {
        type = t; 
    }	
	void setTimeStep(int ts) { 
        TimeStep = ts; 
    }
	void setOrder(Order* o) {
        order = o; 
    }
	void setOrderID(int id) {
        OrderID = id;
    }
    void setExtraMoney(double m) { 
        ExtraMoney = m;
    }
    //getters
	EventType getType() const {
        return type; 
    }
	int getTimeStep() const { 
        return TimeStep;
    }
	Order* getOrder() const { 
        return order; 
    }
	int getOrderID() const {
        return OrderID; 
    }
    double getExtraMoney() const { 
        return ExtraMoney;
    }
    // Print event details
    void print() const {
        cout << "Event Type: " << (type == ARRIVAL ? "Arrival" : type == CANCELLATION ? "Cancellation" : "Promotion")
            << ", TimeStep: " << TimeStep
            << ", OrderID: " << OrderID
            << ", ExtraMoney: " << ExtraMoney
            << endl;
    }
};
