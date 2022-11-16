//
//  QNAuthorityActionFaceComparer.h
//  QNAISDK
//
//  Created by 郭茜 on 2022/1/14.
//

#import <Foundation/Foundation.h>
#import "QNActionLiveDetectResponse.h"

typedef enum{
    QNAuthorityActionFaceBlink, //眨眼
    QNAuthorityActionFaceMouth,//张嘴
    QNAuthorityActionFaceNode,//点头
    QNAuthorityActionFaceShake,//摇头
}QNAuthorityActionFaceType;

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


//// 开始权威动作活体检测
//- (void)startDetectWithTrack:(QNTrack *)track actionTypes:(NSArray*)actionTypes params:(QNAuthoritativeFaceParams *)params;
//
//- (void)detectComplete:(void (^)(QNActionLiveDetectResponse *result,QNAuthoritativeFaceResult *authoritativeResult))complete failure:(nonnull void (^)(NSError * _Nonnull error))failure;

- (void)cancel;

@end

NS_ASSUME_NONNULL_END
