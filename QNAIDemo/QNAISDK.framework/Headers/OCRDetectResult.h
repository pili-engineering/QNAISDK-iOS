//
//  OCRDetectResult.h
//  QNAISDK
//
//  Created by 郭茜 on 2022/1/14.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface OCRDataResult : NSObject

@property (nonatomic, assign) NSInteger line;

@property (nonatomic, copy) NSString *text;

@property (nonatomic, copy) NSString *score;

@property (nonatomic, strong) NSArray *bbox;


@end

@interface OCRDetectResult : NSObject

@property (nonatomic, assign) NSInteger code;

@property (nonatomic, copy) NSString *message;

@property (nonatomic, strong) NSArray<OCRDataResult *> *data;


@end

NS_ASSUME_NONNULL_END
