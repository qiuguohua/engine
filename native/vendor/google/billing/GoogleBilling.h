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

#pragma once

#include <vector>

#include "base/Macros.h"
#include "base/RefCounted.h"

namespace se {
class Object;
}

namespace cc {
class PendingPurchasesParams;
class QueryProductDetailsParams;
class BillingFlowParams;
class ConsumeParams;
class AcknowledgePurchaseParams;
class QueryPurchasesParams;
class GetBillingConfigParams;
class InAppMessageParams;
class BillingResult;

class CC_DLL BillingClient : public cc::RefCounted {
public:
    class Builder {
    public:
        Builder& enableAlternativeBillingOnly() {
            this->_enableAlternativeBillingOnly = true;
            return *this;
        }

        Builder& enableExternalOffer() {
            this->_enableExternalOffer = true;
            return *this;
        }

        Builder& enablePendingPurchases(PendingPurchasesParams* pendingPurchasesParams) {
            this->_pendingPurchasesParams = pendingPurchasesParams;
            return *this;
        }

        Builder& enableUserChoiceBilling(se::Object* listener) ;

        Builder& setListener(se::Object* listener) ;

        BillingClient* build() {
            return new BillingClient(this);
        }

    private:
        friend class BillingClient;
        friend class JniBilling;
        bool _enableAlternativeBillingOnly;
        bool _enableExternalOffer;
        PendingPurchasesParams* _pendingPurchasesParams;
        se::Object* _purchasesUpdatedListener;
        se::Object* _userChoiceBillingListener;
    };
    static Builder* newBuilder() {
        return new Builder();
    }

    void startConnection(se::Object* listener);
    void endConnection();
    int getConnectionState() const;
    bool isReady() const;
    void queryProductDetailsAsync(QueryProductDetailsParams* params, se::Object* listener);
    void launchBillingFlow(BillingFlowParams* params);
    void consumeAsync(ConsumeParams* params, se::Object* listener);
    void acknowledgePurchase(AcknowledgePurchaseParams* params, se::Object* listener);
    void queryPurchasesAsync(QueryPurchasesParams* parmas, se::Object* listener);
    void getBillingConfigAsync(GetBillingConfigParams* params, se::Object* listener);

    void createAlternativeBillingOnlyReportingDetailsAsync(se::Object* listener);
    void isAlternativeBillingOnlyAvailableAsync(se::Object* listener);
    void createExternalOfferReportingDetailsAsync(se::Object* listener);
    void isExternalOfferAvailableAsync(se::Object* listener);
    BillingResult* isFeatureSupported(const std::string& feature);
    BillingResult* showAlternativeBillingOnlyInformationDialog(se::Object* listener);
    BillingResult* showExternalOfferInformationDialog(se::Object* listener);
    BillingResult* showInAppMessages(InAppMessageParams* params, se::Object* listener);
private:
    BillingClient(Builder* builder);
    ~BillingClient();
private:
    friend class GoogleBillingHelper;
    int _tag{-1};
    bool _enableAlternativeBillingOnly{false};
    bool _enableExternalOffer{false};

    se::Object* _purchasesUpdatedListener{nullptr};
    se::Object* _userChoiceBillingListener{nullptr};
    PendingPurchasesParams* _pendingPurchasesParams{nullptr};

    std::vector<se::Object*> _billingClientStateListeners;
    std::vector<se::Object*> _productDetailsResponseListeners;
    std::vector<se::Object*> _consumeResponseListeners;
    std::vector<se::Object*> _acknowledgePurchaseResponseListeners;
    std::vector<se::Object*> _queryPurchasesResponseListeners;

    std::vector<se::Object*> _alternativeBillingOnlyReportingDetailsListeners;
    std::vector<se::Object*> _alternativeBillingOnlyAvailabilityListeners;
    std::vector<se::Object*> _externalOfferReportingDetailsListeners;
    std::vector<se::Object*> _externalOfferAvailabilityListeners;

    std::vector<se::Object*> _alternativeBillingOnlyInformationDialogListeners;
    std::vector<se::Object*> _externalOfferInformationDialogListeners;
    std::vector<se::Object*> _inappListeners;
    
    std::vector<se::Object*> _billingConfigListeners;
};

} // namespace cc
