//
//  QNFaceCompare.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>
#import "QNFaceCompareParams.h"
#import "QNFaceCompareResult.h"

@class QNTrack;
NS_ASSUME_NONNULL_BEGIN

//人脸对比
@interface QNFaceCompare : NSObject

+ (void)startCompareWithParams:(QNFaceCompareParams *)params complete:(void (^)(QNFaceCompareResult *result))complete failure:(nonnull void (^)(NSError * _Nonnull error))failure;

@end

NS_ASSUME_NONNULL_END
