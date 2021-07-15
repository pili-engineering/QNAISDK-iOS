//
//  MBProgressHUD+QNShow.h
//  QiNiu_Solution_iOS
//
//  Created by 郭茜 on 2021/4/27.
//

#import "MBProgressHUD.h"

NS_ASSUME_NONNULL_BEGIN

@interface MBProgressHUD (QNShow)

//文字
+ (void)showText:(NSString *)str;

//转菊花
+ (void)showStatus;

//消失
+(void)dismiss;

@end

NS_ASSUME_NONNULL_END
