#include <iostream>
#include <string>
#include <list>

using namespace std;

//Observer interface
class IObserver {
	
public:
	virtual void update(float temp, float humidity, float pressure) = 0;	
};

//Subject interface (server-handler, notifying abonents)
class ISubject {
	
public:
	virtual void registerObserver(IObserver* o) = 0;
	virtual void removeObserver(IObserver* o) = 0;
	virtual void notifyObservers() = 0;
};

//Displayer interface (ex: sensor for output)
class IDisplayer {
	
public:	
	virtual void display() = 0;
};

//WeatherData class (database with abonents list and weather data)
class WeatherData : public ISubject {

private:	
	list<IObserver*> observers;
	float temperature, humidity, pressure;

public:
	WeatherData() {  }
	
	//adding and removing new abonent functions
	void registerObserver(IObserver* o) override { observers.push_back(o); }	
	void removeObserver(IObserver* o) override { observers.remove(o); }
	
	//updating data function (for all abonents)
	void notifyObservers() override {
		for(auto i = observers.begin(); i != observers.end(); i++) {				
			(*i)->update(temperature, humidity, pressure);		
		}	
	}
	
	//notifying abonents if new data received
	void measurementsChanged() { notifyObservers(); }
	
	//new data saving function
	void setMeasurements(float temperature, float humidity, float pressure) {		
		this->temperature = temperature;
		this->humidity = humidity;
		this->pressure = pressure;	
		measurementsChanged();		
	}
	
	~WeatherData() {
		observers.clear();	
	}
};

//Abonent class
class CurrentConditionsDisplay : public IObserver, IDisplayer {

private:
	float temperature, humidity;
	WeatherData* weatherData;
	
public:
	
	//Connecting to weather data
	CurrentConditionsDisplay(WeatherData* weatherData) {	
		this->weatherData = weatherData;
		(*weatherData).registerObserver(this);	
	}
	
	//Update data
	void update(float temperature, float humidity, float pressure) override {	
		this->temperature = temperature;
		this->humidity = humidity;	
		display();	
	}
	
	//Data output
	void display() override {	
		cout << "Current condition: " << temperature << "F degrees and " << humidity << "% humidity" << endl;	
	}
	
	~CurrentConditionsDisplay() {
		weatherData = NULL;		
	}
};

//Forecast abonent class
class ForecastDisplay : public IObserver, IDisplayer {
	
private:
	float currentPressure;
	float lastPressure;
	WeatherData* weatherData;
	
public:
	
	//Connecting to weather data
	ForecastDisplay(WeatherData* weatherData) {	
		this->weatherData = weatherData;
		(*weatherData).registerObserver(this);	
	}
	
	//Update data
	void update(float temp, float humidity, float pressure) override {	
		lastPressure = currentPressure;
		currentPressure = pressure;
		display();	
	}
	
	//Data output
	void display() override {
		if (currentPressure > lastPressure) {	
			cout << "Improving weather on the way!" << endl;
		} else if (currentPressure == lastPressure) {
			cout << "More of the same" << endl;
		} else if (currentPressure < lastPressure) {
			cout << "Watch out for cooler, rainy weather" << endl;
		}	
	}
	
	~ForecastDisplay() {
		weatherData = NULL;	
	}
};


int main() {
	
	WeatherData* WeatherDataCenter = new WeatherData;
	
	ForecastDisplay * fd = new ForecastDisplay(WeatherDataCenter);
	
	CurrentConditionsDisplay * ccd = new CurrentConditionsDisplay(WeatherDataCenter);
	
	WeatherDataCenter->setMeasurements(80,65,30.4);
	cout << endl;
	
	WeatherDataCenter->setMeasurements(82,70,29.2);
	cout << endl;
	
	WeatherDataCenter->setMeasurements(78,90,29.2);
	cout << endl;
	
	//Delete abonent
	WeatherDataCenter->removeObserver(fd);
	
	WeatherDataCenter->setMeasurements(62,90,28.1);

	return 0;
}
