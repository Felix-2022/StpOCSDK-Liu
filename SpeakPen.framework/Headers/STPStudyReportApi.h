#import <Foundation/Foundation.h>
#import "STPStudyReportModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface STPStudyReportApi : NSObject


/// 各项学习数据 (根据时间)
/// @param type 候选值对应的字符串(获取跟读数据 传 @"follow-reading")
/// 1: 点读数量(point-reading)
/// 2：绘本阅读量 (pic-book)
/// 3：学习时长(duration)
/// 4：跟读次数 (follow-reading)
/// @param start 起始日期 格式 YYYY-MM-DD（当天的话 start、end 都传同一个值）
/// @param end 终止日期
+ (void )getStudyAchieveData:(NSString *)type
                   startDate:(NSString *)start
                     endDate:(NSString *)end
                       block:(nullable void (^)(STPFollowReadResultModel* _Nullable detailModel,NSError * _Nullable error))block;



/// 各项学习数据 (根据顺序)
/// @param type 候选值对应的字符串(获取跟读数据 传 @"follow-reading")
/// 1: 点读数量(point-reading)
/// 2：绘本阅读量 (pic-book)
/// 3：学习时长(duration)
/// 4：跟读次数 (follow-reading)
/// @param fromId 数据起始ID ，0表示最新的数据
/// @param count 数量
/// @param block block
+ (void)getStudyAchieveData:(NSString *)type fromId:(NSInteger)fromId count:(NSInteger)count block:(void (^)(STPFollowReadResultModel * _Nullable detailModel, NSError * _Nullable error))block;


/// 获取已读绘本列表(根据时间)
/// @param start 起始日期 格式 YYYY-MM-DD （当天的话 start、end 都传同一个值）
/// @param end 终止日期
/// @param block block
+ (void)getTodayReadBookListStartDate:(NSString *)start
                              endDate:(NSString *)end
                                block:(nullable void(^)(STPFollowReadResultModel *_Nullable detailModel,NSError* _Nullable error))block;

/// 获取已读绘本列表(根据顺序)
/// @param fromId 数据起始ID ，0表示最新的数据
/// @param count 数量
/// @param block block
+ (void)getTodayReadBookListFromId:(NSInteger)fromId
                             count:(NSInteger)count
                             block:(nullable void(^)(STPFollowReadResultModel *_Nullable detailModel,NSError* _Nullable error))block;



/// 获取各项报告趋势详情
/// @param type (数据类型 例如：获取点读次数 传@"point-reading")
/// 1: 点读数量(point-reading)
/// 2：学习时长(duration)
/// @param start 起始日期 格式 YYYY-MM-DD （当天的话 start、end 都传同一个值）
/// @param end 终止日期
/// @param block block
+ (void)getPassdayTrendListWithType:(NSString *)type
                          StartDate:(NSString *)start
                            endDate:(NSString *)end
                              andCallback:(nullable void(^)(STPTrendListModel *_Nullable detailModel,NSError* _Nullable error))block;

/// 同步课堂开关
/// @param enable YES开 NO关
+ (void)handleSyncSwitch:(BOOL)enable
                   block:(nullable void (^)(BOOL isSuss,NSError* _Nullable error))block;

/// 同步课堂心跳
+ (void)sendSyncHeartbeatWithBlock:(nullable void (^)(BOOL isSuss,NSError* _Nullable error))block;

@end

NS_ASSUME_NONNULL_END
