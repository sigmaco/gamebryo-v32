#ifndef __NETMETRICSDESTINATION_H
#define __NETMETRICSDESTINATION_H

#include "ILogDestination.h"

#include <efd/asserts.h>
#include <efd/utf8string.h>

namespace efd
{

class ILogger;

/**
   NetMetricsDestination: A custom log destination for aggregating network performance metrics and 
   reporting on them.
 */
class EE_EFD_ENTRY NetMetricsDestination : public ILogDestination
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(NetMetricsDestination, efd::kCLASSID_NetMetricsDestination, ILogDestination);
    EE_DECLARE_CONCRETE_REFCOUNT;

    /// @endcond

public:
    // Constructor
    NetMetricsDestination(const efd::utf8string& name, const efd::utf8string& fileName);

    // Destructor
    virtual ~NetMetricsDestination();

private:
    // Hide default constructor, copy constructor and assignment operator
    NetMetricsDestination();
    NetMetricsDestination(const NetMetricsDestination& src);
    NetMetricsDestination& operator=(const NetMetricsDestination& src);

    // Timestamps, for reporting values over time
    efd::TimeType m_startTime;
    efd::TimeType m_finishTime;

    // Specific metrics entry data storage members
    efd::UInt32 m_sentBytesTotal;
    efd::UInt32 m_receivedBytesTotal;
    efd::UInt32 m_sentMessageCount;
    efd::UInt32 m_receivedMessageCount;
    efd::UInt32 m_networkEnvelopeHeader;
    efd::UInt32 m_networkEnvelopeTotal;
    efd::UInt32 m_replicationMessagesSent;
    efd::UInt32 m_replicationMessagesReceived;

    typedef efd::map<efd::utf8string, efd::UInt8> MetricsKeyMap;
    MetricsKeyMap m_metricsKeyMap;

    efd::utf8string m_fileName;

    // Implementation of ILogDestination interface
    virtual efd::Bool OnInit();
    virtual void LogMessage(
        efd::Bool assert,
        const char* timeStampMachine,
        efd::TimeType timeStampGame,
        const char* pModule,
        const char* pLevel,
        const char* pFile,
        efd::SInt32 line,
        const char* pMsg);

    virtual void BeginLog(
        efd::Bool assert,
        const char* timeStampMachine,
        efd::TimeType timeStampGame,
        const char* pModule,
        const char* pLevel,
        const char* pFile,
        efd::SInt32 line);

    virtual void ContinueLog(const char* pMsg);
    virtual void EndLog();
    virtual void Flush();

};

#include "NetMetricsDestination.inl"

/// Define a smart pointer (reference counting, self deleting pointer) for the NetMetricsDestination
/// class.
typedef efd::SmartPointer<NetMetricsDestination> NetMetricsDestinationPtr;

} // namespace efd

#endif // __NETMETRICSDESTINATION_H
