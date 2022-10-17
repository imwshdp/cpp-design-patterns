#include <iostream>
#include <string>

using namespace std;

//Pizza abstract class
class Pizza {
	
public:
	string type = "Unknown Pizza";
	virtual	string getPizzaType() = 0;
	
	void prepare() {
		cout << type << " prepared!" << endl;
	}
	void bake() {
		cout << type << " baked!" << endl;
	}
	void cut() {
		cout << type << " cuted!" << endl;
	}
	void box() {
		cout << type << " boxed!" << endl;
	}
};

//NY Pizza class realization
class NYCheesePizza : public Pizza {
	
public:
	NYCheesePizza() {
		type = "New York Cheese Pizza";
	}	
	string getPizzaType() {
		return type;
	}
	~NYCheesePizza() {}	
};

//NY Pizza class realization
class NYPepperoniPizza : public Pizza {
	
public:
	NYPepperoniPizza() {
		type = "New York Pepperoni Pizza";
	}
	string getPizzaType() {
		return type;
	}
	~NYPepperoniPizza() {}
};

//NY Pizza class realization
class NYClamPizza : public Pizza {
	
public:
	NYClamPizza() {
		type = "New York Clam Pizza";
	}
	string getPizzaType() {
		return type;
	}
	~NYClamPizza() {}
};

//NY Pizza class realization
class NYVeggiePizza : public Pizza {
	
public:
	NYVeggiePizza() {
		type = "New York Veggie Pizza";
	}
	string getPizzaType() {
		return type;
	}
	~NYVeggiePizza() {}
};

//Chicago Pizza class realization
class ChicagoCheesePizza : public Pizza {
	
public:
	ChicagoCheesePizza() {
		type = "Chicago Cheese Pizza";
	}
	string getPizzaType() {
		return type;
	}
	~ChicagoCheesePizza() {}
};

//Chicago Pizza class realization
class ChicagoPepperoniPizza : public Pizza {
	
public:
	ChicagoPepperoniPizza() {
		type = "Chicago Pepperoni Pizza";
	}
	string getPizzaType() {
		return type;
	}
	~ChicagoPepperoniPizza() {}
};

//Chicago Pizza class realization
class ChicagoClamPizza : public Pizza {
	
public:
	ChicagoClamPizza() {
		type = "Chicago Clam Pizza";
	}
	string getPizzaType() {
		return type;
	}
	~ChicagoClamPizza() {}
};

//Chicago Pizza class realization
class ChicagoVeggiePizza : public Pizza {
	
public:
	ChicagoVeggiePizza() {
		type = "Chicago Veggie Pizza";
	}
	string getPizzaType() {
		return type;
	}
	~ChicagoVeggiePizza() {}
};


//Fabric abstract class
class PizzaStore : public Pizza {
	
public:
	virtual Pizza* createPizza(string type) = 0;
	
	string getPizzaType() {
		return type;
	}	
	Pizza* orderPizza(string type) {
		Pizza* pizza = 0;	
		pizza = createPizza(type);	
		pizza->prepare();
		pizza->bake();
		pizza->cut();
		pizza->box();	
		return pizza;
	}
};

//NY Fabric class realization
class NYPizzaStore : public PizzaStore {
	
public:
	Pizza* createPizza(string type) {	
		if(type == "cheese") {
			return new NYCheesePizza();
		} else if(type == "pepperoni") {
			return new NYPepperoniPizza();
		} else if(type == "clam") {
			return new NYClamPizza();
		} else if(type == "veggie") {
			return new NYVeggiePizza();
		}		
	}
};

//Chicago Fabric class realization
class ChicagoPizzaStore : public PizzaStore {
	
public:
	Pizza* createPizza(string type) {
		if(type == "cheese") {
			return new ChicagoCheesePizza();
		} else if(type == "pepperoni") {
			return new ChicagoPepperoniPizza();
		} else if(type == "clam") {
			return new ChicagoClamPizza();
		} else if(type == "veggie") {
			return new ChicagoVeggiePizza();
		}		
	}	
};

int main() {
	
	PizzaStore* nyStore = new NYPizzaStore();
	PizzaStore* chicagoStore = new ChicagoPizzaStore();
	
	Pizza* pizza = nyStore->orderPizza("cheese");
	pizza = chicagoStore->orderPizza("cheese");
	pizza = nyStore->orderPizza("clam");
	
	return 0;
}
