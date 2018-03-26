/**
 * Dummy class, (c) EM ALL Studio, 2018
 */

#include "../UnityAdsNative.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID) && (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)

std::unique_ptr<UnityAdsNative> UnityAdsNative::m_instance;
std::once_flag UnityAdsNative::m_onceFlag;

UnityAdsNative::UnityAdsNative()
{
}

UnityAdsNative::~UnityAdsNative()
{    
}

UnityAdsNative& UnityAdsNative::GetInstance()
{
    std::call_once(m_onceFlag,
        [] {
            m_instance.reset(new UnityAdsNative);
    });
    return *m_instance.get();
}

// Unity Ads required methods
void UnityAdsNative::init(const char* parameter, bool testMode)
{
    // nop
}

bool UnityAdsNative::isReady (const char* parameter) 
{
    return false;
}

void UnityAdsNative::show (const char* parameter) 
{
    // nop
}

// Unity Ads assist methods
bool UnityAdsNative::getDebugMode()
{
    return false;
}

UnityAdsNativePlacementState UnityAdsNative::getPlacementState(const char* parameter) 
{
    return UnityAdsNativePlacementState::kUnityAdsNativePlacementStateNotAvailable;
}

std::string UnityAdsNative::getVersion() 
{
    return "";
}

bool UnityAdsNative::isInitialized()
{
    return false;
}

bool UnityAdsNative::isSupported()
{
    return false;
}

void UnityAdsNative::setDebugMode(bool debugMode)
{
    // nop
}

#endif // (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID) && (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)