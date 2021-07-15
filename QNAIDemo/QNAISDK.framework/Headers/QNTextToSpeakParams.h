//
//  QNTextToSpeakParams.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/6.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNTextToSpeakParams : NSObject
//需要进⾏语⾳合成的⽂本内容，最短1个字，最⻓200字
@property (nonatomic, copy) NSString *text;
//发⾳⼈id，⽤于选择不同⻛格的⼈声，⽬前默认为kefu1， 可选的包括female3，female5，female6，male1，male2， male4，kefu1，girl1
@property (nonatomic, copy) NSString *speaker;
//合成⾳频格式，⽬前默认为wav，可选的包括wav，pcm，mp3
@property (nonatomic, copy) NSString *audio_encoding;
//合成⾳频的采样率，默认为16000，可选的包括8000，16000， 24000，48000
@property (nonatomic, assign) NSInteger sample_rate;
//⾳量⼤⼩，取值范围为0~100，默认为50
@property (nonatomic, assign) NSInteger volume;
//语速，取值范围为-100~100，默认为0
@property (nonatomic, assign) NSInteger speed;

@end

NS_ASSUME_NONNULL_END
