#ifndef CC_ASSERT_REDEFINE_H
#define CC_ASSERT_REDEFINE_H

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//Redefine CC_ASSERT for Android. Crashlytics logging added.

#ifdef CC_ASSERT
#undef CC_ASSERT
#endif

#ifdef CC_NO_MESSAGE_PSEUDOASSERT
#undef CC_NO_MESSAGE_PSEUDOASSERT
#endif

#ifdef CC_MESSAGE_PSEUDOASSERT
#undef CC_MESSAGE_PSEUDOASSERT
#endif

#include <android/log.h>
#include "crashlytics-sdk/CrashlyticsSdk.h"

#define CC_NO_MESSAGE_PSEUDOASSERT(cond)                        \
    if (!(cond)) {                                              \
        __android_log_print(ANDROID_LOG_ERROR,                  \
                            "cocos2d-x assert",                 \
                            "%s function:%s line:%d",           \
                            __FILE__, __FUNCTION__, __LINE__);  \
        CrashlyticsSdk::getInstance().log(StringUtils::format("[assert] %s function:%s line:%d", __FILE__, __FUNCTION__, __LINE__)); \
    }

#define CC_MESSAGE_PSEUDOASSERT(cond, msg)                          \
    if (!(cond)) {                                                  \
        __android_log_print(ANDROID_LOG_ERROR,                      \
                            "cocos2d-x assert",                     \
                            "file:%s function:%s line:%d, %s",      \
                            __FILE__, __FUNCTION__, __LINE__, msg); \
        CrashlyticsSdk::getInstance().log(StringUtils::format("[assert] file:%s function:%s line:%d, %s", __FILE__, __FUNCTION__, __LINE__, msg.c_str())); \
    }

#define CC_ASSERT(cond) CC_NO_MESSAGE_PSEUDOASSERT(cond)

#endif //CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//Redefine CC_ASSERT for iOS. Crashlytics logging added.
#ifdef NDEBUG

#ifdef CC_ASSERT
#undef CC_ASSERT
#endif //CC_ASSERT

#define CC_ASSERT(cond)                                                                                                              \
    if (!(cond)) {                                                                                                                   \
        CrashlyticsSdk::getInstance().log(StringUtils::format("[assert] %s function:%s line:%d", __FILE__, __FUNCTION__, __LINE__)); \
    }

#endif //NDEBUG

#endif //CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#endif //CC_ASSERT_REDEFINE_H
