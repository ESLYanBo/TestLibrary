//
//  BRAddressModel.m
//  BRPickerViewDemo
//
//  Created by 王晨辉 on 2018/3/1.
//  Copyright © 2018年 王晨辉. All rights reserved.
//
//  最新代码下载地址：https://github.com/ESLYanBo/TestLibrary.git

#import "BRAddressModel.h"

@implementation BRProvinceModel

+ (NSDictionary *)modelCustomPropertyMapper {
    return @{
             @"name": @"v",
             @"city": @"n"
             };
}

+ (NSDictionary *)modelContainerPropertyGenericClass {
    return @{
             @"city": [BRCityModel class]
             };
}

@end


@implementation BRCityModel

+ (NSDictionary *)modelCustomPropertyMapper {
    return @{
             @"name": @"v",
             @"town": @"n"
             };
}

+ (NSDictionary *)modelContainerPropertyGenericClass {
    return @{
             @"town": [BRTownModel class]
             };
}

@end


@implementation BRTownModel

+ (NSDictionary *)modelCustomPropertyMapper {
    return @{
             @"name": @"v"
             };
}

@end
