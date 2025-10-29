#include <iostream>
#include <ctime>
using namespace std;


class Order {
	double ArraivalTime;
	string OrderType;       //(vip , normal,veg)
	int OrderSize;
	double OrderPrice;


public:
	//constractor
	Order() : ArraivalTime(0), OrderType("Normal"), OrderSize(0), OrderPrice(0.0) {}
	//destractor
	~Order() {}
	//setters
	void setArraivalTime() {
				time_t now = time(0);
				ArraivalTime = static_cast<double>(now);
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

};
class cooks:public Order{
	string specialization;   //(vip , normal,veg)
	int breakDuration;      //break time
	int speed;              //dishes per time step
	int ordersBeforeBreak;  //number of orders have benn cooked before break


public:
	//constractor
	cooks() : specialization("Normal"), breakDuration(0), speed(0), ordersBeforeBreak(0) {}
	//destractor
	~cooks() {}
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