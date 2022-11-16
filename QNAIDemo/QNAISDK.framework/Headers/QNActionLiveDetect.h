//
//  QNActionLiveDetect.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>
#import "QNActionLiveDetectResponse.h"



NS_ASSUME_NONNULL_BEGIN

@class QNTrack;

//动作活体检测
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

NS_ASSUME_NONNULL_END
