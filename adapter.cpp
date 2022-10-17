#include <iostream>
#include <string>

using namespace std;

//Duck interface
class IDuck {
	
public:
	virtual string quack() = 0;
	virtual string fly() = 0;
};

//Mallard Duck class (IDuck Realization)
class MallardDuck : public IDuck {

public:
	MallardDuck() {}
	string quack() {
		return "quacking";
	}
	string fly() {
		return "flying";
	}
	~MallardDuck() {}

};

//Turkey interface
class ITurkey {
	
public:
	virtual string gobble() = 0;
	virtual string fly() = 0;	
};

//Wild Turkey class (ITurkey Realization)
class WildTurkey : public ITurkey {

public:
	WildTurkey() {}
	string gobble() {
		return "gobbling";
	}
	string fly() {
		return "trying to fly";
	}
	~WildTurkey() {}
};

//Fake Turkey class (ITurkey Realization)
class FakeTurkey : public ITurkey {

public:
	FakeTurkey() {}
	string gobble() override {
		return "not gobbling";
	}
	string fly() override {
		return "not flying";
	}
	~FakeTurkey() {}
};

//Class adapter (using private derivation)
class ClassAdapter : public IDuck, private WildTurkey {
	
public:
	ClassAdapter() {}
	string quack() {
		return WildTurkey::gobble();
	}
	string fly() {
		return WildTurkey::fly();
	}
	~ClassAdapter() {}
};

//Classes adapter (using interface ITurkey)
class ManyClassesAdapter : public IDuck {
	
public:
	ITurkey* turkey;

	ManyClassesAdapter(ITurkey* turkey) {
		this->turkey = turkey;
	}	
	string quack() override {
		return turkey->gobble();
	}
	string fly() override {
		return turkey->fly();
	}
	~ManyClassesAdapter() {
		turkey = NULL;
	}
};


int main() {
	
	IDuck* duck = new MallardDuck;
	cout << "MALLARD DUCK: " << duck->quack() << " and " << duck->fly() << endl;
	
	ITurkey* turkey = new WildTurkey;
	cout << "WILD TURKEY: " << turkey->gobble() << " and " << turkey->fly() << endl;
	
	ITurkey* fake_turkey = new FakeTurkey;
	cout << "FAKE TURKEY: " << fake_turkey->gobble() << " and " << fake_turkey->fly() << endl << endl;

	//Class adapter for wild turkey
	IDuck* class_adapter = new ClassAdapter;
	cout << "ADAPTED WILD TURKEY: " << class_adapter->quack() << " and " << class_adapter->fly() << endl << endl;
	
	//Classes adapter for fake and wild turkey
	IDuck* classes_adapter = new ManyClassesAdapter(fake_turkey);
	cout << "INTERFACE ADAPTED TURKEY (FAKE): " << classes_adapter->quack() << " and " << classes_adapter->fly() << endl;
	
	classes_adapter = new ManyClassesAdapter(turkey);
	cout << "INTERFACE ADAPTED TURKEY (WILD): " << classes_adapter->quack() << " and " << classes_adapter->fly();
	
	return 0;
}