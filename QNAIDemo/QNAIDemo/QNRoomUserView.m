//
//  QNRoomUserView.m
//  QNRTCLiveDemo
//
//  Created by 冯文秀 on 2020/9/8.
//  Copyright © 2020 冯文秀. All rights reserved.
//

#import "QNRoomUserView.h"
#import <Masonry/Masonry.h>
#import <YYCategories/YYCategories.h>

@interface QNRoomUserView()

@property (nonatomic, strong) UILabel *nameLabel;
@property (nonatomic, strong, readwrite) QNVideoView *cameraView;
@property (nonatomic, strong) UIImageView *avatarImageView;

@end

@implementation QNRoomUserView

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        
//        self.backgroundColor = [UIColor colorWithRed:random()%200/255.0 green:random()%200/255.0 blue:random()%100/255.0 alpha:1];
        
        _traks = [[NSMutableArray alloc] init];
        
//        _nameLabel.hidden = YES;
        
        _cameraView = [[QNVideoView alloc] init];
//        _cameraView.hidden = YES;
//        [self insertSubview:_cameraView atIndex:0];
        [self addSubview:_cameraView];
        
        [_cameraView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        _avatarImageView = [[UIImageView alloc]initWithFrame:CGRectMake(0, 0, kScreenWidth, kScreenHeight)];
        [self addSubview:_avatarImageView];
        _avatarImageView.hidden = YES;
        [self bringSubviewToFront:_avatarImageView];
        
        UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(changeSize)];
        tap.numberOfTapsRequired = 2;
        self.userInteractionEnabled = YES;
        [self addGestureRecognizer:tap];
    }
    return self;
}

- (void)changeSize {
    if (self.changeSizeBlock) {
        self.changeSizeBlock();
    }
}

- (void)setUserId:(NSString *)userId {
    _userId = userId;
}

- (void)setAvatar:(NSString *)avatar {
    _avatar = avatar;
}

- (void)setShowImageView:(BOOL)showImageView {
    _showImageView = showImageView;
    self.avatarImageView.hidden = !showImageView;
}

- (void)setShowNameLabel:(BOOL)showNameLabel {
    _showNameLabel = showNameLabel;
    self.nameLabel.hidden = !showNameLabel;
}

- (void)setUserName:(NSString *)userName {
    _userName = userName;
    self.nameLabel.text = _userName;
//    self.nameLabel.hidden = NO;
}

- (void)showCameraView {
    dispatch_async(dispatch_get_main_queue(), ^{
        self.cameraView.hidden = NO;
        [self.cameraView mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(self);
        }];
        
        [UIView animateWithDuration:.25 animations:^{
            [self layoutIfNeeded];
        }];
    });
}

- (QNTrack *)trackInfoWithTrackId:(NSString *)trackId {
    for (QNTrack *trackInfo in self.traks) {
        if ([trackInfo.trackID isEqualToString:trackId]) {
            return trackInfo;
        }
    }
    return nil;
}

- (UILabel *)nameLabel {
    if (!_nameLabel) {
        _nameLabel = [[UILabel alloc] initWithFrame:CGRectZero];
        _nameLabel.numberOfLines = 0;
        _nameLabel.textAlignment = NSTextAlignmentCenter;
        _nameLabel.adjustsFontSizeToFitWidth = YES;
        _nameLabel.textColor = [UIColor whiteColor];
        _nameLabel.font = [UIFont systemFontOfSize:11];
        _nameLabel.backgroundColor = [[UIColor colorWithHexString:@"000000"]colorWithAlphaComponent:0.5];
//        _nameLabel.hidden = YES;

        [self addSubview:_nameLabel];
        [self bringSubviewToFront:_nameLabel];
        
        [_nameLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.bottom.left.right.mas_equalTo(self);
            make.height.mas_equalTo(20);
        }];
    }
    return _nameLabel;
}

@end
