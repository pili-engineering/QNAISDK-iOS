//
//  QNFaceCompareResult.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNFaceToken : NSObject

//人脸的唯一标志
@property (nonatomic, copy) NSString *faceToken;

@end

@interface QNFaceCompareResult : NSObject

//人脸相似度得分，推荐阈值80分
@property (nonatomic, assign) double score;

//人脸信息列表
@property (nonatomic, strong) NSArray<QNFaceToken *> *faceList;

@end

@interface QNFaceCompareResponse : NSObject

// 请求返回码
@property (nonatomic, assign) NSInteger errorCode;

// 提示信息
@property (nonatomic, copy) NSString *errorMsg;

// 请求日志ID
@property (nonatomic, assign) NSInteger logID;

// 请求结果
@property (nonatomic, strong) QNFaceCompareResult *result;

@end

NS_ASSUME_NONNULL_END
