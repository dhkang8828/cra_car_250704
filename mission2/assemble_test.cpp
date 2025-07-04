#include "gmock/gmock.h"
#include "CarAssemble.h"
#include <iostream>

class CarPartsTest : public ::testing::Test {
    CarAssembler assembler;
};

// CarType 테스트
TEST_F(CarPartsTest, CarTypeSetAndGet) {
    Sedan sedan;
    sedan.setType();
    EXPECT_EQ(sedan.getType(), "SEDAN");
    EXPECT_EQ(sedan.getTypeID(), SEDAN);

    Suv suv;
    suv.setType();
    EXPECT_EQ(suv.getType(), "SUV");
    EXPECT_EQ(suv.getTypeID(), SUV);

    Truck truck;
    truck.setType();
    EXPECT_EQ(truck.getType(), "TRUCK");
    EXPECT_EQ(truck.getTypeID(), TRUCK);
}

// Engine 테스트
TEST_F(CarPartsTest, EngineSetAndGet) {
    Gm gm;
    gm.setEngine();
    EXPECT_EQ(gm.getEngine(), "GM");
    EXPECT_EQ(gm.getEngineID(), GM);

    Toyota toyota;
    toyota.setEngine();
    EXPECT_EQ(toyota.getEngine(), "TOYOTA");
    EXPECT_EQ(toyota.getEngineID(), TOYOTA);

    Wia wia;
    wia.setEngine();
    EXPECT_EQ(wia.getEngine(), "WIA");
    EXPECT_EQ(wia.getEngineID(), WIA);

    Broken broken;
    broken.setEngine();
    EXPECT_EQ(broken.getEngine(), "BROKEN");
    EXPECT_EQ(broken.getEngineID(), BROKEN);
}

// BreakSystem 테스트
TEST_F(CarPartsTest, BreakSystemSetAndGet) {
    Mando mando;
    mando.setBreakSystem();
    EXPECT_EQ(mando.getBreakSystem(), "MANDO");
    EXPECT_EQ(mando.getBreakSystemID(), MANDO);
    
    Continental continental;
    continental.setBreakSystem();
    EXPECT_EQ(continental.getBreakSystem(), "CONTINENTAL");
    EXPECT_EQ(continental.getBreakSystemID(), CONTINENTAL);

    Bosch_B bosch;
    bosch.setBreakSystem();
    EXPECT_EQ(bosch.getBreakSystem(), "BOSCH_B");
    EXPECT_EQ(bosch.getBreakSystemID(), BOSCH_B);
}

// SteeringSystem 테스트
TEST_F(CarPartsTest, SteeringSystemSetAndGet) {
    Bosch_S bosch;
    bosch.setSteer();
    EXPECT_EQ(bosch.getSteer(), "BOSCH_S");
    EXPECT_EQ(bosch.getSteerID(), BOSCH_S);

    Mobis mobis;
    mobis.setSteer();
    EXPECT_EQ(mobis.getSteer(), "MOBIS");
    EXPECT_EQ(mobis.getSteerID(), MOBIS);
}

