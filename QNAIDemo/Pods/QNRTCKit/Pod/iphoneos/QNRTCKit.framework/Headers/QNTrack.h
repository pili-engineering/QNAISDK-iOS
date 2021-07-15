//
//  QNTrack.h
//  QNRTCKit
//
//  Created by lawder on 2018/9/3.
//  Copyright © 2018年 Pili Engineering, Qiniu Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QNTypeDefines.h"
#import "QNTrackSubConfiguration.h"
#import "QNVideoView.h"

NS_ASSUME_NONNULL_BEGIN
@class QNTrack;
@protocol QNTrackAudioDataDelegate <NSObject>

@optional
/*!
 * @abstract 音频 Track 数据回调。
 *
 * @since v4.0.0
 */
- (void)track:(QNTrack *)track didGetAudioBuffer:(AudioBuffer *)audioBuffer bitsPerSample:(NSUInteger)bitsPerSample sampleRate:(NSUInteger)sampleRate;

@end

@protocol QNTrackVideoDataDelegate <NSObject>

@optional
/*!
 * @abstract 视频 Track 数据回调。
 *
 * @since v4.0.0
 */
- (void)track:(QNTrack *)track didGetPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@optional

@end


/*!
 * @abstract 用来描述一路 Track 的相关信息
 *
 * @discussion 主要用于发布/订阅时传入 Track 相关的信息，或者远端 Track 状态变更时 SDK 回调给 App Track 相关的信息。
 *
 * @since v2.0.0
 */
@interface QNTrack : NSObject
/*!
 * @abstract 音频 Track 回调代理。
 *
 * @since v4.0.0
 */
@property (nonatomic, weak) id<QNTrackAudioDataDelegate> audioDelegate;
/*!
 * @abstract 视频 Track 回调代理。
 *
 * @since v4.0.0
 */
@property (nonatomic, weak) id<QNTrackVideoDataDelegate> videoDelegate;

/*!
 * @abstract 一路 Track 在 Server 端的唯一标识。
 *
 * @discussion 发布成功时由 SDK 自动生成，订阅/Mute 等操作依据此 trackId 来确定相应的 Track。
 *
 * @since v2.0.0
 */
@property (nonatomic, strong) NSString *trackID;

/*!
 * @abstract 标识该路 Track 是音频还是视频。
 *
 * @discussion 发布时由 SDK 根据 sourceType 确定。
 *
 * @see QNTrackKind，QNRTCSourceType
 *
 * @since v2.0.0
 */
@property (nonatomic, readonly) QNTrackKind kind;

/*!
 * @abstract 标识该路 Track 是否为 master
 *
 * @discussion 该属性默认为 NO。该属性为 YES 时该 Track 可以被 v1.x 版本的 SDK 识别和订阅。
 * 对于音频/视频 Track，分别最多只能有一路为 master。
 *
 * @since v2.0.0
 */
@property (nonatomic, assign, getter=isMaster) BOOL master;

/*!
 * @abstract 标识 Track 是否为 mute 状态
 *
 * @discussion 对于本地 Track，可以将 muted 置为 YES 同时并调用 - (void)muteTracks:(NSArray<QNTrack *> *)tracks 来 mute 本地发布的 Track
 * 对于远端的 Track，muted 属性标识该 Track 的状态。
 *
 * @since v2.0.0
 */
@property (nonatomic, assign) BOOL muted;

/*!
 * @abstract Track 的 tag，SDK 会将其透传到远端，当发布多路视频 Track 时可用 tag 来作区分。
 *
 * @since v2.0.0
 */
@property (nonatomic, strong) NSString *tag;

/*!
 * @abstract 订阅大小流的 QNTrackSubConfiguration 配置
 *
 * @since v2.5.0
 */
@property (nonatomic, strong) NSMutableArray<QNTrackSubConfiguration *> *subConfigurations;

/*!
 * @abstract 发布是否开启大小流，默认关闭
 *
 * @warning 目前版本，开启大小流将默认三路流，暂未支持自定义流数
 *
 * @since v2.5.0
 */
@property (nonatomic, assign) BOOL multiStreamEnable;

/*!
 * @abstract 是否固定分辨率
 *
 * @discussion 对于 sourceType 为 QNRTCSourceTypeScreenRecorder 的视频 Track，该选项为 YES，即会使用固定的分辨率。对于其它 sourceType，默认为 NO。
 *
 * @warning 需在该 Track 被发布前设置，否则无效。仅对视频 Track 有效，音频 Track 忽略该设置。
 *          开启大小流时，请关闭固定分辨率，否则大小流将失效。开启单路转推时，请打开固定分辨率，否则单路转推将无法保证。
 *
 * @since v2.1.1
 */
- (void)setMaintainResolutionEnabled:(BOOL)enabled;

/*!
 * @abstract 初始化指定 sourceType 的 Track, master 属性默认为 NO，若为视频 Track，默认码率为 600kbps，若为音频 Track，默认码率为 64kbps
 *
 * @discussion 视频编码尺寸根据输入的视频帧来确定
 *
 * @since v2.0.0
 */
- (instancetype)initWithSourceType:(QNRTCSourceType)sourceType;

/*!
 * @abstract 初始化指定 sourceType、master 参数的 Track, 若为视频 Track，码率为 600kbps，若为音频 Track，码率为 64kbps
 *
 * @discussion 视频编码尺寸根据输入的视频帧来确定
 *
 * @since v2.0.0
 */
- (instancetype)initWithSourceType:(QNRTCSourceType)sourceType master:(BOOL)master;

/*!
 * @abstract 初始化指定 sourceType、master、bitrate (单位 kbps) 参数的 Track
 *
 * @discussion 视频编码尺寸根据输入的视频帧来确定。
 *
 * @since v2.0.0
 */
- (instancetype)initWithSourceType:(QNRTCSourceType)sourceType
                            master:(BOOL)master
                           bitrate:(NSUInteger)bitrate;

/*!
 * @abstract 初始化指定 sourceType、master、videoEncodeSize 参数的 Track。
 *
 * @discussion 一般用于初始化视频 Track，默认码率为 600kbps。
 *
 * @since v2.0.0
 */
- (instancetype)initWithSourceType:(QNRTCSourceType)sourceType
                            master:(BOOL)master
                   videoEncodeSize:(CGSize)videoEncodeSize;

/*!
 * @abstract 初始化指定 sourceType、master、bitrate (单位 kbps)、videoEncodeSize 参数的 Track。
 *
 * @since v2.0.0
 */
- (instancetype)initWithSourceType:(QNRTCSourceType)sourceType
                            master:(BOOL)master
                           bitrate:(NSUInteger)bitrate
                   videoEncodeSize:(CGSize)videoEncodeSize;

/*!
 * @abstract 初始化指定 sourceType、tag、master、bitrate (单位 kbps)、videoEncodeSize 参数的 Track。
 *
 * @since v2.0.0
 */
- (instancetype)initWithSourceType:(QNRTCSourceType)sourceType
                               tag:(nullable NSString *)tag
                            master:(BOOL)master
                           bitrate:(NSUInteger)bitrate
                   videoEncodeSize:(CGSize)videoEncodeSize;

//本地 camera  使用 QNRTC 中 previewView 属性
- (void)play:(QNVideoView *)renderView;

//@abstract 设置音频 Track 播放音量。范围从 0 ~ 10，10 为最大
- (void)setVolume:(float)volume;

@end


NS_ASSUME_NONNULL_END
