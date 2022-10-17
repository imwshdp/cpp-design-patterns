#include <iostream>
#include <string>

#define NUMCOMMANDS 10

using namespace std;

//Command interface
class ICommand {
	
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
};

//Light class
class Light {
	
private:
	string description;
	
public:
	Light(string description) {
		this->description = description;
	}
	string getDescription() {
		return description;
	}
	void on() {
		cout << getDescription() << ": " << "Light is on" << endl;
	}
	void off() {
		cout << getDescription() << ": " << "Light is off" << endl;
	}
	~Light() {}
};

//Light command class
class LightOnCommand: public ICommand {
	
private:
	Light* light;
	
public:
	LightOnCommand(Light* light) {
		this->light = light;
	}
	void execute() {
		light->on();
	}
	void undo() {
		light->off();
	}
	~LightOnCommand() {
		light = NULL;
	}
};

//Light command class
class LightOffCommand: public ICommand {
	
private:
	Light* light;
	
public:
	LightOffCommand(Light* light) {
		this->light = light;
	}
	void execute() {
		light->off();
	}
	void undo() {
		light->on();
	}
	~LightOffCommand() {
		light = NULL;
	}
};

//Garage class
class Garage {

private:
	string description;
	
public:
	Garage(string description) {
		this->description = description;
	}
	string getDescription() {
		return description;
	}
	void up() {
		cout << getDescription() << ": " << "Garage door is open" << endl;	
	}
	void down() {
		cout << getDescription() << ": " << "Garage door is closed" << endl;	
	}
	void lightOn() {
		cout << getDescription() << ": " << "Garage light is on" << endl;
	}
	void lightOff() {
		cout << getDescription() << ": " << "Garage light is off" << endl;
	}
	~Garage() {}
};

//Garage command class
class GarageLightOnCommand: public ICommand {
	
private:
	Garage* garage;
	
public:
	GarageLightOnCommand(Garage* garage) {
		this->garage = garage;
	}
	void execute() {
		garage->lightOn();
	}
	void undo() {
		garage->lightOff();
	}
	~GarageLightOnCommand() {
		garage = NULL;
	}
};

//Garage command class
class GarageLightOffCommand: public ICommand {
	
private:
	Garage* garage;
	
public:
	GarageLightOffCommand(Garage* garage) {
		this->garage = garage;
	}
	void execute() {
		garage->lightOff();
	}
	void undo() {
		garage->lightOn();
	}
	~GarageLightOffCommand() {
		garage = NULL;
	}
};

//Garage command class
class GarageDoorOpenCommand: public ICommand {
	
private:
	Garage* garage;
	
public:
	GarageDoorOpenCommand(Garage* garage) {
		this->garage = garage;
	}
	void execute() {
		garage->up();
	}
	void undo() {
		garage->down();
	}
	~GarageDoorOpenCommand() {
		garage = NULL;
	}
};

//Garage command class
class GarageDoorCloseCommand: public ICommand {
	
private:
	Garage* garage;
	
public:
	GarageDoorCloseCommand(Garage* garage) {
		this->garage = garage;
	}
	void execute() {
		garage->down();
	}
	void undo() {
		garage->up();
	}
	~GarageDoorCloseCommand() {
		garage = NULL;
	}
};

//Main controller class (with on/off command lists and undo command)
class RemoteControl: public ICommand {
	
private:
	ICommand** onCommands;
	ICommand** offCommands;
	ICommand* undoCommand;

public:
	RemoteControl() {
		onCommands = new ICommand*[NUMCOMMANDS];
		offCommands = new ICommand*[NUMCOMMANDS];
		
		for(auto i = 0; i < NUMCOMMANDS; i++) {
			onCommands[i] = 0;
			offCommands[i] = 0;
			undoCommand = 0;
		}
	}
	
	void setCommand(int slot, ICommand* newOnCommand, ICommand* newOffCommand) {
		onCommands[slot] = newOnCommand;
		offCommands[slot] = newOffCommand;
	}
	void pressOnButton(int slot) {
		onCommands[slot]->execute();
		undoCommand = onCommands[slot];
	}
	void pressOffButton(int slot) {
		offCommands[slot]->execute();
		undoCommand = offCommands[slot];
	}
	void pressUndoButton(int slot) {
		undoCommand->undo();
	}
	void execute() {}
	void undo() {}
	
	~RemoteControl() {
		delete onCommands;
		delete offCommands;
	}
};

//Main loader class
class remoteLoader {

public:
	remoteLoader() {}
	static void loader() {
		
		int LIGHT = 0;
		int GARAGELIGHT = 1;
		int GARAGEDOOR = 2;
		
		RemoteControl* remote = new RemoteControl();
		
		Light* light = new Light("Living room");
		Garage* garage = new Garage("Car garage");
		
		LightOnCommand* lightOn = new LightOnCommand(light);
		LightOffCommand* lightOff = new LightOffCommand(light);
		
		GarageLightOnCommand* GarageLightOn = new GarageLightOnCommand(garage);
		GarageLightOffCommand* GarageLightOff = new GarageLightOffCommand(garage);
		
		GarageDoorOpenCommand* GarageDoorOpen = new GarageDoorOpenCommand(garage);
		GarageDoorCloseCommand* GarageDoorClose = new GarageDoorCloseCommand(garage);
		
		remote->setCommand(LIGHT, lightOn, lightOff);
		remote->setCommand(GARAGELIGHT, GarageLightOn, GarageLightOff);
		remote->setCommand(GARAGEDOOR, GarageDoorOpen, GarageDoorClose);
		
		cout << "LIGHT IN: " << light->getDescription() << endl;
		remote->pressOnButton(LIGHT);
		remote->pressOffButton(LIGHT);
		cout << "UNDO: ";
		remote->pressUndoButton(LIGHT);
		
		cout << endl << "LIGHT IN: " << garage->getDescription() << endl;
		remote->pressOnButton(GARAGELIGHT);
		remote->pressOffButton(GARAGELIGHT);
		cout << "UNDO: ";
		remote->pressUndoButton(GARAGELIGHT);
		
		cout << endl << "DOOR IN: " << garage->getDescription() << endl;
		remote->pressOnButton(GARAGEDOOR);
		remote->pressOffButton(GARAGEDOOR);
		cout << "UNDO: ";
		remote->pressUndoButton(GARAGEDOOR);		
		return;
	}
	~remoteLoader() {}
};

int main() {

	remoteLoader* loader = new remoteLoader();
	loader->loader();
	
	return 0;
}