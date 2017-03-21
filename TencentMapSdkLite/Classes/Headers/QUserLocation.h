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

/**位置信息，如果QMapView的showsUserLocation为NO，或者尚未定位成功，则该值为0**/
@property( nonatomic, readonly) CLLocationCoordinate2D location;

@property(readonly, nonatomic) CLLocationSpeed speed;//速度
@property(readonly, nonatomic) CLLocationDirection course;//方向角
@property(readonly, nonatomic) CLLocationAccuracy horizontalAccuracy;//水平精度

/**
 * 非导航下用户位置图标路径。
 * 用法: 获取图标的绝对路径后,请调用QMapView的
 * - (NSString*)getImageFilePathFlag:(NSString*)imageFilePath 方法
 * 然后再将返回值赋值给pathForLocationImage
 * 下同
 */
@property(nonatomic,strong)NSString* pathForLocationImage;

/**
 * 定位失败后用户位置图标路径
 */
@property(nonatomic,strong)NSString* pathForFailurelocationImage;

/**
 * 非导航下用户位置图标
 */
@property(nonatomic,strong)UIImage* locationImage;


/**
 * 定位失败后用户位置图标
 */
@property(nonatomic,strong)UIImage* failurelocationImage;

@end
