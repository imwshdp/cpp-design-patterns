#include <iostream>
#include <string>

using namespace std;

//Quacking interface
class IQuackBehavior {
	
public:
	virtual string quack() = 0;	
	virtual ~IQuackBehavior() {  };
};

class Quack : public IQuackBehavior {

public:
	Quack() {  }
	string quack() override { return "quacking"; }
	~Quack() {  }
};

class Squeck : public IQuackBehavior {

public:
	Squeck() {  }
	string quack() override { return "squecking"; }
	~Squeck() {  }
};

class MuteQuack : public IQuackBehavior {

public:
	MuteQuack() {  }
	string quack() override { return "say nothing"; }
	~MuteQuack() {  }
};


//Flying interface
class IFlyBehavior {
	
public:
	virtual string fly() = 0;
	virtual ~IFlyBehavior() {  };
};

class FlyWithWings : public IFlyBehavior {
	
public:
	FlyWithWings() {  }
	string fly() override { return "flying using wings"; }
	~FlyWithWings() {  }	
};

class FlyNoWay : public IFlyBehavior {
	
public:
	FlyNoWay() {  }
	string fly() override { return "not flying"; }
	~FlyNoWay() {  }
};


//Common Duck class
class Duck {
	
protected:
	IQuackBehavior* quackBehavior;
	IFlyBehavior* flyBehavior;
	
public:
	Duck() {  }
	string performQuack() { return (*quackBehavior).quack(); }
	string performFly() { return (*flyBehavior).fly(); }	
	string performSwim() { return "swimmig like any common duck"; }

	void setQuackBehavior(IQuackBehavior* quack_behavior) {
		quackBehavior = quack_behavior;
	}	
	void setFlyBehavior(IFlyBehavior* fly_behavior) {		
		flyBehavior = fly_behavior;		
	}
	
	virtual string display() = 0;
	
	~Duck() {	
		quackBehavior = NULL;
		flyBehavior = NULL;				
	}
};

//Mallard Duck class
class MallardDuck : public Duck {
	
public:
	MallardDuck() {
		setQuackBehavior(new Quack);
		setFlyBehavior(new FlyWithWings);
	}
	string display() { return "MALLARD DUCK"; }	
	~MallardDuck() {  }	
};

//RedHead Duck class
class RedHeadDuck : public Duck {
	
public:
	RedHeadDuck() {
		setQuackBehavior(new Quack);
		setFlyBehavior(new FlyWithWings);	
	}
	string display() { return "RED HEAD DUCK"; }
	~RedHeadDuck() {  }
};

//Rubber Duck class
class RubberDuck : public Duck {
	
public:
	RubberDuck() {
		setQuackBehavior(new Squeck);
		setFlyBehavior(new FlyNoWay);	
	}
	string display() { return "RUBBER DUCK"; }
	~RubberDuck() {  }
};

//Decoy Duck class
class DecoyDuck : public Duck {
	
public:
	DecoyDuck() {
		setQuackBehavior(new MuteQuack);
		setFlyBehavior(new FlyNoWay);
	}
	string performSwim() { return "not swimming"; }
	string display() { return "DECOY DUCK"; }
	~DecoyDuck() {  }	
};

int main() {
	
	MallardDuck mallard_duck;
	cout << mallard_duck.display() << " can " << mallard_duck.performQuack() << ", " << mallard_duck.performFly() << " and " << mallard_duck.performSwim() << endl << endl;
	
	RedHeadDuck red_duck;
	cout << red_duck.display() << " can " << red_duck.performQuack() << ", " << red_duck.performFly() << " and " << red_duck.performSwim() << endl << endl;
	
	RubberDuck rubber_duck;
	cout << rubber_duck.display() << " can " << rubber_duck.performQuack() << ", " << rubber_duck.performFly() << " and " << rubber_duck.performSwim() << endl << endl;
	
	DecoyDuck decoy_duck;
	cout << decoy_duck.display() << " can " << decoy_duck.performQuack() << ", " << decoy_duck.performFly() << " and " << decoy_duck.performSwim() << endl;
	
	return 0;
}
