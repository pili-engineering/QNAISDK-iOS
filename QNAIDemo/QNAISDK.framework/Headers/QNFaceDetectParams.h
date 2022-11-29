//
//  QNFaceDetectParams.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 人脸检测参数
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

NS_ASSUME_NONNULL_END
