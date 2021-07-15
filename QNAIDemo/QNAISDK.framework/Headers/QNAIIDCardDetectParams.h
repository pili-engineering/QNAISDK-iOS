//
//  QNAIRequestParams.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/6/24.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

//身份证识别请求参数
@interface QNAIIDCardDetectParams : NSObject

//需要识别的照片base64编码

@property (nonatomic, copy) NSString *image;

// 是否返回识别后的切图(切图是指精确剪裁对齐后的身份证正反面图片)，返回格式为 JPEG 格式二进制图片使用 base64 编码后的字符串

@property (nonatomic, assign) BOOL ret_image;

// 是否返回身份证(人像面)的人脸图 片，返回格式为 JPEG 格式二进制图片使用 base64 编码后的字符串

@property (nonatomic, assign) BOOL ret_portrait;

// 当图片中同时存在身份证正反面时，通过该参数指定识别的版面:取值'Any' - 识别人像面或国徽面，'F' - 仅 识别人像面，'B' - 仅识别国徽面

@property (nonatomic, copy) NSString *ref_side;

// 身份证遮挡检测开关，如果输入图片中的身份证卡片边框不完整则返回告警

@property (nonatomic, assign) BOOL enable_border_check;

// 复印件、翻拍件检测开关，如果输入图片中的身份证卡片是复印件，则返回告警

@property (nonatomic, assign) BOOL enable_detect_copy;

@end

NS_ASSUME_NONNULL_END
