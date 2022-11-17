//
//  QNTextToSpeakResult.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/6.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


@interface QNAudioResult : NSObject

// 语音文件URL
@property (nonatomic, copy) NSString *audioUrl;

@end

@interface QNTextToSpeakResult : NSObject

// 错误码
@property (nonatomic, assign) NSInteger errorCode;
// 错误提示
@property (nonatomic, copy) NSString *errorMsg;

@property (nonatomic, strong) QNAudioResult *result;

@end

NS_ASSUME_NONNULL_END
