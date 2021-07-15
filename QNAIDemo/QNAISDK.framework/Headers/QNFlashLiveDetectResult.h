//
//  QNFlashLiveDetectResult.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNFlashLiveDetectResult : NSObject

@property (nonatomic, copy) NSString *session_id;
//活体分数 [0,100]
@property (nonatomic, assign) CGFloat score;
//视频中通过的人脸帧数
@property (nonatomic, assign) NSInteger pass_num;
//视频中检测到的人脸帧数
@property (nonatomic, assign) NSInteger face_num;

@property (nonatomic, assign) NSInteger errorcode;

@property (nonatomic, copy) NSString *errormsg;

@end

NS_ASSUME_NONNULL_END
