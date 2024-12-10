/****************************************************************************
 Copyright (c) 2024 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/
#include "vendor/google/billing/GoogleBillingHelper.h"

#include "platform/java/jni/JniHelper.h"

#include <cstring>
#include "base/UTF8.h"
#include "base/memory/Memory.h"

#include "cocos/bindings/jswrapper/SeApi.h"
#include "cocos/bindings/jswrapper/Value.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/bindings/manual/jsb_global_init.h"
#include "vendor/google/billing/GoogleBilling.h"
#include "vendor/google/billing/JniBilling.h"
#include "vendor/google/billing/GoogleBillingManager.h"
#include "vendor/google/billing/result-values/Purchase.h"
#include "vendor/google/billing/build-params/AcknowledgePurchaseParams.h"
#include "vendor/google/billing/result-values/ProductDetails.h"
#include "vendor/google/billing/build-params/ConsumeParams.h"
namespace {

#ifndef JCLS_BILLING
    #define JCLS_BILLING "google/billing/GoogleBillingHelper"
#endif
}; // namespace

namespace cc {

void invokeJsCallback(se::Object* obj, const char* jsFunctionName, const se::ValueArray& args) {
    if (!obj) {
        return;
    }

    se::Value funcVal;
    if (!obj->getProperty(jsFunctionName, &funcVal) || !funcVal.isObject()) {
        return;
    }
    se::Value rval;
    funcVal.toObject()->call(args, obj, &rval);
}

template <typename... Args>
void callJSfunc(se::Object* obj, const char* jsFunctionName,  Args&&... inargs) { // NOLINT(readability-identifier-naming)
    if (!se::ScriptEngine::getInstance()->isValid()) {
        return;
    }
    se::AutoHandleScope scope;
    se::ValueArray args;
    args.resize(sizeof...(Args));
    nativevalue_to_se_args_v(args, inargs...);
    invokeJsCallback(obj, jsFunctionName, args);
}

void callJSfunc(se::Object* obj, const char* jsFunctionName) { // NOLINT(readability-identifier-naming)
    if (!se::ScriptEngine::getInstance()->isValid()) {
        return;
    }
    se::AutoHandleScope scope;
    invokeJsCallback(obj, jsFunctionName, se::ValueArray());
}

template void callJSfunc(se::Object* obj, const char*, BillingResult*&&);
template void callJSfunc(se::Object* obj, const char*, BillingResult*&&, const std::vector<cc::ProductDetails*>&);
template void callJSfunc(se::Object* obj, const char*, BillingResult*&&, const std::vector<cc::Purchase*>&);
template void callJSfunc(se::Object* obj, const char*, BillingResult*&&, const std::string&);
template void callJSfunc(se::Object* obj, const char*, BillingResult*&&, BillingConfig*&&);
template void callJSfunc(se::Object* obj, const char*, BillingResult*&&, AlternativeBillingOnlyReportingDetails*&&);
template void callJSfunc(se::Object* obj, const char*, BillingResult*&&, ExternalOfferReportingDetails*&&);
template void callJSfunc(se::Object* obj, const char*, InAppMessageResult*&&);

int GoogleBillingHelper::createGoogleBilling(BillingClient::Builder* builder) {
    int tag = JniHelper::callStaticIntMethod(JCLS_BILLING, "newTag");
    jobject buildObj = JniBilling::newBillingClientBuilderObject(tag, builder);

    cc::JniMethodInfo t;
    cc::JniHelper::getStaticMethodInfo(t, JCLS_BILLING, "createGoogleBilling", "(ILcom/android/billingclient/api/BillingClient$Builder;)V");
    t.env->CallStaticVoidMethod(t.classID, t.methodID, tag, buildObj);

    return tag;
}

void GoogleBillingHelper::removeBillingClient(int tag) {
   JniHelper::callStaticIntMethod(JCLS_BILLING, "removeBillingClient", tag);
}

void GoogleBillingHelper::removeProductDetails(int tag, int productDetailsID) {
    JniHelper::callStaticVoidMethod(JCLS_BILLING, "removeProductDetails", tag, productDetailsID);
}

void GoogleBillingHelper::removePurchase(int tag, int purchaseID) {
    JniHelper::callStaticVoidMethod(JCLS_BILLING, "removePurchase", tag, purchaseID);
}


void GoogleBillingHelper::startConnection(int tag, int callbackID) {
    JniHelper::callStaticVoidMethod(JCLS_BILLING, "startConnection", tag, callbackID);
}

void GoogleBillingHelper::endConnection(int tag) {
    JniHelper::callStaticVoidMethod(JCLS_BILLING, "endConnection", tag);
}

int GoogleBillingHelper::getConnectionState(int tag) {
    return JniHelper::callStaticIntMethod(JCLS_BILLING, "getConnectionState", tag);
}

bool GoogleBillingHelper::isReady(int tag) {
    return JniHelper::callStaticBooleanMethod(JCLS_BILLING, "isReady", tag);
}

void GoogleBillingHelper::queryProductDetailsAsync(int tag, int callbackID, const std::vector<std::string>& productIds, const std::vector<std::string>& productTypes) {
    JniHelper::callStaticVoidMethod(JCLS_BILLING, "queryProductDetailsAsync", tag, callbackID, productIds, productTypes);
}

void GoogleBillingHelper::queryPurchasesAsync(int tag, int callbackId,  const std::string& productType) {
    JniHelper::callStaticVoidMethod(JCLS_BILLING, "queryPurchasesAsync", tag, callbackId, productType);
}

void GoogleBillingHelper::getBillingConfigAsync(int tag, int callbackId) {
    JniHelper::callStaticVoidMethod(JCLS_BILLING, "getBillingConfigAsync", tag, callbackId);
}

void GoogleBillingHelper::createAlternativeBillingOnlyReportingDetailsAsync(int tag, int callbackId) {
    JniHelper::callStaticVoidMethod(JCLS_BILLING, "createAlternativeBillingOnlyReportingDetailsAsync", tag, callbackId);
}

void GoogleBillingHelper::isAlternativeBillingOnlyAvailableAsync(int tag, int callbackId) {
    JniHelper::callStaticVoidMethod(JCLS_BILLING, "isAlternativeBillingOnlyAvailableAsync", tag, callbackId);
}

void GoogleBillingHelper::createExternalOfferReportingDetailsAsync(int tag, int callbackId) {
    JniHelper::callStaticVoidMethod(JCLS_BILLING, "createExternalOfferReportingDetailsAsync", tag, callbackId);
}

void GoogleBillingHelper::isExternalOfferAvailableAsync(int tag, int callbackId) {
    JniHelper::callStaticVoidMethod(JCLS_BILLING, "isExternalOfferAvailableAsync", tag, callbackId);
}

BillingResult* GoogleBillingHelper::showAlternativeBillingOnlyInformationDialog(int tag, int callbackId) {
    return cc::JniBilling::callFunctionAndReturnBillingResult("showAlternativeBillingOnlyInformationDialog", tag, callbackId);
}

BillingResult* GoogleBillingHelper::showExternalOfferInformationDialog(int tag, int callbackId) {
    return cc::JniBilling::callFunctionAndReturnBillingResult("showExternalOfferInformationDialog", tag, callbackId);
}

BillingResult* GoogleBillingHelper::showInAppMessages(int tag, int callbackId, const std::vector<int>& inAppMessageCategoryId) {
    auto* env = JniHelper::getEnv();
    cc::JniMethodInfo t;
    if (cc::JniHelper::getStaticMethodInfo(t, JCLS_BILLING, "showInAppMessages", "(II[I)Lcom/android/billingclient/api/BillingResult;")) {
        const int size = inAppMessageCategoryId.size();
        jintArray result = env->NewIntArray(size);
        jint* buf = new jint[size];
        for (int i = 0; i < size; ++i) {
            buf[i] = inAppMessageCategoryId[i];
        }
        env->SetIntArrayRegion(result, 0, size, buf);
        delete[] buf;
        jobject obj = t.env->CallStaticObjectMethod(t.classID, t.methodID, tag, callbackId, result);
        return cc::JniBilling::toBillingResult(env, obj);
    }
    return nullptr;
}

void GoogleBillingHelper::launchBillingFlow(int tag, BillingFlowParams* params) {
    cc::JniMethodInfo t1;
    cc::JniHelper::getStaticMethodInfo(t1, JCLS_BILLING, "launchBillingFlow", "(ILcom/android/billingclient/api/BillingFlowParams;)V");
    t1.env->CallStaticVoidMethod(t1.classID, t1.methodID, tag, JniBilling::newBillingFlowParamsObject(params));
}

void GoogleBillingHelper::consumeAsync(int tag, int callbackId, ConsumeParams* purchase) {
    cc::JniMethodInfo t;
    cc::JniHelper::getStaticMethodInfo(t, JCLS_BILLING, "consumeAsync", "(IILjava/lang/String;)V");
    jstring purchaseToken = cc::StringUtils::newStringUTFJNI(t.env, purchase->getPurchaseToken());
    t.env->CallStaticVoidMethod(t.classID, t.methodID, tag, callbackId, purchaseToken);
}

void GoogleBillingHelper::acknowledgePurchase(int tag, int callbackId, AcknowledgePurchaseParams* purchase) {
    cc::JniMethodInfo t;
    cc::JniHelper::getStaticMethodInfo(t, JCLS_BILLING, "acknowledgePurchase", "(IILjava/lang/String;)V");
    jstring purchaseToken = cc::StringUtils::newStringUTFJNI(t.env, purchase->getPurchaseToken());
    t.env->CallStaticVoidMethod(t.classID, t.methodID, tag, callbackId, purchaseToken);
}

BillingResult* GoogleBillingHelper::isFeatureSupported(int tag, const std::string& feature) {
    auto* env = JniHelper::getEnv();
    cc::JniMethodInfo t;
    if (cc::JniHelper::getStaticMethodInfo(t, JCLS_BILLING, "isFeatureSupported", "(Ljava/lang/String;)Lcom/android/billingclient/api/BillingResult;")) {
        jstring jFeature = cc::StringUtils::newStringUTFJNI(env, feature);
        jobject obj = t.env->CallStaticObjectMethod(t.classID, t.methodID, jFeature);
        return cc::JniBilling::toBillingResult(env, obj);
    }
    return nullptr;
}

void GoogleBillingHelper::onBillingSetupFinished(JNIEnv* env, jclass clazz, jint tag, jint callbackID, jobject billingResultObj) {
    auto* billingClient = GoogleBillingManager::getInstance()->getBillingClient(tag);
    if (billingClient) {
        CC_ASSERT(callbackID >= 0 && callbackID < billingClient->_billingClientStateListeners.size());
        cc::callJSfunc(billingClient->_billingClientStateListeners[callbackID], "onBillingSetupFinished", cc::JniBilling::toBillingResult(env, billingResultObj));
    }
}

void GoogleBillingHelper::onBillingServiceDisconnected(JNIEnv* env, jclass clazz, jint tag, jint callbackID) {
    auto* billingClient = GoogleBillingManager::getInstance()->getBillingClient(tag);
    if (billingClient) {
        CC_ASSERT(callbackID >= 0 && callbackID < billingClient->_billingClientStateListeners.size());
        cc::callJSfunc(billingClient->_billingClientStateListeners[callbackID], "onBillingServiceDisconnected");
    }
}

void GoogleBillingHelper::onProductDetailsResponse(JNIEnv* env, jclass clazz,
                                                jint tag,
                                                jint callbackID,
                                                jobject billingResultObj,
                                                jobject productDetailsListObj,
                                                jint startID) {
    auto* billingResult = cc::JniBilling::toBillingResult(env, billingResultObj);
    std::vector<cc::ProductDetails*> productDetailsList = cc::JniBilling::toProductDetailList(env, productDetailsListObj, startID);
    auto* billingClient = GoogleBillingManager::getInstance()->getBillingClient(tag);
    if (billingClient) {
        CC_ASSERT(callbackID >= 0 && callbackID < billingClient->_productDetailsResponseListeners.size());
        cc::callJSfunc(billingClient->_productDetailsResponseListeners[callbackID], "onProductDetailsResponse", billingResult, productDetailsList);
    }
}

void GoogleBillingHelper::onPurchasesUpdated(JNIEnv* env, jclass clazz,
                                          jint tag,
                                          jobject billingResultObj,
                                          jobject purchasesListObj,
                                          jint startID) {

    auto* billingClient = GoogleBillingManager::getInstance()->getBillingClient(tag);
    if (billingClient && billingClient->_purchasesUpdatedListener) {
        auto* billingResult = cc::JniBilling::toBillingResult(env, billingResultObj);
        std::vector<cc::Purchase*> purchasesList;
        if (purchasesListObj != nullptr) {
            purchasesList = cc::JniBilling::toPurchaseList(env, purchasesListObj, startID);
        }
        cc::callJSfunc(billingClient->_purchasesUpdatedListener, "onPurchasesUpdated", billingResult, purchasesList);
    }
}

 void GoogleBillingHelper::userSelectedAlternativeBilling(JNIEnv *env, jclass clazz, jint tag, jobject userChoiceDetailsObj) {
    auto* billingClient = GoogleBillingManager::getInstance()->getBillingClient(tag);
    if (billingClient && billingClient->_userChoiceBillingListener) {
        auto* userChoiceDetails = cc::JniBilling::toUserChoiceDetails(env, userChoiceDetailsObj);
        cc::callJSfunc(billingClient->_userChoiceBillingListener, "userSelectedAlternativeBilling", userChoiceDetails);
    }
 }

void GoogleBillingHelper::onConsumeResponse(JNIEnv* env, jclass clazz, jint tag, jint callbackId, jobject billingResultObj, jstring purchaseToken) {
    auto* billingClient = GoogleBillingManager::getInstance()->getBillingClient(tag);
    if (billingClient) {
        CC_ASSERT(callbackId >= 0 && callbackId < billingClient->_consumeResponseListeners.size());
        auto *billingResult = cc::JniBilling::toBillingResult(env, billingResultObj);
        cc::callJSfunc(billingClient->_consumeResponseListeners[callbackId],
                       "onConsumeResponse", billingResult,
                       cc::StringUtils::getStringUTFCharsJNI(env,static_cast<jstring>(purchaseToken)));
    }
}

void GoogleBillingHelper::onAcknowledgePurchaseResponse(JNIEnv* env, jclass clazz, jint tag, jint callbackId, jobject billingResultObj) {
    auto* billingClient = GoogleBillingManager::getInstance()->getBillingClient(tag);
    if (billingClient) {
        CC_ASSERT(callbackId >= 0 &&
                  callbackId < billingClient->_acknowledgePurchaseResponseListeners.size());
        auto *billingResult = cc::JniBilling::toBillingResult(env, billingResultObj);
        cc::callJSfunc(billingClient->_acknowledgePurchaseResponseListeners[callbackId], "onAcknowledgePurchaseResponse", billingResult);
    }
}

void GoogleBillingHelper::onQueryPurchasesResponse(JNIEnv* env, jclass clazz, jint tag, jint callbackId, jobject billingResultObj, jobject purchasesListObj, jint startID) {
    auto* billingClient = GoogleBillingManager::getInstance()->getBillingClient(tag);
    if (billingClient) {
        CC_ASSERT(callbackId >= 0 &&
                  callbackId < billingClient->_queryPurchasesResponseListeners.size());
        auto* billingResult = cc::JniBilling::toBillingResult(env, billingResultObj);
        std::vector<cc::Purchase*> purchasesList = cc::JniBilling::toPurchaseList(env, purchasesListObj, startID);
        cc::callJSfunc(billingClient->_queryPurchasesResponseListeners[callbackId], "onQueryPurchasesResponse", billingResult, purchasesList);
    }
}

void GoogleBillingHelper::onBillingConfigResponse(JNIEnv* env, jclass clazz, jint tag, jint callbackId, jobject billingResultObj, jobject billingConfigObj) {
    auto* billingClient = GoogleBillingManager::getInstance()->getBillingClient(tag);
    if (billingClient) {
        CC_ASSERT(callbackId >= 0 &&
                  callbackId < billingClient->_billingConfigListeners.size());
        auto* billingResult = cc::JniBilling::toBillingResult(env, billingResultObj);
        cc::BillingConfig* billingConfig = nullptr;
        if (billingConfigObj) {
            billingConfig = cc::JniBilling::toBillingConfig(env, billingConfigObj);
        }
        cc::callJSfunc(billingClient->_billingConfigListeners[callbackId], "onBillingConfigResponse", billingResult, billingConfig);
    }
}

void GoogleBillingHelper::onAlternativeBillingOnlyTokenResponse(JNIEnv* env, jclass clazz, jint tag, jint callbackId, jobject billingResultObj, jobject alternativeBillingOnlyReportingDetailsObj) {
    auto* billingClient = GoogleBillingManager::getInstance()->getBillingClient(tag);
    if (billingClient) {
        CC_ASSERT(callbackId >= 0 &&
                  callbackId < billingClient->_alternativeBillingOnlyReportingDetailsListeners.size());
        auto* billingResult = cc::JniBilling::toBillingResult(env, billingResultObj);
        cc::AlternativeBillingOnlyReportingDetails* toAlternativeBillingOnlyReporting = nullptr;
        if (alternativeBillingOnlyReportingDetailsObj) {
            toAlternativeBillingOnlyReporting = cc::JniBilling::toAlternativeBillingOnlyReportingDetails(env, alternativeBillingOnlyReportingDetailsObj);
        }
        cc::callJSfunc(billingClient->_alternativeBillingOnlyReportingDetailsListeners[callbackId], "onAlternativeBillingOnlyTokenResponse", billingResult, toAlternativeBillingOnlyReporting);
    }
}

void GoogleBillingHelper::onExternalOfferReportingDetailsResponse(JNIEnv* env, jclass clazz, jint tag, jint callbackId, jobject billingResultObj, jobject externalOfferReportingDetailsObj) {
    auto* billingClient = GoogleBillingManager::getInstance()->getBillingClient(tag);
    if (billingClient) {
        CC_ASSERT(callbackId >= 0 &&
                  callbackId < billingClient->_externalOfferReportingDetailsListeners.size());
        auto* billingResult = cc::JniBilling::toBillingResult(env, billingResultObj);
        cc::ExternalOfferReportingDetails* externalOfferReportingDetails = nullptr;
        if (externalOfferReportingDetailsObj) {
            externalOfferReportingDetails = cc::JniBilling::toExternalOfferReportingDetails(env, externalOfferReportingDetailsObj);
        }
        cc::callJSfunc(billingClient->_externalOfferReportingDetailsListeners[callbackId], "onExternalOfferReportingDetailsResponse", billingResult, externalOfferReportingDetails);
    }
}

void GoogleBillingHelper::onAlternativeBillingOnlyAvailabilityResponse(JNIEnv* env, jclass clazz, jint tag, jint callbackId, jobject billingResultObj) {
    auto* billingClient = GoogleBillingManager::getInstance()->getBillingClient(tag);
    if (billingClient) {
        CC_ASSERT(callbackId >= 0 &&
                  callbackId < billingClient->_alternativeBillingOnlyAvailabilityListeners.size());
        auto* billingResult = cc::JniBilling::toBillingResult(env, billingResultObj);
        cc::callJSfunc(billingClient->_alternativeBillingOnlyAvailabilityListeners[callbackId], "onAlternativeBillingOnlyAvailabilityResponse", billingResult);
    }
}

void GoogleBillingHelper::onExternalOfferAvailabilityResponse(JNIEnv* env, jclass clazz, jint tag, jint callbackId, jobject billingResultObj) {
    auto* billingClient = GoogleBillingManager::getInstance()->getBillingClient(tag);
    if (billingClient) {
        CC_ASSERT(callbackId >= 0 &&
                  callbackId < billingClient->_externalOfferAvailabilityListeners.size());
        auto* billingResult = cc::JniBilling::toBillingResult(env, billingResultObj);
        cc::callJSfunc(billingClient->_externalOfferAvailabilityListeners[callbackId], "onExternalOfferAvailabilityResponse", billingResult);
    }
}

void GoogleBillingHelper::onAlternativeBillingOnlyInformationDialogResponse(JNIEnv* env, jclass clazz, jint tag, jint callbackId, jobject billingResultObj) {
    auto* billingClient = GoogleBillingManager::getInstance()->getBillingClient(tag);
    if (billingClient) {
        CC_ASSERT(callbackId >= 0 &&
                  callbackId < billingClient->_alternativeBillingOnlyInformationDialogListeners.size());
        auto* billingResult = cc::JniBilling::toBillingResult(env, billingResultObj);
        cc::callJSfunc(billingClient->_alternativeBillingOnlyInformationDialogListeners[callbackId], "onAlternativeBillingOnlyInformationDialogResponse", billingResult);
    }
}

void GoogleBillingHelper::onExternalOfferInformationDialogResponse(JNIEnv* env, jclass clazz, jint tag, jint callbackId, jobject billingResultObj) {
    auto* billingClient = GoogleBillingManager::getInstance()->getBillingClient(tag);
    if (billingClient) {
        CC_ASSERT(callbackId >= 0 &&
                  callbackId < billingClient->_externalOfferInformationDialogListeners.size());
        auto* billingResult = cc::JniBilling::toBillingResult(env, billingResultObj);
        cc::callJSfunc(billingClient->_externalOfferInformationDialogListeners[callbackId], "onExternalOfferInformationDialogResponse", billingResult);
    }
}

void GoogleBillingHelper::onInAppMessageResponse(JNIEnv* env, jclass clazz, jint tag, jint callbackId, jobject inAppMessageResultObj) {
    auto* billingClient = GoogleBillingManager::getInstance()->getBillingClient(tag);
    if (billingClient) {
        CC_ASSERT(callbackId >= 0 &&
                  callbackId < billingClient->_inappListeners.size());
        auto* inAppMessageResult = cc::JniBilling::toInAppMessageResult(env, inAppMessageResultObj);
        cc::callJSfunc(billingClient->_inappListeners[callbackId], "onInAppMessageResponse", inAppMessageResult);
    }
}



} // namespace cc
