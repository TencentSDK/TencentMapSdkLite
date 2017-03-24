/*
 ============================================================================
 Name           : QUserLocation.h
 Author         : 腾讯SOSO地图
 Version        : 1.0
 Copyright      : 腾讯
 Description    : QUserLocation declaration
 ============================================================================
 */

#import <Foundation/Foundation.h>
#import "QAnnotation.h"

/**
 *QUserLocation:定位信息类
 *Author:ksnowlv
 **/
@interface QUserLocation : NSObject <QAnnotation>

/**
 * 位置信息，如果QMapView的showsUserLocation为NO，或者尚未定位成功，return kCLLocationCoordinate2DInvalid
 * setter do nothing
 */
@property( nonatomic, assign) CLLocationCoordinate2D coordinate;

@property(readonly, nonatomic) CLLocationSpeed speed;//速度
@property(readonly, nonatomic) CLLocationDirection course;//方向角
@property(readonly, nonatomic) CLLocationAccuracy horizontalAccuracy;//水平精度

@property (readonly, nonatomic, nullable) CLLocation *location;

@property (readonly, nonatomic, nullable) CLHeading *heading ;
@end
