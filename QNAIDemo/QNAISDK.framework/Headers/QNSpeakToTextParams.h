//
//  QNSpeakToTextParams.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/6.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNSpeakToTextParams : NSObject

// 识别语言，中文: 1, 英文: 2, 中英混合: 0; 默认 1
@property (nonatomic,assign) NSInteger model_type;

// 识别关键字; 相同读音时优先识别为关键字。每个词 2-4 个字, 不同词用 `,` 分割
@property (nonatomic,copy) NSString *key_words;


- (instancetype)init;


@end

NS_ASSUME_NONNULL_END
