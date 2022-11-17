//
//  QNFaceDetect.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>

#import "QNFaceDetectParams.h"
#import "QNFaceDetectResponse.h"

@class QNTrack;
NS_ASSUME_NONNULL_BEGIN
//人脸识别
@interface QNFaceDetect : NSObject

+ (void)startDetectWithParams:(QNFaceDetectParams *)params complete:(void (^)(QNFaceDetectResponse *result))complete failure:(nonnull void (^)(NSError * _Nonnull error))failure;

@end

NS_ASSUME_NONNULL_END
