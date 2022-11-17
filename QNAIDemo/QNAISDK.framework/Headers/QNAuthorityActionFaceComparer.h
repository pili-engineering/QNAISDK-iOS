//
//  QNAuthorityActionFaceComparer.h
//  QNAISDK
//
//  Created by 郭茜 on 2022/1/14.
//

#import <Foundation/Foundation.h>
#import "QNActionLiveDetectResponse.h"

NS_ASSUME_NONNULL_BEGIN

@class QNTrack,QNAuthoritativeFaceParams,QNAuthoritativeFaceResult;

//权威动作活体检测
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

@end

NS_ASSUME_NONNULL_END
