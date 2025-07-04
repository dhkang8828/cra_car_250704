#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

int stack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

enum FLOW_CONTROL {
    LOOP_BREAK = -1,
    LOOP_CONTINUE = -2,
};

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA
};

enum brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS
};

void delay(int ms)
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

void printMenu(int step) {
    printf(CLEAR_SCREEN);
    switch (step) {
    
    case CarType_Q:
        printf("        ______________\n");
        printf("       /|            | \n");
        printf("  ____/_|_____________|____\n");
        printf(" |                      O  |\n");
        printf(" '-(@)----------------(@)--'\n");
        printf("===============================\n");
        printf("� ���� Ÿ���� �����ұ��?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
        break;

    case Engine_Q:
        printf("� ������ ž���ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. ���峭 ����\n");
        break;

    case brakeSystem_Q:
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
        break;

    case SteeringSystem_Q:
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
        break;

    case Run_Test:
        printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
        printf("� ������ �ұ��?\n");
        printf("0. ó�� ȭ������ ���ư���\n");
        printf("1. RUN\n");
        printf("2. Test\n");
        break;

    default:
        printf("Unknown Step");
        break;
    }//switch
}

int CheckInputException(void) {
    char buf[128] = {0, };
    fgets(buf, sizeof(buf), stdin);

    // ���� ���๮�� ����
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);

    if (!strcmp(buf, "exit"))
    {
        printf("���̹���\n");
        return LOOP_BREAK;
    }

    // ���ڷ� �� ������� Ȯ��
    char* checkNumber;
    int answer = strtol(buf, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ

    // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
    if (*checkNumber != '\0')
    {
        printf("ERROR :: ���ڸ� �Է� ����\n");
        delay(800);
        return LOOP_CONTINUE;
    }

    return answer;
    
}

bool isValidInput(int step, int answer) {
    switch (step) {
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

void printInputHelpMsg(int step) {
    switch (step) {
    case CarType_Q:
        printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
        break;
    case Engine_Q:
        printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
        break;
    case brakeSystem_Q:
        printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
        break;
    case SteeringSystem_Q:
        printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
        break;
    case Run_Test:
        printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
        break;
    default:
        printf("Unexpected step.");
        break;
    }//switch
}

void doAssemble(int *step, int answer) {

    switch (*step) {
    case CarType_Q:
        selectCarType(answer);
        delay(800);
        *step = Engine_Q;
        break;

    case Engine_Q:
        selectEngine(answer);
        delay(800);
        *step = brakeSystem_Q;
        break;
        
    case brakeSystem_Q:
        selectbrakeSystem(answer);
        delay(800);
        *step = SteeringSystem_Q;
        break;

    case SteeringSystem_Q:
        selectSteeringSystem(answer);
        delay(800);
        *step = Run_Test;
        break;

    case Run_Test:
        if (answer == 1) {
            runProducedCar();
            delay(2000);
        }
        else if (answer == 2) {
            printf("Test...\n");
            delay(1500);
            testProducedCar();
            delay(2000);
        }
        break;

    default:
        printf("Unknown step.");
        break;
    }//switch
    
}

int main()
{
    char buf[100];
    int step = CarType_Q;
    int answer = 0;

    while (1)
    {
        printMenu(step);
        printf("===============================\n");

        printf("INPUT > ");
        answer = CheckInputException();
        if (answer == LOOP_BREAK) {
            break;
        }
        else if (answer == LOOP_CONTINUE) {
            continue;
        }

        if (!isValidInput(step, answer)) {
            printInputHelpMsg(step);
            delay(800);
            continue;
        }

        // ó������ ���ư���
        if (answer == 0 && step == Run_Test)
        {
            step = CarType_Q;
            continue;
        }

        // �������� ���ư���
        if (answer == 0 && step >= 1)
        {
            step -= 1;
            continue;
        }

        doAssemble(&step, answer);
    }
}

void selectCarType(int answer)
{
    stack[CarType_Q] = answer;
    if (answer == SEDAN)
        printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
    if (answer == SUV)
        printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
    if (answer == TRUCK)
        printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}

void selectEngine(int answer)
{
    stack[Engine_Q] = answer;
    if (answer == GM)
        printf("GM ������ �����ϼ̽��ϴ�.\n");
    if (answer == TOYOTA)
        printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
    if (answer == WIA)
        printf("WIA ������ �����ϼ̽��ϴ�.\n");
}

void selectbrakeSystem(int answer)
{
    stack[brakeSystem_Q] = answer;
    if (answer == MANDO)
        printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == CONTINENTAL)
        printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == BOSCH_B)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

void selectSteeringSystem(int answer)
{
    stack[SteeringSystem_Q] = answer;
    if (answer == BOSCH_S)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == MOBIS)
        printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
}

int isValidCheck()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        return false;
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        return false;
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else
    {
        if (stack[Engine_Q] == 4)
        {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        }
        else
        {
            if (stack[CarType_Q] == SEDAN)
                printf("Car Type : Sedan\n");
            if (stack[CarType_Q] == SUV)
                printf("Car Type : SUV\n");
            if (stack[CarType_Q] == TRUCK)
                printf("Car Type : Truck\n");

            if (stack[Engine_Q] == GM)
                printf("Engine : GM\n");
            if (stack[Engine_Q] == TOYOTA)
                printf("Engine : TOYOTA\n");
            if (stack[Engine_Q] == WIA)
                printf("Engine : WIA\n");


            if (stack[brakeSystem_Q] == MANDO)
                printf("Brake System : Mando");
            if (stack[brakeSystem_Q] == CONTINENTAL)
                printf("Brake System : Continental\n");
            if (stack[brakeSystem_Q] == BOSCH_B)
                printf("Brake System : Bosch\n");

            if (stack[SteeringSystem_Q] == BOSCH_S)
                printf("SteeringSystem : Bosch\n");
            if (stack[SteeringSystem_Q] == MOBIS)
                printf("SteeringSystem : Mobis\n");

            printf("�ڵ����� ���۵˴ϴ�.\n");
        }
    }
}

void testProducedCar()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
    }
    else
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
    }
}

#endif