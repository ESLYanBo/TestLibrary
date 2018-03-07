//
//  ViewController.m
//  Ceshi
//
//  Created by 王晨辉 on 2018/1/9.
//  Copyright © 2018年 王晨辉. All rights reserved.
//

#import "ViewController.h"
#import "RegularVerification.h"
#import "YBNetworking.h"
@interface ViewController ()
@property (nonatomic, strong) YBNetworkReachabilityManager *manager;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}
- (IBAction)sendBtn:(UIButton *)sender {

    if ([RegularVerification checkUserName:@"我的是你的"]) {
        NSLog(@"YES");
    }else{
        NSLog(@"NO");
    }
    [self judgeNet];
}
// 判断网络
- (void)judgeNet
{
    self.manager = [YBNetworkReachabilityManager manager];
//    __weak typeof(self) weakSelf = self;
    [self.manager setReachabilityStatusChangeBlock:^(YBNetworkReachabilityStatus status) {
        switch (status) {
            case YBNetworkReachabilityStatusNotReachable: {
                NSLog(@"网络不可用");
                break;
            }
                
            case YBNetworkReachabilityStatusReachableViaWiFi: {
                NSLog(@"Wifi已开启");
                break;
            }
                
            case YBNetworkReachabilityStatusReachableViaWWAN: {
                NSLog(@"你现在使用的流量");
                break;
            }
                
            case YBNetworkReachabilityStatusUnknown: {
                NSLog(@"你现在使用的未知网络");
                break;
            }
                
            default:
                break;
        }
    }];
    [self.manager startMonitoring];
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
