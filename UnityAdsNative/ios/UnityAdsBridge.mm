//
//  UnityAdsBridge.m
//  UnityAds2Demo
//
//  Created by Solomon Li on 7/15/16.
//  Updated by EM ALL Studio, 2018
//
//

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#import "UnityAdsBridge.h"
#import "AppController.h"

@implementation UnityAdsBridge

+ (UIViewController* ) viewController {
    
    UIApplication* app = [UIApplication sharedApplication];
    AppController* controller = (AppController*)[app delegate];
    UIViewController* rootController = [controller.window rootViewController];
    return rootController;
}

#pragma mark -
#pragma mark UnityAdsDelegate

- (void)unityAdsReady:(NSString *)placementId {
  NSLog(@"[UnityAds delegate] unityAdsReady with placementId=%@", placementId);
  std::string ret = std::string([placementId UTF8String]);
  // Send start event
  cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("unity_ads_ready", (void *) &ret);
  });    
}

- (void)unityAdsDidError:(UnityAdsError)error withMessage:(NSString *)message{
  NSLog(@"[UnityAds delegate] unityAdsDidError with message=%@ , and error=%ld", message, error);
  std::string ret = std::string([message UTF8String]);
  // Send error event
  cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("unity_ads_error", (void *) &ret);
  });      
}

- (void)unityAdsDidStart:(NSString *)placementId{
  std::string ret = std::string([placementId UTF8String]);
  // Send start event
  cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("unity_ads_start", (void *) &ret);
  });
}

- (void)unityAdsDidFinish:(NSString *)placementId
          withFinishState:(UnityAdsFinishState)state{
  // Send reward event
  cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("unity_ads_finish", (void *) &state);
  });
}

@end

#endif