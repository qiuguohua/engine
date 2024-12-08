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
#include "cocos/bindings/jswrapper/SeApi.h"
namespace cc {

class CC_DLL BillingResult : public cc::RefCounted {
public:
    int getResponseCode() const {
        return this->_responseCode;
    }

    std::string getDebugMessage() const {
        return this->_debugMessage;
    }

    std::string toStr() const {
        return this->_toString;
    }
    class Builder {
    private:
        int _responseCode{0};
        std::string _debugMessage;
        std::string _toStr;

    public:
        Builder& setDebugMessage(const std::string debugMsg) {
            this->_debugMessage = debugMsg;
            return *this;
        }
        Builder& setResponseCode(int responseCode) {
            this->_responseCode = responseCode;
            return *this;
        }
        BillingResult* build() {
            auto* p = new BillingResult();
            p->_responseCode = _responseCode;
            p->_debugMessage = _debugMessage;
            return p;
        }
    };
    static Builder* newBuilder() {
        return new Builder();
    }

private:
    friend class GoogleBillingToNative;
    int _responseCode{0};
    std::string _debugMessage;
    std::string _toString;
};

class CC_DLL ProductDetails : public cc::RefCounted {
public:
    ~ProductDetails() override;
    class OneTimePurchaseOfferDetails {
    public:
        long getPriceAmountMicros() const {
            return this->_priceAmountMicros;
        }

        std::string getFormattedPrice() const {
            return this->_formattedPrice;
        }

        std::string getPriceCurrencyCode() const {
            return this->_priceCurrencyCode;
        }

    private:
        friend class GoogleBillingToNative;
        long _priceAmountMicros{0};
        std::string _formattedPrice;
        std::string _priceCurrencyCode;
    };

    class InstallmentPlanDetails {
    public:
        int getInstallmentPlanCommitmentPaymentsCount() const {
            return this->_commitmentPaymentsCount;
        }
        int getSubsequentInstallmentPlanCommitmentPaymentsCount() const {
            return this->_subsequentCommitmentPaymentsCount;
        }

    private:
        friend class GoogleBillingToNative;
        int _commitmentPaymentsCount{0};
        int _subsequentCommitmentPaymentsCount{0};
    };

    class PricingPhase {
    public:
        int getBillingCycleCount() const {
            return this->_billingCycleCount;
        }

        int getRecurrenceMode() const {
            return this->_priceAmountMicros;
        }

        long getPriceAmountMicros() const {
            return this->_recurrenceMode;
        }

        std::string getBillingPeriod() const {
            return this->_billingPeriod;
        }
        std::string getFormattedPrice() const {
            return this->_formattedPrice;
        }

        std::string getPriceCurrencyCode() const {
            return this->_priceCurrencyCode;
        }

    private:
        friend class GoogleBillingToNative;
        int _billingCycleCount{0};
        long _priceAmountMicros{0};
        int _recurrenceMode{0};
        std::string _billingPeriod;
        std::string _formattedPrice;
        std::string _priceCurrencyCode;
    };

    class PricingPhases {
    public:
        std::vector<PricingPhase*> getPricingPhaseList() const {
            return this->_pricingPhaseList;
        }
        ~PricingPhases() {
            for (auto* pricingPhase : _pricingPhaseList) {
                delete pricingPhase;
            }
            _pricingPhaseList.clear();
        }

    private:
        friend class GoogleBillingToNative;
        std::vector<PricingPhase*> _pricingPhaseList;
    };
    class SubscriptionOfferDetails {
    public:
        ~SubscriptionOfferDetails() {
            if (this->_pricingPhases != nullptr) {
                delete this->_pricingPhases;
                this->_pricingPhases = nullptr;
            }

            if (this->_installmentPlanDetails != nullptr) {
                delete this->_installmentPlanDetails;
                this->_installmentPlanDetails = nullptr;
            }
        }
        InstallmentPlanDetails* getInstallmentPlanDetails() const {
            return this->_installmentPlanDetails;
        }

        PricingPhases* getPricingPhases() const {
            return this->_pricingPhases;
        }

        std::string getBasePlanId() const {
            return this->_basePlanId;
        }

        std::string getOfferId() const {
            return this->_offerId;
        }

        std::string getOfferToken() const {
            return this->_offerToken;
        }

        std::vector<std::string> getOfferTags() const {
            return this->_offerTags;
        }

    private:
        friend class GoogleBillingToNative;
        std::string _basePlanId;
        std::string _offerId;
        std::string _offerToken;
        std::vector<std::string> _offerTags;
        PricingPhases* _pricingPhases{nullptr};
        InstallmentPlanDetails* _installmentPlanDetails{nullptr};
    };
    int hashCode() const {
        return this->_hashCode;
    }

    OneTimePurchaseOfferDetails* getOneTimePurchaseOfferDetails() const {
        return this->_oneTimePurchaseOfferDetails;
    }

    std::string getDescription() const {
        return this->_description;
    }

    std::string getName() const {
        return this->_name;
    }

    std::string getProductId() const {
        return this->_productId;
    }

    std::string getProductType() const {
        return this->_productType;
    }

    std::string getTitle() const {
        return this->_title;
    }

    std::string toStr() const {
        return this->_toString;
    }

    bool equals(const ProductDetails& other) const {
        return this->_hashCode == other._hashCode;
    }

    std::vector<SubscriptionOfferDetails*> getSubscriptionOfferDetails() const {
        return this->_subscriptionOfferDetails;
    }

private:
    friend class GoogleBillingToNative;
    friend class GoogleBillingHelper;
    int _id{-1};  // This is an ID that is not visible to ts and is used to free the java object.
    int _tag{-1}; // This is an ID that is not visible to ts and is used to specify which billingclient.
    int _hashCode{0};
    std::string _description;
    std::string _name;
    std::string _productId;
    std::string _productType;
    std::string _title;
    std::string _toString;
    OneTimePurchaseOfferDetails* _oneTimePurchaseOfferDetails{nullptr};
    std::vector<SubscriptionOfferDetails*> _subscriptionOfferDetails;
};
class CC_DLL AccountIdentifiers {
public:
    std::string getObfuscatedAccountId() const {
        return this->_obfuscatedAccountId;
    }

    std::string getObfuscatedProfileId() const {
        return this->_obfuscatedProfileId;
    }

private:
    friend class GoogleBillingToNative;
    friend class Purchase;
    std::string _obfuscatedAccountId;
    std::string _obfuscatedProfileId;
};

class CC_DLL Purchase : public cc::RefCounted {
public:
    class CC_DLL PendingPurchaseUpdate {
    public:
        std::string getPurchaseToken() const {
            return this->_purchaseToken;
        }

        std::vector<std::string> getProducts() const {
            return this->_products;
        }

    private:
        friend class GoogleBillingToNative;
        std::string _purchaseToken;
        std::vector<std::string> _products;
    };

    int getPurchaseState() const {
        return this->_purchaseState;
    }
    int getQuantity() const {
        return this->_quantity;
    }

    int hashCode() const {
        return this->_hashCode;
    }

    long getPurchaseTime() const {
        return this->_purchaseTime;
    }

    AccountIdentifiers* getAccountIdentifiers() const {
        return this->_accountIdentifiers;
    }
    PendingPurchaseUpdate* getPendingPurchaseUpdate() const {
        return this->_pendingPurchaseUpdate;
    }

    std::string getDeveloperPayload() const {
        return this->_developerPayload;
    }

    std::string getOrderId() const {
        return this->_orderId;
    }

    std::string getOriginalJson() const {
        return this->_originalJson;
    }

    std::string getPackageName() const {
        return this->_packageName;
    }

    std::string getPurchaseToken() const {
        return this->_purchaseToken;
    }

    std::string getSignature() const {
        return this->_signature;
    }

    std::string toStr() const {
        return this->_toString;
    }

    std::vector<std::string> getProducts() const {
        return this->_products;
    }
    bool isAcknowledged() const {
        return this->_isAcknowledged;
    }

    bool isAutoRenewing() const {
        return this->_isAutoRenewing;
    }
    ~Purchase() override;
    bool equals(const Purchase& other) const {
        return this->_hashCode == other._hashCode;
    }

private:
    friend class GoogleBillingToNative;
    friend class GoogleBillingHelper;
    int _id{-1};  // This is an ID that is not visible to ts and is used to free the java object.
    int _tag{-1}; // This is an ID that is not visible to ts and is used to specify which billingclient.
    bool _isAcknowledged{false};
    bool _isAutoRenewing{false};
    int _purchaseState{0};
    int _hashCode{0};
    int _quantity{0};
    long _purchaseTime{0};
    std::string _developerPayload;
    std::string _orderId;
    std::string _originalJson;
    std::string _packageName;
    std::string _purchaseToken;
    std::string _signature;
    std::string _toString;
    AccountIdentifiers* _accountIdentifiers{nullptr};
    PendingPurchaseUpdate* _pendingPurchaseUpdate{nullptr};
    std::vector<std::string> _products;
};

class CC_DLL BillingConfig : public cc::RefCounted {
public:
    std::string getCountryCode() const {
        return this->_countryCode;
    }
    static BillingConfig* forCountryCode(const std::string countryCode) {
        return new BillingConfig(countryCode);
    }

private:
    friend class GoogleBillingToNative;
    BillingConfig(const std::string countryCode) {
        this->_countryCode = countryCode;
    }
    std::string _countryCode;
};

class AlternativeBillingOnlyReportingDetails : public cc::RefCounted {
public:
    std::string getExternalTransactionToken() const {
        return this->_externalTransactionToken;
    }

private:
    friend class GoogleBillingToNative;
    std::string _externalTransactionToken;
};

class ExternalOfferReportingDetails : public cc::RefCounted {
public:
    std::string getExternalTransactionToken() const {
        return this->_externalTransactionToken;
    }

private:
    friend class GoogleBillingToNative;
    std::string _externalTransactionToken;
};

class InAppMessageResult : public cc::RefCounted {
public:
    int getResponseCode() const {
        return this->_responseCode;
    }

    std::string getPurchaseToken() const {
        return this->_purchaseToken;
    }

    InAppMessageResult(int responseCode, const std::string& purchaseToken) {
        this->_responseCode = responseCode;
        this->_purchaseToken = purchaseToken;
    }

private:
    friend class GoogleBillingToNative;
    int _responseCode{0};
    std::string _purchaseToken;
};

class UserChoiceDetails : public cc::RefCounted {
public:
    class Product {
    public:
        int hashCode() const {
            return _hashCode;
        }
        std::string getId() const {
            return _id;
        }
        std::string getOfferToken() const {
            return _type;
        }
        std::string getType() const {
            return _offerToken;
        }
        std::string toString() const {
            return _toStr;
        }
        bool equals(const Product& p) {
            if (&p == this) {
                return true;
            }
            return p._id == _id && p._type == _type && p._offerToken == _offerToken;
        }

    private:
        int _hashCode{0};
        std::string _id;
        std::string _type;
        std::string _offerToken;
        std::string _toStr;
    };

    ~UserChoiceDetails() {
        for (auto* product : _products) {
            delete product;
        }
        _products.clear();
    }
    std::string getExternalTransactionToken() const {
        return _externalTransactionToken;
    }
    std::string getOriginalExternalTransactionId() const {
        return _originalExternalTransactionId;
    }

    std::vector<Product*> getProducts() {
        return this->_products;
    }

private:
    friend class GoogleBillingToNative;
    std::string _externalTransactionToken;
    std::string _originalExternalTransactionId;
    std::vector<Product*> _products;
};

class PendingPurchasesParams {
public:
    class Builder {
    private:
        bool _enableOneTimeProducts;
        bool _enablePrepaidPlans;

    public:
        Builder& enableOneTimeProducts() {
            this->_enableOneTimeProducts = true;
            return *this;
        }
        Builder& enablePrepaidPlans() {
            this->_enablePrepaidPlans = true;
            return *this;
        }
        PendingPurchasesParams* build() {
            if (!this->_enableOneTimeProducts) {
                return nullptr;
            }
            return new PendingPurchasesParams(this->_enableOneTimeProducts, this->_enablePrepaidPlans);
        }
    };

    static Builder* newBuilder() {
        return new Builder();
    }

private:
    PendingPurchasesParams(bool enableOneTimeProducts, bool enablePrepaidPlans) {
        this->_enableOneTimeProducts = enableOneTimeProducts;
        this->_enablePrepaidPlans = enablePrepaidPlans;
    }

private:
    friend class BillingClient;
    bool _enableOneTimeProducts{false};
    bool _enablePrepaidPlans{false};
};

class PurchasesUpdatedListener {
public:
    void onPurchasesUpdated(BillingResult, Purchase) {
    }
};

class Product {
public:
    class Builder {
    private:
        std::string _productID;
        std::string _productType;

    public:
        Builder& setProductId(const std::string& productID) {
            this->_productID = productID;
            return *this;
        }
        Builder& setProductType(const std::string& productType) {
            this->_productType = productType;
            return *this;
        }
        Product* build() {
            if (_productID.empty()) {
            } else if (_productType.empty()) {
            }
            return new Product(_productID, _productType);
        }
    };

    static Builder* newBuilder() {
        return new Builder();
    }

private:
    Product(const std::string& productID, const std::string& productType) {
        this->_productID = productID;
        this->_productType = productType;
    }

private:
    friend class BillingClient;
    std::string _productID;
    std::string _productType;
};

class QueryProductDetailsParams {
public:
    class Builder {
    private:
        std::vector<Product*> _productList;

    public:
        Builder& setProductList(const std::vector<Product*>& productList) {
            _productList = productList;
            return *this;
        }

        QueryProductDetailsParams* build() {
            if (this->_productList.empty()) {
                return nullptr;
            }
            return new QueryProductDetailsParams(this->_productList);
        }
    };

    static Builder* newBuilder() {
        return new Builder();
    }

private:
    QueryProductDetailsParams(const std::vector<Product*>& productLists) {
        _productList = productLists;
    }

private:
    friend class BillingClient;
    std::vector<Product*> _productList;
};

class CC_DLL BillingFlowParams {
public:
    class SubscriptionUpdateParams {
    public:
        class Builder {
        public:
            Builder& setOldPurcchaseToken(const std::string& purchaseToken) {
                this->_purchaseToken = purchaseToken;
                return *this;
            }
            Builder& setOriginalExternalTransactionId(const std::string& externalTransactionId) {
                this->_externalTransactionId = externalTransactionId;
                return *this;
            }
            Builder& setSubscriptionReplacementMode(int subscriptionReplacementMode) {
                this->_subscriptionReplacementMode = subscriptionReplacementMode;
                return *this;
            }
            SubscriptionUpdateParams* build() {
                return new SubscriptionUpdateParams(_subscriptionReplacementMode, _purchaseToken, _externalTransactionId);
            }

        private:
            int _subscriptionReplacementMode;
            std::string _purchaseToken;
            std::string _externalTransactionId;
        };
        static Builder* newBuilder() {
            return new Builder();
        }

    private:
        SubscriptionUpdateParams(int subscriptionReplacementMode, const std::string& purchaseToken, const std::string& externalTransactionId) {
            this->_subscriptionReplacementMode = subscriptionReplacementMode;
            this->_purchaseToken = purchaseToken;
            this->_externalTransactionId = externalTransactionId;
        }
        friend class GoogleBillingToNative;
        int _subscriptionReplacementMode;
        std::string _purchaseToken;
        std::string _externalTransactionId;
    };

    class ProductDetailsParams {
    public:
        class Builder {
        public:
            Builder& setOfferToken(const std::string& offerToken) {
                this->_offerToken = offerToken;
                return *this;
            }
            Builder& setProductDetails(ProductDetails* productDetails) {
                this->_productDetails = productDetails;
                return *this;
            }
            ProductDetailsParams* build() {
                return new ProductDetailsParams(_offerToken, _productDetails);
            }

        private:
            std::string _offerToken;
            ProductDetails* _productDetails;
        };
        static Builder* newBuilder() {
            return new Builder();
        }

    private:
        friend class GoogleBillingToNative;
        ProductDetailsParams(std::string offerToken, ProductDetails* _productDetails) {
            this->_offerToken = offerToken;
            this->_productDetails = _productDetails;
        }

        std::string _offerToken;
        ProductDetails* _productDetails{nullptr};
    };

    class Builder {
    public:
        Builder& setIsOfferPersonalized(bool isOfferPersonalized) {
            this->_isOfferPersonalized = isOfferPersonalized;
            return *this;
        }
        Builder& setObfuscatedAccountId(const std::string& obfuscatedAccountid) {
            this->_obfuscatedAccountid = obfuscatedAccountid;
            return *this;
        }
        Builder& setObfuscatedProfileId(const std::string& obfuscatedProfileId) {
            this->_obfuscatedProfileId = obfuscatedProfileId;
            return *this;
        }
        Builder& setProductDetailsParamsList(const std::vector<ProductDetailsParams*>& productDetailsParamsList) {
            this->_productDetailsParamsList = productDetailsParamsList;
            return *this;
        }
        Builder& setSubscriptionUpdateParams(SubscriptionUpdateParams* subscriptionUpdateParams) {
            this->_subscriptionUpdateParams = subscriptionUpdateParams;
            return *this;
        }
        BillingFlowParams* build() {
            return new BillingFlowParams(_isOfferPersonalized, _obfuscatedAccountid, _obfuscatedProfileId, _productDetailsParamsList, _subscriptionUpdateParams);
        }

    private:
        friend class GoogleBillingToNative;
        bool _isOfferPersonalized{false};
        std::string _obfuscatedAccountid;
        std::string _obfuscatedProfileId;
        std::vector<ProductDetailsParams*> _productDetailsParamsList;
        SubscriptionUpdateParams* _subscriptionUpdateParams{nullptr};
    };
    static Builder* newBuilder() {
        return new Builder();
    }

private:
    friend class GoogleBillingHelper;
    friend class GoogleBillingToNative;
    BillingFlowParams(bool isOfferPersonalized,
                      const std::string& obfuscatedAccountid,
                      const std::string& obfuscatedProfileId,
                      const std::vector<ProductDetailsParams*>& productDetailsParamsList,
                      SubscriptionUpdateParams* subscriptionUpdateParams) {
        _isOfferPersonalized = isOfferPersonalized;
        _obfuscatedAccountid = obfuscatedAccountid;
        _obfuscatedProfileId = obfuscatedProfileId;
        _productDetailsParamsList = productDetailsParamsList;
        _subscriptionUpdateParams = subscriptionUpdateParams;
    }
    bool _isOfferPersonalized{false};
    std::string _obfuscatedAccountid;
    std::string _obfuscatedProfileId;
    std::vector<ProductDetailsParams*> _productDetailsParamsList;
    SubscriptionUpdateParams* _subscriptionUpdateParams{nullptr};
};

class ConsumeParams {
public:
    class Builder {
    public:
        Builder& setPurchaseToken(const std::string& purchaseToken) {
            this->_purchaseToken = purchaseToken;
            return *this;
        }

        ConsumeParams* build() {
            return new ConsumeParams(this->_purchaseToken);
        }

    private:
        std::string _purchaseToken;
    };

    std::string getPurchaseToken() const {
        return _purchaseToken;
    }

    static Builder* newBuilder() {
        return new Builder();
    }

private:
    ConsumeParams(const std::string& purchaseToken) {
        this->_purchaseToken = purchaseToken;
    }

    std::string _purchaseToken;
};

class AcknowledgePurchaseParams {
public:
    class Builder {
    public:
        Builder& setPurchaseToken(const std::string& purchaseToken) {
            this->_purchaseToken = purchaseToken;
            return *this;
        }

        AcknowledgePurchaseParams* build() {
            return new AcknowledgePurchaseParams(this->_purchaseToken);
        }

    private:
        std::string _purchaseToken;
    };

    std::string getPurchaseToken() const {
        return _purchaseToken;
    }

    static Builder* newBuilder() {
        return new Builder();
    }

private:
    AcknowledgePurchaseParams(const std::string& purchaseToken) {
        this->_purchaseToken = purchaseToken;
    }

    std::string _purchaseToken;
};

class QueryPurchasesParams {
public:
    class Builder {
    public:
        Builder& setProductType(const std::string& productType) {
            this->_productType = productType;
            return *this;
        }

        QueryPurchasesParams* build() {
            return new QueryPurchasesParams(this->_productType);
        }

    private:
        std::string _productType;
    };

    static Builder* newBuilder() {
        return new Builder();
    }

private:
    QueryPurchasesParams(const std::string& productType) {
        this->_productType = productType;
    }
    friend class BillingClient;
    std::string _productType;
};


class InAppMessageParams {
public:
    class Builder {
    public:
        Builder& addAllInAppMessageCategoriesToShow() {
            this->_inAppMessageCategoryIds.push_back(2);
            return *this;
        }

        Builder& addInAppMessageCategoryToShow(int inAppMessageCategoryId) {
            this->_inAppMessageCategoryIds.push_back(inAppMessageCategoryId);
            return *this;
        }

        InAppMessageParams* build() {
            return new InAppMessageParams(this->_inAppMessageCategoryIds);
        }

    private:
        std::vector<int> _inAppMessageCategoryIds;
    };

    static Builder* newBuilder() {
        return new Builder();
    }

private:
    InAppMessageParams(const std::vector<int>& inAppMessageCategoryIds) {
        this->_inAppMessageCategoryIds = inAppMessageCategoryIds;
    }
    friend class BillingClient;
    std::vector<int> _inAppMessageCategoryIds;
};

class GetBillingConfigParams {
public:
    class Builder {
    public:
        GetBillingConfigParams* build() {
            return new GetBillingConfigParams();
        }
    };

    static Builder* newBuilder() {
        return new Builder();
    }

private:
    GetBillingConfigParams() {
    }
};



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

        Builder& enableUserChoiceBilling(se::Object* listener) {
            listener->root();
            listener->incRef();
            userChoiceBillingListener = listener;
            return *this;
        }

        Builder& setListener(se::Object* listener) {
            listener->root();
            listener->incRef();
            purchasesUpdatedListener = listener;
            // this->invokeListener();
            return *this;
        }

        BillingClient* build() {
            return new BillingClient(this);
        }

    private:
        friend class BillingClient;
        bool _enableAlternativeBillingOnly;
        bool _enableExternalOffer;
        PendingPurchasesParams* _pendingPurchasesParams;
        se::Object* purchasesUpdatedListener;
        se::Object* userChoiceBillingListener;
    };
    static Builder* newBuilder() {
        return new Builder();
    }
    BillingClient(Builder* builder);
    ~BillingClient();
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
    friend class GoogleBillingHelper;
    int _tag{-1};
    bool _enableAlternativeBillingOnly{false};
    bool _enableExternalOffer{false};

    se::Object* purchasesUpdatedListener{nullptr};
    se::Object* userChoiceBillingListener{nullptr};
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
