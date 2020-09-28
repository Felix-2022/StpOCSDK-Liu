 

#import <Foundation/Foundation.h>
NS_ASSUME_NONNULL_BEGIN
@class STPDeviceModel;

//用户基本信息
@interface STPUserModel : NSObject<NSCoding>
@property (nonatomic,strong) NSString *userid;//id
@property (nonatomic,strong) NSString *headimg;//头像
@property (nonatomic,strong) NSString *name;//昵称
@property (nonatomic,strong) NSArray <STPDeviceModel*> *devices;//用户所拥有的设备
@end


NS_ASSUME_NONNULL_END
