//
//  QMapRouteDemoViewController.m
//  QMapKitDemoNew
//
//  Created by ZhangChao on 2017/3/6.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "QMapRouteDemoViewController.h"
#import <QMapKitLite.h>
@interface QMapRouteDemoViewController ()<QMapViewDelegate>
@property (weak, nonatomic) IBOutlet QMapView *mapView;
@property(strong, nonatomic) QRouteOverlayGroup* routeGroupOverlay;
@end

@implementation QMapRouteDemoViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)addRouteOverlayGroupAction:(id)sender {
    [self test];
}

- (void)test {
    //1.准备画线的点串
    int count = 34;
    CLLocationCoordinate2D *coords =  malloc(sizeof(CLLocationCoordinate2D) * count);
    
    coords[0] = CLLocationCoordinate2DMake(39.993832, 116.311599);
    coords[1] = CLLocationCoordinate2DMake(39.993557, 116.311805);
    coords[2] = CLLocationCoordinate2DMake(39.993220, 116.312012);
    coords[3] = CLLocationCoordinate2DMake(39.993027, 116.312228);
    coords[4] = CLLocationCoordinate2DMake(39.992986, 116.312326);
    coords[5] = CLLocationCoordinate2DMake(39.992980, 116.312515);
    coords[6] = CLLocationCoordinate2DMake(39.992980, 116.313044);
    coords[7] = CLLocationCoordinate2DMake(39.992986, 116.313126);
    coords[8] = CLLocationCoordinate2DMake(39.992986, 116.313126);
    coords[9] = CLLocationCoordinate2DMake(39.992980, 116.313916);
    coords[10] = CLLocationCoordinate2DMake(39.992986, 116.315587);
    coords[11] = CLLocationCoordinate2DMake(39.992986, 116.315587);
    coords[12] = CLLocationCoordinate2DMake(39.992105, 116.315686);
    coords[13] = CLLocationCoordinate2DMake(39.992105, 116.315686);
    coords[14] = CLLocationCoordinate2DMake(39.992036, 116.315901);
    coords[15] = CLLocationCoordinate2DMake(39.992119, 116.317375);
    coords[16] = CLLocationCoordinate2DMake(39.992305, 116.321893);
    coords[17] = CLLocationCoordinate2DMake(39.992305, 116.321893);
    coords[18] = CLLocationCoordinate2DMake(39.992408, 116.321876);
    coords[19] = CLLocationCoordinate2DMake(39.992498, 116.321803);
    coords[20] = CLLocationCoordinate2DMake(39.993419, 116.320994);
    coords[21] = CLLocationCoordinate2DMake(39.993419, 116.320994);
    coords[22] = CLLocationCoordinate2DMake(39.993488, 116.321084);
    coords[23] = CLLocationCoordinate2DMake(39.993488, 116.321084);
    coords[24] = CLLocationCoordinate2DMake(39.993661, 116.321318);
    coords[25] = CLLocationCoordinate2DMake(39.993983, 116.321318);
    coords[26] = CLLocationCoordinate2DMake(39.995078, 116.321184);
    coords[27] = CLLocationCoordinate2DMake(39.995924, 116.321103);
    coords[28] = CLLocationCoordinate2DMake(39.996716, 116.321004);
    coords[29] = CLLocationCoordinate2DMake(39.996716, 116.321004);
    coords[30] = CLLocationCoordinate2DMake(39.997108, 116.320438);
    coords[31] = CLLocationCoordinate2DMake(39.997150, 116.320402);
    coords[32] = CLLocationCoordinate2DMake(39.997349, 116.320375);
    coords[33] = CLLocationCoordinate2DMake(39.997349, 116.320375);
    
    NSMutableArray* routePointArray = [NSMutableArray array];
    for (int i = 0; i < count; i++) {
        QRoutePoint *point = [[QRoutePoint alloc] init];
        point.coord = coords[i];
        [routePointArray addObject:point];
    }
    
    //2.创建线段，线段由起点索引（startNum），终点索引（endNum），颜色索引（color）组成, 颜色索引由上到下，见图片color_texture.png
    int segCount = 5;
    NSMutableArray* routeLineArray = [NSMutableArray array];
    QRouteLine *line1 = [[QRouteLine alloc] init];
    line1.startNum = 0;
    line1.endNum = 7;
    line1.color = 2;
    [routeLineArray addObject:line1];
    
    QRouteLine *line2 = [[QRouteLine alloc] init];
    line2.startNum = 7;
    line2.endNum = 15;
    line2.color = 5;
    [routeLineArray addObject:line2];
    
    QRouteLine *line3 = [[QRouteLine alloc] init];
    line3.startNum = 15;
    line3.endNum = 25;
    line3.color = 3;
    [routeLineArray addObject:line3];
    
    QRouteLine *line4 = [[QRouteLine alloc] init];
    line4.startNum = 25;
    line4.endNum = 33;
    line4.color = 4;
    [routeLineArray addObject:line4];
    
    for (int i = 0; i < segCount; i++) {
        QRouteLine *line = [[QRouteLine alloc] init];
        [routeLineArray addObject:line];
    }
    
    //3.创建路线,一条路线由一个点数组和线段数组组成
    QRouteOverlay *routeOverlay = [[QRouteOverlay alloc] initWithArrData:routePointArray arrLine:routeLineArray];
    routeOverlay.isDrawCap = YES;
    routeOverlay.isDrawArrow = YES;
    //4.创建路线组，路线必须被放到路线组才能显示，一个路线组可以包含多条路线，每个路线组创建完成后会带一个groupIndex,用来根据这个索引对路线组进行删除
    self.routeGroupOverlay = [[QRouteOverlayGroup alloc] initWithArrData:@[routeOverlay]];
    NSLog(@"routeOverlayGroupIndex:%ld", self.routeGroupOverlay.groupIndex);
    //5.将路线组添加到地图上
    [self.mapView addRouteOverlayGroup:self.routeGroupOverlay];
    
    //6.如果还想给该路线组再添加一条路线，则继续创建一个QRouteOverlay实例，调用如下方法
    QRouteOverlay *routeOverlay2 = nil;//创建一个路线实例
    //[self.mapView addRouteOverlay:routeOverlay2 routeOverlayGroup:routeOverlayGroup];
    
    //7.移除一条路线
    //[self.mapView removeRouteOverlayGroup:routeOverlayGroup];
    //或
    //[self.mapView removeRouteOverlayGroupByIndex:routeOverlayGroup.groupIndex];
}
- (IBAction)passRouteAction:(id)sender {
    [self.mapView setRoutePassedPointIndex:7 coordinates:CLLocationCoordinate2DMake(39.992986, 116.313126) routeOverlayGroup:self.routeGroupOverlay routeIndex:0 bClear:YES];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/


@end
