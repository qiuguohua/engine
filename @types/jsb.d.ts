// some interfaces might be overridden
/* eslint-disable import/no-mutable-exports */

/**
 * API for jsb module
 * Author: haroel
 * Homepage: https://github.com/haroel/creatorexDTS
 *
 * @deprecated since v3.6.0, please import `native` from 'cc' module instead like `import { native } from 'cc';`.
 */
declare namespace jsb {

    let window: any;

    type AccelerationXYZ = number;
    type AccelerationIncludingGravityXYZ = number;
    type RotationRateAlpha = number;
    type RotationRateBeta = number;
    type RotationRateGamma = number;
    type DeviceMotionValue = [AccelerationXYZ, AccelerationXYZ, AccelerationXYZ,
        AccelerationIncludingGravityXYZ, AccelerationIncludingGravityXYZ, AccelerationIncludingGravityXYZ,
        RotationRateAlpha, RotationRateBeta, RotationRateGamma];
    export namespace device {
        export function getBatteryLevel(): number;
        export function getDevicePixelRatio(): number;
        export function getDeviceOrientation(): number;
        export function getNetworkType(): number; // TODO: enum type
        export function getSafeAreaEdge(): NativeSafeAreaEdge;

        export function setAccelerometerEnabled(isEnabled: boolean);
        export function setAccelerometerInterval(intervalInSeconds: number);
        export function getDeviceMotionValue(): DeviceMotionValue;
    }

    export interface NativeSafeAreaEdge {
        /**
         * top
         */
        x: number;
        /**
         * left
         */
        y: number;
        /**
         * bottom
         */
        z: number;
        /**
         * right
         */
        w: number;
    }

    export interface MouseEvent {
        x: number,
        y: number,
        xDelta: number | undefined,
        yDelta: number | undefined,
        button: number,
        windowId: number,
    }
    type MouseEventCallback = (mouseEvent: MouseEvent) => void;
    export interface MouseWheelEvent extends MouseEvent {
        wheelDeltaX: number,
        wheelDeltaY: number,
    }
    type MouseWheelEventCallback = (mouseEvent: MouseWheelEvent) => void;
    export let onMouseDown: MouseEventCallback | undefined;
    export let onMouseMove: MouseEventCallback | undefined;
    export let onMouseUp: MouseEventCallback | undefined;
    export let onMouseWheel: MouseWheelEventCallback | undefined;

    type TouchEventCallback = (touchList: TouchList, windowId?: number) => void;
    export let onTouchStart: TouchEventCallback | undefined;
    export let onTouchMove: TouchEventCallback | undefined;
    export let onTouchEnd: TouchEventCallback | undefined;
    export let onTouchCancel: TouchEventCallback | undefined;

    export interface ControllerInfo {
        id: number;
        axisInfoList: AxisInfo[],
        buttonInfoList: ButtonInfo[],
        touchInfoList: TouchInfo[],
    }

    export interface AxisInfo {
        code: number,
        value: number,
    }

    export interface ButtonInfo {
        code: number,
        isPressed: boolean,
    }

    export interface TouchInfo {
        code: number,
        value: number,
    }

    export let onControllerInput: (infoList: ControllerInfo[]) => void | undefined;
    export let onHandleInput: (infoList: ControllerInfo[]) => void | undefined;
    export let onControllerChange: (controllerIds: number[]) => void | undefined;

    export interface PoseInfo {
        code: number,
        x: number,
        y: number,
        z: number,
        quaternionX: number,
        quaternionY: number,
        quaternionZ: number,
        quaternionW: number,
    }

    export let onHandlePoseInput: (infoList: PoseInfo[]) => void | undefined;
    export let onHMDPoseInput: (infoList: PoseInfo[]) => void | undefined;
    export let onHandheldPoseInput: (infoList: PoseInfo[]) => void | undefined;

    export interface KeyboardEvent {
        altKey: boolean;
        ctrlKey: boolean;
        metaKey: boolean;
        shiftKey: boolean;
        repeat: boolean;
        keyCode: number;
        windowId: number;
        code: string;
    }
    type KeyboardEventCallback = (keyboardEvent: KeyboardEvent) => void;
    export let onKeyDown: KeyboardEventCallback | undefined;
    export let onKeyUp: KeyboardEventCallback | undefined;

    export interface WindowEvent {
        windowId: number;
        width: number;
        height: number;
    }

    /**
     * @en WindowEvent.width and WindowEvent.height have both been multiplied by DPR
     * @zh WindowEvent.width 和 WindowEvent.height 都已乘以 DPR
     */
    export let onResize: (event: WindowEvent) => void | undefined;
    export let onOrientationChanged: (event: { orientation: number }) => void | undefined;  // TODO: enum orientation type
    export let onResume: () => void | undefined;
    export let onPause: () => void | undefined;
    export let onClose: () => void | undefined;
    export let onWindowLeave: () => void | undefined;
    export let onWindowEnter: () => void | undefined;
    export function openURL(url: string): void;
    export function garbageCollect(): void;
    enum AudioFormat {
        UNKNOWN,
        SIGNED_8,
        UNSIGNED_8,
        SIGNED_16,
        UNSIGNED_16,
        SIGNED_32,
        UNSIGNED_32,
        FLOAT_32,
        FLOAT_64
    }
    interface PCMHeader {
        totalFrames: number;
        sampleRate: number;
        bytesPerFrame: number;
        audioFormat: AudioFormat;
        channelCount: number;
    }
    export namespace AudioEngine {
        export function preload(url: string, cb: (isSuccess: boolean) => void);

        export function play2d(url: string, loop: boolean, volume: number): number;
        export function pause(id: number);
        export function pauseAll();
        export function resume(id: number);
        export function resumeAll();
        export function stop(id: number);
        export function stopAll();

        export function getPlayingAudioCount(): number;
        export function getMaxAudioInstance(): number;
        export function getState(id: number): any;
        export function getDuration(id: number): number;
        export function getVolume(id: number): number;
        export function isLoop(id: number): boolean;
        export function getCurrentTime(id: number): number;

        export function setVolume(id: number, val: number);
        export function setLoop(id: number, val: boolean);
        export function setCurrentTime(id: number, val: number);

        export function uncache(url: string);
        export function uncacheAll();
        export function setErrorCallback(id: number, cb: (err: any) => void);
        export function setFinishCallback(id: number, cb: () => void);

        /**
         * Get PCM header without pcm data. if you want to get pcm data, use getOriginalPCMBuffer instead
         */
        export function getPCMHeader(url: string): PCMHeader;
        /**
         * Get PCM Data in decode format for example Int16Array, the format information is written in PCMHeader.
         * @param url: file relative path, for example player._path
         * @param channelID: ChannelID which should smaller than channel count, start from 0
         */
        export function getOriginalPCMBuffer(url: string, channelID: number): ArrayBuffer | undefined;
    }

    class NativePOD {
        underlyingData(): ArrayBuffer;
        _data(): TypedArray;
        __data: TypedArray;
    }

    export class Color extends NativePOD {
    }
    export class Quat extends NativePOD {
    }
    export class Vec2 extends NativePOD {
    }
    export class Vec3 extends NativePOD {
    }
    export class Vec4 extends NativePOD {
    }

    export class Mat3 extends NativePOD {
    }
    export class Mat4 extends NativePOD {
    }
    export interface ManifestAsset {
        md5: string;
        path: string;
        compressed: boolean;
        size: number;
        downloadState: number;
    }

    export class Manifest {
        constructor(manifestUrl: string);
        constructor(content: string, manifestRoot: string);
        parseFile(manifestUrl: string): void;
        parseJSONString(content: string, manifestRoot: string): void;

        getManifestRoot(): string;
        getManifestFileUrl(): string;
        getVersionFileUrl(): string;
        getSearchPaths(): [string];
        getVersion(): string;
        getPackageUrl(): boolean;

        setUpdating(isUpdating: boolean): void;
        isUpdating(): boolean;
        isVersionLoaded(): boolean;
        isLoaded(): boolean;
    }

    export class EventAssetsManager {
        // EventCode
        static ERROR_NO_LOCAL_MANIFEST: number;
        static ERROR_DOWNLOAD_MANIFEST: number;
        static ERROR_PARSE_MANIFEST: number;
        static NEW_VERSION_FOUND: number;
        static ALREADY_UP_TO_DATE: number;
        static UPDATE_PROGRESSION: number;
        static ASSET_UPDATED: number;
        static ERROR_UPDATING: number;
        static UPDATE_FINISHED: number;
        static UPDATE_FAILED: number;
        static ERROR_DECOMPRESS: number;

        constructor(eventName: string, manager: AssetsManager, eventCode: number,
            assetId?: string, message?: string, curleCode?: number, curlmCode?: number);
        getAssetsManagerEx(): AssetsManager;
        isResuming(): boolean;

        getDownloadedFiles(): number;
        getDownloadedBytes(): number;
        getTotalFiles(): number;
        getTotalBytes(): number;
        getPercent(): number;
        getPercentByFile(): number;

        getEventCode(): number;
        getMessage(): string;
        getAssetId(): string;
        getCURLECode(): number;
        getCURLMCode(): number;
    }

    export namespace AssetsManager {
        export enum State {
            UNINITED,
            UNCHECKED,
            PREDOWNLOAD_VERSION,
            DOWNLOADING_VERSION,
            VERSION_LOADED,
            PREDOWNLOAD_MANIFEST,
            DOWNLOADING_MANIFEST,
            MANIFEST_LOADED,
            NEED_UPDATE,
            READY_TO_UPDATE,
            UPDATING,
            UNZIPPING,
            UP_TO_DATE,
            FAIL_TO_UPDATE,
        }
    }

    export class AssetsManager {
        constructor(manifestUrl: string, storagePath: string, versionCompareHandle?: (versionA: string, versionB: string) => number);
        static create(manifestUrl: string, storagePath: string): AssetsManager;

        getState(): AssetsManager.State;
        getStoragePath(): string
        getMaxConcurrentTask(): number;
        // setMaxConcurrentTask (max: number): void;  // actually not supported

        checkUpdate(): void;
        prepareUpdate(): void;
        update(): void;
        isResuming(): boolean;

        getDownloadedFiles(): number;
        getDownloadedBytes(): number;
        getTotalFiles(): number;
        getTotalBytes(): number;
        downloadFailedAssets(): void;

        getLocalManifest(): Manifest;
        loadLocalManifest(manifestUrl: string): boolean;
        loadLocalManifest(localManifest: Manifest, storagePath: string): boolean;
        getRemoteManifest(): Manifest;
        loadRemoteManifest(remoteManifest: Manifest): boolean;

        /**
         * Setup your own version compare handler, versionA and B is versions in string.
         * if the return value greater than 0, versionA is greater than B,
         * if the return value equals 0, versionA equals to B,
         * if the return value smaller than 0, versionA is smaller than B.
         */
        setVersionCompareHandle(versionCompareHandle?: (versionA: string, versionB: string) => number): void;
        /**
         * Setup the verification callback, Return true if the verification passed, otherwise return false
         */
        setVerifyCallback(verifyCallback: (path: string, asset: ManifestAsset) => boolean): void;
        setEventCallback(eventCallback: (event: EventAssetsManager) => void): void;
    }

    // Android ADPF module
    const adpf: {
        readonly thermalHeadroom: number;
        readonly thermalStatus: number;
        readonly thermalStatusMin: number;
        readonly thermalStatusMax: number;
        readonly thermalStatusNormalized: number;
        onThermalStatusChanged?: (previousStatus: number, newStatus: number, statusMin: number, statusMax: number) => void;
    } | undefined;

    export interface UserChoiceDetailsProduct {
        hashCode(): number;
        getId(): string;
        getOfferToken(): string;
        getType(): string;
        toStr(): string;
        equals(product: Product): boolean;
    }
    export class UserChoiceDetails {
        getExternalTransactionToken(): string;
        getOriginalExternalTransactionId(): string;
        getProducts(): UserChoiceDetailsProduct[];
    }

    /**
     * @en Represents the offer details to buy an one-time purchase product.
     * @zh 代表一次性购买产品的报价详情。
     */
    export interface OneTimePurchaseOfferDetails {
        /**
         * @en The price for the payment in micro-units, where 1,000,000 micro-units equal one unit of the currency.
         * @zh 以微单位返回支付价格，其中 1,000,000 个微单位等于 1 个货币单位。
         */
        getPriceAmountMicros(): number;
        /**
         * @en Formatted price for the payment, including its currency sign.
         * @zh 支付的格式化价格，包括其货币单位。
         */
        getFormattedPrice(): string;
        /**
         * @en ISO 4217 currency code for price.
         * @zh 价格的 ISO 4217 货币代码。
         */
        getPriceCurrencyCode(): string;
    }

    /**
     * @en Represents additional details of an installment subscription plan.
     * @zh 表示分期付款订阅计划的附加详细信息。
     */
    export interface InstallmentPlanDetails {
        /**
         * @en Committed payments count after a user signs up for this subscription plan.
         * @zh 用户注册此订阅计划后承诺的付款数量。
         */
        getInstallmentPlanCommitmentPaymentsCount(): number;
        /**
         * @en Subsequent committed payments count after this subscription plan renews.
         * @zh 此订阅计划续订后的后续承诺付款数量。
         */
        getSubsequentInstallmentPlanCommitmentPaymentsCount(): number;
    }

    /**
     * @en Represents a pricing phase, describing how a user pays at a point in time.
     * @zh 表示定价阶段，描述用户在某个时间点如何付款。
     */
    export interface PricingPhase {
        /**
         * @en Number of cycles for which the billing period is applied.
         * @zh 计费周期适用的周期数。
         */
        getBillingCycleCount(): number;
        /**
         * @en The price for the payment cycle in micro-units, where 1,000,000 micro-units equal one unit of the currency.
         * @zh 微单位付款周期的价格，其中 1,000,000 个微单位等于 1 个货币单位。
         */
        getPriceAmountMicros(): number;
        /**
         * @en RecurrenceMode for the pricing phase.
         * @zh 定价阶段的RecurrenceMode。
         */
        getRecurrenceMode(): number;
        /**
         * @en Billing period for which the given price applies, specified in ISO 8601 format.
         * @zh 给定价格适用的计费期，以 ISO 8601 格式指定。
         */
        getBillingPeriod(): string;
        /**
         * @en Formatted price for the payment cycle, including its currency sign.
         * @zh 付款周期的格式化价格，包括其货币符号。
         */
        getFormattedPrice(): string;
        /**
         * @en Returns ISO 4217 currency code for price.
         * @zh 返回价格的 ISO 4217 货币代码。
         */
        getPriceCurrencyCode(): string;
    }

    /**
     * @en Represents a pricing phase, describing how a user pays at a point in time.
     * @zh 表示定价阶段，描述用户在某个时间点如何付款。
     */
    export interface PricingPhases {
        /**
         * @en Returns ISO 4217 currency code for price.
         * @zh 返回价格的 ISO 4217 货币代码。
         */
        getPricingPhaseList(): PricingPhase[];
    }

    /**
     * @en Represents the available purchase plans to buy a subscription product.
     * @zh 代表一次性购买产品的报价详情。
     */
    export interface SubscriptionOfferDetails {
        /**
         * @en The base plan id associated with the subscription product.
         * @zh 与订阅产品相关的基本计划 ID。
         */
        getBasePlanId(): string;
        /**
        * @en The offer id associated with the subscription product.
        * @zh 与订阅产品相关的优惠 ID。
        */
        getOfferId(): string;
        /**
        * @en The offer tags associated with this Subscription Offer.
        * @zh 与此订阅优惠相关的优惠标签。
        */
        getOfferTags(): string[];
        /**
        * @en The offer token required to pass in launchBillingFlow to purchase the subscription product with these pricing phases.
        * @zh 在 launchBillingFlow 中传递以使用这些定价阶段购买订阅产品所需的优惠令牌。
        */
        getOfferToken(): string;
        /**
         * @en The pricing phases for the subscription product.
         * @zh 订阅产品的定价区间。
         */
        getPricingPhases(): PricingPhases;
        /**
        * @en The additional details of an installment plan.
        * @zh 分期付款计划的附加详细信息。
        */
        getInstallmentPlanDetails(): InstallmentPlanDetails;
    }
    /**
     * @en Represents the details of a one time or subscription product.
     * @zh 代表一次性或订阅产品的详细信息。
     */
    export interface ProductDetails {
        equals(other: ProductDetails): boolean;
        /**
         * @en Hash code
         * @zh hash值
         */
        hashCode(): number;
        /**
         * @en The description of the product.
         * @zh 产品的描述。
         */
        getDescription(): string;
        /**
         * @en The name of the product being sold.
         * @zh 所售产品的名称。
         */
        getName(): string;
        /**
         * @en The product's Id.
         * @zh 产品的 ID。
         */
        getProductId(): string;
        /**
         * @en The ProductType of the product.
         * @zh ProductType产品的。
         */
        getProductType(): string;
        /**
         * @en The title of the product being sold.
         * @zh 所售产品的标题。
         */
        getTitle(): string;
        /**
         * @en To string
         * @zh 转换成字符串
         */
        toStr(): string;
        /**
         * @en The offer details of an one-time purchase product.
         * @zh 代表一次性购买产品的报价详情。
         */
        getOneTimePurchaseOfferDetails(): OneTimePurchaseOfferDetails;
        /**
         * @en A list containing all available offers to purchase a subscription product.
         * @zh 返回包含购买订阅产品的所有可用优惠的列表。
         */
        getSubscriptionOfferDetails(): SubscriptionOfferDetails[];
    }

    /**
     * @en Account identifiers that were specified when the purchase was made.
     * @zh 购买时指定的帐户标识符。
     */
    export interface AccountIdentifiers {
        /**
         * @en The obfuscated account id specified in setObfuscatedAccountId.
         * @zh 在setObfuscatedAccountId中设置的混淆账户id
         */
        getObfuscatedAccountId(): string;
        /**
         * @en The obfuscated profile id specified in setObfuscatedProfileId.
         * @zh 在setObfuscatedProfileId中设置的混淆profile id
         */
        getObfuscatedProfileId(): string;
    }

    /**
     * @en Represents a pending change/update to the existing purchase.
     * @zh 表示对现有购买的待定更改/更新。
     */
    export interface PendingPurchaseUpdate {
        /**
         * @en A token that uniquely identifies this pending transaction.
         * @zh 唯一标识此待处理交易的令牌。
         */
        getPurchaseToken(): string;
        /**
         * @en The product ids.
         * @zh 产品 ID。
         */
        getProducts(): string[];
    }

    /**
     * @en Represents an in-app billing purchase.
     * @zh 代表应用内billing购买。
     */
    export interface Purchase {
        /**
         * @en One of PurchaseState indicating the state of the purchase.
         * @zh PurchaseState表示购买状态的其中一个值。
         */
        getPurchaseState(): number;
        /**
         * @en The time the product was purchased, in milliseconds since the epoch (Jan 1, 1970).
         * @zh 产品购买的时间，以纪元（1970 年 1 月 1 日）以来的毫秒数表示。
         */
        getPurchaseTime(): number;
        /**
         * @en Indicates whether the purchase has been acknowledged.
         * @zh 表示是否已确认购买。
         */
        isAcknowledged(): number;
        /**
         * @en Indicates whether the subscription renews automatically.
         * @zh 指示订阅是否自动续订。
         */
        isAutoRenewing(): number;
        /**
         * @en Hash code
         * @zh hash值
         */
        hashCode(): number;

        /**
         * @en The quantity of the purchased product.
         * @zh 购买产品的数量。
         */
        getQuantity(): number;
        /**
         * @en The payload specified when the purchase was acknowledged or consumed.
         * @zh 确认或消费购买时指定的有效负载。
         */
        getDeveloperPayload(): string;
        /**
         * @en Returns a unique order identifier for the transaction.
         * @zh 交易的唯一订单标识符。
         */
        getOrderId(): string;
        /**
         * @en Returns a String in JSON format that contains details about the purchase order.
         * @zh 包含有关采购订单详细信息的 JSON 格式的字符串。
         */
        getOriginalJson(): string;
        /**
         * @en The application package from which the purchase originated.
         * @zh 购买来源的应用程序包。
         */
        getPackageName(): string;
        /**
         * @en A token that uniquely identifies a purchase for a given item and user pair.
         * @zh 唯一标识给定商品和用户对的购买的令牌。
         */
        getPurchaseToken(): string;
        /**
         * @en String containing the signature of the purchase data that was signed with the private key of the developer.
         * @zh 包含使用开发者私钥签名的购买数据签名的字符串。
         */
        getSignature(): string;
        /**
         * @en To string
         * @zh 转换成字符串
         */
        toStr(): string;

        /**
         * @en Returns account identifiers that were provided when the purchase was made.
         * @zh 返回购买时提供的帐户标识符。
         */
        getAccountIdentifiers(): AccountIdentifiers;
        /**
         * @en The PendingPurchaseUpdate for an uncommitted transaction.
         * @zh 返回PendingPurchaseUpdate未提交的事务。
         */
        getPendingPurchaseUpdate(): PendingPurchaseUpdate;
        /**
         * @en the product Ids.
         * @zh 产品 ID。
         */
        getProducts(): string[];
    }

    export interface BillingConfig {
        /**
         * @en The customer's country code.
         * @zh 客户的国家代码。
         */
        getCountryCode(): string;
    }

    /**
     * @en The details used to report transactions made via alternative billing without user choice to use Google Play Billing.
     * @zh 用于报告用户未选择使用 Google Play Billing方式而通过替代Billing方式进行的交易的详细信息。
     */
    export interface AlternativeBillingOnlyReportingDetails {
        /**
         * @en An external transaction token that can be used to report a transaction made via alternative billing
         *     without user choice to use Google Play billing.
         * @zh 返回一个外部交易令牌，该令牌可用于报告通过替代付款方式进行的交易，而无需用户选择使用 Google Play 付款方式。
         */
        getExternalTransactionToken(): string;
    }

    /**
     * @en The details used to report transactions made via external offer.
     * @zh 用于报告通过外部报价进行的交易的详细信息。
     */
    export interface ExternalOfferReportingDetails {
        /**
         * @en An external transaction token that can be used to report a transaction made via external offer.
         * @zh 可用于报告通过外部报价进行的交易的外部交易令牌。
         */
        getExternalTransactionToken(): string;
    }

    /**
     * @en Results related to in-app messaging.
     * @zh 与应用程序内消息相关的结果。
     */
    export interface InAppMessageResult {
        /**
         * @en Response code for the in-app messaging API call.
         * @zh 应用内消息传递 API 调用的响应代码。
         */
        getResponseCode(): number;
        /**
         * @en Token that identifies the purchase to be acknowledged, if any.
         * @zh 返回标识需要确认的购买的令牌。
         */
        getPurchaseToken(): string;
    }

    export interface BillingResultBuilder {
        setDebugMessage(productType: string): BillingResultBuilder;
        setResponseCode(productType: number): BillingResultBuilder;
        build(): BillingResult;
    }
    export class BillingResult {
        static Builder: {
            new(): BillingResultBuilder
        };
        getResponseCode(): number;
        getDebugMessage(): string;
        toStr(): string;
        public static newBuilder(): BillingResultBuilder;
    }

    export namespace BillingResult {
        type Builder = BillingResultBuilder;
    }

    export interface UserChoiceBillingListener {
        userSelectedAlternativeBilling(userChoiceDetails: UserChoiceDetails): void;
    }
    export interface PurchasesUpdatedListener {
        onPurchasesUpdated(billingResult: BillingResult, purchases: Purchase[]): void;
    }
    export interface BillingClientStateListener {
        onBillingServiceDisconnected(): void;
        onBillingSetupFinished(
            billingResult: BillingResult,
        ): void;
    }

    export interface PendingPurchasesParamsBuilder {
        enableOneTimeProducts: () => PendingPurchasesParamsBuilder;
        enablePrepaidPlans: () => PendingPurchasesParamsBuilder;
        build: () => PendingPurchasesParams;
    }

    export class PendingPurchasesParams {
        private constructor();
        public static newBuilder(): PendingPurchasesParamsBuilder;
    }

    export interface ProductBuilder {
        setProductId: (productID: string) => ProductBuilder;
        setProductType: (productType: string) => ProductBuilder;
        build: () => Product;
    }
    export class Product {
        private constructor();
        public static newBuilder(): ProductBuilder;
    }

    export interface QueryProductDetailsParamsBuilder {
        setProductList: (products: Product[]) => QueryProductDetailsParamsBuilder;
        build: () => QueryProductDetailsParams;
    }
    export class QueryProductDetailsParams {
        private constructor();
        public static newBuilder(): QueryProductDetailsParamsBuilder;
    }

    export interface ProductDetailsResponseListener {
        onProductDetailsResponse(billingResult: BillingResult, productDetailsList: ProductDetails[]): void;
    }

    export interface ConsumeResponseListener {
        onConsumeResponse(billingResult: BillingResult, token: string): void
    }

    export interface AcknowledgePurchaseResponseListener {
        onAcknowledgePurchaseResponse(
            billingResult: BillingResult
        ): void
    }

    export interface BillingClientBuilder {
        enableAlternativeBillingOnly: () => BillingClientBuilder;
        enableExternalOffer: () => BillingClientBuilder;
        enablePendingPurchases: (params: PendingPurchasesParams) => BillingClientBuilder;
        enableUserChoiceBilling: (userChoiceBillingListener: UserChoiceBillingListener) => BillingClientBuilder;
        setListener: (listener: PurchasesUpdatedListener) => BillingClientBuilder;
        build: () => BillingClient;
    }

    export interface PurchasesResponseListener {
        onQueryPurchasesResponse(
            billingResult: BillingResult,
            purchase: Purchase[]
        ): void
    }

    export interface BillingConfigResponseListener {
        onBillingConfigResponse(
            billingResult: BillingResult,
            billingConfig: BillingConfig
        ): void
    }
    export interface AlternativeBillingOnlyReportingDetailsListener {
        onAlternativeBillingOnlyTokenResponse(
            billingResult: BillingResult,
            alternativeBillingOnlyReportingDetails: AlternativeBillingOnlyReportingDetails
        ): void
    }

    export interface ExternalOfferReportingDetailsListener {
        onExternalOfferReportingDetailsResponse(
            billingResult: BillingResult,
            externalOfferReportingDetails: ExternalOfferReportingDetails
        ): void
    }

    export interface AlternativeBillingOnlyAvailabilityListener {
        onAlternativeBillingOnlyAvailabilityResponse(
            billingResult: BillingResult
        ): void
    }

    export interface ExternalOfferAvailabilityListener {
        onExternalOfferAvailabilityResponse(
            billingResult: BillingResult
        ): void
    }
    export interface AlternativeBillingOnlyInformationDialogListener {
        onAlternativeBillingOnlyInformationDialogResponse(
            billingResult: BillingResult
        ): void
    }
    export interface ExternalOfferInformationDialogListener {
        onExternalOfferInformationDialogResponse(
            billingResult: BillingResult
        ): void
    }
    export interface InAppMessageResponseListener {
        onInAppMessageResponse(
            inAppMessageResult: InAppMessageResult
        ): void
    }

    /**
     * @en
     * Connection state of billing client.
     *
     * @zh
     * Billing client的连接状态
     */
    export enum ConnectionState {
        /**
         * @en
         * This client was not yet connected to billing service or was already closed.
         *
         * @zh
         * 此客户端尚未连接到Billing服务或已关闭。
         */
        DISCONNECTED = 0,
        /**
         * @en
         * This client is currently in process of connecting to billing service.
         *
         * @zh
         * 此客户端目前正在连接到Billing服务。
         */
        CONNECTING = 1,
        /**
         * @en
         * This client is currently connected to billing service.
         *
         * @zh
         * 此客户端当前已连接到Billing服务。
         */
        CONNECTED = 2,
        /**
         * @en
         * This client was already closed and shouldn't be used again.
         *
         * @zh
         * 该客户端已关闭，不应再次使用。
         */
        CLOSED = 3,
    }
    /**
     * @en
     * Possible response codes.
     *
     * @zh
     * 可能的响应代码。
     */
    export enum BillingResponseCode {
        /**
         * @en
         * This field is deprecated.
         * See SERVICE_UNAVAILABLE which will be used instead of this code.
         *
         * @zh
         * 这个字段已经废弃。
         * 看看SERVICE_UNAVAILABLE将使用哪一个来代替此代码。
         */
        SERVICE_TIMEOUT = -3,
        /**
         * @en
         * The requested feature is not supported by the Play Store on the current device.
         *
         * @zh
         * 当前设备上的 Play Store 不支持所请求的功能。
         */
        FEATURE_NOT_SUPPORTED = -2,
        /**
         * @en
         * The app is not connected to the Play Store service via the Google Play Billing Library.
         *
         * @zh
         * 该应用未通过 Google Play Billing库连接到 Play Store 服务。
         */
        SERVICE_DISCONNECTED = -1,
        /**
         * @en
         * Success.
         *
         * @zh
         * 成功。
         */
        OK = 0,
        /**
         * @en
         * Transaction was canceled by the user.
         *
         * @zh
         * 交易已被用户取消。
         */
        USER_CANCELED = 1,
        /**
         * @en
         * The service is currently unavailable.
         *
         * @zh
         * 当前设备上的 Play Store 不支持所请求的功能。
         */
        SERVICE_UNAVAILABLE = 2,
        /**
         * @en
         * A user billing error occurred during processing.
         *
         * @zh
         * 处理过程中出现用户billing错误。
         */
        BILLING_UNAVAILABLE = 3,
        /**
         * @en
         * The requested product is not available for purchase.
         *
         * @zh
         * 所请求的产品无法购买。
         */
        ITEM_UNAVAILABLE = 4,
        /**
         * @en
         * Error resulting from incorrect usage of the API.
         *
         * @zh
         * 由于错误使用 API 而导致的错误。
         */
        DEVELOPER_ERROR = 5,
        /**
         * @en
         * Fatal error during the API action.
         *
         * @zh
         * API 操作期间发生致命错误。
         */
        ERROR = 6,
        /**
         * @en
         * The purchase failed because the item is already owned.
         *
         * @zh
         * 购买失败，因为该物品已被拥有。
         */
        ITEM_ALREADY_OWNED = 7,
        /**
         * @en
         * Requested action on the item failed since it is not owned by the user.
         *
         * @zh
         * 由于该项目不属于用户，因此对该项目请求的操作失败。
         */
        ITEM_NOT_OWNED = 8,
        /**
         * @en
         * A network error occurred during the operation.
         *
         * @zh
         * 操作期间发生网络错误。
         */
        NETWORK_ERROR = 12,
    }
    /**
     * @en
     * Features/capabilities supported by isFeatureSupported.
     *
     * @zh
     * 支持的特性/能力isFeatureSupported。
     */
    export enum FeatureType {
        /**
         * @en
         * Purchase/query for subscriptions.
         *
         * @zh
         * 购买/查询订阅。
         */
        SUBSCRIPTIONS = 'subscriptions',
        /**
         * @en
         * Subscriptions update/replace.
         *
         * @zh
         * 订阅更新/替换。
         */
        SUBSCRIPTIONS_UPDATE = 'subscriptionsUpdate',
        /**
         * @en
         * Launch a price change confirmation flow.
         *
         * @zh
         * 启动价格变动确认流程。
         */
        PRICE_CHANGE_CONFIRMATION = 'priceChangeConfirmation',
        /**
        * @en
        * Show in-app messages.
        *
        * @zh
        * 显示应用内消息。
        */
        IN_APP_MESSAGING = 'bbb',
        /**
         * @en
         * Play billing library support for querying and purchasing.
         *
         * @zh
         * Play Billing库支持查询、购买。
         */
        PRODUCT_DETAILS = 'fff',
        /**
         * @en
         * Get billing config.
         *
         * @zh
         * 获取计费配置。
         */
        BILLING_CONFIG = 'ggg',
        /**
         * @en
         * Alternative billing only.
         *
         * @zh
         * 仅限替代Billing。
         */
        ALTERNATIVE_BILLING_ONLY = 'jjj',

        /**
         * @en
         * Play billing library support for external offer.
         *
         * @zh
         * Play billing库支持外部报价。
         */
        EXTERNAL_OFFER = 'kkk',
    }

    /**
     * @en
     * Supported Product types.
     *
     * @zh
     * 支持的产品类型。
     */
    export enum ProductType {
        /**
         * @en
         * A Product type for Android apps in-app products.
         *
         * @zh
         * Android 应用内产品的产品类型。
         */
        INAPP = 'inapp',
        /**
         * @en
         * A Product type for Android apps subscriptions.
         *
         * @zh
         * Android 应用程序订阅的产品类型。
         */
        SUBS = 'subs'
    }

    export interface ProductDetailsParamsBuilder {
        setOfferToken: (purchaseToken: string) => ProductDetailsParamsBuilder;
        setProductDetails: (productDetails: ProductDetails) => ProductDetailsParamsBuilder;
        build: () => ProductDetailsParams;
    }
    export class ProductDetailsParams {
        private constructor();
        static newBuilder: () => ProductDetailsParamsBuilder;
    }

    export interface SubscriptionUpdateParamsBuilder {
        setOldPurcchaseToken: (purchaseToken: string) => SubscriptionUpdateParamsBuilder;
        setOriginalExternalTransactionId: (externalTransactionId: string) => SubscriptionUpdateParamsBuilder;
        setSubscriptionReplacementMode: (subscriptionReplacementMode: number) => SubscriptionUpdateParamsBuilder;
        build: () => SubscriptionUpdateParams;
    }
    export class SubscriptionUpdateParams {
        private constructor();
        static newBuilder(): () => SubscriptionUpdateParamsBuilder;
    }

    export class BillingFlowParams {
        static ProductDetailsParams: typeof jsb.ProductDetailsParams;
        static SubscriptionUpdateParams: typeof jsb.SubscriptionUpdateParams;
        static Builder: BillingFlowParamsBuilder;
        private constructor();
        public static newBuilder(): BillingFlowParamsBuilder;
    }

    export interface BillingFlowParamsBuilder {
        setIsOfferPersonalized: (isOfferPersonalized: boolean) => BillingFlowParamsBuilder;
        setObfuscatedAccountId: (obfuscatedAccountid: string) => BillingFlowParamsBuilder;
        setObfuscatedProfileId: (obfuscatedProfileId: string) => BillingFlowParamsBuilder;
        setProductDetailsParamsList: (userChoiceBillingListener: ProductDetailsParams[]) => BillingFlowParamsBuilder;
        setSubscriptionUpdateParams: (userChoiceBillingListener: SubscriptionUpdateParams) => BillingFlowParamsBuilder;
        build: () => BillingFlowParams;
    }

    export interface ConsumeParamsBuilder {
        setPurchaseToken: (purchaseToken: string) => ConsumeParamsBuilder;
        build: () => ConsumeParams;
    }
    export class ConsumeParams {
        private constructor();
        public static newBuilder(): ConsumeParamsBuilder;
    }
    export interface AcknowledgePurchaseParamsBuilder {
        setPurchaseToken: (purchaseToken: string) => AcknowledgePurchaseParamsBuilder;
        build: () => AcknowledgePurchaseParams;
    }
    export class AcknowledgePurchaseParams {
        private constructor();
        public static newBuilder(): AcknowledgePurchaseParamsBuilder;
    }

    export interface QueryPurchasesParamsBuilder {
        setProductType: (productType: string) => QueryPurchasesParamsBuilder;
        build: () => QueryPurchasesParams;
    }
    export class QueryPurchasesParams {
        private constructor();
        public static newBuilder(): QueryPurchasesParamsBuilder;
    }

    export interface InAppMessageParamsBuilder {
        addAllInAppMessageCategoriesToShow: () => InAppMessageParamsBuilder;
        addInAppMessageCategoryToShow: (inAppMessageCategoryId: number) => InAppMessageParamsBuilder;
        build: () => InAppMessageParams;
    }
    export class InAppMessageParams {
        private constructor();
        public static newBuilder(): InAppMessageParamsBuilder;
    }

    export interface GetBillingConfigParamsBuilder {
        build: () => GetBillingConfigParams;
    }
    export class GetBillingConfigParams {
        private constructor();
        public static newBuilder(): GetBillingConfigParamsBuilder;
    }
    export class BillingClient {
        private constructor();
        static Builder: BillingFlowParamsBuilder;
        static ConnectionState: typeof jsb.ConnectionState;
        static BillingResponseCode: typeof jsb.BillingResponseCode;
        static FeatureType: typeof jsb.FeatureType;
        static ProductType: typeof jsb.ProductType;
        public static newBuilder(): BillingClientBuilder;
        startConnection: (listener: BillingClientStateListener) => void;
        endConnection: () => void;
        getConnectionState: () => number;
        isReady: () => void;
        queryProductDetailsAsync: (params: QueryProductDetailsParams, listener: ProductDetailsResponseListener) => void;
        launchBillingFlow: (params: BillingFlowParams) => void;
        consumeAsync: (params: ConsumeParams, listener: ConsumeResponseListener) => void;
        acknowledgePurchase: (params: AcknowledgePurchaseParams, listener: AcknowledgePurchaseResponseListener) => void;
        queryPurchasesAsync: (params: QueryPurchasesParams, listener: PurchasesResponseListener) => void;
        getBillingConfigAsync: (params: GetBillingConfigParams, listener: BillingConfigResponseListener) => void;
        createAlternativeBillingOnlyReportingDetailsAsync: (listener: AlternativeBillingOnlyReportingDetailsListener) => void;
        isAlternativeBillingOnlyAvailableAsync: (listener: AlternativeBillingOnlyAvailabilityListener) => void;
        createExternalOfferReportingDetailsAsync: (listener: ExternalOfferReportingDetailsListener) => void;
        isExternalOfferAvailableAsync: (listener: ExternalOfferAvailabilityListener) => void;

        isFeatureSupported: (productType: string) => BillingResult;
        showAlternativeBillingOnlyInformationDialog: (listener: AlternativeBillingOnlyInformationDialogListener) => BillingResult;
        showExternalOfferInformationDialog: (listener: ExternalOfferInformationDialogListener) => BillingResult;
        showInAppMessages: (params: InAppMessageParams, listener: InAppMessageResponseListener) => BillingResult;
    }

    // /**
    //  * @en Main interface for communication between the Google Play library and user application code.
    //  * @zh 产品 ID。
    //  */
    // const googleBilling: {
    //     enableAlternativeBillingOnly(): void;
    //     enableExternalOffer(): void;
    //     isEnabledForOneTimeProducts(): boolean;
    //     isEnabledForPrepaidPlans(): boolean;
    //     /**
    //      * @en Starts up BillingClient setup process asynchronously.
    //      * @zh 异步启动 BillingClient 设置过程。
    //      */
    //     startConnection(): void;

    //     /**
    //      * @en Closes the connection and releases all held resources such as service connections.
    //      * @zh 关闭连接并释放所有持有的资源，例如服务连接。
    //      */
    //     endConnection(): void;

    //     /**
    //      * @en Get the current billing client connection state.
    //      * @zh 获取当前计费客户端连接状态。
    //      */
    //     getConnectionState(): number;

    //     /**
    //      * @en Checks if the client is currently connected to the service, so that requests to other methods will succeed.
    //            Returns true if the client is currently connected to the service, false otherwise.
    //      * @zh 检查客户端当前是否连接到服务，以便对其他方法的请求能够成功。
    //            如果客户端当前已连接到服务，则返回 true，否则返回 false。
    //      */
    //     isReady(): boolean;

    //     /**
    //      * @en Performs a network query the details of products available for sale in your app.
    //      * @zh 执行网络查询您的应用中可供销售的产品的详细信息。
    //      */
    //     queryProductDetailsAsync(productId: string[], productType: string[]): void;
    //     /**
    //      * @en Initiates the billing flow for an in-app purchase or subscription.
    //      * @zh 启动应用内购买或订阅的计费流程。
    //      */
    //     launchBillingFlow(productDetails: ProductDetails[], selectedOfferToken: string | null): void;
    //     /**
    //      * @en Consumes a given in-app product.
    //      * @zh 消费指定的应用内产品。
    //      */
    //     consumeAsync(purchases: Purchase[]): void;
    //     /**
    //      * @en Returns purchases details for currently owned items bought within your app.
    //      * @zh 返回您应用内当前拥有的购买商品的购买详情。
    //      */
    //     queryPurchasesAsync(productType: string): void;
    //     /**
    //      * @en Acknowledges in-app purchases..
    //      * @zh 确认应用内购买。
    //      */
    //     acknowledgePurchase(purchases: Purchase[]): void;
    //     /**
    //      * @en Gets the billing config, which stores configuration used to perform billing operations.
    //      * @zh 获取计费配置，其中存储用于执行计费操作的配置。
    //      */
    //     getBillingConfigAsync(): void;

    //     /**
    //      * @en Creates alternative billing only purchase details that can be used to report a transaction made via alternative billing without user choice to use Google Play billing.
    //      * @zh 创建仅限替代结算的购买详情，可用于报告通过替代结算进行的交易，而无需用户选择使用 Google Play Billing。
    //      */
    //     createAlternativeBillingOnlyReportingDetailsAsync(): void;
    //     /**
    //      * @en Checks the availability of offering alternative billing without user choice to use Google Play Billing.
    //      * @zh 检查是否可以提供替代结算方式，而无需用户选择使用 Google Play Billing方式。
    //      */
    //     isAlternativeBillingOnlyAvailableAsync(): void;

    //     /**
    //      * @en Creates purchase details that can be used to report a transaction made via external offer.
    //      * @zh 创建可用于报告通过外部报价进行的交易的购买详情。
    //      */
    //     createExternalOfferReportingDetailsAsync(): void;
    //     /**
    //      * @en Checks the availability of providing external offer.
    //      * @zh 检查提供外部报价的可用性。
    //      */
    //     isExternalOfferAvailableAsync(): void;

    //     /**
    //      * @en Checks if the specified feature or capability is supported by the Play Store.
    //      * @zh 检查 Play Store 是否支持指定的功能。
    //      */
    //     isFeatureSupported(feature: string): BillingResult;

    //     /**
    //      * @en Shows the alternative billing only information dialog on top of the calling app.
    //      * @zh 在调用应用程序顶部显示仅显示备用计费信息对话框。
    //      */
    //     showAlternativeBillingOnlyInformationDialog(): BillingResult;

    //     /**
    //      * @en Shows the external offer information dialog on top of the calling app.
    //      * @zh 在调用应用程序顶部显示外部优惠信息对话框。
    //      */
    //     showExternalOfferInformationDialog(): BillingResult;

    //     /**
    //      * @en Overlays billing related messages on top of the calling app.
    //      * @zh 在调用应用程序上叠加与计费相关的消息。
    //      */
    //     showInAppMessages(): BillingResult;
    // } | undefined;
    // export let onBillingSetupFinished: (result: BillingResult) => void | undefined;
    // export let onBillingServiceDisconnected: () => void | undefined;
    // export let onProductDetailsResponse: (result: BillingResult, productDetailsList: ProductDetails[]) => void | undefined;
    // export let onPurchasesUpdated: (result: BillingResult, purchaseList: Purchase[]) => void | undefined;
    // export let userSelectedAlternativeBilling: (userChoiceDetails: UserChoiceDetails) => void;
    // export let onConsumeResponse: (result: BillingResult, purchaseToken: string) => void | undefined;
    // export let onAcknowledgePurchaseResponse: (result: BillingResult) => void | undefined;
    // export let onQueryPurchasesResponse: (result: BillingResult, purchaseList: Purchase[]) => void | undefined;
    // export let onBillingConfigResponse: (result: BillingResult, config: BillingConfig) => void | undefined;
    // export let onAlternativeBillingOnlyTokenResponse: (result: BillingResult, details: AlternativeBillingOnlyReportingDetails) => void | undefined;
    // export let onExternalOfferReportingDetailsResponse: (result: BillingResult, details: ExternalOfferReportingDetails) => void | undefined;
    // export let onAlternativeBillingOnlyAvailabilityResponse: (result: BillingResult) => void | undefined;
    // export let onExternalOfferAvailabilityResponse: (result: BillingResult) => void | undefined;
    // export let onAlternativeBillingOnlyInformationDialogResponse: (result: BillingResult) => void | undefined;
    // export let onExternalOfferInformationDialogResponse: (result: BillingResult) => void | undefined;
    // export let onInAppMessageResponse: (result: InAppMessageResult) => void | undefined;
}

declare namespace ns {

    class NativePOD {
        underlyingData(): ArrayBuffer;
        _arraybuffer(): ArrayBuffer;
    }
    export class Line extends jsb.NativePOD {
    }
    export class Plane extends jsb.NativePOD {
    }
    export class Ray extends jsb.NativePOD {
    }
    export class Triangle extends jsb.NativePOD {
    }
    export class Sphere extends jsb.NativePOD {
    }
    export class AABB extends jsb.NativePOD {
    }
    export class Capsule extends jsb.NativePOD {
    }
    export class Frustum extends jsb.NativePOD {
    }
}

/**
 * Only defined on native platforms.
 * Now we only support 'V8'
 */
declare const scriptEngineType: 'V8';
