//
//  BRAddressPickerView.h
//  BRPickerViewDemo
//
//  Created by 王晨辉 on 2018/3/1.
//  Copyright © 2018年 王晨辉. All rights reserved.
//
//  最新代码下载地址：https://github.com/ESLYanBo/TestLibrary.git

#import "BaseView.h"

typedef void(^BRAddressResultBlock)(NSArray *selectAddressArr);

@interface BRAddressPickerView : BaseView
/**
 *  显示地址选择器
 *
 *  @param defaultSelectedArr       默认选中的值(传数组，元素为对应的索引值。如：@[@10, @1, @1])
 *  @param isAutoSelect             是否自动选择，即选择完(滚动完)执行结果回调，传选择的结果值
 *  @param resultBlock              选择后的回调
 *
 */
+ (void)showAddressPickerWithDefaultSelected:(NSArray *)defaultSelectedArr isAutoSelect:(BOOL)isAutoSelect resultBlock:(BRAddressResultBlock)resultBlock;

@end
