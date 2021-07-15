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
    QNAITaskType_Flash,//光线活体
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
@property (nonatomic, strong) AVAudioPlayer *audioPlayer;

@property (nonatomic, strong) QNTrack *audioTrack;
@property (nonatomic, strong) QNTrack *cameraTrack;

@property (nonatomic, strong) UIImage *compareImage;//用来人脸对比的图片
@property (nonatomic, strong) UIImage *IDCardImage;//用来身份证识别的图片

@property (nonatomic, copy) NSString *imageBase64Str;
@property (nonatomic, assign) QNAITaskType taskType;


@end

@implementation QNMainViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self configureRTCEngine];
    [self setupButtons];
    
}

- (void)setupButtons {
    
    NSArray *buttonTitles = @[ @"语音转文字",@"人脸对比",@"人脸识别",@"动作活体检测",@"光线活体检测",@"身份证识别",@"文字转语音"];
    NSArray *selectors = @[@"audioToText",@"faceCompare",@"faceDetect",@"actionLiveDetect",@"flashLiveDetect",@"IDCardDetect",@"textToSpeak"];
    
    for (int i = 0; i < buttonTitles.count; i ++) {
        UIButton *button = [[UIButton alloc] init];
        [button setTitle:buttonTitles[i] forState:(UIControlStateNormal)];
        button.titleLabel.font = [UIFont systemFontOfSize:14];
        [button setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        button.backgroundColor = [UIColor blackColor];
        [button addTarget:self action:NSSelectorFromString(selectors[i]) forControlEvents:(UIControlEventTouchUpInside)];
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
        params.text = alertController.textFields.firstObject.text;
        params.speaker = @"female3";
        params.audio_encoding = @"wav";
        params.sample_rate = 16000;
        params.volume = 80;
        params.speed = 0;
        
        [QNTextToSpeakDetect startTextToSpeakWithParams:params complete:^(QNTextToSpeakResult * _Nonnull result) {
                
            [[AVAudioSession sharedInstance] setCategory: AVAudioSessionCategoryPlayback error: nil];
            [[AVAudioSession sharedInstance] setActive: YES error: nil];
            self.audioPlayer = [[AVAudioPlayer alloc] initWithData:result.audioData fileTypeHint:AVFileTypeWAVE error:nil];
            self.audioPlayer.volume = 1;
            [self.audioPlayer play];
                  
            self.audioTrack.audioDelegate = self;
        } failure:^(NSError * _Nonnull error) {
                
            self.audioTrack.audioDelegate = self;
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
    params.force_final = YES;
    self.endSpeakButton.hidden = NO;
    self.textView.hidden = NO;
    self.textView.text = @"";
    [[QNSpeakToTextDetect shareManager] startDetectWithTrack:self.audioTrack params:params complete:^(QNSpeakToTextResult * _Nonnull result) {
        
        if (result.transcript.length > 0) {
            self.textView.text = result.transcript;
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
    QNFaceCompareParams *params = [[QNFaceCompareParams alloc]init];
    params.data_uri_a = self.imageBase64Str;
    params.data_uri_b = [QNImageToVideoTool base64StringByImage:self.compareImage scaleWidth:200];
    [MBProgressHUD showStatus];
    [QNFaceCompare startCompareWithParams:params complete:^(QNFaceCompareResult * _Nonnull result) {
        [MBProgressHUD dismiss];
        NSString *resultStr = @"相似度为0";
        if (result.similarity) {
            resultStr = [NSString stringWithFormat:@"相似度：%f",result.similarity];
        }
        [self showResultAlertWithTitle:@"人脸对比" content:resultStr];
    } failure:^(NSError * _Nonnull error) {
        [MBProgressHUD dismiss];
        [self showResultAlertWithTitle:@"人脸对比" content:@"相似度为0"];
    }];
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary<UIImagePickerControllerInfoKey,id> *)info {
    
    if (self.taskType == QNAITaskType_FaceCompare) {
        self.compareImage = [info objectForKey:UIImagePickerControllerOriginalImage];
        [self startFaceCompare];
    } else if (self.taskType == QNAITaskType_IDCardDetect){
        self.IDCardImage = [info objectForKey:UIImagePickerControllerOriginalImage];
        [self startIDCardDetect];
    }
    
    [picker dismissViewControllerAnimated:YES completion:nil];
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker {
    [picker dismissViewControllerAnimated:YES completion:nil];
}

//人脸识别
- (void)faceDetect {
    
    self.cameraTrack.videoDelegate = self;
    self.taskType = QNAITaskType_FaceDetect;
    
    QNFaceDetectParams *params = [[QNFaceDetectParams alloc]init];
    params.rotate = YES;
    params.image_b64 = self.imageBase64Str;
    [MBProgressHUD showStatus];
    [QNFaceDetect startDetectWithParams:params complete:^(QNFaceDetectResult * _Nonnull result) {
        [MBProgressHUD dismiss];
        NSString *resultStr = @"未识别到人脸";

        if (result.face.count > 0) {
            QNFaceModel *firstModel = result.face.firstObject;
            resultStr = [NSString stringWithFormat:@"人脸数量：%ld\n性别：%@\n年龄：%ld\n闭眼概率：%f\n人脸区域大小：%ld\n人脸分数：%f",result.num_face,[firstModel.gender  isEqualToString:@"F"] ? @"女" : @"男",firstModel.age,firstModel.eye,firstModel.area,firstModel.score];
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

    [[QNActionLiveDetect shareManager] startDetectWithTrack:self.cameraTrack actionTypes:@[@(QNFaceActionTypeShake)]];
    
    [self showCollectAlertWithComplete:^ {
            
        [MBProgressHUD showStatus];
        
        [[QNActionLiveDetect shareManager] detectComplete:^(QNActionLiveDetectResult * _Nonnull result) {
                    
            [MBProgressHUD dismiss];
            NSString *resultStr = [NSString stringWithFormat:@"动作活体状态：%ld",result.live_status];
            [self showResultAlertWithTitle:@"动作活体检测(摇头)" content:resultStr];
            self.cameraTrack.videoDelegate = self;
            
        } failure:^(NSError * _Nonnull error) {
            [MBProgressHUD dismiss];
            self.cameraTrack.videoDelegate = self;
        }];
    }];
}

//光线活体检测
- (void)flashLiveDetect {
        
    self.taskType = QNAITaskType_Flash;

    [[QNFlashLiveDetect shareManager] startDetectWithTrack:self.cameraTrack];
        
    [self showCollectAlertWithComplete:^ {
        [MBProgressHUD showStatus];
        [[QNFlashLiveDetect shareManager] detectComplete:^(QNFlashLiveDetectResult * _Nonnull result) {
                    
            [MBProgressHUD dismiss];
            
            NSString *resultStr = [NSString stringWithFormat:@"视频中检测到的人脸帧数：%ld\n通过数：%ld\n活体分数：%f",result.face_num,result.pass_num,result.score];
            [self showResultAlertWithTitle:@"光线活体检测" content:resultStr];
            self.cameraTrack.videoDelegate = self;
        } failure:^(NSError * _Nonnull error) {
            [MBProgressHUD dismiss];
            self.cameraTrack.videoDelegate = self;
        }];

    }];
        
}

//身份证识别
- (void)IDCardDetect {
    
    self.cameraTrack.videoDelegate = self;
    self.taskType = QNAITaskType_IDCardDetect;

    UIImagePickerController *picker = [[UIImagePickerController alloc]init];
    picker.sourceType = UIImagePickerControllerSourceTypeSavedPhotosAlbum;
    picker.delegate = self;
    [self presentViewController:picker animated:YES completion:nil];
    
}

- (void)startIDCardDetect {
    
    QNAIIDCardDetectParams *params = [[QNAIIDCardDetectParams alloc]init];
    //身份证识别的图片尽量少压缩，不然识别不出来
    params.image = [QNImageToVideoTool base64StringByImage:self.IDCardImage scaleWidth:300];
    params.ref_side = @"F";
    params.enable_border_check = YES;
    
    [MBProgressHUD showStatus];
    
    [QNAIIDCardDetect startDetectWithParams:params complete:^(QNAIIDCardResult * _Nonnull result) {
        
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
    
//    NSLog(@"trackId: %@ tag: %@ RTC房间视频帧",track.trackID,track.tag);
    
    UIImage *image = [QNUtil convertFrame:pixelBuffer];
    self.imageBase64Str = [QNImageToVideoTool base64StringByImage:image scaleWidth:200];
    
}

#pragma mark - QNTrackAudioDataDelegate

- (void)track:(QNTrack *)track didGetAudioBuffer:(AudioBuffer *)audioBuffer bitsPerSample:(NSUInteger)bitsPerSample sampleRate:(NSUInteger)sampleRate {
    
    NSLog(@"trackId: %@ tag: %@ RTC房间音频帧",track.trackID,track.tag);
}


- (void)showResultAlertWithTitle:(NSString *)title content:(NSString *)content {
    
    UIAlertController *alertVc = [UIAlertController alertControllerWithTitle:title message:content preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleCancel handler:^(UIAlertAction *action) {}];
    [alertVc addAction:cancelAction];
    [self presentViewController:alertVc animated:YES completion:nil];
    
}

- (void)showCollectAlertWithComplete:(void (^)(void))complete {
    
    NSString *message =  self.taskType == QNAITaskType_Action ? @"请摇摇头" : nil;

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
