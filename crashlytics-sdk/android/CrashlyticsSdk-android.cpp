#include "../CrashlyticsSdk.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "crashlytics.h"

USING_NS_CC;

std::unique_ptr<CrashlyticsSdk> CrashlyticsSdk::m_instance;
std::once_flag CrashlyticsSdk::m_onceFlag;

/// Crashlytics context
crashlytics_context_t* ctx = nullptr;
   
CrashlyticsSdk::CrashlyticsSdk()
{
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([&](){
        ctx = crashlytics_init();
    });
}

CrashlyticsSdk::~CrashlyticsSdk()
{
    crashlytics_free(&ctx);
    ctx = nullptr;
}

void CrashlyticsSdk::registerUser(const std::string &identifier, const std::string &name, const std::string &email)
{
    if (ctx != nullptr) 
    {
        if (identifier.length() > 0)
        {
            ctx->set_user_identifier(ctx, identifier.c_str());
        }
        if (name.length() > 0)
        {
            ctx->set_user_name(ctx, name.c_str());
        }
        if (email.length() > 0)
        {
            ctx->set_user_email(ctx, email.c_str());
        }        
    }
}

void CrashlyticsSdk::set(const std::string &key, const std::string &value)
{
    if (ctx != nullptr && key.length() > 0 && value.length() > 0)
    {
        ctx->set(ctx, key.c_str(), value.c_str());
    }
}


void CrashlyticsSdk::log(const std::string &message)
{    
    if (ctx != nullptr && message.length() > 0)
    {
        ctx->log(ctx, message.c_str());
    }    
}

CrashlyticsSdk& CrashlyticsSdk::getInstance()
{
    std::call_once(m_onceFlag,
        [] {
            m_instance.reset(new CrashlyticsSdk);
    });
    return *m_instance.get();
}

#endif // CC_PLATFORM_ANDROID