#include <sstream>
#include <climits>
#include <iostream>
#include <algorithm>
#include <cstring>

namespace messaging
{
    constexpr std::size_t MAX_LOG_MESSAGE_LENGTH = 100;
    constexpr char VARIABLE_KEY{ '%' };
    
    using MessageAttribute = std::uint8_t;

    enum class MessageID : std::uint16_t 
    {
        LOG_DATA,
    };

    enum class CommandType : uint16_t
		{
			G = 0,  // Get
			S = 1,  // Set
			R = 2,  // Response
			N = 3,  // Notify
			UNKNOWN = 255
		};

    enum class MessageSubject : uint8_t
    {
        UNKNOWN_SUBJECT 		= 255,
    };

    enum class DataType : uint8_t
    {
        BYTE    = 0,
        SHORT   = 1,
        LONG    = 2,
        BLOCK   = 3,
        FLOAT   = 4,
        UNKNOWN = 255
    };

    struct MessageExtension
    {
        MessageID  messageCode;
        std::uint8_t control{ 0 };
        std::uint8_t version{ 1 };
    };

    struct MessageHeader
    {
        std::uint32_t 	 magicNumber1{ 0x12345678 };
        std::uint32_t  	 magicNumber2{ 0x9ABCDEF0 };
        MessageExtension extension;
        std::uint32_t 	 messageLength; // Length of message  in bytes not including MessageHeader
        std::uint32_t	 messageUniqueId;
    };

    struct MessageContentHeader
    {
        CommandType    commandType;
        std::uint16_t  numOfAttributes;
    };

    struct MessageContent
    {
        MessageSubject 		subject;
        MessageAttribute   	attribute;
        std::uint8_t   		index;
        DataType       		dataType;   
        std::uint32_t  		dataLength { 0 }; 
    };

    class Message
    {
    public:
        Message() = default;
        
        explicit Message(MessageID _id)
        {
            m_header.extension.messageCode = _id;
        }	
    
        ~Message() = default;

        void SetDataLength(const uint32_t _dataLength)
        {
            m_header.messageLength = GetMetaDataLengthWithoutHeader() + _dataLength;
            m_content.dataLength = _dataLength;
        }

        uint32_t GetTotalMessageLength()
        {
            return GetMetaDataLength() + m_content.dataLength;
        }

        void SetMessageUniqueID(const uint32_t _uniqueId)
        {
            m_header.messageUniqueId = _uniqueId;
        }

        uint32_t GetMessageUniqueID() const
        {
            return m_header.messageUniqueId;
        }

        MessageID GetMessageID() const
        {
            return m_header.extension.messageCode;
        }

        MessageSubject GetSubject() const { return m_content.subject; }
        MessageAttribute GetAttribute() const { return m_content.attribute; }
        void SetAttribute(const MessageAttribute _attribute) { m_content.attribute = _attribute; }
        CommandType GetCommand() const { return m_contentHeader.commandType; }
        void SetCommand(const CommandType _command) { m_contentHeader.commandType = _command; }

    protected:
        MessageHeader 		 m_header{};
        MessageContentHeader m_contentHeader{};
        MessageContent		 m_content{};

    private:
        std::uint32_t GetMetaDataLength() { return sizeof(Message);}
        std::uint32_t GetMetaDataLengthWithoutHeader() { return sizeof(Message) - sizeof(MessageHeader);}
    };

    class RemoteLogMessage : public Message
    {
    public:
        enum class LogLevel : std::int32_t
        {
            ErrorLevel = 0,
            WarningLevel = 1,
            DebugLevel = 2,
            UNKNOWN = INT_MAX
        };

        template <class ...Args>
        RemoteLogMessage(const std::int32_t _messageId,
            const LogLevel _severity, const std::string& _format, Args&&... _args)
            : m_messageType{ _severity }
            , m_messageID{ _messageId }
        {
            m_header.extension.messageCode = MessageID::LOG_DATA;
            m_contentHeader.commandType = CommandType::N;
            m_contentHeader.numOfAttributes = 1;
            m_content.subject = MessageSubject::UNKNOWN_SUBJECT;
            m_content.attribute = 0;
            m_content.index = 0;
            m_content.dataType = DataType::BLOCK;

            auto str = Format(_format, std::forward<Args>(_args)...);
            if (str.size() == 0)
            {
                m_numberOfElementsToRead = 0;
            }
            else
            {
                m_numberOfElementsToRead = (str.size() < MAX_LOG_MESSAGE_LENGTH - 1) ? static_cast<std::int32_t>(str.size() + 1) : MAX_LOG_MESSAGE_LENGTH;
            }
            
            std::memcpy(m_logData, str.c_str(), m_numberOfElementsToRead);

            SetDataLength(static_cast<std::uint32_t>(sizeof(m_messageType) + sizeof(m_messageID) + sizeof(m_numberOfElementsToRead) + sizeof(m_logData)));
        }

        ~RemoteLogMessage() = default;

        std::int32_t GetMessageID() const { return m_messageID; }
        LogLevel GetLogLevel() const { return m_messageType; }
        std::string GetLogText() { return std::string{ reinterpret_cast<char*>(m_logData) }; }
        std::int32_t GetLogMessageLength() const { return m_numberOfElementsToRead; }
        static std::size_t GetMaxLogMessageLength() { return 100; }

    private:
        template<class Tuple, std::size_t N>
        struct TuplePrinter
        {
            static void Print(const std::string& _format, std::ostream& _os, const Tuple& _t)
            {
                const size_t idx = _format.find_last_of(VARIABLE_KEY);
                TuplePrinter<Tuple, N - 1>::Print(std::string(_format, 0, idx), _os, _t);
                _os << std::get<N - 1>(_t) << std::string(_format, idx + 1);
            }
        };

        template<class Tuple>
        struct TuplePrinter<Tuple, 1>
        {
            static void Print(const std::string& _format, std::ostream& _os, const Tuple& _t)
            {
                const size_t idx = _format.find_first_of(VARIABLE_KEY);
                _os << std::string(_format, 0, idx) << std::get<0>(_t) << std::string(_format, idx + 1);
            }
        };

        template<class... Args>
        std::string Format(const std::string& _format, Args&&... _args)
        {
            std::stringstream ss;

            if constexpr (sizeof...(_args) == 0)
            {
                ss << _format;
            }
            else
            {
                if (IsFormatValid(_format, sizeof...(_args)))
                {
                    if (_format.find_last_of(VARIABLE_KEY) != _format.npos)
                    {
                        const auto t = std::make_tuple(std::forward<Args>(_args)...);
                        TuplePrinter<decltype(t), sizeof...(Args)>::Print(_format, ss, t);
                    }
                }
            }

            return ss.str();
        }

        bool IsFormatValid(const std::string& _format, int _numberOfArguments)
        {
            return(std::count(_format.begin(), _format.end(), VARIABLE_KEY) == _numberOfArguments);
        }

        LogLevel m_messageType{ LogLevel::UNKNOWN };
        std::int32_t m_messageID{ 0 };
        std::int32_t m_numberOfElementsToRead{ 0 };
        std::uint8_t m_logData[MAX_LOG_MESSAGE_LENGTH]{ 0 };
    };
}
