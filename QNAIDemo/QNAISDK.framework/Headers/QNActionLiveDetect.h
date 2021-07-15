//
//  QNActionLiveDetect.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>
#import "QNActionLiveDetectResult.h"

typedef enum{
    QNFaceActionTypeBlink, //眨眼
    QNFaceActionTypeMouth,//张嘴
    QNFaceActionTypeNode,//点头
    QNFaceActionTypeShake,//摇头
}QNFaceActionType;

NS_ASSUME_NONNULL_BEGIN

@class QNTrack;

//动作活体检测
@interface QNActionLiveDetect : NSObject

+ (instancetype)shareManager;
//开始动作活体检测
- (void)startDetectWithTrack:(QNTrack *)track actionTypes:(NSArray*)actionTypes;

- (void)detectComplete:(void (^)(QNActionLiveDetectResult *result))complete failure:(nonnull void (^)(NSError * _Nonnull error))failure;

- (void)cancel;

@end

NS_ASSUME_NONNULL_END
