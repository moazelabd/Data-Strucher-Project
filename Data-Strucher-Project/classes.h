#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <string>
using namespace std;

// ENUMS
enum OrderType { NORMAL, VEGAN, VIP };
enum Orderstatus { finished, in_service, waiting };
enum CookStatus { AVAILABLE, ON_BREAK, INJURED, BUSY };
enum EventType { ARRIVAL, CANCELLATION, PROMOTION };

// ORDER CLASS
class Order {
private:
    double ArraivalTime;
    OrderType type;
    int OrderSize;
    double OrderPrice;
    int ID;
    double waitingTime;
    double serviceTime;
    double finishTime;
    double deadline;
    Orderstatus Status;

public:
    Order();
    ~Order();

    void setArrivalTime(double t);
    void setOrderType(OrderType t);
    void setOrderSize(int size);
    void setOrderPrice(double price);
    void setID(int id);
    void setWaitingTime(double wt);
    void setServiceTime(double st);
    void setFinishTime(double ft);
    void setDeadline(double d);
    void setStatus(Orderstatus s);

    double getArraivalTime() const;
    OrderType getType() const;
    int getOrderSize() const;
    double getOrderPrice() const;
    int getID() const;
    double getWaitingTime() const;
    double getServiceTime() const;
    double getFinishTime() const;
    double getDeadline() const;
    Orderstatus getStatus() const;

    void print() const;
};

// COOK CLASS
class Cook {
private:
    OrderType specialization;
    int breakDuration;
    int baseSpeed;
    int currentSpeed;
    int ordersBeforeBreak;
    CookStatus status;
    int handledNormalOrders;
    int handledVeganOrders;
    int handledVIPOrders;
    int busyTime;
    int idleTime;
    int breakTime;
    int injuryTime;

public:
    Cook();
    ~Cook();

    void setSpecialization(OrderType spec);
    void setBreakDuration(int duration);
    void setBaseSpeed(int speed);
    void setCurrentSpeed(int speed);
    void setOrdersBeforeBreak(int orders);
    void setStatus(CookStatus s);
    void setHandledNormalOrders(int n);
    void setHandledVeganOrders(int v);
    void setHandledVIPOrders(int vip);
    void setBusyTime(int t);
    void setIdleTime(int t);
    void setBreakTime(int t);
    void setInjuryTime(int t);

    OrderType getSpecialization() const;
    int getBreakDuration() const;
    int getBaseSpeed() const;
    int getCurrentSpeed() const;
    int getOrdersBeforeBreak() const;
    CookStatus getStatus() const;
    int getHandledNormalOrders() const;
    int getHandledVeganOrders() const;
    int getHandledVIPOrders() const;
    int getBusyTime() const;
    int getIdleTime() const;
    int getBreakTime() const;
    int getInjuryTime() const;
};

// EVENT CLASS
class Event {
private:
    EventType type;
    int TimeStep;
    Order* order; // only for Arrival
    int OrderID;  // only for Cancellation & Promotion
    double ExtraMoney; // only for Promotion

public:
    Event(EventType t, int ts, Order* o = nullptr, int id = -1, double m = 0.0);
    ~Event();

    void setType(EventType t);
    void setTimeStep(int ts);
    void setOrder(Order* o);
    void setOrderID(int id);
    void setExtraMoney(double m);

    EventType getType() const;
    int getTimeStep() const;
    Order* getOrder() const;
    int getOrderID() const;
    double getExtraMoney() const;

    void print() const;
};

#endif
