//
//  QMapAnnotationDemoViewController.m
//  QMapKitDemoNew
//
//  Created by ZhangChao on 2017/3/6.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "QMapAnnotationDemoViewController.h"
#import <QMapKitLite.h>
@interface QMapAnnotationDemoViewController ()<QMapViewDelegate>
@property (weak, nonatomic) IBOutlet QMapView *mapView;
@end

@implementation QMapAnnotationDemoViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)addTextAnnotation:(id)sender {
    QTextAnnotation* annotation = [[QTextAnnotation alloc]init];
    
    //绘制文本的字体名称，如果不设置，默认为系统默认字体
    annotation.fontName = @"American Typewriter";
    
    //绘制文本的颜色值,如果不设置，则默认为白色
    annotation.textColorString = @"0x0079FF";
    
    //绘制的文本
    annotation.text = @"@2x";
    
    //文字需要自适应大小
    annotation.autoAdjustTextPositon = YES;
    
    //设置允许展示的最大字体
    annotation.maxFontSize = 40.0f;
    
    //绘制的点串
    int count = 5;
    CLLocationCoordinate2D *coords =  malloc(sizeof(CLLocationCoordinate2D) * count);
    coords[0] = CLLocationCoordinate2DMake(39.2, 116.3);
    coords[1] = CLLocationCoordinate2DMake(39.75, 116.3);
    coords[2] = CLLocationCoordinate2DMake(39.7, 116.7);
    coords[3] = CLLocationCoordinate2DMake(39.4, 116.35);
    coords[4] = CLLocationCoordinate2DMake(39.1, 116.6);
    
    //获取当前点串组成的图形中最优的经纬度范围
    annotation.showRegion = [QPolygonUtil getMaxRectInPolygon:coords count:count];
    
    free(coords);
    //将最优的经纬度范围转换为屏幕坐标区域
    CGRect rc = [_mapView convertRegion:annotation.showRegion toRectToView:_mapView];
    
    //获取当前最优展示的区域可以展示的最大字体及对应字体的文本大小
    CGSize strSize = CGSizeZero;
    CGFloat fontSize =  [QPolygonUtil maxFontSizeThatFitsForString:annotation.text inRect:rc withFont:annotation.fontName size:&strSize maxFontSize:annotation.maxFontSize minFontSize:annotation.minFontSize];
    
    
    if (fontSize ==0)
    {
        NSLog(@"rect is too small,can not show anything,please add a polygon first");
        return;
    }
    //设置annotation 展示的屏幕区域
    annotation.textRc = CGRectMake(ceilf(rc.origin.x), ceilf(rc.origin.y), ceilf(strSize.width), ceilf(strSize.height));
    //设置annotation 显示的字体大小
    annotation.fontSize = fontSize;
    //设置annotation 的中心点
    annotation.coordinate = annotation.showRegion.center;
    //将annotation 加入到mapview
    [_mapView addAnnotation:annotation];
    
    [_mapView setCenterCoordinate:annotation.coordinate animated:YES];
}

- (QAnnotationView *)mapView:(QMapView *)mapView viewForAnnotation:(id <QAnnotation>)annotation
{
    if (([annotation isKindOfClass:[QTextAnnotation class]]))
    {
        static NSString* reuseIdentifier = @"QTextAnnotation";
        QTextAnnotationView* textAnnotationView = (QTextAnnotationView*)[mapView dequeueReusableAnnotationViewWithIdentifier:reuseIdentifier];
        QTextAnnotation* textAnnotation = (QTextAnnotation*)annotation;
        
        if (nil == textAnnotationView) {
            textAnnotationView = [[QTextAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:reuseIdentifier];
        }
        
        textAnnotationView.textRc = textAnnotation.textRc;
        textAnnotationView.imageName = textAnnotation.imageName;
        textAnnotationView.mDrawMode = KIMAGE_MIDDLE_CENTER_MODE;
        return textAnnotationView;
    }
        
    return nil;
}



@end
