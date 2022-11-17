//
//  QNFaceCompare.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>
#import "QNFaceCompareParams.h"
#import "QNFaceCompareResponse.h"

@class QNTrack;
NS_ASSUME_NONNULL_BEGIN

//人脸对比
@interface QNFaceCompare : NSObject

/**
 @param source 源人脸信息
 @param target 目标人脸信息
 @param complete 成功回调
 @param failure 失败回调
 */
+ (void)startCompare:(QNFaceCompareParams *)source
              target:(QNFaceCompareParams *)target
            complete:(void (^)(QNFaceCompareResponse * _Nonnull))complete
             failure:(void (^)(NSError * _Nonnull))failure;

@end

NS_ASSUME_NONNULL_END
