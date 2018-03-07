
#import "YBNetworkReachabilityManager.h"
#if !TARGET_OS_WATCH

#import <netinet/in.h>
#import <netinet6/in6.h>
#import <arpa/inet.h>
#import <ifaddrs.h>
#import <netdb.h>

NSString * const YBNetworkingReachabilityDidChangeNotification = @"com.alamofire.networking.reachability.change";
NSString * const YBNetworkingReachabilityNotificationStatusItem = @"YBNetworkingReachabilityNotificationStatusItem";

typedef void (^YBNetworkReachabilityStatusBlock)(YBNetworkReachabilityStatus status);

NSString * YBStringFromNetworkReachabilityStatus(YBNetworkReachabilityStatus status) {
    switch (status) {
        case YBNetworkReachabilityStatusNotReachable:
            return NSLocalizedStringFromTable(@"Not Reachable", @"YBNetworking", nil);
        case YBNetworkReachabilityStatusReachableViaWWAN:
            return NSLocalizedStringFromTable(@"Reachable via WWAN", @"YBNetworking", nil);
        case YBNetworkReachabilityStatusReachableViaWiFi:
            return NSLocalizedStringFromTable(@"Reachable via WiFi", @"YBNetworking", nil);
        case YBNetworkReachabilityStatusUnknown:
        default:
            return NSLocalizedStringFromTable(@"Unknown", @"YBNetworking", nil);
    }
}

static YBNetworkReachabilityStatus YBNetworkReachabilityStatusForFlags(SCNetworkReachabilityFlags flags) {
    BOOL isReachable = ((flags & kSCNetworkReachabilityFlagsReachable) != 0);
    BOOL needsConnection = ((flags & kSCNetworkReachabilityFlagsConnectionRequired) != 0);
    BOOL canConnectionAutomatically = (((flags & kSCNetworkReachabilityFlagsConnectionOnDemand ) != 0) || ((flags & kSCNetworkReachabilityFlagsConnectionOnTraffic) != 0));
    BOOL canConnectWithoutUserInteraction = (canConnectionAutomatically && (flags & kSCNetworkReachabilityFlagsInterventionRequired) == 0);
    BOOL isNetworkReachable = (isReachable && (!needsConnection || canConnectWithoutUserInteraction));

    YBNetworkReachabilityStatus status = YBNetworkReachabilityStatusUnknown;
    if (isNetworkReachable == NO) {
        status = YBNetworkReachabilityStatusNotReachable;
    }
#if	TARGET_OS_IPHONE
    else if ((flags & kSCNetworkReachabilityFlagsIsWWAN) != 0) {
        status = YBNetworkReachabilityStatusReachableViaWWAN;
    }
#endif
    else {
        status = YBNetworkReachabilityStatusReachableViaWiFi;
    }

    return status;
}


static void YBPostReachabilityStatusChange(SCNetworkReachabilityFlags flags, YBNetworkReachabilityStatusBlock block) {
    YBNetworkReachabilityStatus status = YBNetworkReachabilityStatusForFlags(flags);
    dispatch_async(dispatch_get_main_queue(), ^{
        if (block) {
            block(status);
        }
        NSNotificationCenter *notificationCenter = [NSNotificationCenter defaultCenter];
        NSDictionary *userInfo = @{ YBNetworkingReachabilityNotificationStatusItem: @(status) };
        [notificationCenter postNotificationName:YBNetworkingReachabilityDidChangeNotification object:nil userInfo:userInfo];
    });
}

static void YBNetworkReachabilityCallback(SCNetworkReachabilityRef __unused target, SCNetworkReachabilityFlags flags, void *info) {
    YBPostReachabilityStatusChange(flags, (__bridge YBNetworkReachabilityStatusBlock)info);
}


static const void * YBNetworkReachabilityRetainCallback(const void *info) {
    return Block_copy(info);
}

static void YBNetworkReachabilityReleaseCallback(const void *info) {
    if (info) {
        Block_release(info);
    }
}

@interface YBNetworkReachabilityManager ()
@property (readonly, nonatomic, assign) SCNetworkReachabilityRef networkReachability;
@property (readwrite, nonatomic, assign) YBNetworkReachabilityStatus networkReachabilityStatus;
@property (readwrite, nonatomic, copy) YBNetworkReachabilityStatusBlock networkReachabilityStatusBlock;
@end

@implementation YBNetworkReachabilityManager

+ (instancetype)sharedManager {
    static YBNetworkReachabilityManager *_sharedManager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _sharedManager = [self manager];
    });

    return _sharedManager;
}

+ (instancetype)managerForDomain:(NSString *)domain {
    SCNetworkReachabilityRef reachability = SCNetworkReachabilityCreateWithName(kCFAllocatorDefault, [domain UTF8String]);

    YBNetworkReachabilityManager *manager = [[self alloc] initWithReachability:reachability];
    
    CFRelease(reachability);

    return manager;
}

+ (instancetype)managerForAddress:(const void *)address {
    SCNetworkReachabilityRef reachability = SCNetworkReachabilityCreateWithAddress(kCFAllocatorDefault, (const struct sockaddr *)address);
    YBNetworkReachabilityManager *manager = [[self alloc] initWithReachability:reachability];

    CFRelease(reachability);
    
    return manager;
}

+ (instancetype)manager
{
#if (defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 90000) || (defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101100)
    struct sockaddr_in6 address;
    bzero(&address, sizeof(address));
    address.sin6_len = sizeof(address);
    address.sin6_family = AF_INET6;
#else
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_len = sizeof(address);
    address.sin_family = AF_INET;
#endif
    return [self managerForAddress:&address];
}

- (instancetype)initWithReachability:(SCNetworkReachabilityRef)reachability {
    self = [super init];
    if (!self) {
        return nil;
    }

    _networkReachability = CFRetain(reachability);
    self.networkReachabilityStatus = YBNetworkReachabilityStatusUnknown;

    return self;
}

- (instancetype)init NS_UNAVAILABLE
{
    return nil;
}

- (void)dealloc {
    [self stopMonitoring];
    
    if (_networkReachability != NULL) {
        CFRelease(_networkReachability);
    }
}

#pragma mark -

- (BOOL)isReachable {
    return [self isReachableViaWWAN] || [self isReachableViaWiFi];
}

- (BOOL)isReachableViaWWAN {
    return self.networkReachabilityStatus == YBNetworkReachabilityStatusReachableViaWWAN;
}

- (BOOL)isReachableViaWiFi {
    return self.networkReachabilityStatus == YBNetworkReachabilityStatusReachableViaWiFi;
}

#pragma mark -

- (void)startMonitoring {
    [self stopMonitoring];

    if (!self.networkReachability) {
        return;
    }

    __weak __typeof(self)weakSelf = self;
    YBNetworkReachabilityStatusBlock callback = ^(YBNetworkReachabilityStatus status) {
        __strong __typeof(weakSelf)strongSelf = weakSelf;

        strongSelf.networkReachabilityStatus = status;
        if (strongSelf.networkReachabilityStatusBlock) {
            strongSelf.networkReachabilityStatusBlock(status);
        }

    };

    SCNetworkReachabilityContext context = {0, (__bridge void *)callback, YBNetworkReachabilityRetainCallback, YBNetworkReachabilityReleaseCallback, NULL};
    SCNetworkReachabilitySetCallback(self.networkReachability, YBNetworkReachabilityCallback, &context);
    SCNetworkReachabilityScheduleWithRunLoop(self.networkReachability, CFRunLoopGetMain(), kCFRunLoopCommonModes);

    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0),^{
        SCNetworkReachabilityFlags flags;
        if (SCNetworkReachabilityGetFlags(self.networkReachability, &flags)) {
            YBPostReachabilityStatusChange(flags, callback);
        }
    });
}

- (void)stopMonitoring {
    if (!self.networkReachability) {
        return;
    }

    SCNetworkReachabilityUnscheduleFromRunLoop(self.networkReachability, CFRunLoopGetMain(), kCFRunLoopCommonModes);
}

#pragma mark -

- (NSString *)localizedNetworkReachabilityStatusString {
    return YBStringFromNetworkReachabilityStatus(self.networkReachabilityStatus);
}

#pragma mark -

- (void)setReachabilityStatusChangeBlock:(void (^)(YBNetworkReachabilityStatus status))block {
    self.networkReachabilityStatusBlock = block;
}

#pragma mark - NSKeyValueObserving

+ (NSSet *)keyPathsForValuesAffectingValueForKey:(NSString *)key {
    if ([key isEqualToString:@"reachable"] || [key isEqualToString:@"reachableViaWWAN"] || [key isEqualToString:@"reachableViaWiFi"]) {
        return [NSSet setWithObject:@"networkReachabilityStatus"];
    }

    return [super keyPathsForValuesAffectingValueForKey:key];
}

@end
#endif
