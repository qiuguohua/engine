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

#include "vendor/google/billing/GoogleBilling.h"
#include "cocos/bindings/jswrapper/SeApi.h"
#include "platform/java/jni/JniHelper.h"
#include "platform/java/jni/JniImp.h"
#include "vendor/google/billing/GoogleBillingHelper.h"
#include "vendor/google/billing/GoogleBillingManager.h"
#include "vendor/google/billing/build-params/AcknowledgePurchaseParams.h"
#include "vendor/google/billing/build-params/BillingFlowParams.h"
#include "vendor/google/billing/build-params/ConsumeParams.h"
#include "vendor/google/billing/build-params/GetBillingConfigParams.h"
#include "vendor/google/billing/build-params/InAppMessageParams.h"
#include "vendor/google/billing/build-params/PendingPurchasesParams.h"
#include "vendor/google/billing/build-params/QueryProductDetailsParams.h"
#include "vendor/google/billing/build-params/QueryPurchasesParams.h"

namespace cc {

#define ADD_JS_OBJ_REF(obj) \
    do {                    \
        obj->root();        \
        obj->incRef();      \
    } while (0)

#define DEL_JS_OBJ_REF(obj) \
    do {                    \
        if (obj) {          \
            obj->unroot();  \
            obj->decRef();  \
        }                   \
    } while (0)

BillingClient::Builder& BillingClient::Builder::enableUserChoiceBilling(se::Object* listener) {
    if (!listener) {
        CC_LOG_WARNING("Can't set an empty listener.");
        return *this;
    }
    ADD_JS_OBJ_REF(listener);
    _userChoiceBillingListener = listener;
    return *this;
}

BillingClient::Builder& BillingClient::Builder::setListener(se::Object* listener) {
    if (!listener) {
        CC_LOG_WARNING("Can't set an empty listener.");
        return *this;
    }
    ADD_JS_OBJ_REF(listener);
    _purchasesUpdatedListener = listener;
    return *this;
}

BillingClient::BillingClient(Builder* builder) {
    this->_enableAlternativeBillingOnly = builder->_enableAlternativeBillingOnly;
    this->_enableExternalOffer = builder->_enableExternalOffer;
    this->_pendingPurchasesParams = builder->_pendingPurchasesParams;
    this->_purchasesUpdatedListener = builder->_purchasesUpdatedListener;
    this->_userChoiceBillingListener = builder->_userChoiceBillingListener;

    _tag = GoogleBillingHelper::createGoogleBilling(builder);

    CC_ASSERT(_tag >= 0);
    GoogleBillingManager::getInstance()->pushBillingClient(_tag, this);
    delete builder;
}

void BillingClient::RemoveJsObject(std::vector<se::Object*>* listeners) {
    for (auto* listener : *listeners) {
        DEL_JS_OBJ_REF(listener);
    }
    listeners->clear();
}

BillingClient::~BillingClient() {
    CC_ASSERT(_tag >= 0);
    GoogleBillingHelper::removeGoogleBilling(_tag);
    GoogleBillingManager::getInstance()->removeGoogleBilling(_tag);

    DEL_JS_OBJ_REF(_purchasesUpdatedListener);
    DEL_JS_OBJ_REF(_userChoiceBillingListener);
    RemoveJsObject(&_billingClientStateListeners);
    RemoveJsObject(&_productDetailsResponseListeners);
    RemoveJsObject(&_consumeResponseListeners);
    RemoveJsObject(&_acknowledgePurchaseResponseListeners);
    RemoveJsObject(&_queryPurchasesResponseListeners);
    RemoveJsObject(&_alternativeBillingOnlyReportingDetailsListeners);
    RemoveJsObject(&_alternativeBillingOnlyAvailabilityListeners);
    RemoveJsObject(&_externalOfferReportingDetailsListeners);
    RemoveJsObject(&_externalOfferAvailabilityListeners);
    RemoveJsObject(&_alternativeBillingOnlyInformationDialogListeners);
    RemoveJsObject(&_externalOfferInformationDialogListeners);
    RemoveJsObject(&_inappListeners);
    RemoveJsObject(&_billingConfigListeners);
}

void BillingClient::startConnection(se::Object* listener) {
    auto it = std::find(_billingClientStateListeners.begin(), _billingClientStateListeners.end(), listener);
    if (it == _billingClientStateListeners.end()) {
        listener->root();
        listener->incRef();
        _billingClientStateListeners.push_back(listener);
        GoogleBillingHelper::startConnection(_tag, _billingClientStateListeners.size() - 1);
    } else {
        //
    }
}

void BillingClient::endConnection() {
    GoogleBillingHelper::endConnection(_tag);
}

int BillingClient::getConnectionState() const {
    return GoogleBillingHelper::getConnectionState(_tag);
}

bool BillingClient::isReady() const {
    return GoogleBillingHelper::isReady(_tag);
}

void BillingClient::queryProductDetailsAsync(QueryProductDetailsParams* params, se::Object* listener) {
    auto it = std::find(_productDetailsResponseListeners.begin(), _productDetailsResponseListeners.end(), listener);
    if (it == _productDetailsResponseListeners.end()) {
        listener->root();
        listener->incRef();
        _productDetailsResponseListeners.push_back(listener);
        std::vector<std::string> productIDs;
        std::vector<std::string> productTypes;
        for (auto product : params->_productList) {
            productIDs.push_back(product->_productID);
            productTypes.push_back(product->_productType);
        }
        GoogleBillingHelper::queryProductDetailsAsync(_tag, _productDetailsResponseListeners.size() - 1, productIDs, productTypes);
    } else {
        //
    }
}

void BillingClient::launchBillingFlow(BillingFlowParams* params) {
    GoogleBillingHelper::launchBillingFlow(_tag, params);
}

void BillingClient::consumeAsync(ConsumeParams* params, se::Object* listener) {
    auto it = std::find(_consumeResponseListeners.begin(), _consumeResponseListeners.end(), listener);
    if (it == _consumeResponseListeners.end()) {
        listener->root();
        listener->incRef();
        _consumeResponseListeners.push_back(listener);
        GoogleBillingHelper::consumeAsync(_tag, _consumeResponseListeners.size() - 1, params);
    } else {
        //
    }
}

void BillingClient::acknowledgePurchase(AcknowledgePurchaseParams* params, se::Object* listener) {
    auto it = std::find(_acknowledgePurchaseResponseListeners.begin(), _acknowledgePurchaseResponseListeners.end(), listener);
    if (it == _acknowledgePurchaseResponseListeners.end()) {
        listener->root();
        listener->incRef();
        _acknowledgePurchaseResponseListeners.push_back(listener);
        GoogleBillingHelper::acknowledgePurchase(_tag, _acknowledgePurchaseResponseListeners.size() - 1, params);
    } else {
        //
    }
}

void BillingClient::queryPurchasesAsync(QueryPurchasesParams* params, se::Object* listener) {
    auto it = std::find(_queryPurchasesResponseListeners.begin(), _queryPurchasesResponseListeners.end(), listener);
    if (it == _queryPurchasesResponseListeners.end()) {
        listener->root();
        listener->incRef();
        _queryPurchasesResponseListeners.push_back(listener);
        GoogleBillingHelper::queryPurchasesAsync(_tag, _queryPurchasesResponseListeners.size() - 1, params->_productType);
    } else {
        //
    }
}

void BillingClient::getBillingConfigAsync(GetBillingConfigParams* params, se::Object* listener) {
    auto it = std::find(_billingConfigListeners.begin(), _billingConfigListeners.end(), listener);
    if (it == _billingConfigListeners.end()) {
        listener->root();
        listener->incRef();
        _billingConfigListeners.push_back(listener);
        GoogleBillingHelper::getBillingConfigAsync(_tag, _billingConfigListeners.size() - 1);
    } else {
        //
    }
}

BillingResult* BillingClient::isFeatureSupported(const std::string& feature) {
    return GoogleBillingHelper::isFeatureSupported(_tag, feature);
}

void BillingClient::createAlternativeBillingOnlyReportingDetailsAsync(se::Object* listener) {
    auto it = std::find(_alternativeBillingOnlyReportingDetailsListeners.begin(), _alternativeBillingOnlyReportingDetailsListeners.end(), listener);
    if (it == _alternativeBillingOnlyReportingDetailsListeners.end()) {
        listener->root();
        listener->incRef();
        _alternativeBillingOnlyReportingDetailsListeners.push_back(listener);
        GoogleBillingHelper::createAlternativeBillingOnlyReportingDetailsAsync(_tag, _alternativeBillingOnlyReportingDetailsListeners.size() - 1);
    } else {
        //
    }
}

void BillingClient::isAlternativeBillingOnlyAvailableAsync(se::Object* listener) {
    auto it = std::find(_alternativeBillingOnlyAvailabilityListeners.begin(), _alternativeBillingOnlyAvailabilityListeners.end(), listener);
    if (it == _alternativeBillingOnlyAvailabilityListeners.end()) {
        listener->root();
        listener->incRef();
        _alternativeBillingOnlyAvailabilityListeners.push_back(listener);
        GoogleBillingHelper::isAlternativeBillingOnlyAvailableAsync(_tag, _alternativeBillingOnlyAvailabilityListeners.size() - 1);
    } else {
        //
    }
}

void BillingClient::createExternalOfferReportingDetailsAsync(se::Object* listener) {
    auto it = std::find(_externalOfferReportingDetailsListeners.begin(), _externalOfferReportingDetailsListeners.end(), listener);
    if (it == _externalOfferReportingDetailsListeners.end()) {
        listener->root();
        listener->incRef();
        _externalOfferReportingDetailsListeners.push_back(listener);
        GoogleBillingHelper::createExternalOfferReportingDetailsAsync(_tag, _externalOfferReportingDetailsListeners.size() - 1);
    } else {
        //
    }
}

void BillingClient::isExternalOfferAvailableAsync(se::Object* listener) {
    auto it = std::find(_externalOfferAvailabilityListeners.begin(), _externalOfferAvailabilityListeners.end(), listener);
    if (it == _externalOfferAvailabilityListeners.end()) {
        listener->root();
        listener->incRef();
        _externalOfferAvailabilityListeners.push_back(listener);
        GoogleBillingHelper::isExternalOfferAvailableAsync(_tag, _externalOfferAvailabilityListeners.size() - 1);
    } else {
        //
    }
}

BillingResult* BillingClient::showAlternativeBillingOnlyInformationDialog(se::Object* listener) {
    auto it = std::find(_alternativeBillingOnlyInformationDialogListeners.begin(), _alternativeBillingOnlyInformationDialogListeners.end(), listener);
    if (it == _alternativeBillingOnlyInformationDialogListeners.end()) {
        listener->root();
        listener->incRef();
        _alternativeBillingOnlyInformationDialogListeners.push_back(listener);
        return GoogleBillingHelper::showAlternativeBillingOnlyInformationDialog(_tag, _alternativeBillingOnlyInformationDialogListeners.size() - 1);
    } else {
        //
    }
    return nullptr;
}

BillingResult* BillingClient::showExternalOfferInformationDialog(se::Object* listener) {
    auto it = std::find(_externalOfferInformationDialogListeners.begin(), _externalOfferInformationDialogListeners.end(), listener);
    if (it == _externalOfferInformationDialogListeners.end()) {
        listener->root();
        listener->incRef();
        _externalOfferInformationDialogListeners.push_back(listener);
        return GoogleBillingHelper::showExternalOfferInformationDialog(_tag, _externalOfferInformationDialogListeners.size() - 1);
    } else {
        //
    }
    return nullptr;
}

BillingResult* BillingClient::showInAppMessages(InAppMessageParams* params, se::Object* listener) {
    auto it = std::find(_inappListeners.begin(), _inappListeners.end(), listener);
    if (it == _inappListeners.end()) {
        listener->root();
        listener->incRef();
        _inappListeners.push_back(listener);
        return GoogleBillingHelper::showInAppMessages(_tag, _inappListeners.size() - 1, params->_inAppMessageCategoryIds);
    } else {
        //
    }
    return nullptr;
}

} // namespace cc
