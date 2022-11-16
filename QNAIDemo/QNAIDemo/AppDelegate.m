//
//  AppDelegate.m
//  QNAIDemo
//
//  Created by 郭茜 on 2021/6/24.
//

#import "AppDelegate.h"
#import <QNAISDK/QNAISDK.h>
#import "QNMainViewController.h"
#import "MBProgressHUD+QNShow.h"
#import <QNRTCKit/QNRTCKit.h>
#include <CommonCrypto/CommonHMAC.h>
#include <CommonCrypto/CommonDigest.h>

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    //测试用的token ,接入时使用registerWithAIToken方法 使用从服务端获取的token
    [[QNAISDKManager shareManager] setAIToken:[self debugAiToken]];
    [[QNAISDKManager shareManager] setSignBlock:^NSString * _Nonnull(NSString * _Nonnull url) {
        return [self token:url];
    }];

    [QNRTCEngine enableFileLogging];
    [self requestRoomTokenWithRoomName:@"41341343" appId:@"d8lk7l4ed" userId:@"5923"];
    
    return YES;
}


//获取roomToken
- (void)requestRoomTokenWithRoomName:(NSString *)roomName appId:(NSString *)appId userId:(NSString *)userId {
    
    NSURL *requestUrl = [NSURL URLWithString:[NSString stringWithFormat:@"https://api-demo.qnsdk.com/v1/rtc/token/admin/app/%@/room/%@/user/%@", appId, roomName, userId]];
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] initWithURL:requestUrl];
    [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
    request.HTTPMethod = @"GET";
    request.timeoutInterval = 10;
    
    NSURLSessionDataTask *task = [[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {

        NSString *roomToken = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
        if (roomToken.length > 0) {
            [self gotoRTCVcWithRoomToken:roomToken];
            NSLog(@"roomtoken = %@",roomToken);
        } else {
            [MBProgressHUD showText:@"roomToken为空"];
        }
    }];
    [task resume];

}

- (void)gotoRTCVcWithRoomToken:(NSString *)roomToken {
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
        self.window.backgroundColor = [UIColor whiteColor];
        QNMainViewController *vc = [[QNMainViewController alloc]init];
        vc.modalPresentationStyle = UIModalPresentationFullScreen;
        vc.roomToken = roomToken;
        self.window.rootViewController = vc;
        [self.window makeKeyAndVisible];
       
    });
    
}


#pragma mark - Debug
//HmacSHA1加密；
- (NSString *)HmacSha1:(NSString *)key data:(NSString *)data
{
    const char *cKey  = [key cStringUsingEncoding:NSASCIIStringEncoding];
    const char *cData = [data cStringUsingEncoding:NSASCIIStringEncoding];
    
    //sha1
    unsigned char cHMAC[CC_SHA1_DIGEST_LENGTH];
    CCHmac(kCCHmacAlgSHA1, cKey, strlen(cKey), cData, strlen(cData), cHMAC);

    NSData *HMAC = [[NSData alloc] initWithBytes:cHMAC length:sizeof(cHMAC)];
    NSString *hash = [HMAC base64EncodedStringWithOptions:0];//将加密结果进行一次BASE64编码。
    
    return hash;
}

- (NSString *)token:(NSString *)url {
    NSString *token = [@"QxZugR8TAhI38AiJ_cptTl3RbzLyca3t-AAiH-Hh:" stringByAppendingString:[self HmacSha1:@"4yv8mE9kFeoE31PVlIjWvi3nfTytwT0JiAxWjCDa" data:url]];
    token = [token stringByReplacingOccurrencesOfString:@"/" withString:@"_"];
    token = [token stringByReplacingOccurrencesOfString:@"+" withString:@"-"];
    return token;
}

- (NSString *)debugAiToken {
    NSString *appId = @"testApp";
    NSString *expiration = [self getDate:[NSDate date] day:7];
    NSString *src = [NSString stringWithFormat:@"%@:%@",appId,expiration];
    NSString *base64Str = [[src dataUsingEncoding:NSUTF8StringEncoding] base64EncodedStringWithOptions:0];
    
    NSString *encodedStr = [self HmacSha1:@"B8IUczRc8wlbttCxesVLzS0pEWZ_aKEQ63Cz9CzR" data:base64Str];
    encodedStr = [encodedStr stringByReplacingOccurrencesOfString:@"/" withString:@"_"];
    encodedStr = [encodedStr stringByReplacingOccurrencesOfString:@"+" withString:@"-"];
    
    NSString *token = [NSString stringWithFormat:@"QD bsOUqUaLN-cJ3DlmdD6jU8B7_Nq5fo6IDZVAhtLe:%@:%@",encodedStr,base64Str];
        
    return token;
}

//获取指定日期几天后的时间戳
- (NSString *)getDate:(NSDate *)currentDate day:(NSInteger)day {
    NSTimeInterval oneDay = 24 * 60 * 60;  // 一天一共有多少秒
    NSDate *appointDate = [currentDate initWithTimeIntervalSinceNow: +(oneDay * day)];
    
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init] ;
    [formatter setDateStyle:NSDateFormatterMediumStyle];
    [formatter setTimeStyle:NSDateFormatterShortStyle];
    [formatter setDateFormat:@"YYYY-MM-dd HH:mm:ss"];
    NSTimeZone* timeZone = [NSTimeZone timeZoneWithName:@"Asia/Shanghai"];
    [formatter setTimeZone:timeZone];

    NSString *timeSp = [NSString stringWithFormat:@"%ld", (long)[appointDate timeIntervalSince1970]];
    return timeSp;
}

@end
