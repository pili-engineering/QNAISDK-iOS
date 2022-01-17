//
//  QNAuthoritativeFaceComparer.h
//  QNAISDK
//
//  Created by 郭茜 on 2022/1/14.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

//权威人脸比对

@class QNAuthoritativeFaceParams,QNAuthoritativeFaceResult,QNTrack;;

@interface QNAuthoritativeFaceComparer : NSObject

+ (instancetype)shareManager;

- (void)startDetectWithVideoTrack:(QNTrack *)track params:(QNAuthoritativeFaceParams *)params complete:(void (^)(QNAuthoritativeFaceResult *result))complete failure:(nonnull void (^)(NSError * _Nonnull error))failure;

@end

NS_ASSUME_NONNULL_END
