#include "gmock/gmock.h"
#include "CarAssemble.h"
#include <iostream>

class CarPartsTest : public ::testing::Test {
    CarAssembler assembler;
};

class MockUserInput : public IUserInput {
public:
    MOCK_METHOD(char*, getInput, (), (override));
};

class CarAssembleTest : public ::testing::Test {
protected:
    MockUserInput mockInput;
    CarAssembler* assembler;

    void SetUp() override {
        assembler = new CarAssembler(&mockInput);
    }

    void TearDown() override {
        delete assembler;
    }
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


TEST_F(CarAssembleTest, RunTestTC1) {
    
    EXPECT_CALL(mockInput, getInput())
        .Times(6)
        .WillOnce(::testing::Return(const_cast<char*>("1")))
        .WillOnce(::testing::Return(const_cast<char*>("1")))
        .WillOnce(::testing::Return(const_cast<char*>("1")))
        .WillOnce(::testing::Return(const_cast<char*>("1")))
        .WillOnce(::testing::Return(const_cast<char*>("1")))
        .WillOnce(::testing::Return(const_cast<char*>("exit")));
       
    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_PASS);
    
}

TEST_F(CarAssembleTest, RunTestTC2) {

    EXPECT_CALL(mockInput, getInput())
        .Times(6)
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("2")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("exit")));

    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_PASS);
}

TEST_F(CarAssembleTest, RunTestTC3) {

    EXPECT_CALL(mockInput, getInput())
        .Times(6)
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("2")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("exit")));

    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_FAIL);
}

TEST_F(CarAssembleTest, RunTestTC4) {

    EXPECT_CALL(mockInput, getInput())
        .Times(6)
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("2")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("2")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("exit")));

    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_FAIL);
}

TEST_F(CarAssembleTest, RunTestTC5) {

    EXPECT_CALL(mockInput, getInput())
        .Times(6)
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("3")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("exit")));

    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_PASS);
}

TEST_F(CarAssembleTest, RunTestTC6) {

    EXPECT_CALL(mockInput, getInput())
        .Times(6)
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("3")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("2")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("exit")));

    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_FAIL);
}

TEST_F(CarAssembleTest, RunTestTC7) {

    EXPECT_CALL(mockInput, getInput())
        .Times(6)
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("2")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("exit")));

    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_PASS);
}

TEST_F(CarAssembleTest, RunTestTC8) {

    EXPECT_CALL(mockInput, getInput())
        .Times(6)
        .WillOnce(::testing::Return(const_cast<char*>("2")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("2")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("exit")));

    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_FAIL);
}

TEST_F(CarAssembleTest, RunTestTC9) {

    EXPECT_CALL(mockInput, getInput())
        .Times(6)
        .WillOnce(::testing::Return(const_cast<char*>("3")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("3")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("exit")));

    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_FAIL);
}

TEST_F(CarAssembleTest, RunTestTC10) {

    EXPECT_CALL(mockInput, getInput())
        .Times(6)
        .WillOnce(::testing::Return(const_cast<char*>("3")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("exit")));

    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_FAIL);
}

TEST_F(CarAssembleTest, RunTestTC11) {

    EXPECT_CALL(mockInput, getInput())
        .Times(6)
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("2")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("exit")));

    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_PASS);
}

TEST_F(CarAssembleTest, RunTestTC12) {

    EXPECT_CALL(mockInput, getInput())
        .Times(7)
        .WillOnce(::testing::Return(const_cast<char*>("qqq")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("exit")));

    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_PASS);
}

TEST_F(CarAssembleTest, RunTestTC13) {

    EXPECT_CALL(mockInput, getInput())
        .Times(7)
        .WillOnce(::testing::Return(const_cast<char*>("8")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("4")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("exit")));

    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_FAIL);
}

TEST_F(CarAssembleTest, RunTestTC14) {

    EXPECT_CALL(mockInput, getInput())
        .Times(6)
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("4")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("exit")));

    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_FAIL);
}

TEST_F(CarAssembleTest, RunTestTC15) {

    EXPECT_CALL(mockInput, getInput())
        .Times(11)
        .WillOnce(::testing::Return(const_cast<char*>("8")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("9")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("9")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("9")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("9")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("exit")));

    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_PASS);
}

TEST_F(CarAssembleTest, RunTestTC16) {

    EXPECT_CALL(mockInput, getInput())
        .Times(11)
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("0")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("exit")));

    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_PASS);
}

TEST_F(CarAssembleTest, RunTestTC17) {

    EXPECT_CALL(mockInput, getInput())
        .Times(8)
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Type: Sedan, SUV, TRUCK
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Engine: GM, TOYOTA, WIA, BROKEN
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("0")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Break: MANDO, CONTINENTAL, BOSHC_B
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Steer:: BOSHC_S, MOBIS
        .WillOnce(::testing::Return(const_cast<char*>("1")))    //Test Run: RUN, Test
        .WillOnce(::testing::Return(const_cast<char*>("exit")));

    CarAssembler assembler(&mockInput);
    assembler.doAssemble();
    int testResult = assembler.GetTestResult();
    EXPECT_EQ(testResult, TEST_PASS);
}


