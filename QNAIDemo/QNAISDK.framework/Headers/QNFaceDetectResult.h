//
//  QNFaceDetectResult.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNFaceModel : NSObject
//人脸模糊度，取值范围[0,1]，越大越清晰
@property (nonatomic, assign) CGFloat blur;
//性别，’M’代表男，’F’代表女
@property (nonatomic, copy) NSString *gender;
//年龄，区间 1-107 岁
@property (nonatomic, assign) NSInteger age;
//人脸光照范围，取值范围[0,100]，越大光照质量越好
@property (nonatomic, assign) CGFloat illumination;
//人脸尺寸分数，取值分数[0,100]， 越大人脸尺寸越大
@property (nonatomic, assign) CGFloat facesize;
//人脸综合质量分数，取值范围[0,100], 越大质量越好
@property (nonatomic, assign) CGFloat quality;
//闭眼概率,取值范围[0,100]
@property (nonatomic, assign) CGFloat eye;
//闭嘴概率,取值范围[0,100]
@property (nonatomic, assign) CGFloat mouth;
//三维旋转之俯仰角，[-180,180]
@property (nonatomic, assign) CGFloat pitch;
//三维旋转之旋转角，[-180,180]
@property (nonatomic, assign) CGFloat roll;
//三维旋转之左右旋转角, [-180,180]
@property (nonatomic, assign) CGFloat yaw;
//取值0到100；0表示人脸不完整，溢出了图像边界，100 表示人脸是完整的，在图像边界内
@property (nonatomic, assign) NSInteger completeness;
//人脸区域的大小
@property (nonatomic, assign) NSInteger area;
//使用 base64 编码的对齐后人脸图片数据
@property (nonatomic, copy) NSString *face_aligned_b64;
//人脸分数 取值范围 [0,100]
@property (nonatomic, assign) CGFloat score;
//人脸框的左上角 x 坐标
@property (nonatomic, assign) NSInteger x;
//人脸框的左上角 y 坐标
@property (nonatomic, assign) NSInteger y;
//人脸框的宽度
@property (nonatomic, assign) NSInteger width;
//人脸框的高度
@property (nonatomic, assign) NSInteger height;
//人脸 106 个关键点坐标，包含 face_profile，left_eye, left_eyebrow，right_eye，right_eyebrow，mouth，nose，pupil 等组件，每个组件都是一个 json
@property (nonatomic, copy) NSString *face_shape;

@end

@interface QNFaceDetectResult : NSObject
//图像中人脸数量
@property (nonatomic, assign) NSInteger num_face;
//图像旋转角度
@property (nonatomic, assign) CGFloat rotangle;

@property (nonatomic, strong) NSArray <QNFaceModel *> *face;

@property (nonatomic, assign) NSInteger errorcode;

@property (nonatomic, copy) NSString *errormsg;

@end

NS_ASSUME_NONNULL_END
