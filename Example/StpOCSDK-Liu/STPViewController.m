
#import "STPViewController.h"

#import <SpeakPen/STPAuthApi.h>
#import <SpeakPen/STPDeviceApi.h>
#import <SpeakPen/STPAccessConfig.h>
#import <SpeakPen/STPPictureBookApi.h>
#import <SpeakPen/STPPicBookResourceModel.h>
#import <SpeakPen/STPStudyReportApi.h>
#import <SpeakPen/STPStudyReportModel.h>
#import <YYModel.h>

@interface STPViewController ()<UITableViewDelegate,UITableViewDataSource>
@property (nonatomic, strong) UITableView *tableView;

@property (nonatomic, strong) NSArray * dataArray;
@property (nonatomic, strong) UIAlertController *alertVc;
@end

@implementation STPViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"speakPen 演示demo";
    [self setupFunctionItem];
    self.tableView = [[UITableView alloc] initWithFrame:self.view.bounds style:UITableViewStylePlain];
    
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:NSStringFromClass([UITableViewCell class])];
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    [self.view addSubview:self.tableView];
    STPAccessConfiger.developEnv = Env_Development;//开发环境
//    STPAccessConfiger.developEnv = Env_Distribution;//生产环境
    [STPAccessConfiger setPackageId:@"stp.sdk" ];
    
    [STPAuthApi login:@"13552966915" passWord:@"111111" pushId:@"" completionBlock:^(STPUserModel * _Nonnull user, NSError * _Nonnull error) {
        NSString *tips = @"登录成功";
        NSString *message = @"点击下面列表测试";
        if (error) {
            tips = @"登录失败";
            message = error.description;
        } else {
            if (user.devices.count > 0) {
                NSString* deviceId =[[user.devices firstObject] deviceID];
                NSString* appId =[[user.devices firstObject] appId] ;
                NSLog(@"deviceId:%@,appId:%@",deviceId,appId);
                
                [STPAccessConfiger setCurrDeviceID:deviceId appId:appId   ];
            }
        }
        self.alertVc = [UIAlertController alertControllerWithTitle:tips message:message preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *sureBtn = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDestructive handler:^(UIAlertAction * _Nonnull   action) {
            NSLog(@"确定");
        }];
        [sureBtn setValue:[UIColor redColor] forKey:@"titleTextColor"];
        //将action添加到控制器
        [self.alertVc addAction :sureBtn];
        //展示
        [self presentViewController:self.alertVc animated:YES completion:nil];
        
    }];
    // Do any additional setup after loading the view.
}

-(void)setupFunctionItem
{
    _dataArray = @[
        @"获取当前用户的设备",
        @"获取设备硬件信息",
        @"获取设备的详细信息",
        @"修改设备的名称",
        @"修改设备音量",
        @"获取绘本列表",
        @"搜索绘本列表",
        @"获取绘本详情",
        @"上传绘本",
        @"删除绘本",
        @"获取设备端绘本列表",
        @"获取设备端存储卡容量信息",
        @"获取学习成就 （按照日期进行选择）",
        @"获取学习成就 （按照数量进行选择）",
        @"获取学习成就详情 （按照数量进行选择）",
        @"获取跟读评测统计 （按照日期进行选择）",
        @"获取跟读评测统计 （按照数量进行选择）",
        @"手机号是否注册过"
    ];
}

#pragma mark ------------------- UITableViewDelegate ------------------------

-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    return 1;
}


-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.dataArray.count;
}

-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
    return 60;
}

-(UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:NSStringFromClass([UITableViewCell class])];
    cell.textLabel.text =[NSString stringWithFormat:@"%ld——%@",(long)indexPath.row,_dataArray[indexPath.row]];
    
    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    __block NSString *message;
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    switch (indexPath.row) {
        case 0:
        {
            [STPDeviceApi getDeviceList:YES block:^(NSArray<STPDeviceModel *> * _Nonnull device, NSError * _Nonnull error) {
                NSLog(@"--获取设备列表-%@-----%@",device,error);
                if (error) {
                    message = error.description;
                } else {
                    message = [device yy_modelToJSONString];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 1:
        {
            [STPDeviceApi getHardwareInfo:^(STPHardwareModel *deviceDict, NSError * _Nonnull error) {
                NSLog(@"获取设备硬件信息: %@---%@",deviceDict,error);
                if (error) {
                    message = error.description;
                } else {
                    message = [deviceDict yy_modelToJSONString];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 2:
        {
            [STPDeviceApi getDeviceDetail:^(STPDeviceModel* _Nonnull detail, NSError * _Nonnull error) {
                NSLog(@"获取设备详情: %@---%@",detail,error);
                if (error) {
                    message = error.description;
                } else {
                    message = [detail yy_modelToJSONString];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 3:
        {
            [STPDeviceApi updateDeviceName:@"点读笔1" block:^(BOOL isSuccess, NSError * _Nonnull error) {
                NSLog(@"修改设备名称: %d---%@",isSuccess,error);
                if (error) {
                    message = error.description;
                } else {
                    message = [NSString stringWithFormat:@"是否成功 isSuccess ： %d",isSuccess];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 4:
        {
            [STPDeviceApi changeDeviceVolume:50 block:^(BOOL isSuccess, NSError * _Nonnull error) {
                NSLog(@"修改设备音量:%d-------%@",isSuccess,error);
                if (error) {
                    message = error.description;
                } else {
                    message = [NSString stringWithFormat:@"是否成功 isSuccess ： %d",isSuccess];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 5:
        {
            [STPPictureBookApi getAllPicbookList:0 count:20 block:^(STPPicBookResourceList * _Nullable list, NSError * _Nullable error) {
                NSLog(@"获取绘本列表:%@",error);
                if (error) {
                    message = error.description;
                } else {
                    message = [list yy_modelToJSONString];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 6:
        {
            [STPPictureBookApi searchPicbookList:@"英" block:^(STPPicBookResourceList * _Nullable list, NSError * _Nullable error) {
                NSLog(@"搜索绘本列表:%@",error);
                if (error) {
                    message = error.description;
                } else {
                    message = [list yy_modelToJSONString];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 7:
        {
            [STPPictureBookApi getPicbookDetail:@"3562496" block:^(STPPicBookDetailModel * _Nullable detailModel, NSError * _Nullable error) {
                NSLog(@"获取绘本详情:%@",error);
                if (error) {
                    message = error.description;
                } else {
                    message = [detailModel yy_modelToJSONString];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 8:
        {
            [STPPictureBookApi uploadPicbook:@"2576772" block:^(BOOL isSuss, NSError * _Nullable error) {
                NSLog(@"上传绘本:%d-------%@",isSuss,error);
                if (error) {
                    message = error.description;
                } else {
                    message = [NSString stringWithFormat:@"是否成功 isSuccess ： %d",isSuss];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 9:
        {
            [STPPictureBookApi deletePicbook:@"2576772" block:^(BOOL isSuss, NSError * _Nullable error) {
                NSLog(@"删除绘本:%d-------%@",isSuss,error);
                if (error) {
                    message = error.description;
                } else {
                    message = [NSString stringWithFormat:@"是否成功 isSuccess ： %d",isSuss];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 10:
        {
            [STPPictureBookApi getLocalPicbookList:0 count:7 block:^(STPPicBookDetailList * _Nullable list, NSError * _Nullable error) {
                NSLog(@"获取设备端绘本列表:%@",error);
                if (error) {
                    message = error.description;
                } else {
                    message = [list yy_modelToJSONString];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 11:
        {
            [STPPictureBookApi getSdcardInfo:^(STPSdcardInfo * _Nullable cardInfo, NSError * _Nullable error) {
                NSLog(@"获取设备端存储卡容量信息:%@",error);
                if (error) {
                    message = error.description;
                } else {
                    message = [cardInfo yy_modelToJSONString];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 12:
        {
            
            [STPStudyReportApi getStudyAchieveData:@"point-reading" startDate:@"2020-01-01" endDate:@"2020-03-31" block:^(STPStudyAchieveList * _Nullable list, NSError * _Nullable error) {
                NSLog(@"获取学习成就 （按照日期进行选择）:%@",error);
                if (error) {
                    message = error.description;
                } else {
                    message = [list yy_modelToJSONString];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 13:
        {
            [STPStudyReportApi getStudyAchieveData:@"point-reading" fromId:0 count:7 block:^(STPStudyAchieveList * _Nullable list, NSError * _Nullable error) {
                NSLog(@"获取学习成就 （按照数量进行选择）:%@",error);
                if (error) {
                    message = error.description;
                } else {
                    message = [list yy_modelToJSONString];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 14:
        {
            
            [STPStudyReportApi getStudyAchieveDetailData:@"duration" fromId:0 count:7 block:^(STPStudyAchieveDetail * _Nullable list, NSError * _Nullable error) {
                NSLog(@"获取学习成就详情 （按照数量进行选择）:%@",error);
                
                if (error) {
                    message = error.description;
                } else {
                    message = [list yy_modelToJSONString];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 15:
        {
            [STPStudyReportApi getFollowReadData:@"2020-03-24" endDate:@"2020-03-31" block:^(NSArray * _Nullable list, NSError * _Nullable error) {
                NSLog(@"获取跟读评测统计 （按照日期进行选择）:%@",error);
                if (error) {
                    message = error.description;
                } else {
                    message = [list yy_modelToJSONString];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 16:
        {
            
            [STPStudyReportApi getFollowReadData:0 count:7 block:^(NSArray * _Nullable list, NSError * _Nullable error) {
                NSLog(@"获取跟读评测统计 （按照数量进行选择）:%@",error);
                if (error) {
                    message = error.description;
                } else {
                    message = [list yy_modelToJSONString];
                }
                [self showMessage:message];
            }];
        }
            break;
        case 17:{
             [STPAuthApi isRegist:@"13511111111" completionBlock:^(NSNumber * _Nonnull isRegist, NSError * _Nonnull error) {
                 if ([isRegist isEqualToNumber:@(1)]) {
                      message =@"手机号码已注册";
                    }else{
                     message =@"手机号码未注册";
                    }
                   [self showMessage:message];
                }];
        }
            break;
        default:
            break;
    }
}

- (void)showMessage:(NSString *)message {
    self.alertVc = [UIAlertController alertControllerWithTitle:@"结果" message:message preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *sureBtn = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDestructive handler:^(UIAlertAction * _Nonnull   action) {
        NSLog(@"确定");
    }];
    [sureBtn setValue:[UIColor redColor] forKey:@"titleTextColor"];
    //将action添加到控制器
    [self.alertVc addAction :sureBtn];
    //展示
    [self presentViewController:self.alertVc animated:YES completion:nil];
}

@end
