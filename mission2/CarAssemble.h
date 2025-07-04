#pragma once
#include <iostream>
#include <vector>
#include "type.h"
using namespace std;

class ICarType {
public:
	virtual void setType() = 0;
	virtual string getType() = 0;
	virtual ~ICarType() = default;
protected:
	string type;
};

class Sedan : public ICarType {
public:
	void setType() override { this->type = "SEDAN"; }
	string getType() override { return this->type;  }
};

class Suv : public ICarType {
public:
	void setType() override { this->type = "SUV"; }
	string getType() override { return this->type; }
};

class Truck : public ICarType {
public:
	void setType() override { this->type = "TRUCK"; }
	string getType() override { return this->type; }
};

class IEngine {
public:
	virtual void setEngine() = 0;
	virtual string getEngine() = 0;
	virtual ~IEngine() = default;
protected:
	string engine;
};

class Gm : public IEngine {
public:
	void setEngine() override { this->engine = "GM"; }
	string getEngine() override { return this->engine; }
};

class Toyota : public IEngine {
public:
	void setEngine() override { this->engine = "TOYOTA"; }
	string getEngine() override { return this->engine; }
};

class Wia : public IEngine {
public:
	void setEngine() override { this->engine = "WIA"; }
	string getEngine() override { return this->engine; }
};

class IBreakSystem {
public:
	virtual void setBreakSystem() = 0;
	virtual string getBreakSystem() = 0;
	virtual ~IBreakSystem() = default;
protected:
	string breakSystem;
};

class Mando : public IBreakSystem {
public:
	void setBreakSystem() override { this->breakSystem = "MANDO"; }
	string getBreakSystem() override { return this->breakSystem; }
};

class Continental : public IBreakSystem {
public:
	void setBreakSystem() override { this->breakSystem = "CONTINENTAL"; }
	string getBreakSystem() override { return this->breakSystem; }
};

class Bosch_B : public IBreakSystem {
public:
	void setBreakSystem() override { this->breakSystem = "BOSCH_B"; }
	string getBreakSystem() override { return this->breakSystem; }
};

class ISteeringSystem {
public:
	virtual void setSteer() = 0;
	virtual string getSteer() = 0;
	virtual ~ISteeringSystem() = default;
protected:
	string steer;
};

class Bosch_S : public ISteeringSystem {
public:
	void setSteer() override { this->steer = "BOSCH_S"; }
	string getSteer() override { return this->steer; }
};

class Mobis : public ISteeringSystem {
public:
	void setSteer() override { this->steer = "MOBIS"; }
	string getSteer() override { return this->steer; }
};

class Car
{
public:
	std::unique_ptr<ICarType> carType;
	std::unique_ptr<IEngine> carEngine;
	std::unique_ptr<IBreakSystem> carBreak;
	std::unique_ptr<ISteeringSystem> carSteer;

	void PrintCarInfo() {
		cout << "CarType: " << carType->getType() << endl;
		cout << "Engine: " << carEngine->getEngine() << endl;
		cout << "BreakSystem: " << carBreak->getBreakSystem() << endl;
		cout << "SteeringSystem: " << carSteer->getSteer() << endl;
	}
};

class CarAssembler
{
public:
	CarAssembler() : step(0), answer(0) {
		car = make_unique<Car>();
	}
	void printMenu();
	int CheckInputException();
	void doAssemble(); 
	bool isValidInput();
	void printInputHelpMsg();
	
	void AssembleCar();
	void selectCarType();
	void selectEngine();
	void selectBreakSystem();
	void selectSteeringSystem();
	void RunAssembledCar();
	void TestAssembledCar();
	
	unique_ptr<Car> car;
	int step;
	int answer;
};

