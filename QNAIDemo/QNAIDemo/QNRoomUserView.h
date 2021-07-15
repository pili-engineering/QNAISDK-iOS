//
//  QNRoomUserView.h
//  QNRTCLiveDemo
//
//  Created by 冯文秀 on 2020/9/8.
//  Copyright © 2020 冯文秀. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QNRTCKit/QNRTCKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface QNRoomUserView : UIView

@property (nonatomic, strong) NSString *trackId;
@property (nonatomic, strong) NSString *userId;
@property (nonatomic, strong) NSString *userName;
@property (nonatomic, strong) NSString *avatar;
@property (nonatomic, assign) BOOL showImageView;//是否显示头像
@property (nonatomic, assign) BOOL showNameLabel;//是否显示名称
@property (nonatomic, strong) NSMutableArray *traks;
@property (nonatomic, copy) void (^changeSizeBlock)(void);

@property (nonatomic, readonly) QNVideoView *cameraView;

- (QNTrack *)trackInfoWithTrackId:(NSString *)trackId;
- (void)showCameraView;

@end

NS_ASSUME_NONNULL_END
