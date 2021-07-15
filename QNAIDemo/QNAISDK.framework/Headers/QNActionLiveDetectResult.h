//
//  QNActionLiveDetectResult.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNActionLiveBestFramesModel : NSObject
//base64 编码的二进制图片
@property (nonatomic, copy) NSString *image_b64;
//图像质量分数
@property (nonatomic, assign) NSInteger quality;

@end

@interface QNActionLiveDetectResult : NSObject

@property (nonatomic, copy) NSString *session_id;
//动作活体状态码，1 表示通过，0 表示不通过
@property (nonatomic, assign) NSInteger live_status;
//最优帧列表
@property (nonatomic, strong) NSArray <QNActionLiveBestFramesModel *> *best_frames;

@property (nonatomic, assign) NSInteger errorcode;

@property (nonatomic, copy) NSString *errormsg;

@end

NS_ASSUME_NONNULL_END
