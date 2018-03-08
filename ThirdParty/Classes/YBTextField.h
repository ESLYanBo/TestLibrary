//
//  YBTextField.h
//  YBPickerViewDemo
//
//  Created by 王晨辉 on 2018/3/1.
//  Copyright © 2018年 王晨辉. All rights reserved.
//
//  最新代码下载地址：https://github.com/ESLYanBo/TestLibrary.git

#import <UIKit/UIKit.h>

typedef void(^YBTapAcitonBlock)(void);
typedef void(^YBEndEditBlock)(NSString *text);

@interface YBTextField : UITextField
/** textField 的点击回调 */
@property (nonatomic, copy) YBTapAcitonBlock tapAcitonBlock;
/** textField 结束编辑的回调 */
@property (nonatomic, copy) YBEndEditBlock endEditBlock;

@end
