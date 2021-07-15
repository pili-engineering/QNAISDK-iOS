# QNAISDK-iOS

# 七牛AI

### SDK注册

```
[[QNAISDKManager shareManager] registerWithAIToken:@""];

```

### 人脸识别

```
//开启人脸识别

QNFaceDetectParams *params = [[QNFaceDetectParams alloc]init];
params.rotate = YES;//人脸检测失败时，是否对图像做旋转再检测
params.image_b64 = @"需要识别的base64Str格式人脸照片";

[QNFaceDetect startDetectWithParams:params complete:^(QNFaceDetectResult * _Nonnull result) {
        //成功回调
 } failure:^(NSError * _Nonnull error) {
        
 }];

```

### 人脸比对

```

QNFaceCompareParams *params = [[QNFaceCompareParams alloc]init];
params.data_uri_a = @"对比图片1的base64Str"; 
params.data_uri_b = @"对比图片2的base64Str";
//开启人脸比对
[QNFaceCompare startCompareWithParams:params complete:^(QNFaceCompareResult * _Nonnull result) {
        
 } failure:^(NSError * _Nonnull error) {
        
 }];
    
 ```
 
 ### 动作活体检测
 
 ```

 /** 
 
 track：需要识别的视频轨道
 
 动作类型 

  QNFaceActionTypeBlink, //眨眼
  QNFaceActionTypeMouth,//张嘴
  QNFaceActionTypeNode,//点头
  QNFaceActionTypeShake,//摇头

*/

 //开始检测
 [[QNActionLiveDetect shareManager] startDetectWithTrack:self.cameraTrack actionTypes:@[@(QNFaceActionTypeShake)]];
 
 ```
 
  ```
  // 获取检测结果
 [[QNActionLiveDetect shareManager] detectComplete:^(QNActionLiveDetectResult * _Nonnull result) {
          //识别结果                        
  } failure:^(NSError * _Nonnull error) {
         
  }];
  
   ```
   
   ```
   //停止检测
   [[QNActionLiveDetect shareManager] cancel];
   
   ```
   
   ### 光线活体检测
   
    ```
    // 开始检测 ，传入需要检测的视频轨道
    [[QNFlashLiveDetect shareManager] startDetectWithTrack:self.cameraTrack];
     ```
     
       ```
    // 获取检测结果
    [[QNFlashLiveDetect shareManager] detectComplete:^(QNFlashLiveDetectResult * _Nonnull result) {
                 //识别结果                
        } failure:^(NSError * _Nonnull error) {
                      
        }];
        
     ```
     
   ```
    
   //停止检测
   
   [[QNFlashLiveDetect shareManager] cancel];
   
  ```
   
   ### 身份证识别OCR
   
   ```
   
     QNAIIDCardDetectParams *params = [[QNAIIDCardDetectParams alloc]init];
    params.image = @"需要识别的base64Str格式身份证照片";
    params.ref_side = @"Any";// 当图片中同时存在身份证正反面时，通过该参数指定识别的版面
        
    [QNAIIDCardDetect startDetectWithParams:params complete:^(QNAIIDCardResult * _Nonnull result) {
            //识别结果            
    } failure:^(NSError * _Nonnull error) {
        
    }];
   ```
   
   ### 文字转语音
   ```
   
   QNTextToSpeakParams *params = [[QNTextToSpeakParams alloc]init];
   params.text = @"需要转换的文字";
   params.speaker = @"female3";//发⾳⼈id，⽤于选择不同⻛格的⼈声
   params.audio_encoding = @"wav";//合成⾳频格式
   params.sample_rate = 16000;//合成⾳频的采样率
   params.volume = 80;//⾳量⼤⼩，取值范围为0~100
   params.speed = 0;//语速，取值范围为-100~100
        
        [QNTextToSpeakDetect startTextToSpeakWithParams:params complete:^(QNTextToSpeakResult * _Nonnull result) {
             //播放转换的语音
            [[AVAudioSession sharedInstance] setCategory: AVAudioSessionCategoryPlayback error: nil];
            [[AVAudioSession sharedInstance] setActive: YES error: nil];
            self.audioPlayer = [[AVAudioPlayer alloc] initWithData:result.audioData fileTypeHint:AVFileTypeWAVE error:nil];
            self.audioPlayer.volume = 1;
            [self.audioPlayer play];
                  
        } failure:^(NSError * _Nonnull error) {
                
            
        }];
        
   ```
   
   ### 实时语音识别
   
   ```
   QNSpeakToTextParams *params = [[QNSpeakToTextParams alloc]init];
    params.force_final = YES;//是否在text为空的时候返回final信息
    params.voice_sample = 48000;//采样率
    params.maxsil = 10;//最长静音间隔，单位秒
    
    //开始实时语音识别，track为需要识别的语音轨道
    [[QNSpeakToTextDetect shareManager] startDetectWithTrack:self.audioTrack params:params complete:^(QNSpeakToTextResult * _Nonnull result) {
        
         NSLog(@"识别出来的文字：%@",result.transcript);
         
    } failure:^(NSError *error) {
    
    }];
   
  ```
  
  ```
  
  //停止语音识别
   [[QNSpeakToTextDetect shareManager] stopDetect];
   
  ```
   
   
