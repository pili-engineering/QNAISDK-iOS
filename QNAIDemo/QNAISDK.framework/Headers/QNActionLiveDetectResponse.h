//
//  QNActionLiveDetectResult.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef enum{
    QNFaceActionTypeBlink = 0, //请眨眨眼
    QNFaceActionTypeRaise = 4,//请抬头
    QNFaceActionTypeLower = 5,//请低头
    QNFaceActionTypeShake = 7,//请摇摇头
} QNFaceActionType;

@interface QNActiveSessionRequest : NSObject

//视频动作活体的验证码最小长度：最大3 最小1 默认1
@property (nonatomic, assign) NSInteger min_code_length;

//视频动作活体的验证码最大长度：最大3 最小1 默认3
@property (nonatomic, assign) NSInteger max_code_length;

@end

@interface QNActiveSession : NSObject

//随机校验码会话id，有效期5分钟，请提示用户在五分钟内完成全部操作验证码使用过即失效，每次使用视频活体前请重新拉取验证码
@property (nonatomic, copy) NSString *sessionID;

//随机验证码，数字形式，1~6位数字；若为动作活体时，返回数字表示的动作对应关系为：0:眨眼 4:抬头 5:低头 7:左右转头(不区分先后顺序，分别向左和向右转头)
@property (nonatomic, copy) NSString *code;

- (NSArray<NSNumber *> *) actions;

@end

@interface QNActiveSessionResponse : NSObject

//请求返回码
@property (nonatomic, assign) NSInteger errorCode;

//请求返回错误信息
@property (nonatomic, copy) NSString *errorMsg;

//服务端日志ID
@property (nonatomic, copy) NSString *serverLogID;

@property (nonatomic, strong) QNActiveSession *result;

@end


@interface QNActionLiveDetectParam : NSObject

//会话ID, 获取方式参考校验码接口
@property (nonatomic, copy) NSString *sessionID;

//需要使用合成图功能时, 此项传入spoofing;需要使用图片质量信息时，则传入quality;字段之间使用,号分隔，eg：spoofing,quality
@property (nonatomic, copy) NSString *faceField;


@end



@interface QNActionLiveDetectOcclusion : NSObject

@property (nonatomic, assign) double leftEye;    //左眼遮挡比例，[0-1] ，1表示完全遮挡
@property (nonatomic, assign) double rightEye;   //右眼遮挡比例，[0-1] ，1表示完全遮挡
@property (nonatomic, assign) double nose;       //鼻子遮挡比例，[0-1] ，1表示完全遮挡
@property (nonatomic, assign) double mouth;      //嘴遮挡比例，[0-1] ，1表示完全遮挡
@property (nonatomic, assign) double leftCheek;  //左脸颊遮挡比例，[0-1] ，1表示完全遮挡
@property (nonatomic, assign) double rightCheek; //右脸颊遮挡比例，[0-1] ，1表示完全遮挡
@property (nonatomic, assign) double chinContour;//下巴遮挡比例，[0-1] ，1表示完全遮挡

@end

@interface QNActionLiveDetectQuality : NSObject

@property (nonatomic, strong) QNActionLiveDetectOcclusion *occlusion; //人脸各部分遮挡的概率，范围[0~1]，0表示完整，1表示不完整
@property (nonatomic, assign) double blur;         //人脸模糊程度，范围[0~1]，0表示清晰，1表示模糊
@property (nonatomic, assign) double illumination; //取值范围在[0~255], 表示脸部区域的光照程度 越大表示光照越好
@property (nonatomic, assign) double completeness; //人脸完整度，0或1, 0为人脸溢出图像边界，1为人脸都在图像边界内

@end

@interface QNActionLiveDetectAngle : NSObject

@property (nonatomic, assign) double yaw;
@property (nonatomic, assign) double pitch;
@property (nonatomic, assign) double roll;

@end

@interface QNActionLiveDetectImage : NSObject

//base64编码后的图片信息
@property (nonatomic, copy) NSString *pic;

//人脸图片的唯一标识
@property (nonatomic, copy) NSString *faceToken;

//人脸ID
@property (nonatomic, copy) NSString *faceID;

//此图片的活体分数，范围[0,1]
@property (nonatomic, assign)   double livenessScore;

//此图片的合成图分数，范围[0,1]
@property (nonatomic, assign) double spoofing;


@property (nonatomic, assign) double notSpoofing;

//人脸质量信息。face_field包含quality时返回
@property (nonatomic, strong) QNActionLiveDetectQuality *quality;

//角度信息
@property (nonatomic, strong) QNActionLiveDetectAngle *angle;

@end

@interface QNActionLiveDetectThresholds : NSObject

//万分之一误拒率的阈值
@property (nonatomic, assign) double frr_1e4;

//千分之一误拒率的阈值
@property (nonatomic, assign) double frr_1e3;

//百分之一误拒率的阈值
@property (nonatomic, assign) double frr_1e2;

@end

@interface QNActionLiveDetectResult : NSObject

//活体检测的总体打分 范围[0,1]，分数越高则活体的概率越大
@property (nonatomic, assign) double score;

//返回的1-8张图片中合成图检测得分的最大值 范围[0,1]，分数越高则概率越大
@property (nonatomic, assign) double maxSpoofing;

//返回的1-8张图片中合成图检测得分的中位数 范围[0,1]，分数越高则概率越大
@property (nonatomic, assign) double spoofingScore;

//动作识别结果 pass代表动作验证通过，fail代表动作验证未通过
@property (nonatomic, copy) NSString *actionVerify;

//阈值 按活体检测分数>阈值来判定活体检测是否通过(阈值视产品需求选择其中一个)
@property (nonatomic, strong) QNActionLiveDetectThresholds *thresholds;

//图片信息
@property (nonatomic, strong) QNActionLiveDetectImage *bestImage;

//返回1-8张抽取出来的图片信息
@property (nonatomic, strong) NSArray<QNActionLiveDetectImage*> *picList;

@end


@interface QNActionLiveDetectResponse : NSObject

//请求返回码
@property (nonatomic, assign) NSInteger errorCode;

//请求返回错误信息
@property (nonatomic, copy) NSString *errorMsg;

//服务端日志ID
@property (nonatomic, copy) NSString *serverLogID;

//检测结果
@property (nonatomic, strong) QNActionLiveDetectResult *result;

@end

NS_ASSUME_NONNULL_END
