//
//  QNFaceCompareResult.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNFaceCompareResult : NSObject

@property (nonatomic, copy) NSString *session_id;
//两个 face 的相似度, 取值范围为[0,100]
@property (nonatomic, assign) CGFloat similarity;

@property (nonatomic, assign) NSInteger errorcode;

@property (nonatomic, copy) NSString *errormsg;

@end

NS_ASSUME_NONNULL_END
