 

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, STPEnv) {
    Env_Distribution = 0,// 发布环境
    Env_Development,// 测试环境
};


#define STPAccessConfiger [STPAccessConfig defaultConfig]
/**
  stp sdk 全局配置文件
 */
@interface STPAccessConfig : NSObject


/**
 开发环境   分为开发和发布环境
 */
@property(nonatomic,assign) STPEnv developEnv;
/**
   产品Id
 */
@property(nonatomic,strong,nonnull,readonly) NSString* appID;
/**
   登录用户的id
 */
@property(nonatomic,strong,nonnull) NSString *userID;

/**
   登录用户的accessToken
 */
@property(nonatomic,strong,nonnull) NSString *accessToken;

/**
  当前连接的设备ID 当切换控制设备时 需要更改currDeviceID值
 */
@property(nonatomic,strong,nonnull,readonly) NSString *currDeviceID;

@property(nonatomic,strong,nonnull,readonly) NSString *packageId;

/**
 获取配置类
 */
+ (instancetype)defaultConfig;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new  NS_UNAVAILABLE;

/**
 清空资源配置文件
 */
-(void)clearLoginUserData;
-(void)setPackageId:(NSString * _Nonnull)packageId;
-(void)setCurrDeviceID:(NSString * _Nonnull)currDeviceID  appId:(NSString *_Nonnull) appId;
@end

NS_ASSUME_NONNULL_END
