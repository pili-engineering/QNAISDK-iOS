//
//  QNFaceDetectParams.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNFaceDetectParams : NSObject
//人脸检测失败时，是否对图像 A 做旋转再检测，旋转角包 括 90、180、270 三个角度，默认值为 False
@property (nonatomic, assign) BOOL rotate;
//base64编码的图片数据
@property (nonatomic, copy) NSString *image_b64;

@end

NS_ASSUME_NONNULL_END
