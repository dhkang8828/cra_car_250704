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
    char buf[128] = { 0, };
    fgets(buf, sizeof(buf), stdin);

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

    default:
        printf("Unknown Step");
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
    default:
        return false;
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
    default:
        printf("Unexpected step.");
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

    default:
        cout << "Unknown carType" << endl;
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
        
    default:
        cout << "Unknown carEngine" << endl;
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
    default:
        cout << "Unknown Break System" << endl;
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

    default:
        cout << "Unknown carSteer " << endl;
        break;
    }
    car->carSteer->setSteer();
}

void CarAssembler::RunAssembledCar() {

}

void CarAssembler::TestAssembledCar() {

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

    default:
        printf("Unknown step.");
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
