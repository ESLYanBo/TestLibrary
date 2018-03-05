//
//  ViewController.m
//  Ceshi
//
//  Created by 王晨辉 on 2018/1/9.
//  Copyright © 2018年 王晨辉. All rights reserved.
//

#import "ViewController.h"
#import "RegularVerification.h"
@interface ViewController ()

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
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
