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

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    //测试用的token ,接入时使用registerWithAIToken方法 使用从服务端获取的token
    [[QNAISDKManager shareManager] debugToken];
//    [[QNAISDKManager shareManager] registerWithAIToken:@""];
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


@end
