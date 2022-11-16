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

+ (void)startCompare:(QNFaceCompareParams *)source
              target:(QNFaceCompareParams *)target
            complete:(void (^)(QNFaceCompareResponse * _Nonnull))complete
             failure:(void (^)(NSError * _Nonnull))failure;

@end

NS_ASSUME_NONNULL_END
