//
//  QNSpeakToTextDetect.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/6.
//

#import <Foundation/Foundation.h>
#import "QNSpeakToTextParams.h"
#import "QNSpeakToTextResult.h"

@class QNTrack;

NS_ASSUME_NONNULL_BEGIN

@interface QNSpeakToTextDetect : NSObject

+ (instancetype)shareManager;

/// 语音转文字
/// @param track audio track
/// @param params 识别请求参数
/// @param complete 成功回调
/// @param failure 失败回调
- (void)startDetectWithTrack:(QNTrack *)track params:(QNSpeakToTextParams *)params complete:(void (^)(QNSpeakToTextResult * _Nonnull result))complete failure:(void (^)(NSError *error))failure ;

- (void)stopDetect;

@end

NS_ASSUME_NONNULL_END
