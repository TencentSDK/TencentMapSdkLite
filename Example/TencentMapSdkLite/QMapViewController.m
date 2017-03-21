//
//  QMapViewController.m
//  TencentMapSdkLite
//
//  Created by eximpression on 03/21/2017.
//  Copyright (c) 2017 eximpression. All rights reserved.
//

#import "QMapViewController.h"
#import <TencentMapSdkLite/QMapView.h>
@interface QMapViewController ()
@property (strong, nonatomic) IBOutlet QMapView *mapView;

@end

@implementation QMapViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.mapView.showsUserLocation = YES;
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
