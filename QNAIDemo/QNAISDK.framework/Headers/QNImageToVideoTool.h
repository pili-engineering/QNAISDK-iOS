//
//  QNImageToVideoTool.h
//  QNAISDK
//
//  Created by 郭茜 on 2021/7/7.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AVKit/AVKit.h>
#import <MediaPlayer/MediaPlayer.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNImageToVideoTool : NSObject


+ (UIImage *) imageFromSampleBuffer:(CMSampleBufferRef) sampleBuffer;
//对图片进行压缩
+ (UIImage*)imageWithImage:(UIImage*)image scaledToSize:(CGSize)newSize;
//CVPixelBufferRef转图片
+ (UIImage *)imageFromPixelBuffer:(CVPixelBufferRef)pixelBufferRef;
/// 视频base64编码
+ (void)videoB64StrFromImageArray:(NSArray *)imageArray complete:(void (^)(NSString *base64Str))complete ;
/// 图片转base64编码  scaleWidth 需要压缩的大小
+ (NSString *)base64StringByImage:(UIImage *)image scaleWidth:(NSInteger)scaleWidth;


@end

NS_ASSUME_NONNULL_END
