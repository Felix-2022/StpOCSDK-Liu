 

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface STPStudyReportModel : NSObject

@end

#pragma mark - FollowRead Model

/// 跟读STPStudyReportModel
@interface STPFollowReadMediaInfoModel : NSObject<NSCopying>

@property(nonatomic,copy) NSString *book_id;
@property(nonatomic,copy) NSString *oid;

/// 跟读资源名称
@property(nonatomic,copy) NSString *text;

/// 跟读资源网络地址
@property(nonatomic,copy) NSString *url;

/// 跟读资源分数
@property(nonatomic,copy) NSString *score;

@end

@interface STPFollowReadExtraModel : NSObject<NSCopying>

@property(nonatomic,assign) NSInteger bookCnt;
@property(nonatomic,assign) NSInteger pointReadingCnt;
@property(nonatomic,assign) NSInteger followReadingCnt;
@property(nonatomic,assign) NSInteger duration;
@property(nonatomic,copy) NSArray *bookIds;

// 跟读信息
@property(nonatomic,assign) NSInteger cnt;
@property(nonatomic,copy) NSArray <STPFollowReadMediaInfoModel *>*list;

@end

/// 跟读图书数据
@interface STPFollowReadBookModel : NSObject<NSCopying>

@property(nonatomic,assign) NSInteger rID; //资源ID
@property(nonatomic,copy) NSString *name;
@property(nonatomic,copy) NSString *author;
@property(nonatomic,copy) NSString *artist;
@property(nonatomic,copy) NSString *lyricist;
@property(nonatomic,copy) NSString *icon;
@property(nonatomic,copy) NSString *image;
@property(nonatomic,copy) NSString *desc;
@property(nonatomic,copy) NSString *press;
@property(nonatomic,copy) NSString *readGuideHtml;
@property(nonatomic,assign) NSInteger playCnt;

@end

/// 学习报告数据
@interface STPFollowReadReportModel : NSObject<NSCopying>

@property(nonatomic,assign) NSInteger rID; //资源ID
@property(nonatomic,copy) NSString *name;
@property(nonatomic,assign) NSInteger score;
@property(nonatomic,copy) NSString *type;
@property(nonatomic,strong) STPFollowReadExtraModel *extra;
@property(nonatomic,copy) NSArray <STPFollowReadBookModel *>*books;

/// 获取没有重复数据的 资源列表
- (NSArray <STPFollowReadBookModel *> *)getNoRepeatBooksList;

@end

/// 学习报告数据列表model
@interface STPFollowReadResultModel : NSObject<NSCopying>

/// 学习报告数据列表
@property(nonatomic,copy) NSArray <STPFollowReadReportModel *>*data;

/*
 以下数据是根据 学习报告数据列表data 计算得出，方便业务端直接使用。
 */

/// 累计点读书本数量
@property(nonatomic, assign) NSInteger totalReadBookCount;

/// 累计点读时长
@property(nonatomic, assign) NSInteger totalDuration;

/// 累计点读次数
@property(nonatomic, assign) NSInteger totalPointReadingCount;

/// 累计跟读次数
@property(nonatomic, assign) NSInteger totalFollowReadingCount;

/// 跟读数据列表
@property(nonatomic,strong) NSMutableArray <STPFollowReadMediaInfoModel *>*totalMediaList;

/// 阅读书籍列表
@property(nonatomic,strong) NSMutableArray <STPFollowReadBookModel *>*totalBookList;


@end

#pragma mark - Trend Model 趋势历史数据

@interface STPTrendDetailModel : NSObject

@property(nonatomic,copy) NSString *day;
@property(nonatomic, assign) NSInteger value; // 时长 Or 次数

@end

@interface STPTrendListModel : NSObject

@property(nonatomic, assign) NSInteger total; // 累计数据 时长 Or 次数

@property(nonatomic,copy) NSArray <STPTrendDetailModel *>*list;

@end

NS_ASSUME_NONNULL_END
