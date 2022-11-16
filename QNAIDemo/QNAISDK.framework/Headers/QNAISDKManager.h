//
//  QNAISDKManager.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/6/24.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * _Nonnull (^QNUrlSignBlock)(NSString  * _Nonnull url);


@interface QNAISDKManager : NSObject

+ (instancetype)shareManager;

- (void)setAIToken:(NSString *)aiToken;

- (void)setSignBlock:(QNUrlSignBlock) block;

- (NSString *)signUrl:(NSString *)url;

@property (nonatomic, copy) NSString *aiToken;

@end

NS_ASSUME_NONNULL_END
