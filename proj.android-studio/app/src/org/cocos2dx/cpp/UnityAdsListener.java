package org.cocos2dx.cpp;

import android.util.Log;

import com.unity3d.ads.IUnityAdsListener;
import com.unity3d.ads.UnityAds;
import com.unity3d.ads.log.DeviceLog;

/**
 * Created by solomonli on 7/8/16.
 * (c) EM ALL Studio, 2018.
 */
public class UnityAdsListener implements IUnityAdsListener {

    @Override
    public void onUnityAdsReady(final String placementId) {
        DeviceLog.debug("[UnityAdsListener] onUnityAdsReady for placement: " + placementId);
        UnityAdsJNI.adsReady(placementId);
    }

    @Override
    public void onUnityAdsStart(String placementId) {
        DeviceLog.debug("[UnityAdsListener] onUnityAdsStart for placement: " + placementId);
        UnityAdsJNI.adsStart(placementId);        
    }

    @Override
    public void onUnityAdsFinish(String placementId, UnityAds.FinishState result) {
        DeviceLog.debug("[UnityAdsListener] onUnityAdsFinish with FinishState: " + result.name() + " for placement: " + placementId);
        UnityAdsJNI.adsFinish(placementId, result.ordinal());
    }

    @Override
    public void onUnityAdsError(UnityAds.UnityAdsError error, String message) {
        DeviceLog.debug("[UnityAdsListener] onUnityAdsError with message: " + message);
        UnityAdsJNI.adsError(message);        
    }
}
