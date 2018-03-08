//
//  BRAddressModel.h
//  BRPickerViewDemo
//
//  Created by 王晨辉 on 2018/3/1.
//  Copyright © 2018年 王晨辉. All rights reserved.
//
//  最新代码下载地址：https://github.com/ESLYanBo/TestLibrary.git

#import <Foundation/Foundation.h>

@class BRProvinceModel, BRCityModel, BRTownModel;

@interface BRProvinceModel : NSObject

@property (nonatomic, copy) NSString *name;
@property (nonatomic, strong) NSArray *city;

@end

@interface BRCityModel : NSObject

@property (nonatomic, copy) NSString *name;
@property (nonatomic, strong) NSArray *town;

@end


@interface BRTownModel : NSObject

@property (nonatomic, copy) NSString *name;

@end
