//
//  QNAISDKManager.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/6/24.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNAISDKManager : NSObject

+ (instancetype)shareManager;

- (void)registerWithAIToken:(NSString *)aiToken;

-(void)debugToken;

@property (nonatomic, copy) NSString *aiToken;

@end

NS_ASSUME_NONNULL_END
