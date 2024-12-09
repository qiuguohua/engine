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

namespace cc {

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
        friend class JniBilling;
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
        friend class JniBilling;
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
        friend class JniBilling;
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
        friend class JniBilling;
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
        friend class JniBilling;
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
    friend class JniBilling;
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

} // namespace cc
