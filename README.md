# QNAISDK-iOS

# 说明

* 本文档介绍七牛RTC 接入AI 的SDK 使用方式。

* 适合 QNAISDK v2.0.1 版本。



# 2.SDK初始化

```

[[QNAISDKManager shareManager] setAIToken:@""];
[[QNAISDKManager shareManager] setSignBlock:^NSString * _Nonnull(NSString * _Nonnull url) {
    return @"";
}];
```

## 2.1 AIToken

AIToken 用于请求服务端接口的身份验证。

```
// app_id 加上过期时间
src="<app_id>:<expiration>"
encodedSrc=urlsafe_base64_encode(src)
// 计算HMAC-SHA1签名，并对签名结果做URL安全的Base64编码
sign=hmac_sha1(encodedSrc,"Your_Secret_Key")
encodedSign=urlsafe_base64_encode(sign)
// 拼接上述结果得到 token
token="QD "+Your_Access_Key+":"+encodedSign+":"+encodedSrc``
```

涉及到用户_Secret_Key 建议签名逻辑运行在接入方服务器端完成。

## 2.2 URL签算

URL签算，用于避免URL 的内容被篡改。

URL 签算逻辑，参考 [URL签算](https://developer.qiniu.com/kodo/1202/download-token)

涉及到用户_Secret_Key 建议签名逻辑运行在接入方服务器端完成。



# 3. 人脸检测

人脸检测，用于识别视频图片中的人脸信息。

## 3.1 API 参考

#### QNFaceDetect 接口

```objc
@interface QNFaceDetect : NSObject

+ (void)startDetectWithParams:(QNFaceDetectParams *)params complete:(void (^)(QNFaceDetectResponse *result))complete failure:(nonnull void (^)(NSError * _Nonnull error))failure;

@end
```



#### 识别参数 QNFaceDetectParams

```objc
@interface QNFaceDetectParams : NSObject

//图片类型
// BASE64:图片的base64值，base64编码后的图片数据，编码后的图片大小不超过2M；
// URL: 图片的 URL地址( 可能由于网络等原因导致下载图片时间过长)；
// FACE_TOKEN: 人脸图片的唯一标识，调用人脸检测接口时，会为每个人脸图片赋予一个唯一的FACE_TOKEN，同一张图片多次检测得到的FACE_TOKEN是同一个。
@property (nonatomic, copy) NSString *imageType;

//图片信息(总数据大小应小于10M，图片尺寸在1920x1080以下)，图片上传方式根据image_type来判断。 两张图片通过json格式上传，格式参考表格下方示例
@property (nonatomic, copy) NSString *image;

//活体检测控制：
// NONE: 不进行控制，
// LOW:较低的活体要求(高通过率 低攻击拒绝率)，
// NORMAL: 一般的活体要求(平衡的攻击拒绝率, 通过率)，
// HIGH: 较高的活体要求(高攻击拒绝率 低通过率)
@property (nonatomic, strong) NSString *livenessControl;

//人脸检测排序类型 0:代表检测出的人脸按照人脸面积从大到小排列，1:代表检测出的人脸按照距离图片中心从近到远排列
@property (nonatomic, assign) NSInteger faceSortType;
    
// 是否显示检测人脸的裁剪图base64值 0：不显示（默认），1：显示
@property (nonatomic, assign) NSInteger displayCorpImage;

// 人脸的类型，默认为 LIVE
// LIVE：表示生活照：通常为手机、相机拍摄的人像图片、或从网络获取的人像图片等，
// IDCARD：表示身份证芯片照：二代身份证内置芯片中的人像照片，
// WATERMARK：表示带水印证件照：一般为带水印的小图，如公安网小图，
// CERT：表示证件照片：如拍摄的身份证、工卡、护照、学生证等证件图片
@property (nonatomic, copy)  NSString *faceType;
    
//包括age,expression,face_shape,gender,glasses,landmark,landmark150,quality,eye_status,emotion,face_type,mask,spoofing信息逗号分隔. 默认只返回face_token、人脸框、概率和旋转角度
@property (nonatomic, copy)  NSString *faceField;
    
//最多处理人脸的数目，默认值为1，根据人脸检测排序类型检测图片中排序第一的人脸（默认为人脸面积最大的人脸），最大值120
@property (nonatomic, assign) NSInteger maxFaceNum;

@end
```



#### 识别结果

```objc
@interface QNFaceDetectResponse : NSObject

@property (nonatomic, assign) NSInteger errorCode;
@property (nonatomic, copy) NSString *errorMsg;
//请求日志ID
@property (nonatomic, copy) NSString *logID;
@property (nonatomic, strong) QNFaceDetectResult *result;

@end
  
@interface QNFaceDetectResult : NSObject
// 识别出的人脸数量
@property (nonatomic, assign) NSInteger faceNum;
// 人脸模型列表
@property (nonatomic, strong) NSArray<QNFaceModel *> *faceList;
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
```



## 3.2 使用参考

```objc
    QNFaceDetectParams *params = [[QNFaceDetectParams alloc]init];
    params.imageType = @"BASE64";
    params.image = self.imageBase64Str;

    [QNFaceDetect startDetectWithParams:params complete:^(QNFaceDetectResponse * _Nonnull response) {
        if (response.errorCode != 0) {
            // 识别失败，服务端返回错误码
            return;
        }
        
        QNFaceDetectResult *result = response.result;
        // 处理识别结果
    } failure:^(NSError * _Nonnull error) {
        // 识别失败，请求服务端失败。
    }];
```



# 4 人脸比对

人脸对比，比较两个照片中人脸的相似度。

## 4.1 API 参考

```objc
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
```

#### 人脸信息参数 QNFaceCompareParams
```objc
@interface QNFaceCompareParams : NSObject

/**
 * 图片信息(总数据大小应小于10M，图片尺寸在1920x1080以下)
 */
@property (nonatomic, copy) NSString *image;

/**
 * 图片类型
 * BASE64: 图片的base64值，base64编码后的图片数据，编码后的图片大小不超过2M
 * URL:图片的 URL地址( 可能由于网络等原因导致下载图片时间过长)
 */
@property (nonatomic, copy) NSString *imageType;

/**
 * 人脸的类型
 * LIVE：表示生活照：通常为手机、相机拍摄的人像图片、或从网络获取的人像图片等，
 * IDCARD：表示身份证芯片照：二代身份证内置芯片中的人像照片，
 * WATERMARK：表示带水印证件照：一般为带水印的小图，如公安网小图
 * CERT：表示证件照片：如拍摄的身份证、工卡、护照、学生证等证件图片
 * INFRARED：表示红外照片,使用红外相机拍摄的照片
 * HYBRID：表示混合类型，如果传递此值时会先对图片进行检测判断所属类型(生活照 or 证件照)（仅针对请求参数 image_type 为 BASE64 或 URL 时有效）
 * 默认LIVE
 */
@property (nonatomic, copy) NSString *faceType;
   
/**
 * 人脸检测排序类型
 * 0:代表检测出的人脸按照人脸面积从大到小排列
 * 1:代表检测出的人脸按照距离图片中心从近到远排列
 * 默认为0
 */
@property (nonatomic, assign) NSInteger faceSortType;

/**
 * 图片质量控制
 * NONE: 不进行控制
 * LOW:较低的质量要求
 * NORMAL: 一般的质量要求
 * HIGH: 较高的质量要求
 * 默认 NONE
 * 若图片质量不满足要求，则返回结果中会提示质量检测失败
 */
@property (nonatomic, copy) NSString *qualityControl;
    
/**
 * 活体检测控制
 * NONE: 不进行控制
 * LOW:较低的活体要求(高通过率 低攻击拒绝率)
 * NORMAL: 一般的活体要求(平衡的攻击拒绝率, 通过率)
 * HIGH: 较高的活体要求(高攻击拒绝率 低通过率)
 * 默认 NONE
 * 若活体检测结果不满足要求，则返回结果中会提示活体检测失败
 */
@property (nonatomic, copy) NSString *livenessControl;

/**
 * 合成图控制参数
 * NONE: 不进行控制
 * LOW:较低的合成图阈值数值，由于合成图判定逻辑为大于阈值视为合成图攻击，该项代表低通过率、高攻击拒绝率
 * NORMAL: 一般的合成图阈值数值，由于合成图判定逻辑为大于阈值视为合成图攻击，该项代表平衡的攻击拒绝率, 通过率
 * HIGH: 较高的合成图阈值数值，由于合成图判定逻辑为大于阈值视为合成图攻击，该项代表高通过率、低攻击拒绝率
 * 默认为NONE
 */
@property (nonatomic, copy) NSString *spoofingControl;

@end
```

#### 返回结果

```objc
@interface QNFaceCompareResponse : NSObject
// 请求返回码
@property (nonatomic, assign) NSInteger errorCode;
// 提示信息
@property (nonatomic, copy) NSString *errorMsg;
// 请求日志ID
@property (nonatomic, assign) NSInteger logID;
// 请求结果
@property (nonatomic, strong) QNFaceCompareResult *result;
@end

@interface QNFaceCompareResult : NSObject
//人脸相似度得分，推荐阈值80分
@property (nonatomic, assign) double score;

//人脸信息列表，返回两个人脸信息
@property (nonatomic, strong) NSArray<QNFaceToken *> *faceList;
@end

@interface QNFaceToken : NSObject
//人脸的唯一标志
@property (nonatomic, copy) NSString *faceToken;
@end
```

## 4.2 使用样例

```objc
    QNFaceCompareParams *source = [[QNFaceCompareParams alloc]init];
    source.image = self.imageBase64Str;
    source.imageType = @"BASE64";
    
    QNFaceCompareParams *target = [[QNFaceCompareParams alloc]init];
    target.imageType = @"BASE64";
    target.image = [QNImageToVideoTool base64StringByImage:self.compareImage scaleWidth:200];
    

    [QNFaceCompare startCompare:source target:target complete:^(QNFaceCompareResponse * _Nonnull response) {
        if (response.errorCode != 0) {
            // 服务端返回错误码。
            return;
        }
        
        QNFaceCompareResult *result = response.result;
        // 成功结果处理
        
    } failure:^(NSError * _Nonnull error) {
        // 请求服务端接口失败
    }];
    
```



 # 5 动作活体检测

## 5.1 API 参考

```objc
@interface QNActionLiveDetect : NSObject

+ (instancetype)shareManager;

// 获取活体检测校验码
- (void)getFaceActliveSession:(QNActiveSessionRequest *)request
                     complete:(void (^)(QNActiveSessionResponse *response))complete
                      failure:(void (^)(NSError * _Nonnull))failure;

// 开始活体检测流录制，建议录制时间 1~10秒
- (void)startDetectWithTrack:(QNTrack *)track;


// 进行人脸检测
- (void)commitWithParam:(QNActionLiveDetectParam *)param
               complete:(void (^)(QNActionLiveDetectResponse *response))complete
                failure:(nonnull void (^)(NSError * _Nonnull error))failure;

// 取消检测
- (void)cancel;

@end
```

### 5.1.1 获取检测校验码参数

#### 检验码参数 QNActiveSessionRequest

```objc
@interface QNActiveSessionRequest : NSObject

//视频动作活体的验证码最小长度：最大3 最小1 默认1
@property (nonatomic, assign) NSInteger min_code_length;

//视频动作活体的验证码最大长度：最大3 最小1 默认3
@property (nonatomic, assign) NSInteger max_code_length;

@end
```

#### 检验码结果 QNActiveSessionResponse

```objc
@interface QNActiveSessionResponse : NSObject

//请求返回码
@property (nonatomic, assign) NSInteger errorCode;

//请求返回错误信息
@property (nonatomic, copy) NSString *errorMsg;

//服务端日志ID
@property (nonatomic, copy) NSString *serverLogID;

@property (nonatomic, strong) QNActiveSession *result;

@end
  
@interface QNActiveSession : NSObject

//随机校验码会话id，有效期5分钟，请提示用户在五分钟内完成全部操作验证码使用过即失效，每次使用视频活体前请重新拉取验证码
@property (nonatomic, copy) NSString *sessionID;

//随机验证码，数字形式，1~6位数字；若为动作活体时，返回数字表示的动作对应关系为：0:眨眼 4:抬头 5:低头 7:左右转头(不区分先后顺序，分别向左和向右转头)
@property (nonatomic, copy) NSString *code;

- (NSArray<NSNumber *> *) actions;

@end

// 动作枚举值  
typedef enum{
    QNFaceActionTypeBlink = 0, //请眨眨眼
    QNFaceActionTypeRaise = 4,//请抬头
    QNFaceActionTypeLower = 5,//请低头
    QNFaceActionTypeShake = 7,//请摇摇头
} QNFaceActionType;  
```



### 5.1.2 活体检测参数

#### 活体检测参数：QNActionLiveDetectParam

```objc
@interface QNActionLiveDetectParam : NSObject

//会话ID, 获取方式参考校验码接口
@property (nonatomic, copy) NSString *sessionID;

//需要使用合成图功能时, 此项传入spoofing;需要使用图片质量信息时，则传入quality;字段之间使用,号分隔，eg：spoofing,quality
@property (nonatomic, copy) NSString *faceField;


@end
```



#### 活体检测应答：QNActionLiveDetectResponse

```objc
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
```



## 5.2 使用样例

 ```objc
    // 1. 请求活体检测校验码
    QNActiveSessionRequest *sessionRequest = [[QNActiveSessionRequest alloc] init];
    [[QNActionLiveDetect shareManager] getFaceActliveSession:sessionRequest complete:^(QNActiveSessionResponse * _Nonnull response) {
        if (response.errorCode != 0 || !response.result) {
            // 服务端返回失败
            return;
        }
        
        // 2.1 根据校验码动作列表，提示用户。建议一个动作停顿 2~3 秒。
        NSArray<NSNumber *> *actions = [response.result actions];
        
        // 2.2 同时开始录制视频
        [[QNActionLiveDetect shareManager] startDetectWithTrack:self.cameraTrack];
        

        // 3 提交检测
        QNActionLiveDetectParam *param = [[QNActionLiveDetectParam alloc] init];
        param.sessionID = response.result.sessionID;
        param.faceField = @"spoofing,quality";
            
        [[QNActionLiveDetect shareManager] commitWithParam:param complete:^(QNActionLiveDetectResponse * _Nonnull response) {
                if (response.errorCode != 0) {
                    // 服务端返回失败。
                    return;
                }
                
                // 处理检测结果
            } failure:^(NSError * _Nonnull error) {
                // 失败处理
            }];
        }];
    } failure:^(NSError * _Nonnull error) {
        // 失败处理
    }];
    
 ```



   # 6 文字转语音

## 6.1 API 参考

#### QNTextToSpeakDetect 接口

   ```objc
   @interface QNTextToSpeakDetect : NSObject
   
   /// 文字转语音
   /// @param params 请求参数
   /// @param complete 成功回调
   /// @param failure 失败回调
   + (void)startTextToSpeakWithParams:(QNTextToSpeakParams *)params complete:(void (^)(QNTextToSpeakResult *result))complete failure:(nonnull void (^)(NSError * _Nonnull error))failure;
   
   @end
        
   ```



#### 请求参数 QNTextToSpeakParams

```objc
@interface QNTextToSpeakParams : NSObject

//需要进⾏语⾳合成的⽂本内容，最短1个字，最⻓200字
@property (nonatomic, copy) NSString *content;

// TTS 发音人标识音源 id 0-6,实际可用范围根据情况, 可以不设置,默认是 0;
// 0：女声（柔和）；
// 1，女声（正式）
// 2，女生（柔和带正式）；
// 3：男声（柔和）
// 4：男声（柔和带正式）
// 5：男声（闽南话）；
// 6：女生（闽南话）。
@property (nonatomic, assign) NSInteger spkid;

/**
 * 可不填，不填时默认为 3。
 * audioType=3 返回 16K 采样率的 mp3
 * audioType=4 返回 8K 采样率的 mp3
 * audioType=5 返回 24K 采样率的 mp3
 * audioType=6 返回 48k采样率的mp3
 * audioType=7 返回 16K 采样率的 pcm 格式
 * audioType=8 返回 8K 采样率的 pcm 格式
 * audioType=9 返回 24k 采样率的pcm格式
 * audioType=10 返回 8K 采样率的 wav 格式
 * audioType=11 返回 16K 采样率的 wav 格式
 */
@property (nonatomic, assign) NSInteger audioType;

// 音量大小，取值范围为 0.75 - 1.25，默认为1
@property (nonatomic, assign) float volume;

// 语速，取值范围为 0.75 - 1.25，默认为1
@property (nonatomic, assign) float speed;

@end
```



#### 返回结果 QNTextToSpeakResult

```objc
@interface QNTextToSpeakResult : NSObject

// 错误码
@property (nonatomic, assign) NSInteger errorCode;
// 错误提示
@property (nonatomic, copy) NSString *errorMsg;

@property (nonatomic, strong) QNAudioResult *result;

@end
  
@interface QNAudioResult : NSObject

// 语音文件URL
@property (nonatomic, copy) NSString *audioUrl;

@end
```



## 6.2 使用样例

```objc
QNTextToSpeakParams *params = [[QNTextToSpeakParams alloc]init];
params.content = @"你好";
        
[QNTextToSpeakDetect startTextToSpeakWithParams:params complete:^(QNTextToSpeakResult * _Nonnull result) {
    if (result.errorCode != 0) {
        // 服务端返回错误码处理
        return;
    }
    
    // 播放语音
    [[AVAudioSession sharedInstance] setCategory: AVAudioSessionCategoryPlayback error: nil];                 
    [[AVAudioSession sharedInstance] setActive: YES error: nil];
            
    NSURL *url = [NSURL URLWithString:result.result.audioUrl];
    self.avPlayer = [[AVPlayer alloc] initWithURL:url];
    [self.avPlayer play];
} failure:^(NSError * _Nonnull error) {
    // 请求服务端接口失败处理
}];
```



   # 7 实时语音识别

## 7.1 API 参考

#### QNSpeakToTextDetect 接口

```objc
@interface QNSpeakToTextDetect : NSObject

+ (instancetype)shareManager;

// 语音转文字
// @param track audio track
// @param params 识别请求参数
// @param complete 成功回调
// @param failure 失败回调
- (void)startDetectWithTrack:(QNTrack *)track params:(QNSpeakToTextParams *)params complete:(void (^)(QNSpeakToTextResult * _Nonnull result))complete failure:(void (^)(NSError *error))failure ;

// 停止识别
- (void)stopDetect;

@end
```



#### 语音识别参数 QNSpeakToTextParams

```objc
@interface QNSpeakToTextParams : NSObject

// 识别语言，中文: 1, 英文: 2, 中英混合: 0; 默认 1
@property (nonatomic,assign) NSInteger model_type;

// 识别关键字; 相同读音时优先识别为关键字。每个词 2-4 个字, 不同词用 `,` 分割
@property (nonatomic,copy) NSString *key_words;

@end
```



语音识别结果 

   ```objc
   @interface QNSpeakToTextResult : NSObject
   
   //此识别结果是否为第一片
   @property (nonatomic, assign) BOOL isBegin;
   
   //此识别结果是否为最终结果
   @property (nonatomic, assign) BOOL isFinal;
   
   //最好的转写候选
   @property (nonatomic, strong) QNBestTranscription *bestTranscription;
   
   @end
   
     
   @interface QNBestTranscription : NSObject
   
   //句子的开始时间, 单位毫秒
   @property (nonatomic, assign) NSInteger beginTimestamp;
   //句子的结束时间, 单位毫秒
   @property (nonatomic, assign) NSInteger endTimestamp;
   //转写结果
   @property (nonatomic, copy) NSString *transcribedText;
   //转写结果中包含KeyWords内容
   @property (nonatomic, strong) NSArray<QNkeyWordsType *> *keyWordsType;
   //转写结果的分解（只对final状态结果有效，返回每个字及标点的详细信息）
   @property (nonatomic, strong) NSArray<QNPiece *> *piece;
   
   @end
     
     
   
   @interface QNPiece : NSObject
   
   //分解开始时间(音频开始时间为0), 单位毫秒
   @property (nonatomic, assign) NSInteger startTimestamp;
   //分解结束时间(音频开始时间为0), 单位毫秒
   @property (nonatomic, assign) NSInteger endTimestamp;
   //转写分解结果。
   @property (nonatomic, copy) NSString *transcribedText;
   
   @end
     
     
   @interface QNkeyWordsType : NSObject
   
   //关键词开始时间, 单位毫秒
   @property (nonatomic, assign) NSInteger startTimestamp;
   
   //关键词结束时间, 单位毫秒
   @property (nonatomic, assign) NSInteger endTimestamp;
   
   //命中的关键词KeyWords。返回不多于10个。
   @property (nonatomic, copy) NSString *keyWords;
   
   //命中的关键词KeyWords相应的分数。分数越高表示和关键词越相似，对应kws中的分数。
   @property (nonatomic, assign) CGFloat keyWordsScore;
   
   @end
   ```

   

## 7.2 使用样例

```objc
QNSpeakToTextParams *params = [[QNSpeakToTextParams alloc]init];
params.model_type = 1;
params.key_words = @"你好";
    
[[QNSpeakToTextDetect shareManager] startDetectWithTrack:self.audioTrack params:params complete:^(QNSpeakToTextResult * _Nonnull result) {
   // 识别结果显示
   if (result.bestTranscription && result.bestTranscription.transcribedText && result.bestTranscription.transcribedText.length > 0) {
       self.textView.text = result.bestTranscription.transcribedText;
   }
} failure:^(NSError *error) {
   // 识别失败处理
}];
```



# 8 身份证识别

## 8.1 API 参考

#### QNAIIDCardDetect 接口

```objc
@interface QNAIIDCardDetect : NSObject

+ (instancetype)shareManager;
/// 开始进行身份证识别
/// @param params 识别请求参数
/// @param complete 成功回调
/// @param failure 失败回调
- (void)startDetectWithVideoTrack:(QNTrack *)track params:(QNAIIDCardDetectParams *)params complete:(void (^)(QNAIIDCardResult *result))complete failure:(nonnull void (^)(NSError * _Nonnull error))failure;

@end
```



#### 识别参数 QNAIIDCardDetectParams

```objc
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
```



#### 返回结果

```objc
@interface QNAIIDCardResult : NSObject

@property (nonatomic, assign) NSInteger errorcode;

@property (nonatomic, copy) NSString *errormsg;
//身份证文字识别结果
@property (nonatomic, strong) QNAIIDCardOCRResult *ocr_result;
//图片识别结果
@property (nonatomic, strong) QNAIIDCardImageResult *image_result;

@end
  
@interface QNAIIDCardImageResult : NSObject
// 框坐标，格式为 [[x0, y0], [x1, y1], [x2, y2], [x3, y3]]
@property (nonatomic, strong) NSArray *idcard_bbox;

@end 
  
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
```



## 8.2 使用样例

```objc
QNAIIDCardDetectParams *params = [[QNAIIDCardDetectParams alloc]init];
params.ref_side = @"F";
params.enable_border_check = YES;
    
[[QNAIIDCardDetect shareManager] startDetectWithVideoTrack:self.cameraTrack params:params complete:^(QNAIIDCardResult * _Nonnull result) {
    if (result.errorcode != 0) {
        // 服务端返回错误处理
        return;
    }
        
    // 识别结果处理
        
} failure:^(NSError * _Nonnull error) {
    //请求服务端接口失败
}];
```



# 9 权威人脸对比

## 9.1 API 参考

#### QNAuthoritativeFaceComparer 接口

```objc
@interface QNAuthoritativeFaceComparer : NSObject

+ (instancetype)shareManager;

- (void)startDetectWithVideoTrack:(QNTrack *)track params:(QNAuthoritativeFaceParams *)params complete:(void (^)(QNAuthoritativeFaceResult *result))complete failure:(nonnull void (^)(NSError * _Nonnull error))failure;

@end
```



#### 对比参数 QNAuthoritativeFaceParams

```objc
@interface QNAuthoritativeFaceParams : NSObject
// 真实姓名
@property (nonatomic, copy) NSString *realname;
// 身份证号
@property (nonatomic, copy) NSString *idcard;

@end

```



#### 对比结果 QNAuthoritativeFaceResult

```objc
@interface QNAuthoritativeFaceResult : NSObject

@property (nonatomic, assign) NSInteger errorcode;

@property (nonatomic, copy) NSString *errormsg;

// 相似度
@property (nonatomic, assign) double similarity;

// 是否比对通过 true 通过；false 不通过
@property (nonatomic, assign) BOOL *pass;


@end
```



## 9.2 使用样例

```objc
QNAuthoritativeFaceParams *params = [QNAuthoritativeFaceParams new];
params.idcard = @"123456788999";
params.realname = @"张三";
        
[[QNAuthoritativeFaceComparer shareManager] startDetectWithVideoTrack:weakSelf.cameraTrack params:params complete:^(QNAuthoritativeFaceResult * _Nonnull result) {
    if (result.errorcode != 0) {
        // 服务端返回错误码处理
        return;
    }
            
    // 比对结果处理
} failure:^(NSError * _Nonnull error) {
    // 请求服务端接口失败
}];
```





# 10 权威动作活体检测

权威动作活体检测，相当于动作活体检测 + 权威人脸对比。

## 10.1 API 参考

#### QNAuthorityActionFaceComparer 接口

```objc
@interface QNAuthorityActionFaceComparer : NSObject

+ (instancetype)shareManager;

// 获取活体检测校验码
- (void)getFaceActliveSession:(QNActiveSessionRequest *)request
                     complete:(void (^)(QNActiveSessionResponse *response))complete
                      failure:(void (^)(NSError * _Nonnull))failure;

// 开始活体检测流录制，建议录制时间 1~10秒后执行 commit
- (void)startDetectWithTrack:(QNTrack *)track;


// 进行人脸检测
- (void)commitWithDetectParam:(QNActionLiveDetectParam *)detectParam
                       authParam:(QNAuthoritativeFaceParams *)authParam
               complete:(void (^)(QNActionLiveDetectResponse *detectResponse, QNAuthoritativeFaceResult *authResponse))complete
                failure:(nonnull void (^)(NSError * _Nonnull error))failure;


- (void)cancel;
```



#### 检验码参数 QNActiveSessionRequest

* 参考 5.1.1

#### 检验码结果 QNActiveSessionResponse

* 参考 5.1.1

#### 活体检测参数 QNActionLiveDetectParam

* 参考 5.1.2

#### 活体检测返回参数 QNActionLiveDetectResponse

* 参考 5.1.2

#### 权威人脸对比参数 QNAuthoritativeFaceParams

* 参考 9.1

#### 权威人脸对比结果 QNAuthoritativeFaceResult

* 参考9.2

  

## 10.2 使用样例

```objc
    // 1. 请求检验码
    QNActiveSessionRequest *sessionRequest = [[QNActiveSessionRequest alloc] init];
    [[QNAuthorityActionFaceComparer shareManager] getFaceActliveSession:sessionRequest complete:^(QNActiveSessionResponse * _Nonnull response) {
         if (response.errorCode != 0 || !response.result) {
            // 服务端返回失败
            return;
        }
        
        // 2.1 根据校验码动作列表，提示用户。建议一个动作停顿 2~3 秒。
        NSArray<NSNumber *> *actions = [response.result actions];
        
        // 2.2 同时开始录制视频
        [[QNAuthorityActionFaceComparer shareManager] startDetectWithTrack:self.cameraTrack];
        
        // 3. 构建参数，开始检测
        QNAuthoritativeFaceParams *params = [QNAuthoritativeFaceParams new];
        params.idcard = IDNum;
        params.realname = name;
            
        QNActionLiveDetectParam *detectParam = [[QNActionLiveDetectParam alloc] init];
        detectParam.sessionID = response.result.sessionID;
        detectParam.faceField = @"spoofing,quality";
            
        [[QNAuthorityActionFaceComparer shareManager] commitWithDetectParam:detectParam authParam:authParam complete:^(QNActionLiveDetectResponse * _Nonnull detectResponse, QNAuthoritativeFaceResult * _Nonnull authResponse) {
        // 处理活体检测结果，与权威人脸对比结果。
               
        } failure:^(NSError * _Nonnull error) {
            // 请求服务端接口失败处理
        }];
    } failure:^(NSError * _Nonnull error) {
        // 请求服务端接口失败
    }];
```





# 错误码

```c
业务错误码	信息

//通用:
0	成功
1000	未知异常
1001	音频/视频轨道没有数据返回
1002	音频/视频数据异常

//语音转文字:
2000	网络异常连接中断

//身份证识别:
53090001	请求解析失败
53090002	图片解码错误
53090003	OCR 内部错误
53090004	无法识别的身份证(非中国身份证等)
53090005	参数错误
55060030	鉴权失败
53091001	黑白复印件
53091003	无法检测到人脸
53091004	证件信息缺失或错误
53091005	证件过期
53091006	身份证不完整

//人脸检测:
55060001	请求字段有非法传输
55060002	图片解码失败
55060006	人脸特征提取失败
55060018	人脸配准失败
55060019	人脸检测图片 Base64 解码失败
55060033	人脸图片无效

//人脸对比:
55060001	请求字段有非法传输
55060002	图片解码失败
55060028	人脸比对图片 A Base64 解码失败
55060029	人脸比对图片 B Base64 解码失败
55060040	图片A人脸检测失败
55060041	图片B人脸检测失败

// 动作活体检测:
55060001	请求字段有非法传输
55060002	图片解码失败
55060012	点头动作检测失败
55060013	摇头动作检测失败
55060014	眨眼动作检测失败
55060015	张嘴动作检测失败
55060016	不是活体
55060024	视频帧率过低
55060016	动作类型无效

//光线活体
55060001    请求字段有非法传输
55060002	图片解码失败
55060009	视频无效
55060011	视频中人脸检测失败
55060016	不是活体

//文转音
100        请求参数缺失
101        请求参数不合法，⽐如合成⽂本过⻓
102        服务不可⽤
103        语⾳合成错误

//权威人脸
55060001	ERROR_PARAMETER_INVALID	请求字段有非法传输
55060004	FACE_DETECT_FAILED	高清照人脸检测失败
55060006	FEATURE_EXTRACT_FAILED	人脸特征提取失败
55060019	IMAGE_BASE64_DECODE_FAILED	人脸检测图片 Base64 解码失败
55060029	FACE_IDENTIFY_FAILED	人脸鉴别失败
55060044	REALNAME_FORMAT_ERROR	姓名格式不正确
55060045	IDCARD_NUMBER_ERROR	身份证号码有误
55060046	PHOTO_SIZE_NOT_SUITABLE	照片大小不在1kb-30kb的范围内
55060047	AUTH_INFORMATION_NOT_EXISTED	认证信息不存在
55060048	IDCARD_PHOTO_NOT_EXISTED	证件照不存在
55060049	PHOTO_NOT_ACCEPTED	照片质量检验不合格
55060050	PHOTO_MULTIFACE_DETECTED	照片出现多张人脸
```
