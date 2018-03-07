

#import <Foundation/Foundation.h>

#if !TARGET_OS_WATCH
#import <SystemConfiguration/SystemConfiguration.h>

typedef NS_ENUM(NSInteger, YBNetworkReachabilityStatus) {
    YBNetworkReachabilityStatusUnknown          = -1,
    YBNetworkReachabilityStatusNotReachable     = 0,
    YBNetworkReachabilityStatusReachableViaWWAN = 1,
    YBNetworkReachabilityStatusReachableViaWiFi = 2,
};

NS_ASSUME_NONNULL_BEGIN


@interface YBNetworkReachabilityManager : NSObject

@property (readonly, nonatomic, assign) YBNetworkReachabilityStatus networkReachabilityStatus;


@property (readonly, nonatomic, assign, getter = isReachable) BOOL reachable;


@property (readonly, nonatomic, assign, getter = isReachableViaWWAN) BOOL reachableViaWWAN;


@property (readonly, nonatomic, assign, getter = isReachableViaWiFi) BOOL reachableViaWiFi;


+ (instancetype)sharedManager;


+ (instancetype)manager;


+ (instancetype)managerForDomain:(NSString *)domain;


+ (instancetype)managerForAddress:(const void *)address;


- (instancetype)initWithReachability:(SCNetworkReachabilityRef)reachability NS_DESIGNATED_INITIALIZER;


- (nullable instancetype)init NS_UNAVAILABLE;


- (void)startMonitoring;

- (void)stopMonitoring;


- (NSString *)localizedNetworkReachabilityStatusString;


- (void)setReachabilityStatusChangeBlock:(nullable void (^)(YBNetworkReachabilityStatus status))block;

@end


FOUNDATION_EXPORT NSString * const YBNetworkingReachabilityDidChangeNotification;
FOUNDATION_EXPORT NSString * const YBNetworkingReachabilityNotificationStatusItem;


FOUNDATION_EXPORT NSString * YBStringFromNetworkReachabilityStatus(YBNetworkReachabilityStatus status);

NS_ASSUME_NONNULL_END
#endif
