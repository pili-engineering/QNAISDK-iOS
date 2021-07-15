//
//  QNTextToSpeakResult.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/6.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNTextToSpeakResult : NSObject
//语音Id
@property (nonatomic, copy) NSString *voice_id;
//错误码
@property (nonatomic, assign) NSInteger errorcode;
//错误提示
@property (nonatomic, copy) NSString *errormsg;
//语音文件base64字符串
@property (nonatomic, copy) NSString *audio;
//可播放的语音文件，AVAudioPlayer可直接播放NSData
@property (nonatomic, strong) NSData *audioData;

@end

NS_ASSUME_NONNULL_END
