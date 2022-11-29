//
//  QNAuthoritativeFaceResult.h
//  QNAISDK
//
//  Created by 郭茜 on 2022/1/14.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNAuthoritativeFaceResult : NSObject

@property (nonatomic, assign) NSInteger errorcode;

@property (nonatomic, copy) NSString *errormsg;

/// 相似度
@property (nonatomic, assign) double similarity;

/// 是否比对通过 true 通过；false 不通过
@property (nonatomic, assign) BOOL *pass;


@end

NS_ASSUME_NONNULL_END
