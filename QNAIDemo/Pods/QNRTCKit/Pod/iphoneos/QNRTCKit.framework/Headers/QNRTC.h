//
//  QNRTC.h
//  QNRTCKit
//
//  Created by 何云旗 on 2021/6/18.
//  Copyright © 2021 Pili Engineering, Qiniu Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "QNTypeDefines.h"
#import "QNTrack.h"
#import "QNRTCClient.h"
#import "QNMicrophoneAudioTrackConfig.h"
#import "QNCustomAudioTrackConfig.h"
#import "QNCameraVideoTrackConfig.h"
#import "QNScreenVideoTrackConfig.h"
#import "QNCustomVideoTrackConfig.h"

@class QNRTC;
@class QNRTCConfiguration;

NS_ASSUME_NONNULL_BEGIN

@interface QNRTC : NSObject

/*!
 * @abstract 用 configuration 配置 QNRTC。
 *
 * @param configuration QNRTC 的配置。
 *
 * @since v4.0.0
 */
+ (void)configRTC:(QNRTCConfiguration *)configuration;

+ (void)deinit;

/*!
 * @abstract 创建 QNRTCClient。
 *
 * @since v4.0.0
 */
+ (QNRTCClient *)createRTCClient;

/*!
 * @abstract 创建一路以麦克风采集为数据源的音频 track，默认码率为 64kbps
 *
 * @since v4.0.0
 */
+ (QNTrack *)createMicrophoneAudioTrack;

/*!
 * @abstract 创建一路以麦克风采集为数据源的音频 track
 *
 * @param configuration 用于初始化麦克风采集的音频 track 的配置。
 *
 * @since v4.0.0
 */
+ (QNTrack *)createMicrophoneAudioTrackWithConfig:(QNMicrophoneAudioTrackConfig *)configuration;

/*!
 * @abstract 创建一路以外部数据导入为数据源的音频 track，默认码率为 64kbps
 *
 * @since v4.0.0
 */
+ (QNTrack *)createCustomAudioTrack;

/*!
 * @abstract 创建一路以外部数据导入为数据源的音频 track
 *
 * @param configuration 用于初始化外部数据导入的音频 track 的配置。
 *
 * @since v4.0.0
 */
+ (QNTrack *)createCustomAudioTrackWithConfig:(QNCustomAudioTrackConfig *)configuration;

/*!
 * @abstract 创建一路以摄像头采集为数据源的视频 track，默认码率为 600 kbps
 *
 * @since v4.0.0
 */
+ (QNTrack *)createCameraVideoTrack;

/*!
 * @abstract 创建一路以摄像头采集为数据源的视频 track
 *
 * @param configuration 用于初始化摄像头采集的视频 track 的配置。
 *
 * @since v4.0.0
 */
+ (QNTrack *)createCameraVideoTrackWithConfig:(QNCameraVideoTrackConfig *)configuration;

/*!
 * @abstract 创建一路以屏幕录制采集为数据源的视频 track，默认码率为 600 kbps
 *
 * @since v4.0.0
 */
+ (QNTrack *)createScreenVideoTrack;

/*!
 * @abstract 创建一路以屏幕录制采集为数据源的视频 track。
 *
 * @param configuration 用于初始化屏幕录制采集的视频 track 的配置。
 *
 * @since v4.0.0
 */
+ (QNTrack *)createScreenVideoTrackWithConfig:(QNScreenVideoTrackConfig *)configuration;

/*!
 * @abstract 创建一路以外部视频数据导入为数据源的视频 track，默认码率为 600 kbps
 *
 * @since v4.0.0
 */
+ (QNTrack *)createCustomVideoTrack;

/*!
 * @abstract 创建一路以外部视频数据导入为数据源的视频 track
 *
 * @param configuration 用于初始化外部视频数据导入的视频 track 的配置。
 *
 * @since v4.0.0
 */
+ (QNTrack *)createcreateCustomVideoTrackWithConfig:(QNCustomVideoTrackConfig *)configuration;


@end

#pragma mark - Category (Device)

/*!
 * @category QNRTC(Device)
 *
 * @discussion 与设备相关的接口
 *
 * @since v4.0.0
 *
 */
@interface QNRTC (Device)

/*!
 * @abstract 摄像头的预览视图，调用 createCameraVideoTrack 后才会有画面。
 *
 * @since v4.0.0
 */
+ (UIView *)getCameraPreviewView;

/*!
 * @abstract 设置 cameraPreviewView  中视频的填充方式，默认使用 QNVideoFillModePreserveAspectRatioAndFill。
 *
 * @since v4.0.0
 */
+ (void)setCameraVideoFillMode:(QNVideoFillModeType)fillMode;

/*!
 * @abstract 获取 previewView 中视频的填充方式，默认使用 QNVideoFillModePreserveAspectRatioAndFill。
 *
 * @since v4.0.0
 */
+ (QNVideoFillModeType)getCameraVideoFillMode;

/*!
 * @abstract 设置摄像头的位置，默认为 AVCaptureDevicePositionFront。
 *
 * @since v4.0.0
 */
+ (void)setCaptureDevicePosition:(AVCaptureDevicePosition)captureDevicePosition;

/*!
 * @abstract 获取摄像头当前位置，默认为 AVCaptureDevicePositionFront。
 *
 * @since v4.0.0
 */
+ (AVCaptureDevicePosition)getCaptureDevicePosition;

/*!
 * @abstract 开启 camera 时的采集摄像头的旋转方向，默认为 AVCaptureVideoOrientationPortrait。
 *
 * @since v4.0.0
 */
+ (void)setCameraVideoOrientation:(AVCaptureVideoOrientation)videoOrientation;

/*!
 * @abstract 获取开启 camera 时的采集摄像头的旋转方向，默认为 AVCaptureVideoOrientationPortrait。
 *
 * @since v4.0.0
 */
+ (AVCaptureVideoOrientation)getCameraVideoOrientation;

/*!
 * @abstract 是否开启手电筒，默认为 NO。
 *
 * @since v4.0.0
 */
+ (void)setTorchOn:(BOOL)torchOn;

/*!
 * @abstract 获取手电筒开关状态，默认为 NO。
 *
 * @since v4.0.0
 */
+ (BOOL)isTorchOn;

/*!
 * @abstract 设备支持的 formats。
 *
 * @since v4.0.0
 */
+ (NSArray<AVCaptureDeviceFormat *> *)getSupportVideoFormats;

/*!
 * @abstract 设置摄像头设备当前的 format。
 *
 * @since v4.0.0
 */
+ (void)setCameraActiveFormat:(AVCaptureDeviceFormat *)activeFormat;

/*!
 * @abstract 获取设备当前的 format。
 *
 * @since v4.0.0
 */
+ (AVCaptureDeviceFormat *)getCameraActiveFormat;

/*!
 * @abstract 采集的视频的 sessionPreset，默认为 AVCaptureSessionPreset640x480。
 *
 * @since v4.0.0
 */
+ (void)setCameraSessionPreset:(NSString *)sessionPreset;

/*!
 * @abstract 获取当前采集的视频的 sessionPreset，默认为 AVCaptureSessionPreset640x480。
 *
 * @since v4.0.0
 */
+ (NSString *)getCameraSessionPreset;

/*!
 * @abstract 采集的视频数据的帧率，默认为 24。
 *
 * @since v4.0.0
 */
+ (void)setCameraFrameRate:(NSUInteger)frameRate;

/*!
 * @abstract 获取当前采集的视频数据的帧率，默认为 24。
 *
 * @since v4.0.0
 */
+ (NSUInteger)getCameraFrameRate;

/*!
 * @abstract 切换前后摄像头。
 *
 * @since v4.0.0
 */
+ (void)switchCamera;

/*!
 * @abstract 是否将声音从扬声器输出。
 *
 * @discussion 传入 YES 时，强制声音从扬声器输出。
 *
 * @warning 由于系统原因，在某些设备（如 iPhone XS Max、iPhone 8 Plus）上，连接 AirPods 后无法通过
 * 该接口将声音强制设为扬声器输出。如有需求，可以通过使用 AVRoutePickerView 来切换。
 *
 * @since v4.0.0
 */
+ (void)setSpeakerphoneOn:(BOOL)speakerOn;

@end

#pragma mark - Category (ScreenRecorder)

/*!
 * @category QNRTC(ScreenRecorder)
 *
 * @discussion 与录屏相关的接口
 *
 * @since v4.0.0
 */
@interface QNRTC (ScreenRecorder)

/*!
 * @abstract 判断屏幕录制功能是否可用
 *
 * @discussion 屏幕录制功能仅在 iOS 11 及以上版本可用
 *
 * @since v4.0.0
 */
+ (BOOL)isScreenRecorderAvailable;

/*!
 * @abstract 屏幕录制的帧率，默认值为 20，可设置 [10, 60] 之间的值，超出范围则不变更
 *
 * @discussion 该值仅为期望值，受 ReplayKit 的限制，在特定情况（比如画面保持不动）下，ReplayKit 可能隔几秒才会回调一帧数据。
 *
 * @since v4.0.0
 */

+ (void)setScreenRecorderFrameRate:(NSUInteger)screenRecorderFrameRate;
+ (NSUInteger)getScreenRecorderFrameRate;



@end

#pragma mark - Category (Logging)

/*!
 * @category QNRTC(Logging)
 *
 * @discussion 与日志相关的接口。
 *
 * @since v4.0.0
 */
@interface QNRTC (Logging)

/*!
* @abstract 开启文件日志
*
* @discussion 为了不错过日志，建议在 App 启动时即开启，日志文件位于 App Container/Library/Caches/Pili/Logs 目录下以 QNRTC+当前时间命名的目录内
* 注意：文件日志功能主要用于排查问题，打开文件日志功能会对性能有一定影响，上线前请记得关闭文件日志功能！
*
* @since v4.0.0
*/
+ (void)enableFileLogging;

@end

#pragma mark - Category (Info)

/*!
 * @category QNRTC(Info)
 *
 * @discussion SDK 相关信息的接口。
 *
 * @since v4.0.0
 */
@interface QNRTC (Info)

/*!
 * @abstract 获取 SDK 的版本信息。
 *
 * @since v4.0.0
 */
+ (NSString *)versionInfo;

@end


NS_ASSUME_NONNULL_END
