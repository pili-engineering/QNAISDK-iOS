//
//  QNFlashLiveDetect.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>
#import "QNFlashLiveDetectResult.h"

@class QNTrack;

NS_ASSUME_NONNULL_BEGIN
//光线活体检测
@interface QNFlashLiveDetect : NSObject 

+ (instancetype)shareManager DEPRECATED_ATTRIBUTE;

//开始光线活体检测
- (void)startDetectWithTrack:(QNTrack *)track DEPRECATED_ATTRIBUTE;

- (void)detectComplete:(void (^)(QNFlashLiveDetectResult *result))complete failure:(nonnull void (^)(NSError * _Nonnull error))failure DEPRECATED_ATTRIBUTE;

- (void)cancel DEPRECATED_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END
