//
//  QNRTCClient.h
//  QNRTCKit
//
//  Created by 何云旗 on 2021/6/18.
//  Copyright © 2021 Pili Engineering, Qiniu Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QNTypeDefines.h"
#import "QNTrack.h"
#import "QNRTCUser.h"

@class QNRTCClient;
NS_ASSUME_NONNULL_BEGIN

@protocol QNRTCClientDelegate <NSObject>

@optional

/*!
 * @abstract 房间状态变更的回调。
 *
 * @discussion 当状态变为 QNConnectionStateReconnecting 时，SDK 会为您自动重连，如果希望退出，直接调用 leave 即可。
 * 重连成功后的状态为 QNConnectionStateReconnected。
 *
 * @since v4.0.0
 */
- (void)RTCClient:(QNRTCClient *)client didConnectionStateChanged:(QNConnectionState)state;

/*!
 * @abstract 远端用户加入房间的回调。
 *
 * @since v4.0.0
 */
- (void)RTCClient:(QNRTCClient *)client didJoinOfUserID:(NSString *)userID userData:(NSString *)userData;

/*!
 * @abstract 远端用户离开房间的回调。
 *
 * @since v4.0.0
 */
- (void)RTCClient:(QNRTCClient *)client didLeaveOfUserID:(NSString *)userID;

/*!
 * @abstract 订阅远端用户成功的回调。
 *
 * @since v4.0.0
 */
- (void)RTCClient:(QNRTCClient *)client didSubscribeTracks:(NSArray<QNTrack *> *)tracks ofUserID:(NSString *)userID;

/*!
 * @abstract 远端用户发布音/视频的回调。
 *
 * @since v4.0.0
 */
- (void)RTCClient:(QNRTCClient *)client didUserPublishTracks:(NSArray<QNTrack *> *)tracks ofUserID:(NSString *)userID;

/*!
 * @abstract 远端用户取消发布音/视频的回调。
 *
 * @since v4.0.0
 */
- (void)RTCClient:(QNRTCClient *)client didUserUnpublishTracks:(NSArray<QNTrack *> *)tracks ofUserID:(NSString *)userID;

/*!
 * @abstract 本地用户离开房间成功的回调。
 *
 * @discussion 调用 leave 离开房间成功的回调
 *
 * @since v4.0.0
 */
- (void)RTCClient:(QNRTCClient *)client didLeaveOfSuccess:(BOOL)success;

/*!
 * @abstract   远端用户发生重连的回调。
 *
 * @since v4.0.0
*/
- (void)RTCClient:(QNRTCClient *)client didReconnectingOfUserID:(NSString *)userID;

/*!
* @abstract 远端用户重连成功的回调。
*
* @since v4.0.0
*/
- (void)RTCClient:(QNRTCClient *)client didReconnectedOfUserID:(NSString *)userID;




@end



@interface QNRTCClient : NSObject

@property (nonatomic, weak) id<QNRTCClientDelegate> delegate;

/*!
 * @abstract 远端用户列表
 *
 * @since v4.0.0
 */
@property (nonatomic, strong, readonly) NSArray<QNRTCUser *> *remoteUserList;

/*!
 * @abstract 已发布 track 列表
 *
 * @since v4.0.0
 */
@property (nonatomic, strong, readonly) NSArray<QNTrack *> *publishedTracks;

/*!
 * @abstract 加入房间。
 *
 * @since v4.0.0
 */
- (void)join:(NSString *)token completeCallback:(QNJoinResultCallback)callback;

/*!
 * @abstract 加入房间。
 *
 * @since v4.0.0
 */
- (void)join:(NSString *)token userData:(NSString *)userData completeCallback:(QNJoinResultCallback)callback;

/*!
 * @abstract 退出房间。
 *
 * @since v4.0.0
 */
- (void)leave;

/*!
 * @abstract 发布 tracks。
 *
 * @since v4.0.0
 */
-(void)publish:(NSArray<QNTrack *> *)tracks;

/*!
 * @abstract 发布 tracks。
 *
 * @since v4.0.0
 */
-(void)publish:(NSArray<QNTrack *> *)tracks completeCallback:(QNPublishResultCallback)callback;

/*!
 * @abstract 取消发布 tracks。
 *
 * @since v4.0.0
 */
- (void)unpublish:(NSArray<QNTrack *> *)tracks;

/*!
 * @abstract 订阅 tracks。
 *
 * @since v4.0.0
 */
- (void)subscribe:(NSArray<QNTrack *> *)tracks;

/*!
 * @abstract 取消订阅。
 *
 * @since v4.0.0
 */
- (void)unsubscribe:(NSArray<QNTrack *> *)tracks;

/*!
 * @abstract 获取指定用户已被自己订阅的 tracks。
 *
 * @since v4.0.0
 */
- (NSArray <QNTrack *> *)getSubscribedTracks:(NSString *)userID;

@end

NS_ASSUME_NONNULL_END
