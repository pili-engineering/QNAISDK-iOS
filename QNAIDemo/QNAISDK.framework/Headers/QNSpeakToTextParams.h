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
/**
     * 提供热词，格式为: hot_words=热词1,因子1;热词2,因子2，每个热词由热词本身和方法因子以英文逗号隔开，不同热词通过;隔开，最多100个热词，每个热词40字节以内。由于潜在的http服务对url大小的限制，以实际支持的热词个数为准
     * 因子范围[-10,10], 正数代表权重权重越高，权重越高越容易识别成这个词，建议设置1 ，负数代表不想识别
     */
@property (nonatomic,copy) NSString *hot_words;

@end

NS_ASSUME_NONNULL_END
