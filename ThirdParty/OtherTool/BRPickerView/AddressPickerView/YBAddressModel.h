//
//  YBAddressModel.h
//  YBPickerViewDemo
//
//  Created by 王晨辉 on 2018/3/1.
//  Copyright © 2018年 王晨辉. All rights reserved.
//
//  最新代码下载地址：https://github.com/ESLYanBo/TestLibrary.git

#import <Foundation/Foundation.h>

@class YBProvinceModel, YBCityModel, YBTownModel;

@interface YBProvinceModel : NSObject

@property (nonatomic, copy) NSString *name;
@property (nonatomic, strong) NSArray *city;

@end

@interface YBCityModel : NSObject

@property (nonatomic, copy) NSString *name;
@property (nonatomic, strong) NSArray *town;

@end


@interface YBTownModel : NSObject

@property (nonatomic, copy) NSString *name;

@end
