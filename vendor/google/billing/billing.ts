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

import { JSB } from 'internal:constants';
import './billing-enum';

declare const jsb: any;

export namespace google {
    export namespace billing {
        export const BillingClient = JSB ? jsb.BillingClient : null;
        export const BillingResult = JSB ? jsb.BillingResult : null;

        export const PendingPurchasesParams = JSB ? jsb.PendingPurchasesParams : null;

        // export const ProductDetailsParams = jsb.ProductDetailsParams;
        export const QueryProductDetailsParams = JSB ? jsb.QueryProductDetailsParams : null;

        export const Product = JSB ? jsb.Product : null;
        export const BillingFlowParams = JSB ? jsb.BillingFlowParams : null;

        export const ConsumeParams = JSB ? jsb.ConsumeParams : null;
        export const AcknowledgePurchaseParams = JSB ? jsb.AcknowledgePurchaseParams : null;
        export const QueryPurchasesParams = JSB ? jsb.QueryPurchasesParams : null;
        export const InAppMessageParams = JSB ? jsb.InAppMessageParams : null;
        export const GetBillingConfigParams = JSB ? jsb.GetBillingConfigParams : null;
    }
}

export declare namespace google {
    export namespace billing {
        export type UserChoiceDetails = jsb.UserChoiceDetails;
        export type OneTimePurchaseOfferDetails = jsb.OneTimePurchaseOfferDetails;
        export type InstallmentPlanDetails = jsb.InstallmentPlanDetails;
        export type PricingPhase = jsb.PricingPhase;
        export type SubscriptionOfferDetails = jsb.SubscriptionOfferDetails;

        export type AccountIdentifiers = jsb.AccountIdentifiers;
        export type PendingPurchaseUpdate = jsb.PendingPurchaseUpdate;

        export type BillingConfig = jsb.BillingConfig;
        export type AlternativeBillingOnlyReportingDetails = jsb.AlternativeBillingOnlyReportingDetails;
        export type ExternalOfferReportingDetails = jsb.ExternalOfferReportingDetails;
        export type InAppMessageResult = jsb.InAppMessageResult;

        export type BillingResult = jsb.BillingResult;
        export type PendingPurchasesParams = jsb.PendingPurchasesParams;

        export namespace ProductDetails {
            export type RecurrenceMode = jsb.RecurrenceMode;
        }
        export type ProductDetails = jsb.ProductDetails;

        export namespace Purchase {
            export type PurchaseState = jsb.PurchaseState;
        }
        export type Purchase = jsb.Purchase;

        export type BillingClient = jsb.BillingClient;
        export namespace BillingFlowParams {
            export type Builder = jsb.BillingFlowParamsBuilder;
            export type SubscriptionUpdateParams = jsb.SubscriptionUpdateParams;
            export type ProductDetailsParams = jsb.ProductDetailsParams;
        }
        export type BillingFlowParams = jsb.BillingFlowParams;

        export namespace QueryProductDetailsParams {
            export type Product = jsb.Product;
        }
        export type QueryProductDetailsParams = jsb.QueryProductDetailsParams;

        export type ConsumeParams = jsb.ConsumeParams;
        export type AcknowledgePurchaseParams = jsb.AcknowledgePurchaseParams;
        export type QueryPurchasesParams = jsb.QueryPurchasesParams;
        export type InAppMessageParams = jsb.InAppMessageParams;
        export type GetBillingConfigParams = jsb.GetBillingConfigParams;

    }
}
