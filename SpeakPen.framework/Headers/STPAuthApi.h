 
#import <Foundation/Foundation.h>
#import "STPUserModel.h"



typedef NS_ENUM(NSInteger,STPSendCodeType) {
    STPSendCodeTypeRegister = 1,/**!注册新账号号发送**/
    STPSendCodeTypeResetPhone    = 2,/**!修改手机号发送**/
    STPSendCodeTypeResetPsd      = 3,/**!修改其他发送**/
};


NS_ASSUME_NONNULL_BEGIN


#pragma mark ------------------- 用户注册 ------------------------
/**
 用户登录与注册api 目前不对外开放
 */
@interface STPAuthApi : NSObject

/**
 用户手机号码是否注册
 
 @param phoneNum 手机号码
 @param completionBlock IsRegist 1 = 注册  0=未注册
 */
+ (void)isRegist:(NSString *_Nonnull)phoneNum completionBlock:(nullable void (^)(NSNumber* isRegist,NSError *_Nullable error)) completionBlock;

/**
 用户注册
 
 @param phoneNum 手机号码
 @param password 用户密码
 @param code 验证码
 @param nickName 用户名称
 */
+ (void)regist:(NSString *_Nonnull)phoneNum password:(NSString *_Nonnull)password code:(NSString *_Nonnull)code nickName:(NSString *_Nonnull)nickName  pushId:(NSString*)pushId  completionBlock:(nullable void (^)(STPUserModel * _Nullable user,NSError * _Nullable error)) completionBlock;

/**
 发送验证码
 
 @param phoneNum 手机号码
 @param type 验证码类型
 
 */
+ (void)sendCode:(NSString *_Nonnull)phoneNum type:(STPSendCodeType )type completionBlock:(nullable void (^)(BOOL isSend,NSError * _Nullable error)) completionBlock;

#pragma mark ------------------- 用户登录 ------------------------
/**
 用户登录
 
 @param phoneNum 手机号码
 @param passWord 用户密码
 
 */
+ (void)login:(NSString*_Nonnull)phoneNum passWord:(NSString*_Nonnull)passWord pushId:(NSString*)pushId completionBlock:(nullable void (^)(STPUserModel * _Nullable user,NSError * _Nullable error)) completionBlock;

/**
 第三方登录

 @param phone 手机号码
 @param passwd 用户密码
 @param thirdCode 第三方code
 */
+(void)loginEx:(NSString*)phone passwd:(NSString*)passwd thirdCode:(NSString*)thirdCode block:(void (^)(STPUserModel * _Nullable user,NSError * _Nullable error))block;

/**
 更改手机号码
 
 @param phoneNum 手机号码
 @param code 验证码
 @param password 手机密码
 */
+ (void)updatePhoneNum:(NSString *_Nonnull)phoneNum  code:(NSString *_Nonnull)code password:(NSString *_Nonnull)password completionBlock:(nullable void (^)(BOOL isSuccess,NSError * _Nullable error)) completionBlock;

/**
 修改密码
 
 @param oldPsd 旧密码
 @param newPsd 新密码
 */
+ (void)updatePassword:(NSString *_Nonnull)oldPsd newPsd:(NSString *_Nonnull)newPsd completionBlock:(nullable void (^)(BOOL isSuccess,NSError * _Nullable error)) completionBlock;

/**
 忘记密码重置
 
 @param password 新密码
 @param phoneNum 手机号码
 @param code 手机验证码
 
 */
+ (void)resetPassword:(NSString *_Nonnull)password phoneNum:(NSString*_Nonnull) phoneNum  code :(NSString *_Nonnull)code  completionBlock:(nullable void (^)(BOOL isSuccess,NSError * _Nullable error)) completionBlock;


/**
  登出
 */
+ (void)logOut:(void (^)(BOOL isSuccess,NSError * _Nullable error))  block;

/**
 设置个推ID,更新用户推送的token
 @param pushId 个推Cid
 @param completionBlock result
 */
+ (void)updateUserPushToken:(NSString *_Nonnull)pushId completionBlock:(void (^)(BOOL  isSuccess,NSError * _Nullable error)) completionBlock;

@end
NS_ASSUME_NONNULL_END
