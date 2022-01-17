//
//  QNAuthoritativeFaceResult.h
//  QNAISDK
//
//  Created by 郭茜 on 2022/1/14.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNAuthoritativeFaceResult : NSObject

@property (nonatomic, copy) NSString *similarity;

@property (nonatomic, assign) NSInteger errorcode;

@property (nonatomic, copy) NSString *errormsg;

@property (nonatomic, assign) BOOL *pass;


@end

NS_ASSUME_NONNULL_END
