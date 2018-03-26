//
//  UnityAdsNative.h
//  UnityAds2Demo
//
//  (c) EM ALL Studio, 2018
//
//

#ifndef __UNITYADSNATIVE_H_
#define __UNITYADSNATIVE_H_

#include "cocos2d.h"
#include <memory>
#include <mutex>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

/**
 *  An enumerate that describes the state of `UnityAds` placements. 
 *  @note All placement states, other than `kUnityAdsPlacementStateReady`, indicate that the placement is not currently ready to show ads.
 */
enum UnityAdsNativePlacementState {
    /**
     *  A state that indicates that the placement is ready to show an ad. The `show:` selector can be called.
     */
    kUnityAdsNativePlacementStateReady,
    /**
     *  A state that indicates that no state is information is available.
     *  @warning This state can that UnityAds is not initialized or that the placement is not correctly configured in the Unity Ads admin tool.
     */
    kUnityAdsNativePlacementStateNotAvailable,
    /**
     *  A state that indicates that the placement is currently disabled. The placement can be enabled in the Unity Ads admin tools.
     */
    kUnityAdsNativePlacementStateDisabled,
    /**
     *  A state that indicates that the placement is not currently ready, but will be in the future.
     *  @note This state most likely indicates that the ad content is currently caching.
     */
    kUnityAdsNativePlacementStateWaiting,
    /**
     *  A state that indicates that the placement is properly configured, but there are currently no ads available for the placement.
     */
    kUnityAdsNativePlacementStateNoFill
};

/**
 *  An enumeration for the completion state of an ad.
 */
enum UnityAdsNativeFinishState {
    /**
     *  A state that indicates that the ad did not successfully display.
     */
    kUnityAdsNativeFinishStateError,
    /**
     *  A state that indicates that the user skipped the ad.
     */
    kUnityAdsNativeFinishStateSkipped,
    /**
     *  A state that indicates that the ad was played entirely.
     */
    kUnityAdsNativeFinishStateCompleted
};

/**
 *  An enumeration for the various errors that can be emitted through the `UnityAdsDelegate` `unityAdsDidError:withMessage:` method.
 */
enum UnityAdsNativeError {
    /**
     *  An error that indicates failure due to `UnityAds` currently being uninitialized.
     */
    kUnityAdsNativeErrorNotInitialized = 0,
    /**
     *  An error that indicates failure due to a failure in the initialization process.
     */
    kUnityAdsNativeErrorInitializedFailed,
    /**
     *  An error that indicates failure due to attempting to initialize `UnityAds` with invalid parameters.
     */
    kUnityAdsNativeErrorInvalidArgument,
    /**
     *  An error that indicates failure of the video player.
     */
    kUnityAdsNativeErrorVideoPlayerError,
    /**
     *  An error that indicates failure due to having attempted to initialize the `UnityAds` class in an invalid environment.
     */
    kUnityAdsNativeErrorInitSanityCheckFail,
    /**
     *  An error that indicates failure due to the presence of an ad blocker.
     */
    kUnityAdsNativeErrorAdBlockerDetected,
    /**
     *  An error that indicates failure due to inability to read or write a file.
     */
    kUnityAdsNativeErrorFileIoError,
    /**
     *  An error that indicates failure due to a bad device identifier.
     */
    kUnityAdsNativeErrorDeviceIdError,
    /**
     *  An error that indicates a failure when attempting to show an ad.
     */
    kUnityAdsNativeErrorShowError,
    /**
     *  An error that indicates an internal failure in `UnityAds`.
     */
    kUnityAdsNativeErrorInternalError,
};

class UnityAdsNative {
    public:
    virtual ~UnityAdsNative();
    /**
    @brief Get the current application instance.
    @return Current application instance pointer.
    */
    static UnityAdsNative& GetInstance();

    // Unity Ads required methods
    void init(const char* parameter, bool testMode);
    bool isReady (const char* parameter);
    void show (const char* parameter);

    // Unity Ads assist methods
    bool getDebugMode();
    UnityAdsNativePlacementState getPlacementState(const char* parameter);
    std::string getVersion();
    bool isInitialized();
    bool isSupported();
    void setDebugMode(bool debugMode);

    private:
    /// instance ptr
    static std::unique_ptr<UnityAdsNative> m_instance;

    /// thread-safe flag
    static std::once_flag m_onceFlag;

    /// constructors and etc.
    UnityAdsNative(void);
    UnityAdsNative(const UnityAdsNative& src);
    UnityAdsNative& operator=(const UnityAdsNative& rhs);
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#endif // __UNITYADSNATIVE_H_
