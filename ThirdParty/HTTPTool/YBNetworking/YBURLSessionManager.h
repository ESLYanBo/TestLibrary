//  Created by 王晨辉 on 2018/1/9.
//  Copyright © 2018年 王晨辉. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "YBURLResponseSerialization.h"
#import "YBURLRequestSerialization.h"
#import "YBSecurityPolicy.h"
#if !TARGET_OS_WATCH
#import "YBNetworkReachabilityManager.h"
#endif


NS_ASSUME_NONNULL_BEGIN

@interface YBURLSessionManager : NSObject <NSURLSessionDelegate, NSURLSessionTaskDelegate, NSURLSessionDataDelegate, NSURLSessionDownloadDelegate, NSSecureCoding, NSCopying>


@property (readonly, nonatomic, strong) NSURLSession *session;


@property (readonly, nonatomic, strong) NSOperationQueue *operationQueue;


@property (nonatomic, strong) id <YBURLResponseSerialization> responseSerializer;


@property (nonatomic, strong) YBSecurityPolicy *securityPolicy;

#if !TARGET_OS_WATCH

@property (readwrite, nonatomic, strong) YBNetworkReachabilityManager *reachabilityManager;
#endif


@property (readonly, nonatomic, strong) NSArray <NSURLSessionTask *> *tasks;


@property (readonly, nonatomic, strong) NSArray <NSURLSessionDataTask *> *dataTasks;


@property (readonly, nonatomic, strong) NSArray <NSURLSessionUploadTask *> *uploadTasks;


@property (readonly, nonatomic, strong) NSArray <NSURLSessionDownloadTask *> *downloadTasks;


@property (nonatomic, strong, nullable) dispatch_queue_t completionQueue;


@property (nonatomic, strong, nullable) dispatch_group_t completionGroup;


@property (nonatomic, assign) BOOL attemptsToRecreateUploadTasksForBackgroundSessions;


- (instancetype)initWithSessionConfiguration:(nullable NSURLSessionConfiguration *)configuration NS_DESIGNATED_INITIALIZER;


- (void)invalidateSessionCancelingTasks:(BOOL)cancelPendingTasks;


- (NSURLSessionDataTask *)dataTaskWithRequest:(NSURLRequest *)request
                            completionHandler:(nullable void (^)(NSURLResponse *response, id _Nullable responseObject,  NSError * _Nullable error))completionHandler DEPRECATED_ATTRIBUTE;


- (NSURLSessionDataTask *)dataTaskWithRequest:(NSURLRequest *)request
                               uploadProgress:(nullable void (^)(NSProgress *uploadProgress))uploadProgressBlock
                             downloadProgress:(nullable void (^)(NSProgress *downloadProgress))downloadProgressBlock
                            completionHandler:(nullable void (^)(NSURLResponse *response, id _Nullable responseObject,  NSError * _Nullable error))completionHandler;


- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request
                                         fromFile:(NSURL *)fileURL
                                         progress:(nullable void (^)(NSProgress *uploadProgress))uploadProgressBlock
                                completionHandler:(nullable void (^)(NSURLResponse *response, id _Nullable responseObject, NSError  * _Nullable error))completionHandler;


- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request
                                         fromData:(nullable NSData *)bodyData
                                         progress:(nullable void (^)(NSProgress *uploadProgress))uploadProgressBlock
                                completionHandler:(nullable void (^)(NSURLResponse *response, id _Nullable responseObject, NSError * _Nullable error))completionHandler;


- (NSURLSessionUploadTask *)uploadTaskWithStreamedRequest:(NSURLRequest *)request
                                                 progress:(nullable void (^)(NSProgress *uploadProgress))uploadProgressBlock
                                        completionHandler:(nullable void (^)(NSURLResponse *response, id _Nullable responseObject, NSError * _Nullable error))completionHandler;


- (NSURLSessionDownloadTask *)downloadTaskWithRequest:(NSURLRequest *)request
                                             progress:(nullable void (^)(NSProgress *downloadProgress))downloadProgressBlock
                                          destination:(nullable NSURL * (^)(NSURL *targetPath, NSURLResponse *response))destination
                                    completionHandler:(nullable void (^)(NSURLResponse *response, NSURL * _Nullable filePath, NSError * _Nullable error))completionHandler;


- (NSURLSessionDownloadTask *)downloadTaskWithResumeData:(NSData *)resumeData
                                                progress:(nullable void (^)(NSProgress *downloadProgress))downloadProgressBlock
                                             destination:(nullable NSURL * (^)(NSURL *targetPath, NSURLResponse *response))destination
                                       completionHandler:(nullable void (^)(NSURLResponse *response, NSURL * _Nullable filePath, NSError * _Nullable error))completionHandler;


- (nullable NSProgress *)uploadProgressForTask:(NSURLSessionTask *)task;


- (nullable NSProgress *)downloadProgressForTask:(NSURLSessionTask *)task;


- (void)setSessionDidBecomeInvalidBlock:(nullable void (^)(NSURLSession *session, NSError *error))block;


- (void)setSessionDidReceiveAuthenticationChallengeBlock:(nullable NSURLSessionAuthChallengeDisposition (^)(NSURLSession *session, NSURLAuthenticationChallenge *challenge, NSURLCredential * _Nullable __autoreleasing * _Nullable credential))block;


- (void)setTaskNeedNewBodyStreamBlock:(nullable NSInputStream * (^)(NSURLSession *session, NSURLSessionTask *task))block;


- (void)setTaskWillPerformHTTPRedirectionBlock:(nullable NSURLRequest * (^)(NSURLSession *session, NSURLSessionTask *task, NSURLResponse *response, NSURLRequest *request))block;


- (void)setTaskDidReceiveAuthenticationChallengeBlock:(nullable NSURLSessionAuthChallengeDisposition (^)(NSURLSession *session, NSURLSessionTask *task, NSURLAuthenticationChallenge *challenge, NSURLCredential * _Nullable __autoreleasing * _Nullable credential))block;


- (void)setTaskDidSendBodyDataBlock:(nullable void (^)(NSURLSession *session, NSURLSessionTask *task, int64_t bytesSent, int64_t totalBytesSent, int64_t totalBytesExpectedToSend))block;


- (void)setTaskDidCompleteBlock:(nullable void (^)(NSURLSession *session, NSURLSessionTask *task, NSError * _Nullable error))block;


- (void)setDataTaskDidReceiveResponseBlock:(nullable NSURLSessionResponseDisposition (^)(NSURLSession *session, NSURLSessionDataTask *dataTask, NSURLResponse *response))block;


- (void)setDataTaskDidBecomeDownloadTaskBlock:(nullable void (^)(NSURLSession *session, NSURLSessionDataTask *dataTask, NSURLSessionDownloadTask *downloadTask))block;


- (void)setDataTaskDidReceiveDataBlock:(nullable void (^)(NSURLSession *session, NSURLSessionDataTask *dataTask, NSData *data))block;


- (void)setDataTaskWillCacheResponseBlock:(nullable NSCachedURLResponse * (^)(NSURLSession *session, NSURLSessionDataTask *dataTask, NSCachedURLResponse *proposedResponse))block;


- (void)setDidFinishEventsForBackgroundURLSessionBlock:(nullable void (^)(NSURLSession *session))block;


- (void)setDownloadTaskDidFinishDownloadingBlock:(nullable NSURL * _Nullable  (^)(NSURLSession *session, NSURLSessionDownloadTask *downloadTask, NSURL *location))block;

- (void)setDownloadTaskDidWriteDataBlock:(nullable void (^)(NSURLSession *session, NSURLSessionDownloadTask *downloadTask, int64_t bytesWritten, int64_t totalBytesWritten, int64_t totalBytesExpectedToWrite))block;


- (void)setDownloadTaskDidResumeBlock:(nullable void (^)(NSURLSession *session, NSURLSessionDownloadTask *downloadTask, int64_t fileOffset, int64_t expectedTotalBytes))block;

@end


FOUNDATION_EXPORT NSString * const YBNetworkingTaskDidResumeNotification;


FOUNDATION_EXPORT NSString * const YBNetworkingTaskDidCompleteNotification;

FOUNDATION_EXPORT NSString * const YBNetworkingTaskDidSuspendNotification;


FOUNDATION_EXPORT NSString * const YBURLSessionDidInvalidateNotification;


FOUNDATION_EXPORT NSString * const YBURLSessionDownloadTaskDidFailToMoveFileNotification;


FOUNDATION_EXPORT NSString * const YBNetworkingTaskDidCompleteResponseDataKey;


FOUNDATION_EXPORT NSString * const YBNetworkingTaskDidCompleteSerializedResponseKey;


FOUNDATION_EXPORT NSString * const YBNetworkingTaskDidCompleteResponseSerializerKey;


FOUNDATION_EXPORT NSString * const YBNetworkingTaskDidCompleteAssetPathKey;


FOUNDATION_EXPORT NSString * const YBNetworkingTaskDidCompleteErrorKey;

NS_ASSUME_NONNULL_END
