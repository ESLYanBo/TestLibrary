//  Created by 王晨辉 on 2018/1/9.
//  Copyright © 2018年 王晨辉. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <Availability.h>
#import <TargetConditionals.h>

#ifndef _YBNETWORKING_
    #define _YBNETWORKING_

    #import "YBURLRequestSerialization.h"
    #import "YBURLResponseSerialization.h"
    #import "YBSecurityPolicy.h"

#if !TARGET_OS_WATCH
    #import "YBNetworkReachabilityManager.h"
#endif

    #import "YBURLSessionManager.h"
    #import "YBHTTPSessionManager.h"

#endif /* _YBNETWORKING_ */
