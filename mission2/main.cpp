#include <iostream>
#ifdef _DEBUG

#include "gmock/gmock.h"
#include "CarAssemble.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

int main()
{
  
}

#endif