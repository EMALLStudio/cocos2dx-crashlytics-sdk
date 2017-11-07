#ifndef __CRASHLYTICS_SDK_H__
#define __CRASHLYTICS_SDK_H__

#include "cocos2d.h"
#include <memory>
#include <mutex>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

class CrashlyticsSdk {
    public:
    virtual ~CrashlyticsSdk();
    /**
    @brief Get the current instance.
    @return Current instance pointer.
    */
    static CrashlyticsSdk& getInstance();

    /**
    @brief Register current user
    @param identifier Many of our customers have requested the ability to tie crashes to specific end-users of their application in order to facilitate responses to support requests or permit the ability to reach out for more information.
    @param name Optionally set a end-user's name or username for display within the Crashlytics UI.
    @param email Optionally set a end-user's name or username for display within the Crashlytics UI.
    */
    void registerUser(const std::string &identifier, const std::string &name, const std::string &email);

    /**
    @brief Sets key and value which will be associated with crash data.
    @param key Key for your crash data.
    @param value Value to be associated with a given key for your crash data.
    */
    void set(const std::string &key, const std::string &value);

    /**
    @brief Add text logging that will be sent with your next report.
    @param message string.
    */
    void log(const std::string &message);
    
    private:
    /// instance ptr
    static std::unique_ptr<CrashlyticsSdk> m_instance;

    /// thread-safe flag
    static std::once_flag m_onceFlag;

    /// constructors and etc.
    CrashlyticsSdk(void);
    CrashlyticsSdk(const CrashlyticsSdk& src);
    CrashlyticsSdk& operator=(const CrashlyticsSdk& rhs);
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#endif // __CRASHLYTICS_SDK_H__