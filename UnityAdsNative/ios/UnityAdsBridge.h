//
//  UnityAdsBridge.h
//  UnityAds2Demo
//
//  Created by Solomon Li on 7/15/16.
//
//

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#import <Foundation/Foundation.h>
#import <UnityAds/UnityAds.h>


@interface UnityAdsBridge : UIViewController<UnityAdsDelegate>

+ (UIViewController* ) viewController;

@end

#endif