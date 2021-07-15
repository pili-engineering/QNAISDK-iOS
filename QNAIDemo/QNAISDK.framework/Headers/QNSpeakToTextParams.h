//
//  QNSpeakToTextParams.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/6.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNSpeakToTextParams : NSObject

//是否在text为空的时候返回final信息, 1->强制返回;0->不强制返回。
@property (nonatomic,assign) NSInteger force_final;
//最长静音间隔，单位秒 默认10秒
@property (nonatomic,assign) NSInteger maxsil;
// 0->cn; 默认0
@property (nonatomic,assign) NSInteger model_type;
// 是否返回partial文本，1->返回，0-> 不返回
@property (nonatomic,assign) NSInteger need_partial;
// 是否需要vad;0->关闭;1->开启; 
@property (nonatomic,assign) NSInteger needvad;
//采样率 默认为48000
@property (nonatomic,assign) NSInteger voice_sample;

@end

NS_ASSUME_NONNULL_END
