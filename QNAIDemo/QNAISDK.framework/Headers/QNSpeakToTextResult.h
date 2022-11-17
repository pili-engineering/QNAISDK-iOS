//
//  QNSpeakToTextResult.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/6.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN


@interface QNkeyWordsType : NSObject

//关键词开始时间, 单位毫秒
@property (nonatomic, assign) NSInteger startTimestamp;

//关键词结束时间, 单位毫秒
@property (nonatomic, assign) NSInteger endTimestamp;

//命中的关键词KeyWords。返回不多于10个。
@property (nonatomic, copy) NSString *keyWords;

//命中的关键词KeyWords相应的分数。分数越高表示和关键词越相似，对应kws中的分数。
@property (nonatomic, assign) CGFloat keyWordsScore;


@end

@interface QNPiece : NSObject

//分解开始时间(音频开始时间为0), 单位毫秒
@property (nonatomic, assign) NSInteger startTimestamp;
//分解结束时间(音频开始时间为0), 单位毫秒
@property (nonatomic, assign) NSInteger endTimestamp;
//转写分解结果。
@property (nonatomic, copy) NSString *transcribedText;

@end

@interface QNBestTranscription : NSObject

//句子的开始时间, 单位毫秒
@property (nonatomic, assign) NSInteger beginTimestamp;
//句子的结束时间, 单位毫秒
@property (nonatomic, assign) NSInteger endTimestamp;
//转写结果
@property (nonatomic, copy) NSString *transcribedText;
//转写结果中包含KeyWords内容
@property (nonatomic, strong) NSArray<QNkeyWordsType *> *keyWordsType;
//转写结果的分解（只对final状态结果有效，返回每个字及标点的详细信息）
@property (nonatomic, strong) NSArray<QNPiece *> *piece;

@end

@interface QNSpeakToTextResult : NSObject

//此识别结果是否为第一片
@property (nonatomic, assign) BOOL isBegin;

//此识别结果是否为最终结果
@property (nonatomic, assign) BOOL isFinal;

//最好的转写候选
@property (nonatomic, strong) QNBestTranscription *bestTranscription;

@end

NS_ASSUME_NONNULL_END
