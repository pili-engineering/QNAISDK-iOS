//
//  QNSpeakToTextResult.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/6.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN

@interface QNWordsModel : NSObject
//词语本身，包括标点符号
@property (nonatomic,copy) NSString *word;
//该词语相对当前分段的起始时间, 毫秒
@property (nonatomic,assign) CGFloat seg_start;
//该词语相对当前分段的终止时间, 毫秒
@property (nonatomic,assign) CGFloat seg_end;
//该词语相对整个数据流的起始时间, 毫秒
@property (nonatomic,assign) CGFloat voice_start;
//该词语相对整个数据流的终止时间, 毫秒
@property (nonatomic,assign) CGFloat voice_end;

@end

@interface QNSpeakToTextResult : NSObject
//服务端生成的uuid
@property (nonatomic,copy) NSString *uuid;
//是否是websocket最后一条数据,0:非最后一条数据,1: 最后一条数据
@property (nonatomic,assign) NSInteger ended;
//分片结束,当前消息的transcript为该片段最终结果，否则为partial结果
@property (nonatomic,assign) NSInteger isFinal;
//语音的文本, 如果final=0, 则为partinal结果
@property (nonatomic,copy) NSString *transcript;
//该文本所在的切片的起点(包含), 否则为-1
@property (nonatomic,assign) NSInteger start_seq;
//为该文本所在的切片的终点(包含)，否则为-1
@property (nonatomic,assign) NSInteger end_seq;
//该片段的起始时间，毫秒
@property (nonatomic,assign) CGFloat start_time;
//该片段的终止时间，毫秒
@property (nonatomic,assign) CGFloat end_time;
//是否分段开始: 1:是; 0:不是。 一般分段后返回
@property (nonatomic,assign) NSInteger seg_begin;
//partial结果文本, 开启needpartial后返回
@property (nonatomic,copy) NSString *partial_transcript;
//是否是vad分段开始说话的开始1:是分段开始说话; 0:不是。
@property (nonatomic,assign) NSInteger spk_begin;
//当前返回是第几个vad分段上， 从0开始
@property (nonatomic,assign) NSInteger seg_index;
//是否长时间静音，0:否;1:是
@property (nonatomic,assign) NSInteger long_sil;
//返回词语的对齐信息, 参数need_words=1时返回
@property (nonatomic,strong) NSArray<QNWordsModel *> *words;

@end

NS_ASSUME_NONNULL_END
