//
//  UnityAdsNative-android.cpp
//  UnityAds2Demo
//
//  Created by Solomon Li on 7/15/16.
//  (c) EM ALL Studio, 2018
//
//

#include "../UnityAdsNative.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform/android/jni/JniHelper.h"

#define LOG_TAG "UnityAdsNative"

#define JNI_FUNC_PREFIX(func) Java_org_cocos2dx_cpp_UnityAdsJNI_##func

#define CLASS_NAME "org/cocos2dx/cpp/UnityAdsJNI"

USING_NS_CC;

std::unique_ptr<UnityAdsNative> UnityAdsNative::m_instance;
std::once_flag UnityAdsNative::m_onceFlag;

UnityAdsNative::UnityAdsNative()
{
}

UnityAdsNative::~UnityAdsNative()
{
}

UnityAdsNative &UnityAdsNative::GetInstance()
{
  std::call_once(m_onceFlag,
                 [] {
                   m_instance.reset(new UnityAdsNative);
                 });
  return *m_instance.get();
}

// Unity Ads required methods
void UnityAdsNative::init(const char *parameter, bool testMode)
{
  JniHelper::callStaticVoidMethod(CLASS_NAME, "UnityAdsInitialize", parameter, testMode);
}

bool UnityAdsNative::isReady(const char *parameter)
{
  return JniHelper::callStaticBooleanMethod(CLASS_NAME, "UnityAdsIsReady", parameter);
}

void UnityAdsNative::show(const char *parameter)
{
  JniHelper::callStaticVoidMethod(CLASS_NAME, "UnityAdsShow", parameter);
}

// Unity Ads assist methods
bool UnityAdsNative::getDebugMode()
{
  return JniHelper::callStaticBooleanMethod(CLASS_NAME, "UnityAdsGetDebugMode");
}

UnityAdsNativePlacementState UnityAdsNative::getPlacementState(const char *parameter)
{
  return static_cast<UnityAdsNativePlacementState>(JniHelper::callStaticIntMethod(CLASS_NAME, "UnityAdsGetPlacementState", parameter));
}

std::string UnityAdsNative::getVersion()
{
  return JniHelper::callStaticStringMethod(CLASS_NAME, "UnityAdsGetVersion");
}

bool UnityAdsNative::isInitialized()
{
  return JniHelper::callStaticBooleanMethod(CLASS_NAME, "UnityAdsIsInitialized");
}

bool UnityAdsNative::isSupported()
{
  return JniHelper::callStaticBooleanMethod(CLASS_NAME, "UnityAdsIsSupported");
}

void UnityAdsNative::setDebugMode(bool debugMode)
{
  JniHelper::callStaticVoidMethod(CLASS_NAME, "UnityAdsSetDebugMode", debugMode);
}

extern "C" 
{

  JNIEXPORT void JNICALL JNI_FUNC_PREFIX(adsFinish)(JNIEnv *env, jobject thiz, jstring placementId, jint finishState)
  {
    UnityAdsNativeFinishState finishStateResult = static_cast<UnityAdsNativeFinishState>(finishState);

    std::string ret = JniHelper::jstring2string(placementId);

    CCLOG("%s finish. Placement id = %s", LOG_TAG, ret.c_str());

    // Send ads finish event
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
      Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("unity_ads_finish", (void *) &finishStateResult);
    });
  }

  JNIEXPORT void JNICALL JNI_FUNC_PREFIX(adsReady)(JNIEnv *env, jobject jobj, jstring placementId)
  {
    std::string ret = JniHelper::jstring2string(placementId);

    CCLOG("%s ready. Placement id = %s", LOG_TAG,  ret.c_str());

    // Send ads ready event
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
      Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("unity_ads_ready", (void *) &ret);
    });
  }

  JNIEXPORT void JNICALL JNI_FUNC_PREFIX(adsStart)(JNIEnv *env, jobject thiz, jstring placementId)
  {
    std::string ret = JniHelper::jstring2string(placementId);

    CCLOG("%s start. Placement id = %s", LOG_TAG, ret.c_str());

    // Send ads start event
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
      Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("unity_ads_start", (void *) &ret);
    });
  }

  JNIEXPORT void JNICALL JNI_FUNC_PREFIX(adsError)(JNIEnv *env, jobject jobj, jstring message)
  {
    std::string ret = JniHelper::jstring2string(message);

    CCLOG("%s Error. Error string = %s", LOG_TAG, ret.c_str());

    // Send ads error event
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
      Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("unity_ads_error", (void *) &ret);
    });
  }
}
#endif // CC_PLATFORM_ANDROID