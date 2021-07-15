//
//  QNTextToSpeakDetect.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/6.
//

#import <Foundation/Foundation.h>
#import "QNTextToSpeakParams.h"
#import "QNTextToSpeakResult.h"

@class QNTrack;

NS_ASSUME_NONNULL_BEGIN

@interface QNTextToSpeakDetect : NSObject

/// 文字转语音
/// @param params 请求参数
/// @param complete 成功回调
/// @param failure 失败回调
+ (void)startTextToSpeakWithParams:(QNTextToSpeakParams *)params complete:(void (^)(QNTextToSpeakResult *result))complete failure:(nonnull void (^)(NSError * _Nonnull error))failure;

@end

NS_ASSUME_NONNULL_END
