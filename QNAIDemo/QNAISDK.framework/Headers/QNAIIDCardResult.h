//
//  QNAIIDCardResult.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/6/25.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNAIIDCardOCRResult : NSObject
// 地址(人像面)
@property (nonatomic, copy) NSString *address;
// F-身份证人像面，B-身份 证国徽面
@property (nonatomic, copy) NSString *side;
// 身份号码(人像面)
@property (nonatomic, copy) NSString *idno;
// 姓名(人像面)
@property (nonatomic, copy) NSString *name;
// 生日(人像面) eg. "19900111"
@property (nonatomic, copy) NSString *birthdate;
// 性别(人像面)
@property (nonatomic, copy) NSString *gender;
// 民族(人像面)
@property (nonatomic, copy) NSString *nation;
// 有效期(国徽面) eg. "20001010-20101009"
@property (nonatomic, copy) NSString *validthru;
// 签发机关(国徽面)
@property (nonatomic, copy) NSString *issuedby;

@end


@interface QNAIIDCardImageResult : NSObject
// 框坐标，格式为 [[x0, y0], [x1, y1], [x2, y2], [x3, y3]]
@property (nonatomic, strong) NSArray *idcard_bbox;

@end


@interface QNAIIDCardResult : NSObject

@property (nonatomic, assign) NSInteger errorcode;

@property (nonatomic, copy) NSString *errormsg;
//身份证文字识别结果
@property (nonatomic, strong) QNAIIDCardOCRResult *ocr_result;
//图片识别结果
@property (nonatomic, strong) QNAIIDCardImageResult *image_result;

@end

NS_ASSUME_NONNULL_END
