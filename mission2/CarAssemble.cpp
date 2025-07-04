#include "CarAssemble.h"

#define CLEAR_SCREEN "\033[H\033[2J"

static void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

int CarAssembler::CheckInputException() {
    char buf[64] = { 0, };
    strcpy_s(buf, sizeof(buf), input->getInput());

    // 엔터 개행문자 제거
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);

    if (!strcmp(buf, "exit"))
    {
        printf("바이바이\n");
        return LOOP_BREAK;
    }

    // 숫자로 된 대답인지 확인
    char* checkNumber;
    int _answer = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환

    // 입력받은 문자가 숫자가 아니라면
    if (*checkNumber != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        delay(800);
        return LOOP_CONTINUE;
    }

    return _answer;
}

void CarAssembler::printMenu() {
    printf(CLEAR_SCREEN);
    switch (this->step) {

    case CarType_Q:
        printf("        ______________\n");
        printf("       /|            | \n");
        printf("  ____/_|_____________|____\n");
        printf(" |                      O  |\n");
        printf(" '-(@)----------------(@)--'\n");
        printf("===============================\n");
        printf("어떤 차량 타입을 선택할까요?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
        break;

    case Engine_Q:
        printf("어떤 엔진을 탑재할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. 고장난 엔진\n");
        break;

    case brakeSystem_Q:
        printf("어떤 제동장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
        break;

    case SteeringSystem_Q:
        printf("어떤 조향장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
        break;

    case Run_Test:
        printf("멋진 차량이 완성되었습니다.\n");
        printf("어떤 동작을 할까요?\n");
        printf("0. 처음 화면으로 돌아가기\n");
        printf("1. RUN\n");
        printf("2. Test\n");
        break;
    }//switch
}

bool CarAssembler::isValidInput() {
    switch (this->step) {
    case CarType_Q:
        return answer >= 1 && answer <= 3;
    case Engine_Q:
        return answer >= 0 && answer <= 4;
    case brakeSystem_Q:
        return answer >= 0 && answer <= 3;
    case SteeringSystem_Q:
        return answer >= 0 && answer <= 2;
    case Run_Test:
        return answer >= 0 && answer <= 2;
    }//switch
}

void CarAssembler::printInputHelpMsg() {
    switch (step) {
    case CarType_Q:
        printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
        break;
    case Engine_Q:
        printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
        break;
    case brakeSystem_Q:
        printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
        break;
    case SteeringSystem_Q:
        printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
        break;
    case Run_Test:
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
        break;
    }//switch
}

void CarAssembler::selectCarType() {
    switch (answer) { 
    case SEDAN:
        cout << "Select carType = Sedan" << endl;
        car->carType = make_unique<Sedan>();
        break;
       
    case SUV:
        cout << "Select carType = SUV" << endl;
        car->carType = make_unique<Suv>();
        break;

    case TRUCK:
        cout << "Select carType = Truck" << endl;
        car->carType = make_unique<Truck>();
        break;
    }
    car->carType->setType();
}

void CarAssembler::selectEngine() {
    switch (answer) {
    case GM:
        cout << "Select carEngin: GM" << endl;
        car->carEngine = make_unique<Gm>();
        break;

    case TOYOTA:
        cout << "Select carEngin: Toyoya" << endl;
        car->carEngine = make_unique<Toyota>();
        break;

    case WIA:
        cout << "Select carEngin: WIA" << endl;
        car->carEngine = make_unique<Wia>();
        break;
    
    case BROKEN:
        cout << "Select carEngin: BROKEN" << endl;
        car->carEngine = make_unique<Broken>();
        break;
     
    }
    car->carEngine->setEngine();
}

void CarAssembler::selectBreakSystem() {
    switch (answer) {
    case MANDO:
        cout << "Select carBreakSystem: MANDON" << endl;
        car->carBreak = make_unique<Mando>();
        break;
    case CONTINENTAL:
        cout << "Select carBreakSystem: CONTINENTAL" << endl;
        car->carBreak = make_unique<Continental>();
        break;
    case BOSCH_B:
        cout << "Select carBreakSystem: BOSCH_B" << endl;
        car->carBreak = make_unique<Bosch_B>();
        break;
    }
    car->carBreak->setBreakSystem();
}

void CarAssembler::selectSteeringSystem() {
    switch (answer) {
    case BOSCH_S:
        cout << "Select carSteer: BOSCH_S" << endl;
        car->carSteer = make_unique<Bosch_S>();
        break;

    case MOBIS:
        cout << "Select carSteer: MOBIS" << endl;
        car->carSteer = make_unique<Mobis>();
        break;
    }
    car->carSteer->setSteer();
}

bool CarAssembler::validationCheck() {
    int carID = car->carType->getTypeID();
    int carEngineID = car->carEngine->getEngineID();
    int carBreakID = car->carBreak->getBreakSystemID();
    int carSteerID = car->carSteer->getSteerID();

    if (carID == SEDAN && carBreakID == CONTINENTAL) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
        return false;
    }
    else if (carID == SUV && carEngineID == TOYOTA) {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
        return false;
    }
    else if (carID == TRUCK && carEngineID == WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
        return false;
    }
    else if (carID == TRUCK && carBreakID == MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
        return false;
    }
    else if (carBreakID == BOSCH_B && carSteerID != BOSCH_S)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
        return false;
    }
    else
    {
        testResult = TEST_PASS;
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
        return true;
    }
}

void CarAssembler::RunAssembledCar() {

    if (!validationCheck()) {
        cout << "자동차가 동작하지 않습니다." << endl;
        testResult = TEST_FAIL;
    }
    else { 
        if (car->carEngine->getEngineID() == BROKEN) {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
            testResult = TEST_FAIL;
        }
        else {
            car->PrintCarInfo();
            cout << "자동차 정상 작동." << endl;
            testResult = TEST_PASS;
        }
    }
}

void CarAssembler::TestAssembledCar() {
    validationCheck();
}

void CarAssembler::AssembleCar() {
    switch (step) {
    case CarType_Q:
        selectCarType();
        delay(800);
        step = Engine_Q;
        break;

    case Engine_Q:
        selectEngine();
        delay(800);
        step = brakeSystem_Q;
        break;

    case brakeSystem_Q:
        selectBreakSystem();
        delay(800);
        step = SteeringSystem_Q;
        break;

    case SteeringSystem_Q:
        selectSteeringSystem();
        delay(800);
        step = Run_Test;
        break;

    case Run_Test:
        if (answer == 1) {
            RunAssembledCar();
            delay(2000);
        }
        else if (answer == 2) {
            printf("Test...\n");
            delay(1500);
            TestAssembledCar();
            delay(2000);
        }
        break;

    }//switch
}

void CarAssembler::doAssemble() {
    char buf[100];
    this->step = CarType_Q;
    this->answer = 0;

    while (1)
    {
        printMenu();
        printf("===============================\n");

        printf("INPUT > ");
        answer = CheckInputException();
        if (answer == LOOP_BREAK) {
            break;
        }
        else if (answer == LOOP_CONTINUE) {
            continue;
        }

        if (!isValidInput()) {
            printInputHelpMsg();
            delay(800);
            continue;
        }

        // 처음으로 돌아가기
        if (answer == 0 && step == Run_Test)
        {
            step = CarType_Q;
            continue;
        }

        // 이전으로 돌아가기
        if (answer == 0 && step >= 1)
        {
            step -= 1;
            continue;
        }
        AssembleCar();
    }
}
