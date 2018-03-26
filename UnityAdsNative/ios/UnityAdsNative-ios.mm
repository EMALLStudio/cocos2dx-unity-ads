//
//  UnityAdsNative-ios.mm
//  UnityAds2Demo
//
//  Created by Solomon Li on 7/15/16.
//  (c) EM ALL Studio, 2018
//
//

#import "../UnityAdsNative.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#import "UnityAdsBridge.h"

USING_NS_CC;

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
  NSLog(@"[UnityAds] UnityAdsInit");
    
  UnityAdsBridge* bridge = [UnityAdsBridge new];
  NSString* gameId = [NSString stringWithFormat:@"%s", parameter];
  [UnityAds initialize:gameId delegate:bridge testMode:testMode];
}

bool UnityAdsNative::isReady (const char* parameter) 
{
  NSString* placementId = [NSString stringWithFormat:@"%s", parameter];
  NSLog(@"[UnityAds] UnityAdsIsReady for placement=%@", placementId);
  return [UnityAds isReady:placementId];
}

void UnityAdsNative::show (const char* parameter) 
{
  NSString* placementId = [NSString stringWithFormat:@"%s", parameter];
  [UnityAds show:[UnityAdsBridge viewController] placementId:placementId];
}

// Unity Ads assist methods
bool UnityAdsNative::getDebugMode()
{
  NSLog(@"[UnityAds] UnityAdsGetDebugMode");
  return [UnityAds getDebugMode];
}

UnityAdsNativePlacementState UnityAdsNative::getPlacementState(const char* parameter)
{
  NSLog(@"[UnityAds] UnityAdsGetPlacementState");
  UnityAdsPlacementState state = [UnityAds getPlacementState];
  return static_cast<UnityAdsNativePlacementState>(state);
}

std::string UnityAdsNative::getVersion() 
{
  NSLog(@"[UnityAds] UnityAdsGetVersion");
  std::string ret = std::string([[UnityAds getVersion] UTF8String]);
  return ret;
}

bool UnityAdsNative::isInitialized()
{
  NSLog(@"[UnityAds] UnityAdsIsInitialized");
  return [UnityAds isInitialized];
}

bool UnityAdsNative::isSupported()
{
  NSLog(@"[UnityAds] UnityAdsIsSupported");
  return [UnityAds isSupported];
}

void UnityAdsNative::setDebugMode(bool debugMode)
{
  NSLog(@"[UnityAds] UnityAdsSetDebugMode");
  [UnityAds setDebugMode:debugMode];
}

#endif // CC_PLATFORM_IOS
