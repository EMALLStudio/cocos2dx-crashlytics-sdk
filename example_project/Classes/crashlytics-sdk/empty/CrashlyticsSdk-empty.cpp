/**
 * Dummy class
 */

#include "../CrashlyticsSdk.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID) && (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)

std::unique_ptr<CrashlyticsSdk> CrashlyticsSdk::m_instance;
std::once_flag CrashlyticsSdk::m_onceFlag;

CrashlyticsSdk::CrashlyticsSdk()
{
}

CrashlyticsSdk::~CrashlyticsSdk()
{
}

void CrashlyticsSdk::registerUser(const std::string &identifier, const std::string &name, const std::string &email)
{
}

void CrashlyticsSdk::set(const std::string &key, const std::string &value)
{
}


void CrashlyticsSdk::log(const std::string &message)
{    
}

CrashlyticsSdk& CrashlyticsSdk::getInstance()
{
    std::call_once(m_onceFlag,
        [] {
            m_instance.reset(new CrashlyticsSdk);
    });
    return *m_instance.get();
}

#endif // (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID) && (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)