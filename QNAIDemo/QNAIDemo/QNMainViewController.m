//
//  QNMainViewController.m
//  QNIMDemo
//
//  Created by 郭茜 on 2021/6/17.
//

#import "QNMainViewController.h"
#import <QNRTCKit/QNRTCKit.h>
#import <YYCategories/YYCategories.h>
#import "MBProgressHUD+QNShow.h"
#import "QNRoomUserView.h"
#import "QNNetworkUtil.h"
#import <QNAISDK/QNAISDK.h>
#import <Masonry/Masonry.h>
#import <MediaPlayer/MediaPlayer.h>

typedef enum{
    QNAITaskType_Action, //动作活体
    QNAITaskType_AuthoritativeFaceCompare,//权威人脸对比
    QNAITaskType_AuthorityActionFaceComparer,//权威动作活体
    QNAITaskType_FaceCompare,//人脸对比
    QNAITaskType_FaceDetect,//人脸识别
    QNAITaskType_IDCardDetect,//身份证识别
    QNAITaskType_textToAudio,//文转音
    QNAITaskType_SpeakToText,//语音识别
}QNAITaskType;

@interface QNMainViewController ()<QNRTCClientDelegate,QNTrackAudioDataDelegate,QNTrackVideoDataDelegate,UIImagePickerControllerDelegate,UINavigationControllerDelegate>

@property (nonatomic, strong) QNRTCClient *rtcClient;

@property (nonatomic, strong) UIView *preview;

@property (nonatomic, strong) UIButton *commentButton;
@property (nonatomic, strong) UITextView *textView;
@property (nonatomic, strong) UIButton *endSpeakButton;
//要播放音频 player不能设置为局部变量
@property (nonatomic, strong) AVPlayer *avPlayer;

@property (nonatomic, strong) QNTrack *audioTrack;
@property (nonatomic, strong) QNTrack *cameraTrack;

@property (nonatomic, strong) UIImage *compareImage;//用来人脸对比的图片

@property (nonatomic, copy) NSString *imageBase64Str;

@property (nonatomic, assign) QNAITaskType taskType;
@property (nonatomic, copy) NSString *actionMessage;

@property (nonatomic,strong) MPMoviePlayerController *mpcontrol;


@end

@implementation QNMainViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self configureRTCEngine];
    [self setupButtons];
}

- (void)setupButtons {
    NSArray *buttons = @[
        @{@"title":@"语音转文字", @"selector":@"audioToText"},
        @{@"title":@"文字转语音", @"selector":@"textToSpeak"},
        
        @{@"title":@"人脸识别", @"selector":@"faceDetect"},
        @{@"title":@"人脸对比", @"selector":@"faceCompare"},
        
        @{@"title":@"动作活体检测", @"selector":@"actionLiveDetect"},
       
        @{@"title":@"权威人脸对比", @"selector":@"authoritativeFaceCompare"},
        @{@"title":@"权威动作活体检测", @"selector":@"authorityActionFaceComparer"},
        
        @{@"title":@"身份证识别", @"selector":@"IDCardDetect"},
    ];
    
    
    for (int i = 0; i < buttons.count; i ++) {
        UIButton *button = [[UIButton alloc] init];
        [button setTitle:buttons[i][@"title"] forState:(UIControlStateNormal)];
        button.titleLabel.font = [UIFont systemFontOfSize:14];
        [button setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        button.backgroundColor = [UIColor blackColor];
        [button addTarget:self action:NSSelectorFromString(buttons[i][@"selector"]) forControlEvents:(UIControlEventTouchUpInside)];
        [self.view addSubview:button];

        [button mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(self.view).offset(80 + 50 * i);
            make.right.equalTo(self.view).offset(-30);
            make.height.mas_equalTo(35);
        }];
    }
}

//文字转语音
- (void)textToSpeak {
    
    self.taskType = QNAITaskType_textToAudio;
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"请输入需要转换的文字" message:nil preferredStyle:UIAlertControllerStyleAlert];
    
    [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {}];
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleCancel handler:^(UIAlertAction *action) {}];
        
    UIAlertAction *otherAction = [UIAlertAction actionWithTitle:@"开始" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
                        
        QNTextToSpeakParams *params = [[QNTextToSpeakParams alloc]init];
        params.content = alertController.textFields.firstObject.text;

        
        [QNTextToSpeakDetect startTextToSpeakWithParams:params complete:^(QNTextToSpeakResult * _Nonnull result) {
            if (result.errorCode != 0) {
                NSLog(@"reqeust error %ld, msg %@", result.errorCode, result.errorMsg);
                return;
            }
            [[AVAudioSession sharedInstance] setCategory: AVAudioSessionCategoryPlayback error: nil];
            [[AVAudioSession sharedInstance] setActive: YES error: nil];
            
            NSURL *url = [NSURL URLWithString:result.result.audioUrl];
            self.avPlayer = [[AVPlayer alloc] initWithURL:url];
            [self.avPlayer play];
        } failure:^(NSError * _Nonnull error) {
            NSLog(@"request error %@", error);
        }];
        
    }];
        
    [alertController addAction:cancelAction];
    [alertController addAction:otherAction];
    [self presentViewController:alertController animated:YES completion:nil];
        
}

//语音转文字
- (void)audioToText {
    
    self.taskType = QNAITaskType_SpeakToText;

    QNSpeakToTextParams *params = [[QNSpeakToTextParams alloc]init];
    params.model_type = 1;
    params.key_words = @"你好";
    
    self.endSpeakButton.hidden = NO;
    self.textView.hidden = NO;
    self.textView.text = @"";
    
    [[QNSpeakToTextDetect shareManager] startDetectWithTrack:self.audioTrack params:params complete:^(QNSpeakToTextResult * _Nonnull result) {
        if (result.bestTranscription && result.bestTranscription.transcribedText && result.bestTranscription.transcribedText.length > 0) {
            self.textView.text = result.bestTranscription.transcribedText;
        }
    } failure:^(NSError *error) {
        
    }];

  
}

//人脸对比
- (void)faceCompare {
    
    self.cameraTrack.videoDelegate = self;
    
    self.taskType = QNAITaskType_FaceCompare;

    UIImagePickerController *picker = [[UIImagePickerController alloc]init];
    picker.sourceType = UIImagePickerControllerSourceTypeSavedPhotosAlbum;
    picker.delegate = self;
    [self presentViewController:picker animated:YES completion:nil];
    
}

- (void)startFaceCompare {
    QNFaceCompareParams *source = [[QNFaceCompareParams alloc]init];
    source.image = self.imageBase64Str;
    source.imageType = @"BASE64";
    
    QNFaceCompareParams *target = [[QNFaceCompareParams alloc]init];
    target.imageType = @"BASE64";
    target.image = [QNImageToVideoTool base64StringByImage:self.compareImage scaleWidth:200];
    
    [MBProgressHUD showStatus];
    [QNFaceCompare startCompare:source target:target complete:^(QNFaceCompareResponse * _Nonnull response) {
        [MBProgressHUD dismiss];
        
        if (response.errorCode != 0) {
            NSString *msg = [NSString stringWithFormat:@"错误码 %ld，%@", response.errorCode, response.errorMsg];
            [self showResultAlertWithTitle:@"人脸对比" content:msg];
            return;
        }
        
        QNFaceCompareResult *result = response.result;
        
        NSString *resultStr = @"相似度为0";
        if (result.score) {
            resultStr = [NSString stringWithFormat:@"相似度：%f",result.score];
        }
        [self showResultAlertWithTitle:@"人脸对比" content:resultStr];
    } failure:^(NSError * _Nonnull error) {
        [MBProgressHUD dismiss];
        [self showResultAlertWithTitle:@"人脸对比" content:@"相似度为0"];
    }];
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary<UIImagePickerControllerInfoKey,id> *)info {
    
    self.compareImage = [info objectForKey:UIImagePickerControllerOriginalImage];
    [self startFaceCompare];
    
    [picker dismissViewControllerAnimated:YES completion:nil];
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker {
    [picker dismissViewControllerAnimated:YES completion:nil];
}

//权威人脸对比
-(void)authoritativeFaceCompare {
    __weak typeof(self)weakSelf = self;
    [self showAlertInputMessageComplete:^(NSString *name, NSString *IDNum) {
        weakSelf.cameraTrack.videoDelegate = weakSelf;
        weakSelf.taskType = QNAITaskType_AuthoritativeFaceCompare;
        
        QNAuthoritativeFaceParams *params = [QNAuthoritativeFaceParams new];
        
        params.idcard = IDNum;
        params.realname = name;
        [[QNAuthoritativeFaceComparer shareManager] startDetectWithVideoTrack:weakSelf.cameraTrack params:params complete:^(QNAuthoritativeFaceResult * _Nonnull result) {
                
            NSString *resultStr = @"人脸不匹配";

            if (result.errorcode == 0) {
                resultStr = [NSString stringWithFormat:@"人脸相似度%@",result.similarity];
            }
            [weakSelf showResultAlertWithTitle:@"权威人脸检测" content:resultStr];

            } failure:^(NSError * _Nonnull error) {
                [weakSelf showResultAlertWithTitle:@"权威人脸检测" content:@"检测失败"];
            }];
        
    }];
    
}

//权威动作活体检测
- (void)authorityActionFaceComparer {
    __weak typeof(self)weakSelf = self;
    [self showAlertInputMessageComplete:^(NSString *name, NSString *IDNum) {
        weakSelf.taskType = QNAITaskType_AuthorityActionFaceComparer;

        QNAuthoritativeFaceParams *params = [QNAuthoritativeFaceParams new];
        params.idcard = IDNum;
        params.realname = name;

        [weakSelf authorityActionFaceComparerWithParam:params];
    }];
}

- (void) authorityActionFaceComparerWithParam:(QNAuthoritativeFaceParams *)authParam {
    QNActiveSessionRequest *sessionRequest = [[QNActiveSessionRequest alloc] init];
    [[QNAuthorityActionFaceComparer shareManager] getFaceActliveSession:sessionRequest complete:^(QNActiveSessionResponse * _Nonnull response) {
        if (response.errorCode != 0 || !response.result) {
            NSLog(@"getFaceActliveSession error %ld, %@", response.errorCode, response.errorMsg);
            return;
        }
        self.actionMessage = [self getActionMessage:response];
        
        [[QNAuthorityActionFaceComparer shareManager] startDetectWithTrack:self.cameraTrack];
        
        [self showCollectAlertWithComplete:^ {
            [MBProgressHUD showStatus];
            
            QNActionLiveDetectParam *detectParam = [[QNActionLiveDetectParam alloc] init];
            detectParam.sessionID = response.result.sessionID;
            detectParam.faceField = @"spoofing,quality";
            
            [[QNAuthorityActionFaceComparer shareManager] commitWithDetectParam:detectParam authParam:authParam complete:^(QNActionLiveDetectResponse * _Nonnull detectResponse, QNAuthoritativeFaceResult * _Nonnull authResponse) {
                [MBProgressHUD dismiss];
                self.cameraTrack.videoDelegate = self;
                
                // 实际处理需要检查 errorCode
                NSString *detectResultStr = [NSString stringWithFormat:@"动作活体分数：%f, 结果：%@",detectResponse.result.score, detectResponse.result.actionVerify];
                NSString *authResultStr = [NSString stringWithFormat:@"人脸识别相似度：%f", authResponse.similarity];
                NSString *msg = [NSString stringWithFormat:@"%@\n%@", detectResultStr, authResultStr];
                
                [self showResultAlertWithTitle:@"权威动作活体检测" content:msg];
            } failure:^(NSError * _Nonnull error) {
                [MBProgressHUD dismiss];
                self.cameraTrack.videoDelegate = self;
                
                NSString *msg = [NSString stringWithFormat:@"检测失败：%@", error];
                [self showResultAlertWithTitle:@"权威动作活体检测" content:msg];
            }];
        }];
        
    } failure:^(NSError * _Nonnull error) {
        NSString *msg = [NSString stringWithFormat:@"获取检验码失败：%@", error];
        [self showResultAlertWithTitle:@"权威动作活体检测" content:msg];
    }];
}

- (NSString *)getActionMessage:(QNActiveSessionResponse *)response {
    if (!response || !response.result) {
        return @"";
    }
    
    NSString *actionMessage = @"";
    NSArray<NSNumber *> *actions = [response.result actions];
    for (int i = 0; i < [actions count] ; i++) {
        if (actions[i].integerValue == QNFaceActionTypeBlink) {
            actionMessage = [actionMessage stringByAppendingString: @"请眨眼，"];
        }
        
        if (actions[i].integerValue == QNFaceActionTypeRaise) {
            actionMessage = [actionMessage stringByAppendingString: @"请抬头，"];
        }
        
        if (actions[i].integerValue == QNFaceActionTypeLower) {
            actionMessage = [actionMessage stringByAppendingString: @"请低头，"];
        }
        
        if (actions[i].integerValue == QNFaceActionTypeShake) {
            actionMessage = [actionMessage stringByAppendingString: @"请摇头，"];
        }
    }
    
    return actionMessage;
}

//人脸识别
- (void)faceDetect {
    
    self.cameraTrack.videoDelegate = self;
    self.taskType = QNAITaskType_FaceDetect;
    
    QNFaceDetectParams *params = [[QNFaceDetectParams alloc]init];
    params.imageType = @"BASE64";
    params.image = self.imageBase64Str;
    [MBProgressHUD showStatus];
    [QNFaceDetect startDetectWithParams:params complete:^(QNFaceDetectResponse * _Nonnull response) {
        [MBProgressHUD dismiss];
        
        if (response.errorCode != 0) {
            [self showResultAlertWithTitle:@"人脸识别" content:@"识别失败"];
            return;
        }
        
        QNFaceDetectResult *result = response.result;

        NSString *resultStr = @"未识别到人脸";
        if (result.faceNum > 0) {
            resultStr = [NSString stringWithFormat:@"识别到人脸数量：%ld", result.faceNum];
        }

        [self showResultAlertWithTitle:@"人脸识别" content:resultStr];

    } failure:^(NSError * _Nonnull error) {
        [MBProgressHUD dismiss];
        [self showResultAlertWithTitle:@"人脸识别" content:@"识别失败"];
    }];
}

//动作活体检测
- (void)actionLiveDetect {
        
    self.taskType = QNAITaskType_Action;
    
    QNActiveSessionRequest *sessionRequest = [[QNActiveSessionRequest alloc] init];
    
    [[QNActionLiveDetect shareManager] getFaceActliveSession:sessionRequest complete:^(QNActiveSessionResponse * _Nonnull response) {
        if (response.errorCode != 0 || !response.result) {
            NSLog(@"getFaceActliveSession error %ld, %@", response.errorCode, response.errorMsg);
            return;
        }
        self.actionMessage = [self getActionMessage:response];
        
        [[QNActionLiveDetect shareManager] startDetectWithTrack:self.cameraTrack];
        
        [self showCollectAlertWithComplete:^ {
            [MBProgressHUD showStatus];
            
            QNActionLiveDetectParam *param = [[QNActionLiveDetectParam alloc] init];
            param.sessionID = response.result.sessionID;
            param.faceField = @"spoofing,quality";
            
            [[QNActionLiveDetect shareManager] commitWithParam:param complete:^(QNActionLiveDetectResponse * _Nonnull response) {
                [MBProgressHUD dismiss];
                self.cameraTrack.videoDelegate = self;
                
                NSString *resultStr = [NSString stringWithFormat:@"动作活体分数：%f, 结果：%@",response.result.score, response.result.actionVerify];
                [self showResultAlertWithTitle:@"动作活体检测" content:resultStr];
                
            } failure:^(NSError * _Nonnull error) {
                [MBProgressHUD dismiss];
                self.cameraTrack.videoDelegate = self;
            }];
        }];
        
    } failure:^(NSError * _Nonnull error) {
        
    }];

    
    
}

- (void)play {

    NSString *documentPath= NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask,YES).firstObject;
    NSString *moviePath = [documentPath  stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.mp4",@"imagetovideo"]];
    
    NSURL *url = [NSURL fileURLWithPath:moviePath];

    MPMoviePlayerController *mpcontrol = [[MPMoviePlayerController alloc] initWithContentURL:url];

    [self.view addSubview:mpcontrol.view];

    mpcontrol.view.frame = CGRectMake(0, 0, 320, 380);
    mpcontrol.fullscreen = YES;

    mpcontrol.scalingMode = MPMovieScalingModeFill;

    [mpcontrol play];
}

//身份证识别
- (void)IDCardDetect {
    
    self.cameraTrack.videoDelegate = self;
    self.taskType = QNAITaskType_IDCardDetect;

    QNAIIDCardDetectParams *params = [[QNAIIDCardDetectParams alloc]init];
    params.ref_side = @"F";
    params.enable_border_check = YES;
    
    [MBProgressHUD showStatus];
    
    [[QNAIIDCardDetect shareManager] startDetectWithVideoTrack:self.cameraTrack params:params complete:^(QNAIIDCardResult * _Nonnull result) {
        
        [MBProgressHUD dismiss];
        
        NSString *resultStr = @"未识别到身份证";
        
        if ([result.ocr_result.side isEqualToString:@"F"]) {
            
            resultStr = [NSString stringWithFormat:@"人像面\n姓名：%@\n民族：%@\n生日：%@\n地址：%@\n身份证号码：%@\n",result.ocr_result.name,result.ocr_result.nation,result.ocr_result.birthdate,result.ocr_result.address,result.ocr_result.idno];
            
        } else if ([result.ocr_result.side isEqualToString:@"B"]){
            
            resultStr = [NSString stringWithFormat:@"国徽面\n身份证有效期：%@\n签发机关：%@",result.ocr_result.validthru,result.ocr_result.issuedby];
        }
        
        [self showResultAlertWithTitle:@"身份证识别" content:resultStr];
        
    } failure:^(NSError * _Nonnull error) {
        [MBProgressHUD dismiss];
        [self showResultAlertWithTitle:@"身份证识别" content:@"识别失败"];
    }];
    
}

- (void)configureRTCEngine {
    
    [QNRTC configRTC:[QNRTCConfiguration defaultConfiguration]];

    // QNRTCClient 初始化
    self.rtcClient = [QNRTC createRTCClient];
    self.rtcClient.delegate = self;

    // 设置本地预览视图
    self.preview = [QNRTC getCameraPreviewView];
    self.preview.frame = CGRectMake(0, 0, kScreenWidth, kScreenHeight);
    [self.view addSubview:self.preview];
    
    // 设置采集视频的帧率
    [QNRTC setCameraFrameRate:16];
    [QNRTC setPreviewMirrorFrontFacing:NO];
    
    // 加入房间
    [self.rtcClient join:self.roomToken completeCallback:^(BOOL success, NSError *error) {
        if (success) {
            NSLog(@"joinWithToken succeed");
            dispatch_async(dispatch_get_main_queue(), ^{
               
                // 音频
                QNTrack * audioTrack = [QNRTC createMicrophoneAudioTrack];
                
                [audioTrack setVolume:0.5];
                self.audioTrack = audioTrack;
                self.audioTrack.audioDelegate = self;
                // 视频
                QNCameraVideoTrackConfig * cameraConfig = [[QNCameraVideoTrackConfig alloc] initWithSourceTag:@"camera" bitrate:400 videoEncodeSize:CGSizeMake(480, 640)];
                QNTrack * cameraTrack = [QNRTC createCameraVideoTrackWithConfig:cameraConfig];
                
                self.cameraTrack = cameraTrack;
                self.cameraTrack.videoDelegate = self;
            
                // 发布音视频
                [self.rtcClient publish:@[audioTrack, cameraTrack] completeCallback:^(NSArray *onPublishedList, NSError *error) {
                    if (!error && onPublishedList.count > 0) {
                        NSLog(@"didPublishLocalTracks - %@", onPublishedList);

                    }else {
                        NSLog(@"publish error: %@",error);
                    }
                }];
            });
        }else
        {
            NSLog(@"joinWithToken error: %@",error);
        }
    }];
}

#pragma mark - QNRTCClientDelegate 代理回调

/*
 房间内状态变化的回调
 */
- (void)RTCClient:(QNRTCClient *)client didConnectionStateChanged:(QNConnectionState)state {
    NSDictionary *connectionStateDictionary =  @{@(QNConnectionStateIdle) : @"Idle",
                                           @(QNConnectionStateConnecting) : @"Connecting",
                                           @(QNConnectionStateConnected): @"Connected",
                                           @(QNConnectionStateReconnecting) : @"Reconnecting",
                                           @(QNConnectionStateReconnected) : @"Reconnected"
                                           };
    NSLog(@"roomStateDidChange - %@", connectionStateDictionary[@(state)]);
    dispatch_async(dispatch_get_main_queue(), ^{
        if (QNConnectionStateConnected == state) {
        } else if (QNConnectionStateIdle == state) {

            
        } else if (QNConnectionStateReconnecting == state) {

            
        } else if (QNConnectionStateReconnected == state) {

            
        }
    });
}
/*
 远端用户加入房间的回调
 */
- (void)RTCClient:(QNRTCClient *)client didJoinOfUserID:(NSString *)userID userData:(NSString *)userData {
    NSLog(@"didJoinOfUserId - userId %@ userData %@", userID, userData);
}

/*
 远端用户发布音/视频的回调
 */
- (void)RTCClient:(QNRTCClient *)client didUserPublishTracks:(NSArray<QNTrack *> *)tracks ofUserID:(NSString *)userID {
    NSLog(@"didUserPublishTracks - tracks %@ userId %@", tracks, userID);
}

#pragma mark - QNTrackVideoDataDelegate

- (void)track:(QNTrack *)track didGetPixelBuffer:(CVPixelBufferRef)pixelBuffer {
    
    NSLog(@"trackId: %@ tag: %@ RTC房间视频帧",track.trackID,track.tag);
    
    UIImage *image = [QNUtil convertFrame:pixelBuffer];
    self.imageBase64Str = [QNImageToVideoTool base64StringByImage:image scaleWidth:200];
    
}

#pragma mark - QNTrackAudioDataDelegate

- (void)track:(QNTrack *)track didGetAudioBuffer:(AudioBuffer *)audioBuffer bitsPerSample:(NSUInteger)bitsPerSample sampleRate:(NSUInteger)sampleRate {
    
//    NSLog(@"trackId: %@ tag: %@ RTC房间音频帧",track.trackID,track.tag);
}


- (void)showResultAlertWithTitle:(NSString *)title content:(NSString *)content {
    
    UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:title message:content preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleCancel handler:^(UIAlertAction *action) {}];
    [alertVc addAction:cancelAction];
    [self presentViewController:alertVc animated:YES completion:nil];
    
}

- (void)showAlertInputMessageComplete:(void (^)(NSString *name,NSString *IDNum))complete {
    
    UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:@"请输入对比信息" message:@"" preferredStyle:UIAlertControllerStyleAlert];
    
    [alertVc addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
        textField.placeholder = @"请输入对比姓名";
    }];
    
    [alertVc addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
        textField.placeholder = @"请输入对比身份证号";
    }];
    
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleCancel handler:^(UIAlertAction *action) {
        
        [[alertVc.textFields firstObject] endEditing:YES];
        [[alertVc.textFields lastObject] endEditing:YES];
        
        complete(alertVc.textFields.firstObject.text,alertVc.textFields.lastObject.text);
        
    }];
    [alertVc addAction:cancelAction];
    [self presentViewController:alertVc animated:YES completion:nil];
    
}

- (void)showCollectAlertWithComplete:(void (^)(void))complete {
    
    NSString *message = (self.taskType == QNAITaskType_Action || self.taskType == QNAITaskType_AuthorityActionFaceComparer)? self.actionMessage : nil;

    UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:@"采集中" message:message preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"开始检测" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        complete();
    }];
    [alertVc addAction:cancelAction];
    [self presentViewController:alertVc animated:YES completion:nil];
    
}

- (UITextView *)textView {
    if (!_textView) {
        _textView = [[UITextView alloc]initWithFrame:CGRectMake((kScreenWidth - 300)/2, kScreenHeight - 100, 300, 50)];
        _textView.backgroundColor = [UIColor blackColor];
        _textView.textColor = [UIColor whiteColor];
        [self.view addSubview:_textView];
        _textView.font = [UIFont systemFontOfSize:14];
        _textView.hidden = YES;
        
    }
    return _textView;
}

- (UIButton *)endSpeakButton {
    if (!_endSpeakButton) {
        _endSpeakButton = [[UIButton alloc]initWithFrame:CGRectMake(200, 80, 60, 35)];
        [_endSpeakButton setTitle:@"停止识别" forState:(UIControlStateNormal)];
        _endSpeakButton.titleLabel.font = [UIFont systemFontOfSize:14];
        [_endSpeakButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
        _endSpeakButton.backgroundColor = [UIColor whiteColor];
        [_endSpeakButton addTarget:self action:@selector(endSpeak) forControlEvents:(UIControlEventTouchUpInside)];
        [self.view addSubview:_endSpeakButton];
        _endSpeakButton.hidden = YES;
    }
    return _endSpeakButton;
}

- (void)endSpeak {
    [[QNSpeakToTextDetect shareManager] stopDetect];
    self.textView.hidden = YES;
    self.endSpeakButton.hidden = YES;
    self.audioTrack.audioDelegate = self;
}
@end
