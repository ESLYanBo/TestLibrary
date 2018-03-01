# TestLibrary
测试Git和第一个项目
```
这里第一版是某些正则表达式的判定。
#pragma 正则匹配手机号
+(BOOL)checkTelNumber:(NSString *) telNumber;
#pragma 正则匹配用户密码6-18位数字和字母组合
+(BOOL)checkPassword:(NSString *) password;
#pragma 正则匹配用户姓名,20位的中文或英文
+(BOOL)checkUserName : (NSString *) userName;
#pragma 正则匹配用户身份证号
+(BOOL)checkUserIdCard: (NSString *) idCard;
+ (BOOL) validateIdentityCard: (NSString *)value;
#pragma 正则匹配邮箱
+ (BOOL)checkUserEmail:(NSString *)email;
#pragma 正则匹配银行卡号
+ (BOOL)checkUserBankNumber:(NSString *)BankNumber;
```
