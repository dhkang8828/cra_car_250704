#include <iostream>
#include "CarAssemble.h"
#ifdef _DEBUG

#include "gmock/gmock.h"
int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}
#else
int main()
{
    CarAssembler assembler;
    assembler.doAssemble();
}
#endif