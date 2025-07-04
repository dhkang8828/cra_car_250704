#pragma once
#include <iostream>
#include <vector>
#include "type.h"
using namespace std;

class ICarType {
public:
	virtual void setType() = 0;
	virtual string getType() = 0;
	virtual int getTypeID() = 0;
	virtual ~ICarType() = default;
protected:
	string type;
	int typeID;
};

class Sedan : public ICarType {
public:
	void setType() override { this->type = "SEDAN"; typeID = SEDAN; }
	string getType() override { return this->type;  }
	int getTypeID() override { return this->typeID; }
};

class Suv : public ICarType {
public:
	void setType() override { this->type = "SUV"; typeID = SUV; }
	string getType() override { return this->type; }
	int getTypeID() override { return this->typeID; }
};

class Truck : public ICarType {
public:
	void setType() override { this->type = "TRUCK"; typeID = TRUCK; }
	string getType() override { return this->type; }
	int getTypeID() override { return this->typeID; }
};

class IEngine {
public:
	virtual void setEngine() = 0;
	virtual string getEngine() = 0;
	virtual int getEngineID() = 0;
	virtual ~IEngine() = default;
protected:
	string engine;
	int engineID;
};

class Gm : public IEngine {
public:
	void setEngine() override { this->engine = "GM"; engineID = GM; }
	string getEngine() override { return this->engine; }
	int getEngineID() override { return this->engineID; }
};

class Toyota : public IEngine {
public:
	void setEngine() override { this->engine = "TOYOTA"; engineID = TOYOTA; }
	string getEngine() override { return this->engine; }
	int getEngineID() override { return this->engineID; }
};

class Wia : public IEngine {
public:
	void setEngine() override { this->engine = "WIA"; engineID = WIA; }
	string getEngine() override { return this->engine; }
	int getEngineID() override { return this->engineID; }
};

class Broken : public IEngine {
public:
	void setEngine() override { this->engine = "BROKEN"; engineID = BROKEN; }
	string getEngine() override { return this->engine; }
	int getEngineID() override { return this->engineID; }
};

class IBreakSystem {
public:
	virtual void setBreakSystem() = 0;
	virtual string getBreakSystem() = 0;
	virtual int getBreakSystemID() = 0;
	virtual ~IBreakSystem() = default;
protected:
	string breakSystem;
	int breakSystemID;
};

class Mando : public IBreakSystem {
public:
	void setBreakSystem() override { this->breakSystem = "MANDO"; breakSystemID = MANDO; }
	string getBreakSystem() override { return this->breakSystem; }
	int getBreakSystemID() override { return breakSystemID; }
};

class Continental : public IBreakSystem {
public:
	void setBreakSystem() override { this->breakSystem = "CONTINENTAL"; breakSystemID = CONTINENTAL; }
	string getBreakSystem() override { return this->breakSystem; }
	int getBreakSystemID() override { return breakSystemID; }
};

class Bosch_B : public IBreakSystem {
public:
	void setBreakSystem() override { this->breakSystem = "BOSCH_B"; breakSystemID = BOSCH_B; }
	string getBreakSystem() override { return this->breakSystem; }
	int getBreakSystemID() override { return breakSystemID; }
};

class ISteeringSystem {
public:
	virtual void setSteer() = 0;
	virtual string getSteer() = 0;
	virtual int getSteerID() = 0;
	virtual ~ISteeringSystem() = default;
protected:
	string steer;
	int steerID;
};

class Bosch_S : public ISteeringSystem {
public:
	void setSteer() override { this->steer = "BOSCH_S"; steerID = BOSCH_S; }
	string getSteer() override { return this->steer; }
	int getSteerID() override { return steerID; }
};

class Mobis : public ISteeringSystem {
public:
	void setSteer() override { this->steer = "MOBIS"; steerID = MOBIS; }
	string getSteer() override { return this->steer; }
	int getSteerID() override { return steerID; }
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
	bool validationCheck();
	void RunAssembledCar();
	void TestAssembledCar();
	
	unique_ptr<Car> car;
	int step;
	int answer;
};

