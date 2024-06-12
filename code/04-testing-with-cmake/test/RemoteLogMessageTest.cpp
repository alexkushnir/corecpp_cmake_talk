#include "../src/RemoteLogMessage.h"

#include <string>

using namespace messaging;

namespace 
{
	template<class ...Args>
	RemoteLogMessage CreateLogMessage(const std::string& _format, Args&&... _args)
	{
		return RemoteLogMessage{ 777, RemoteLogMessage::LogLevel::DebugLevel, _format, std::forward<Args>(_args)... };
	}

    void VerifyMetaData(const RemoteLogMessage& _message)
	{
		if ((_message.GetMessageID() != 777) || (_message.GetLogLevel() != RemoteLogMessage::LogLevel::DebugLevel))
        {
            std::exit(1);
        }
	}
}

void NoArguments()
{
	const std::string testString{ "This is a test message without arguments" };
		
	auto rlm = CreateLogMessage(testString);
	VerifyMetaData(rlm);
    
	if (rlm.GetLogText() != testString)
    {
        std::exit(1);
    }
}

void VariadicArguments()
{
	std::tuple<std::int32_t, std::string, char> testTuple = std::make_tuple(123, "A string", 'x');
	std::stringstream expectedResultStream;
	expectedResultStream << "A " << std::get<0>(testTuple) << " variadic " << std::get<1>(testTuple) << 
        " message " << std::get<2>(testTuple) << " for test";

	auto rlm = CreateLogMessage("A % variadic % message % for test", 
        std::get<0>(testTuple), std::get<1>(testTuple), std::get<2>(testTuple));
	VerifyMetaData(rlm);

	if(expectedResultStream.str() != rlm.GetLogText())
    {
        std::exit(1);
    }
}

int main()
{
    NoArguments();
    VariadicArguments();
    return 0;
}