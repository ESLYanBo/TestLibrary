
#import <Foundation/Foundation.h>
#import <Security/Security.h>

typedef NS_ENUM(NSUInteger, YBSSLPinningMode) {
    YBSSLPinningModeNone,
    YBSSLPinningModePublicKey,
    YBSSLPinningModeCertificate,
};



NS_ASSUME_NONNULL_BEGIN

@interface YBSecurityPolicy : NSObject <NSSecureCoding, NSCopying>


@property (readonly, nonatomic, assign) YBSSLPinningMode SSLPinningMode;


@property (nonatomic, strong, nullable) NSSet <NSData *> *pinnedCertificates;


@property (nonatomic, assign) BOOL allowInvalidCertificates;


@property (nonatomic, assign) BOOL validatesDomainName;


+ (NSSet <NSData *> *)certificatesInBundle:(NSBundle *)bundle;


+ (instancetype)defaultPolicy;


+ (instancetype)policyWithPinningMode:(YBSSLPinningMode)pinningMode;


+ (instancetype)policyWithPinningMode:(YBSSLPinningMode)pinningMode withPinnedCertificates:(NSSet <NSData *> *)pinnedCertificates;


- (BOOL)evaluateServerTrust:(SecTrustRef)serverTrust
                  forDomain:(nullable NSString *)domain;

@end

NS_ASSUME_NONNULL_END


