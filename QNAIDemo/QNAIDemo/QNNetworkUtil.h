//
//  QNNetworkUtil.h
//  QiNiu_Solution_iOS
//
//  Created by 郭茜 on 2021/4/13.
//

#import <Foundation/Foundation.h>
#import <AFNetworking/AFNetworking.h>

@interface QNNetworkUtil : NSObject

+ (AFHTTPSessionManager *)manager;
//登录请求
+ (void)postLoginRequestWithAction:(NSString *)action params:(NSDictionary *)params success:(void (^)(NSDictionary *))success failure:(void (^)(NSError *))failure;
//IM请求
+ (void)postIMRequestWithAction:(NSString *)action params:(NSDictionary *)params success:(void (^)(NSDictionary *responseData))success failure:(void (^)(NSError *error))failure;

@end
