//
//  QNNetworkUtil.m
//  QiNiu_Solution_iOS
//
//  Created by 郭茜 on 2021/4/13.
//

#import "QNNetworkUtil.h"
#import <AFNetworking/AFNetworking.h>
#import <YYCategories/YYCategories.h>

#ifdef DEBUG
#define NSLog(FORMAT, ...) fprintf(stderr,"\n %s:%d   %s\n",[[[NSString stringWithUTF8String:__FILE__] lastPathComponent] UTF8String],__LINE__, [[[NSString alloc] initWithData:[[NSString stringWithFormat:FORMAT, ##__VA_ARGS__] dataUsingEncoding:NSUTF8StringEncoding] encoding:NSNonLossyASCIIStringEncoding] UTF8String]);
#else
#define NSLog(...)
#endif

@implementation QNNetworkUtil

+ (AFHTTPSessionManager *)manager {
    
    AFHTTPSessionManager *manager = [AFHTTPSessionManager manager];
    manager.responseSerializer.acceptableContentTypes = [[NSSet alloc] initWithObjects:
                                                              @"application/xml",
                                                              @"text/xml",
                                                              @"text/html",
                                                              @"application/json",
                                                              @"text/plain",
                                                              @"image/jpeg",
                                                              @"image/png",
                                                              @"application/octet-stream",
                                                              @"text/json",
                                                              @"charset=utf-8",nil];
    
    manager.requestSerializer = [AFHTTPRequestSerializer serializer];
    
    [manager.requestSerializer setValue:@"application/x-www-form-urlencoded" forHTTPHeaderField:@"Content-Type"];
    
    return manager;
}

+ (void)postIMRequestWithAction:(NSString *)action params:(NSDictionary *)params success:(void (^)(NSDictionary *))success failure:(void (^)(NSError *))failure {
    
    AFHTTPSessionManager *manager = [QNNetworkUtil manager];

    NSString *apiStr = @"https://im-test.qiniuapi.com/v1/mock/";
    NSString *requestUrl = [NSString stringWithFormat:@"%@%@",apiStr,action];
    
    [manager POST:requestUrl parameters:params headers:nil progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        
        NSLog(@"\n POST \n action : %@ \n HTTPRequestHeaders:%@ \n params:%@ \n responseObject = %@",requestUrl,manager.requestSerializer.HTTPRequestHeaders,params,responseObject);

        if ([responseObject[@"code"] isEqualToNumber:@(0)]) {
            success(responseObject[@"data"] ?: nil);
        } else {
            failure(nil);
        }
        
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        NSLog(@"\n POST \n action : %@ \n HTTPRequestHeaders:%@ \n params:%@ \n error = %@",requestUrl,manager.requestSerializer.HTTPRequestHeaders,params,error);
        failure(error);
    }];
    
}

+ (void)postLoginRequestWithAction:(NSString *)action params:(NSDictionary *)params success:(void (^)(NSDictionary *))success failure:(void (^)(NSError *))failure {
    
    AFHTTPSessionManager *manager = [QNNetworkUtil manager];

    NSString *requestUrl = [[NSString alloc]initWithFormat:@"https://niucube-api.qiniu.com/v1/%@",action];
    
    [manager POST:requestUrl parameters:params headers:nil progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        
        NSLog(@"\n POST \n action : %@ \n HTTPRequestHeaders:%@ \n params:%@ \n responseObject = %@",requestUrl,manager.requestSerializer.HTTPRequestHeaders,params,responseObject);
       
        if ([responseObject[@"code"] isEqualToNumber:@(0)]) {
            success(responseObject[@"data"] ?: nil);
        } else {
            failure(nil);
        }
        
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        NSLog(@"\n POST \n action : %@ \n HTTPRequestHeaders:%@ \n params:%@ \n error = %@",requestUrl,manager.requestSerializer.HTTPRequestHeaders,params,error);
        failure(error);
    }];
    
}

@end
