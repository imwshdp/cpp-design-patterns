#include <iostream>

using namespace std;

//Miers Singleton class
class ChocolateBoiler {

protected:
	ChocolateBoiler() {
		empty = true;
		boiled = false;
	}
	~ChocolateBoiler() {}
	ChocolateBoiler(const ChocolateBoiler&);
	ChocolateBoiler& operator=(const ChocolateBoiler&);

private:
	bool empty;
	bool boiled;
	
public:
	static ChocolateBoiler& Instance() {
		static ChocolateBoiler singleton;
		return singleton;
	}
	bool isEmpty() {
		return empty;
	}
	bool isBoiled() {
		return boiled;
	}
	void fill() {
		if(isEmpty() && !isBoiled()) {
			empty = false;
			boiled = false;
			cout << "Boiler filled." << endl;
		}
	}
	
	void boil() {
		if(!isEmpty() && !isBoiled()) {
			boiled = true;
			cout << "Boiler boiled." << endl;
		}
	}
	
	void drain() {
		if(!isEmpty() && isBoiled()) {
			empty = true;
			boiled = false;
			cout << "Boiler drained." << endl;
		}
	}
};

int main() {
	
	cout << "Boiler status:" << endl;
	cout << "Boiiler emptiness: " << ChocolateBoiler::Instance().isEmpty() << endl;
	cout << "Boiiler boiling: " << ChocolateBoiler::Instance().isBoiled() << endl << endl;
	
	ChocolateBoiler::Instance().fill();
	
	cout << endl << "Boiler status after filling:" << endl;
	cout << "Boiiler emptiness: " << ChocolateBoiler::Instance().isEmpty() << endl;
	cout << "Boiiler boiling: " << ChocolateBoiler::Instance().isBoiled() << endl << endl;
	
	ChocolateBoiler::Instance().boil();
	
	cout << endl << "Boiler status after boiling:" << endl;
	cout << "Boiiler emptiness: " << ChocolateBoiler::Instance().isEmpty() << endl;
	cout << "Boiiler boiling: " << ChocolateBoiler::Instance().isBoiled() << endl << endl;
	
	ChocolateBoiler::Instance().drain();
	
	cout << endl << "Boiler status after drainig:" << endl;
	cout << "Boiiler emptiness: " << ChocolateBoiler::Instance().isEmpty() << endl;
	cout << "Boiiler boiling: " << ChocolateBoiler::Instance().isBoiled() << endl;

	getchar();
	
	return 0;
}

