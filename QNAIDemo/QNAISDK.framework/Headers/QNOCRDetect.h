//
//  QNOCRDetect.h
//  QNAISDK
//
//  Created by 郭茜 on 2022/1/14.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class OCRDetectResult,QNTrack;;

@interface QNOCRDetect : NSObject

+ (instancetype)shareManager;

- (void)startDetectWithVideoTrack:(QNTrack *)track complete:(void (^)(OCRDetectResult *result))complete failure:(nonnull void (^)(NSError * _Nonnull error))failure;

@end

NS_ASSUME_NONNULL_END
