//
//  QUserLocationView.h
//  QMapKitLite
//
//  Created by ZhangChao on 2017/3/22.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "QUserLocation.h"
@interface QUserLocationView : UIView

/**关联的annotation**/
@property (nonatomic, readonly) QUserLocation* annotation;

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

/**
 * 定位精度圈颜色
 */
@property(nonatomic,strong)UIColor* circleColor;
@end
