/* eslint-disable @typescript-eslint/no-namespace */
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
*****************************************************************************/

import { EventTarget } from '../../../cocos/core/event';

export namespace google {
    export namespace billing {
        export const BillingClient = jsb.BillingClient;
        export const BillingResult = jsb.BillingResult;

        export const PendingPurchasesParams = jsb.PendingPurchasesParams;

        // export const ProductDetailsParams = jsb.ProductDetailsParams;
        export const QueryProductDetailsParams = jsb.QueryProductDetailsParams;

        export const Product = jsb.Product;
        export const BillingFlowParams = jsb.BillingFlowParams;

        export const ConsumeParams = jsb.ConsumeParams;
        export const AcknowledgePurchaseParams = jsb.AcknowledgePurchaseParams;
        export const QueryPurchasesParams = jsb.QueryPurchasesParams;
        export const InAppMessageParams = jsb.InAppMessageParams;
        export const GetBillingConfigParams = jsb.GetBillingConfigParams;
    }
}

export declare namespace google {
    export namespace billing {
        export type UserChoiceDetails = jsb.UserChoiceDetails;
        export type OneTimePurchaseOfferDetails = jsb.OneTimePurchaseOfferDetails;
        export type InstallmentPlanDetails = jsb.InstallmentPlanDetails;
        export type PricingPhase = jsb.PricingPhase;
        export type SubscriptionOfferDetails = jsb.SubscriptionOfferDetails;
        export type ProductDetails = jsb.ProductDetails;
        export type AccountIdentifiers = jsb.AccountIdentifiers;
        export type PendingPurchaseUpdate = jsb.PendingPurchaseUpdate;
        export type Purchase = jsb.Purchase;
        export type BillingConfig = jsb.BillingConfig;
        export type AlternativeBillingOnlyReportingDetails = jsb.AlternativeBillingOnlyReportingDetails;
        export type ExternalOfferReportingDetails = jsb.ExternalOfferReportingDetails;
        export type InAppMessageResult = jsb.InAppMessageResult;
        export type BillingClient = jsb.BillingClient;
        export type BillingResult = jsb.BillingResult;
        export type PendingPurchasesParams = jsb.PendingPurchasesParams;
        export type QueryProductDetailsParams = jsb.QueryProductDetailsParams;
        export type Product = jsb.Product;
        export namespace BillingFlowParams {
            //export type Builder = typeof jsb.BillingFlowParamsBuilder;
            export type SubscriptionUpdateParams = jsb.SubscriptionUpdateParams;
            export type ProductDetailsParams = jsb.ProductDetailsParams;
        }
        export type ConsumeParams = jsb.ConsumeParams;
        export type AcknowledgePurchaseParams = jsb.AcknowledgePurchaseParams;
        export type QueryPurchasesParams = jsb.QueryPurchasesParams;
        export type InAppMessageParams = jsb.InAppMessageParams;
        export type GetBillingConfigParams = jsb.GetBillingConfigParams;
    }
}
// export declare namespace BillingFlowParams {
//     export type Builder = jsb.BillingFlowParamsBuilder;
//     export type SubscriptionUpdateParams = jsb.SubscriptionUpdateParams;
//     export type ProductDetailsParams = jsb.ProductDetailsParams;
// }
// export type  BillingFlowParams = jsb.BillingFlowParams;
// export const BillingFlowParams: typeof jsb.BillingFlowParams = jsb.BillingFlowParams;

// export declare namespace google {
//     export namespace BillingFlowParams {
//         export type Builder = jsb.BillingFlowParamsBuilder;
//         export type SubscriptionUpdateParams = jsb.SubscriptionUpdateParams;
//         export type ProductDetailsParams = jsb.ProductDetailsParams;
//     }
//     export type  BillingFlowParams = jsb.BillingFlowParams;
//     export const BillingFlowParams: typeof jsb.BillingFlowParams = jsb.BillingFlowParams;
// }
