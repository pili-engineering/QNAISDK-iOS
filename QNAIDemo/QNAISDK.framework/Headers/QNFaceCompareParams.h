//
//  QNFaceCompareParams.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNFaceCompareParams : NSObject
//图片数据 A: base64 编码 
@property (nonatomic, copy) NSString *data_uri_a;
//图片数据 B: base64 编码
@property (nonatomic, copy) NSString *data_uri_b;
//人脸检测失败时，是否对图像 A 做旋转再检测，旋转角包括 90、180、270 三个角度，默认值为 False
@property (nonatomic, assign) BOOL rotate_A;
//人脸检测失败时，是否对图像 B 做旋转再检测，旋转角包括 90、180、270 三个角度，默认值为 False
@property (nonatomic, assign) BOOL rotate_B;
//图像 A 中检测到多张人脸时是否取最大区域的人脸作为输出，默认值为 False
@property (nonatomic, assign) BOOL maxface_A;
//图像 B 中检测到多张人脸时是否取最大区域的人脸作为输出，默认值为 False
@property (nonatomic, assign) BOOL maxface_B;

@end

NS_ASSUME_NONNULL_END
