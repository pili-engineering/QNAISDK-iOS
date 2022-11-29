//
//  QNAuthoritativeFaceParams.h
//  QNAISDK
//
//  Created by 郭茜 on 2022/1/14.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNAuthoritativeFaceParams : NSObject

/// 真实姓名
@property (nonatomic, copy) NSString *realname;

///  身份证ID
@property (nonatomic, copy) NSString *idcard;

@end

NS_ASSUME_NONNULL_END
