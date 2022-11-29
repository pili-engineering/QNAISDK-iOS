//
//  QNFaceDetectResult.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNFaceAngle : NSObject

@property (nonatomic, assign) double yaw;  //三维旋转之左右旋转角[-90(左), 90(右)]
@property (nonatomic, assign) double pitch;//三维旋转之俯仰角度[-90(上), 90(下)]
@property (nonatomic, assign) double roll; //平面内旋转角[-180(逆时针), 180(顺时针)]

@end

@interface QNFaceLocation : NSObject
@property (nonatomic, assign) double left;   //人脸区域离左边界的距离
@property (nonatomic, assign) double top;    //人脸区域离上边界的距离
@property (nonatomic, assign) double width;  //人脸区域的宽度
@property (nonatomic, assign) double height; //人脸区域的高度
@property (nonatomic, assign) double rotation; //人脸框相对于竖直方向的顺时针旋转角，[-180,180]
@end

@interface QNFaceExpression : NSObject
@property (nonatomic, copy) NSString *type;  //none:不笑；smile:微笑；laugh:大笑
@property (nonatomic, assign) double probability;//表情置信度，范围【0~1】，0最小、1最大。
@end

@interface QNFaceGender : NSObject
@property (nonatomic, copy) NSString *type;       //square: 正方形 triangle:三角形 oval: 椭圆 heart: 心形 round: 圆形
@property (nonatomic, assign) double probability;//置信度，范围【0~1】，0最小、1最大。
@end

@interface QNFaceGlasses : NSObject
@property (nonatomic, copy) NSString *type;       //none:无眼镜，common:普通眼镜，sun:墨镜
@property (nonatomic, assign) double probability;//置信度，范围【0~1】，0最小、1最大。
@end

@interface QNFaceShape : NSObject
@property (nonatomic, copy) NSString *type; //human: 真实人脸 cartoon: 卡通人脸
@property (nonatomic, assign) double probability; //human: 真实人脸 cartoon: 卡通人脸
@end

@interface QNFaceOcclusion : NSObject

 @property (nonatomic, assign) int leftEye;    //左眼遮挡比例，[0-1] ，1表示完全遮挡
@property (nonatomic, assign)  int rightEye;   //右眼遮挡比例，[0-1] ，1表示完全遮挡
@property (nonatomic, assign)  int nose;       //鼻子遮挡比例，[0-1] ，1表示完全遮挡
@property (nonatomic, assign)  int mouth;      //嘴遮挡比例，[0-1] ，1表示完全遮挡
@property (nonatomic, assign)  int leftCheek;  //左脸颊遮挡比例，[0-1] ，1表示完全遮挡
@property (nonatomic, assign)  int rightCheek; //右脸颊遮挡比例，[0-1] ，1表示完全遮挡
@property (nonatomic, assign)  int chinContour;//下巴遮挡比例，[0-1] ，1表示完全遮挡
                

@end

@interface QNFaceQuality : NSObject

@property (nonatomic, strong) QNFaceOcclusion *occlusion; //人脸各部分遮挡的概率，范围[0~1]，0表示完整，1表示不完整
@property (nonatomic, assign) int blur;            //人脸模糊程度，范围[0~1]，0表示清晰，1表示模糊
@property (nonatomic, assign) int illumination;    //取值范围在[0~255], 表示脸部区域的光照程度 越大表示光照越好
@property (nonatomic, assign) int completeness;    //人脸完整度，0或1, 0为人脸溢出图像边界，1为人脸都在图像边界内

@end

@interface QNFaceLandmark : NSObject
@property (nonatomic, assign) double x;
@property (nonatomic, assign) double y;
@end

@interface QNFaceModel : NSObject

@property (nonatomic, copy) NSString *faceToken;    //人脸图片的唯一标识
@property (nonatomic, assign) NSInteger faceProbability; //人脸置信度，范围【0~1】，代表这是一张人脸的概率，0最小、1最大。其中返回0或1时，数据类型为Integer
@property (nonatomic, assign) double age;          //年龄 ，当face_field包含age时返回
@property (nonatomic, strong) QNFaceLocation *location;   //人脸在图片中的位置
@property (nonatomic, strong) QNFaceAngle *angle;         //人脸旋转角度参数
@property (nonatomic, strong) QNFaceExpression *expression;//表情，当 face_field包含expression时返回
@property (nonatomic, strong) QNFaceGender *gender;        //性别，face_field包含gender时返回
@property (nonatomic, strong) QNFaceGlasses *glasses;      //是否带眼镜，face_field包含glasses时返回
@property (nonatomic, strong) QNFaceShape *faceShape;  //脸型，当face_field包含face_shape时返回
@property (nonatomic, strong) QNFaceQuality *quality;      //人脸质量信息。face_field包含quality时返回
@property (nonatomic, strong) NSArray<QNFaceLandmark *> *landmark; //4个关键点位置，左眼中心、右眼中心、鼻尖、嘴中心。face_field包含landmark时返回
@property (nonatomic, strong) NSArray<QNFaceLandmark *> *landmark72; //72个特征点位置 face_field包含landmark时返回

@end



@interface QNFaceDetectResult : NSObject

@property (nonatomic, assign) NSInteger faceNum;
@property (nonatomic, strong) NSArray<QNFaceModel *> *faceList;

@end

@interface QNFaceDetectResponse : NSObject


@property (nonatomic, assign) NSInteger errorCode;

@property (nonatomic, copy) NSString *errorMsg;

//请求日志ID
@property (nonatomic, copy) NSString *logID;

@property (nonatomic, strong) QNFaceDetectResult *result;

@end

NS_ASSUME_NONNULL_END
