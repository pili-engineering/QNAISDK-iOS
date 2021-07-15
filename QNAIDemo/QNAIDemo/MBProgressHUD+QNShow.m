//
//  MBProgressHUD+QNShow.m
//  QiNiu_Solution_iOS
//
//  Created by 郭茜 on 2021/4/27.
//

#import "MBProgressHUD+QNShow.h"

@implementation MBProgressHUD (QNShow)

+ (void)showText:(NSString *)str
{
    MBProgressHUD *HUD = [MBProgressHUD showHUDAddedTo:[UIApplication sharedApplication].keyWindow animated:YES];;
    HUD.mode = MBProgressHUDModeText;
    HUD.label.text = str;
    [HUD hideAnimated:YES afterDelay:2.f];
}

+ (void)showStatus
{
    MBProgressHUD *HUD = [MBProgressHUD showHUDAddedTo:[UIApplication sharedApplication].keyWindow animated:YES];;
    HUD.mode = MBProgressHUDModeIndeterminate;
}

+(void)dismiss{
    [MBProgressHUD hideHUDForView:[UIApplication sharedApplication].keyWindow animated:YES];
}

@end
