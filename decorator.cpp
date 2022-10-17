#include <iostream>
#include <string>

using namespace std;

//Beverage abstract class
class Beverage {
	
public:
	string description = "Unknown Beverage";
	virtual double bevCost() = 0;
	virtual string getDescription() { return description; }
};

//Beverage class realization
class DarkRoast : public Beverage {
	
public:
	DarkRoast() {
		description = "Dark Roast Coffee";
	}
	double bevCost() {
		return .99;
	}
	~DarkRoast() {}
};

//Beverage class realization
class Espresso : public Beverage {
	
public:
	Espresso() {
		description = "Espresso Coffee";
	}	
	double bevCost() {
		return .7;
	}
	~Espresso() {}
};

//Beverage class realization
class HouseBlend : public Beverage {
	
public:
	HouseBlend() {
		description = "House Blend Coffee";
	}	
	double bevCost() {
		return .6;
	}
	~HouseBlend() {}
};

//Beverage class realization
class Decaf : public Beverage {
	
public:
	Decaf() {
		description = "Decaffeinated Coffee";
	}	
	double bevCost() {
		return .89;
	}
	~Decaf() {}
};

//Decorator class
class CondimentDecorator : public Beverage {
	
public:
	Beverage* beverage;
};

//Decoration class
class Milk : public CondimentDecorator {
	
public:
	Milk(Beverage* beverage) {
		this->beverage = beverage;
	}
	string getDescription() {
		return beverage->getDescription() + ", Milk";
	}
	double bevCost() {
		return .10 + beverage->bevCost();
	}
	~Milk() {}
};

//Decoration class
class Mocha : public CondimentDecorator {
	
public:
	Mocha(Beverage* beverage) {
		this->beverage = beverage;
	}
	string getDescription() {
		return beverage->getDescription() + ", Mocha";
	}
	double bevCost() {
		return .30 + beverage->bevCost();
	}
	~Mocha() {}
};

//Decoration class
class Whip : public CondimentDecorator {
	
public:
	Whip(Beverage* beverage) {
		this->beverage = beverage;
	}
	string getDescription() {
		return beverage->getDescription() + ", Whip";
	}
	double bevCost() {
		return .40 + beverage->bevCost();
	}
	~Whip() {}
};

int main() {
	
	Beverage *NewBev = new DarkRoast();
	NewBev = new Mocha(NewBev);
	NewBev = new Mocha(NewBev);
	NewBev = new Whip(NewBev);
	
	cout << NewBev->getDescription() << endl << "Total cost: $" << NewBev->bevCost() << endl << endl;
	
	NewBev = new Mocha(NewBev);
	cout << NewBev->getDescription() << endl << "Total cost: $" << NewBev->bevCost() << endl << endl;
	
	Beverage *AnotherBev = new Espresso();
	AnotherBev = new Whip(AnotherBev);
	
	cout << AnotherBev->getDescription() << endl << "Total cost: $" << AnotherBev->bevCost() << endl;
	
	return 0;
}
