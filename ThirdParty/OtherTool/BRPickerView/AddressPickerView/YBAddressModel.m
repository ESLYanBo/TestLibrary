//
//  YBAddressModel.m
//  YBPickerViewDemo
//
//  Created by 王晨辉 on 2018/3/1.
//  Copyright © 2018年 王晨辉. All rights reserved.
//
//  最新代码下载地址：https://github.com/ESLYanBo/TestLibrary.git

#import "YBAddressModel.h"

@implementation YBProvinceModel

+ (NSDictionary *)modelCustomPropertyMapper {
    return @{
             @"name": @"v",
             @"city": @"n"
             };
}

+ (NSDictionary *)modelContainerPropertyGenericClass {
    return @{
             @"city": [YBCityModel class]
             };
}

@end


@implementation YBCityModel

+ (NSDictionary *)modelCustomPropertyMapper {
    return @{
             @"name": @"v",
             @"town": @"n"
             };
}

+ (NSDictionary *)modelContainerPropertyGenericClass {
    return @{
             @"town": [YBTownModel class]
             };
}

@end


@implementation YBTownModel

+ (NSDictionary *)modelCustomPropertyMapper {
    return @{
             @"name": @"v"
             };
}

@end
