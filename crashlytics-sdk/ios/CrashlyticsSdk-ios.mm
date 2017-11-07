#import "../CrashlyticsSdk.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#import <Crashlytics/Crashlytics.h>

USING_NS_CC;

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
    if (identifier.length() > 0)
    {
        [CrashlyticsKit setUserIdentifier: [NSString stringWithUTF8String:identifier.c_str()]];
    }
    if (name.length() > 0)
    {
        [CrashlyticsKit setUserEmail: [NSString stringWithUTF8String:name.c_str()]];
    }
    if (email.length() > 0)
    {
        [CrashlyticsKit setUserName: [NSString stringWithUTF8String:email.c_str()] ];
    }
}

void CrashlyticsSdk::set(const std::string &key, const std::string &value)
{
    [CrashlyticsKit setObjectValue: [NSString stringWithUTF8String:key.c_str()] forKey:[NSString stringWithUTF8String:value.c_str()]];
}


void CrashlyticsSdk::log(const std::string &message)
{
    CLS_LOG("%@", [NSString stringWithUTF8String:message.c_str()]);
}

CrashlyticsSdk& CrashlyticsSdk::getInstance()
{
    std::call_once(m_onceFlag,
        [] {
            m_instance.reset(new CrashlyticsSdk);
    });
    return *m_instance.get();
}

#endif // CC_PLATFORM_IOS
