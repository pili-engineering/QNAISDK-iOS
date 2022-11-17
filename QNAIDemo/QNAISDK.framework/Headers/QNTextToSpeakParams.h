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
@property (nonatomic, copy) NSString *content;

// TTS 发音人标识音源 id 0-6,实际可用范围根据情况, 可以不设置,默认是 0;
// 0：女声（柔和）；
// 1，女声（正式）
// 2，女生（柔和带正式）；
// 3：男声（柔和）
// 4：男声（柔和带正式）
// 5：男声（闽南话）；
// 6：女生（闽南话）。
@property (nonatomic, assign) NSInteger spkid;

/**
 * 可不填，不填时默认为 3。
 * audioType=3 返回 16K 采样率的 mp3
 * audioType=4 返回 8K 采样率的 mp3
 * audioType=5 返回 24K 采样率的 mp3
 * audioType=6 返回 48k采样率的mp3
 * audioType=7 返回 16K 采样率的 pcm 格式
 * audioType=8 返回 8K 采样率的 pcm 格式
 * audioType=9 返回 24k 采样率的pcm格式
 * audioType=10 返回 8K 采样率的 wav 格式
 * audioType=11 返回 16K 采样率的 wav 格式
 */
@property (nonatomic, assign) NSInteger audioType;

// 音量大小，取值范围为 0.75 - 1.25，默认为1
@property (nonatomic, assign) float volume;

// 语速，取值范围为 0.75 - 1.25，默认为1
@property (nonatomic, assign) float speed;

@end

NS_ASSUME_NONNULL_END
