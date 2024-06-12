#include "RemoteLogMessage.h"
#include <iostream>

int main()
{
    messaging::RemoteLogMessage rlm{ 700, messaging::RemoteLogMessage::LogLevel::DebugLevel, "How to print a % number?", 7474 };
}