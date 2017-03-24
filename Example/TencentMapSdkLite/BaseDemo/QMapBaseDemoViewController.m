//
//  QMapBaseDemoViewController.m
//  QMapKitDemoNew
//
//  Created by ZhangChao on 2017/3/6.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "QMapBaseDemoViewController.h"
#import <QMapKitLite.h>
@interface QMapBaseDemoViewController ()<QMapViewDelegate>
@property (weak, nonatomic) IBOutlet QMapView *mapView;

@end

@implementation QMapBaseDemoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.mapView.delegate = self;
    self.mapView.userLocationView.locationImage = [UIImage imageNamed:@"car.png"];
    UIColor* ac = self.mapView.userLocationView.circleColor;
    self.mapView.userLocationView.circleColor = [UIColor redColor];
    QPointAnnotation* annotation = [[QPointAnnotation alloc]init];
    [annotation setCoordinate:CLLocationCoordinate2DMake(39.5, 116.3)];
    annotation.title = @"helldfjidfjaindifjei";
    [self.mapView addAnnotation:annotation];
    
    QCircle* circle = [QCircle circleWithCenterCoordinate:CLLocationCoordinate2DMake(39.5, 116.3) radius:10];
    [self.mapView addOverlay:circle];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/


- (IBAction)toggleCompassAction:(id)sender {
    self.mapView.showsCompass = !self.mapView.showsCompass;
}


- (IBAction)toggle3DAction:(id)sender {
    self.mapView.show3D = !self.mapView.show3D;
}

- (IBAction)toggleFollowingAction:(id)sender {
    switch (self.mapView.userTrackingMode)
    {
        case QMUserTrackingModeNone:
        default:
        {
            //_mapView.userTrackingMode = QMUserTrackingModeFollow;
            [self.mapView setUserTrackingMode:QMUserTrackingModeFollow animated:NO];
            break;
        }
        case QMUserTrackingModeFollow:
        {
            if ([CLLocationManager headingAvailable])
                // _mapView.userTrackingMode = QMUserTrackingModeFollowWithHeading;
                [self.mapView setUserTrackingMode:QMUserTrackingModeFollowWithHeading animated:NO];
            else
                //_mapView.userTrackingMode = QMUserTrackingModeNone;
                [self.mapView setUserTrackingMode:QMUserTrackingModeNone animated:NO];
            
            break;
        }
        case QMUserTrackingModeFollowWithHeading:
        {
            // _mapView.userTrackingMode = QMUserTrackingModeNone;
            [self.mapView setUserTrackingMode:QMUserTrackingModeNone animated:NO];
            break;
        }
    }
}

- (IBAction)changeMapStatusAction:(id)sender {
    QMapStatus mapStatus = self.mapView.mapStatus;
    mapStatus.scale = 15.4;
    mapStatus.overlooking = 20;
    mapStatus.rotation = 30;
    mapStatus.centerCoordinate.latitude = mapStatus.centerCoordinate.latitude + 0.05;
    

    
    CLLocationCoordinate2D coordinate = mapStatus.centerCoordinate;
    mapStatus.screenPoint = CGPointMake(100, 200);
    [self.mapView setMapStatus:mapStatus withAnimation:YES animationType:QMapAnimationCurveEaseInOut duration:5.0 completion:^(BOOL finished){
        NSLog(@"mapstatus animation end with finished = %d",finished);
        CGPoint point = [self.mapView convertCoordinate:coordinate toPointToView:nil];
        NSLog(NSStringFromCGPoint(point));
        
    }];
    
}


- (IBAction)adjustScaleViewPosition:(id)sender {
    int xOffset = arc4random_uniform(100) - 50;
    int yOffset = arc4random_uniform(100) - 50;
    CGPoint offset = CGPointMake(xOffset, yOffset);
    [self.mapView setScaleViewOffset:offset];
}

- (IBAction)toggleUserLocation:(id)sender {
    self.mapView.showsUserLocation = !self.mapView.showsUserLocation;
}


-(void)mapView:(QMapView *)mapView regionDidChangeAnimated:(BOOL)animated gesture:(BOOL)bGesture{
    NSLog(@"regionDidChange zoomlever = %d",mapView.zoomLevel);
    NSLog(@"regionDidChange zoomScale = %f",mapView.mapScale);
}

#pragma mark - mapview delegate
- (QAnnotationView *)mapView:(QMapView *)mapView viewForAnnotation:(id <QAnnotation>)annotation
{
    if (mapView == _mapView) {
        
        if ([annotation isKindOfClass:[QPointAnnotation class]])
        {
            if (NO)
            {
                static NSString* reuseIdentifier = @"QPinAnnotation";
                QPinAnnotationView* pinAnnotationView = (QPinAnnotationView*)[mapView dequeueReusableAnnotationViewWithIdentifier:reuseIdentifier];
                
                if (nil == pinAnnotationView) {
                    pinAnnotationView = [[QPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:reuseIdentifier];
                }
                pinAnnotationView.pinColor = QPinAnnotationColorGreen;
                UIButton* leftView =[[UIButton alloc]initWithFrame:CGRectMake(0, 0, 40,40)];
                leftView.backgroundColor = [UIColor redColor];
                UIButton* rightView =[UIButton buttonWithType:UIButtonTypeInfoLight];
                pinAnnotationView.leftCalloutAccessoryView =leftView;
                pinAnnotationView.rightCalloutAccessoryView = rightView;
                leftView.tag = 0;
                rightView.tag = 1;
                //pinAnnotationView.mDrawMode = KIMAGE_BOTTOM_CENTER_MODE;
                pinAnnotationView.canCalloutScrollToVisible = NO;
                pinAnnotationView.animatesDrop = NO;
                pinAnnotationView.canShowCallout = YES;
                //pinAnnotationView.anchorPoint = CGPointMake(14.5, 38);
                //pinAnnotationView.angle = 60;
                //pinAnnotationView.calloutOffset = CGPointMake(24, -24);
                //pinAnnotationView.canCalloutScrollToVisible = NO;
                pinAnnotationView.pinColor = QPinAnnotationColorGreen;
                return pinAnnotationView;
                
            }
            else{
                static NSString* reuseIdentifier = @"Annotation";
                QAnnotationView* annotationView = (QAnnotationView*)[mapView dequeueReusableAnnotationViewWithIdentifier:reuseIdentifier];
                
                if (nil == annotationView) {
                    annotationView = [[QAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:reuseIdentifier];
                }
                
                annotationView.anchorPoint = CGPointMake(12, 12);
                annotationView.imageName = @"car.png";
                annotationView.mDrawMode = KIMAGE_TOP_RIGHT_MODE;
                
                //annotationView.mDrawMode = KIMAGE_MIDDLE_CENTER_MODE;

                //annotationView.calloutOffset = CGPointMake(24, -24);
                return annotationView;
            }
        }
    }
    return nil;
}

#pragma mark - mapview delegate
-(QOverlayView*)mapView:(QMapView *)mapView viewForOverlay:(id<QOverlay>)overlay
{
    if ([overlay isKindOfClass:[QCircle class]])
    {
        
        QCircle* circle = (QCircle*)overlay;
        QCircleView* circleView = [[QCircleView alloc]initWithCircle:circle];
        circleView.fillColor = [UIColor redColor];
        circleView.strokeColor = [UIColor clearColor];
        circleView.lineWidth = 0.0;
        return circleView;
        
    }
    return nil;
}
@end
