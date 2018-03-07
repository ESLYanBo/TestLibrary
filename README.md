# 1,TestLibrary
常用工具库
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
# 2,GET请求
```
YBHTTPSessionManager *manager = [YBHTTPSessionManager manager]; 

[manager GET:URL parameters:nil progress:^(NSProgress * _Nonnull downloadProgress) {  

}     
 success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {  

 NSLog(@"这里打印请求成功要做的事");  

}

failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull   error) {  

NSLog(@"%@",error);  //这里打印错误信息

}];
```
# 3,POST请求
```
YBHTTPSessionManager *manager = [YBHTTPSessionManager manager];

NSMutableDictionary *parameters = @{@"":@"",@"":@""};

[manager POST:URL parameters:parameters progress:^(NSProgress * _Nonnull uploadProgress) {
    
    
} success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
    
    
} failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {

}];
```
# 4,YB下载方法
```
- (void)downLoad{

    //1.创建管理者对象
    YBHTTPSessionManager *manager = [YBHTTPSessionManager manager];
    //2.确定请求的URL地址
    NSURL *url = [NSURL URLWithString:@""];
    
    //3.创建请求对象
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    
    //下载任务
    NSURLSessionDownloadTask *task = [manager downloadTaskWithRequest:request progress:^(NSProgress * _Nonnull downloadProgress) {
        //打印下下载进度
        NSLog(@"%lf",1.0 * downloadProgress.completedUnitCount / downloadProgress.totalUnitCount);
        
    } destination:^NSURL * _Nonnull(NSURL * _Nonnull targetPath, NSURLResponse * _Nonnull response) {
        //下载地址
        NSLog(@"默认下载地址:%@",targetPath);
        
        //设置下载路径，通过沙盒获取缓存地址，最后返回NSURL对象
        NSString *filePath = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES)lastObject];
        return [NSURL fileURLWithPath:filePath];
        
        
    } completionHandler:^(NSURLResponse * _Nonnull response, NSURL * _Nullable filePath, NSError * _Nullable error) {
        
        //下载完成调用的方法
        NSLog(@"下载完成：");
        NSLog(@"%@--%@",response,filePath);
        
    }];
    
    //开始启动任务
    [task resume];

}
```
# 5,YB上传
```
/**
 * YB 上传
 *      有两种方式
 *          upLoad1 和 upLoad2
 */

//第一种方法是通过工程中的文件进行上传
- (void)upLoad1{

    //1。创建管理者对象
    YBHTTPSessionManager *manager = [YBHTTPSessionManager manager];

    //2.上传文件
    NSDictionary *dict = @{@"username":@"1234"};
    
    NSString *urlString = @"22222";
    [manager POST:urlString parameters:dict constructingBodyWithBlock:^(id<YBMultipartFormData>  _Nonnull formData) {
        //上传文件参数
        UIImage *iamge = [UIImage imageNamed:@"123.png"];
        NSData *data = UIImagePNGRepresentation(iamge);
        //这个就是参数
        [formData appendPartWithFileData:data name:@"file" fileName:@"123.png" mimeType:@"image/png"];
        
    } progress:^(NSProgress * _Nonnull uploadProgress) {
        
        //打印下上传进度
        NSLog(@"%lf",1.0 *uploadProgress.completedUnitCount / uploadProgress.totalUnitCount);
    } success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        
        //请求成功
        NSLog(@"请求成功：%@",responseObject);
    
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        
        //请求失败
        NSLog(@"请求失败：%@",error);
    }];

}

//第二种是通过URL来获取路径，进入沙盒或者系统相册等等
- (void)upLoda2{
    //1.创建管理者对象
    YBHTTPSessionManager *manager = [YBHTTPSessionManager manager];
    //2.上传文件
    NSDictionary *dict = @{@"username":@"1234"};
    
    NSString *urlString = @"22222";
    [manager POST:urlString parameters:dict constructingBodyWithBlock:^(id<YBMultipartFormData>  _Nonnull formData) {

        [formData appendPartWithFileURL:[NSURL fileURLWithPath:@"文件地址"] name:@"file" fileName:@"1234.png" mimeType:@"application/octet-stream" error:nil];
    } progress:^(NSProgress * _Nonnull uploadProgress) {
        
        //打印下上传进度
        NSLog(@"%lf",1.0 *uploadProgress.completedUnitCount / uploadProgress.totalUnitCount);
    } success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        
        //请求成功
        NSLog(@"请求成功：%@",responseObject);
        
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        
        //请求失败
        NSLog(@"请求失败：%@",error);
    }];
}
```
# 6,监测当前网络状态（网络监听）
```
@property (nonatomic, strong) YBNetworkReachabilityManager *manager;

- (void)judgeNet
{
    self.manager = [YBNetworkReachabilityManager manager];
    __weak typeof(self) weakSelf = self;
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
```
