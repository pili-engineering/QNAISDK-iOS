//
//  QNAuthorityActionFaceComparer.h
//  QNAISDK
//
//  Created by 郭茜 on 2022/1/14.
//

#import <Foundation/Foundation.h>
#import "QNActionLiveDetectResult.h"

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
//开始权威动作活体检测
- (void)startDetectWithTrack:(QNTrack *)track actionTypes:(NSArray*)actionTypes params:(QNAuthoritativeFaceParams *)params;

- (void)detectComplete:(void (^)(QNActionLiveDetectResult *result,QNAuthoritativeFaceResult *authoritativeResult))complete failure:(nonnull void (^)(NSError * _Nonnull error))failure;

- (void)cancel;

@end

NS_ASSUME_NONNULL_END
