 /*
 ============================================================================
 Name           : QMapView.h
 Author         : 腾讯地图
 Version        : 2.0
 Copyright      : 腾讯
 Description    : QMapView declaration
 ============================================================================
 */

#import <UIKit/UIKit.h>
#import <MapKit/Mapkit.h>
#import <MapKit/MKFoundation.h>
#import "QAnnotationView.h"
#import "QAnnotation.h"
#import "QOverlay.h"
#import "QOverlayView.h"
#import "QGeometry.h"
#import "QTypes.h"
#import "QUserLocation.h"
#import "QOverlay.h"
#import "QUserLocationView.h"
@class QPointAnnotation;
@class QRouteOverlay;
@class QRouteOverlayGroup;
@class QBusStationBubble;
@class QAnnotation;

@protocol QMapViewDelegate;

/**
 * QMapView:地图View类,可以显示地图窗口，并且对地图进行相关的操作,如拖动，放缩等
 */
@interface QMapView : UIView

#pragma mark - Delegates
/**
 * 指定地图语言的初始化方法
 * @param frame 地图frame
 * @param language 初始化地图的语言
 */
- (instancetype)initWithFrame:(CGRect)frame mapLanguage:(QMapLanguage)language;

#pragma mark - Delegates
/** 
 * 地图View的Delegate
 */
@property(nonatomic, weak)IBOutlet id <QMapViewDelegate> delegate;

#pragma mark - Map appearance
/**
 * 当前地图类型，可设定为普通模式或卫星地图模式
 */
@property(nonatomic, assign) QMapType mapType;

/**
 *是否3D模式显示地图
 */
@property(nonatomic)BOOL show3D;

/**
 *  @brief 楼块是否显示2D效果, 默认为NO
 *  @warning SDK2.0 以后2D模式下都不显示楼块的3D效果，只有地图在3D模式下才会显示楼块，所以这个属性在2.0上只在地图3D模式下有作用
 */
@property (nonatomic, assign, getter = isDisable3DBuildingEffect) BOOL disable3DBuildingEffect;

/**
 * 设定是否显示指南针
 */
@property(nonatomic, assign) BOOL showsCompass;

/**
 * 设定是否显示比例尺
 */
@property(nonatomic, assign) BOOL hideScaleView;

/**
 * 设置地图语言
 */
@property(nonatomic, assign) QMapLanguage mapLanguage;

/**
 * 设置地图比例尺偏移
 * @param offset 比例尺中心的偏移量. 如果offset为CGPointZero则为默认位置
 */
- (void)setScaleViewOffset:(CGPoint) offset;

/**
 * 设置地图比例尺隐藏
 * @param hidden 是否隐藏，YES隐藏，否则不隐藏
 */
- (void)setScaleViewHidden:(BOOL)hidden;

/**
 * 获取比例尺的显示状态
 */
- (BOOL)isScaleViewHidden;

/**
 * 设置地图Logo偏移
 * @param offset Logo中心的偏移量. 如果offset为CGPointZero则为默认位置
 */
- (void) setLogoOffSet:(CGPoint)offset;

/**
 * 设置3D模式下是否显示楼块
 * @param isShow 是否显示，YES显示，否则不显示
 */
- (void) setIsShowPillarIn3D:(BOOL)isShow;

/*
 * 3D模式下是否显示楼块
 */
- (BOOL) isShowPillarIn3D;

/**
 * 设置指南针偏移
 * @param yOffset 指南针中心Y基于默认位置的偏移量
 */
- (void) setCompassYOffSet:(CGFloat)yOffset;

/**
 * 地图状态 gettter & setter
 */
@property(nonatomic, assign)QMapStatus mapStatus;

/**
 * 设置地图状态
 * @param mapStatus    地图状态信息
 * @param bAnimation   是否需要动画效果
 * @param animationType    是否需要动画效果
 * @param duration     动画时间
 * @param completion   动画完成后回调
 */
- (void)setMapStatus:(QMapStatus)mapStatus
       withAnimation:(BOOL)bAnimation
           animationType:(QMapAnimationCurveType)animationType
            duration:(NSTimeInterval)duration
          completion:(void (^)(BOOL finished))completion;

#pragma mark - Others

/**
 * 如果需要传入非地图Bundle下的图片，请使用getImageFilePathFlag
 * 方法获得路径标识，sdk会根据此标识来加载指定路径下的图片,ImageFilePathFlag后面请跟绝对路径
 * 此方法适合annotation.imageName及路线纹理等指定路径的图片
 */
- (NSString*)getImageFilePathFlag:(NSString*)imageFilePath;

#pragma mark - Gesture

/**
 * 设定地图View能否支持用户长按，默认为NO
 */
@property(nonatomic, getter=isLongPressedEnabled) BOOL longPressedEnabled;

/**
 * 设定地图View能否支持用户多点缩放
 */
@property(nonatomic, getter=isZoomEnabled) BOOL zoomEnabled;

/**
 * 设定地图View能否支持用户移动地图
 */
@property(nonatomic, getter=isScrollEnabled) BOOL scrollEnabled;

/**
 * 是否支持手势进入3D模式. 默认为YES.
 */
@property (nonatomic, assign, getter=isPitchEnabled) BOOL pitchEnabled;

#pragma mark - Map zoom & map scale

/**
 * @brief 地图比例尺级别
 * @warning mapScale与zoomLevel 没有对应关系, mapScale仅仅用于更精确的表示地图比例尺级别的变化
 */
@property(nonatomic, assign) NSInteger zoomLevel;

/**
 * 以当前中心点，放大比例尺
 * @param zoomLevel 指定比例尺级别
 * @param animated 是否动画
 */
- (void)setZoomLevel:(NSInteger)zoomLevel animated:(BOOL)animated;

/**
 *  @brief 地图比例尺级别，浮点型
 *  @warning mapScale与zoomLevel 没有对应关系, mapScale仅仅用于更精确的表示地图比例尺级别的变化
 */
@property(nonatomic, assign) CGFloat mapScale;

/**
 * 是否支持按照中心点缩放, 默认为NO.
 */
@property (nonatomic, assign, getter=isStayCenteredDuringZoom) BOOL stayCenteredDuringZoom;

/**
 * 如果不支持按中心点缩放, 则以anchorPoint为缩放中心点
 */
@property(nonatomic, assign) CGPoint anchorPointOfScale;

/**
 * 放大一级比例尺
 */
- (void)zoomIn;

/**
 * 缩小一级比例尺
 */
- (void)zoomOut;

/**
 * 根据指定位置为中心，放大一级比例尺
 * @param x 指定位置x坐标
 * @param y 指定位置y坐标
 * @param animated 是否动画
 */
- (void)zoomInOnPoint:(CGFloat)x y:(CGFloat)y animated:(BOOL)animated;

/**
 * 根据指定位置为中心，缩小一级比例尺
 * @param x 指定位置x坐标
 * @param y 指定位置y坐标
 * @param animated 是否动画
 */
- (void)zoomOutOnPoint:(CGFloat)x y:(CGFloat)y animated:(BOOL)animated;

/**
 *  计算与mapRect相匹配的zoomLevel
 *  @warning mapScale与zoomLevel 没有对应关系, mapScale仅仅用于更精确的表示地图比例尺级别的变化
 *  @param mapRect mapRect
 *  @return 相匹配的zoomLevel
 */
- (NSInteger)zoomLevelFitsMapRect:(QMapRect)mapRect;

/**
 *  计算与region相匹配的zoomLevel
 *  @warning mapScale与zoomLevel 没有对应关系, mapScale仅仅用于更精确的表示地图比例尺级别的变化
 *  @param region region
 *  @return 相匹配的zoomLevel
 */
- (NSInteger)zoomLevelFitsRegion:(QCoordinateRegion)region;

/**
 *  计算与mapRect相匹配的 mapScale
 *  @warning mapScale与zoomLevel 没有对应关系, mapScale仅仅用于更精确的表示地图比例尺级别的变化
 *  @param mapRect mapRect
 *  @return 相匹配的mapScale 浮点型
 */
- (CGFloat) mapScaleFitsMapRect:(QMapRect)mapRect;

/**
 * 计算与mapRect相匹配的 mapScale
 * @warning mapScale与zoomLevel 没有对应关系, mapScale仅仅用于更精确的表示地图比例尺级别的变化
 * @param mapRect mapRect
 * @param insets mapRect四周要预留的边界大小
 * @return 相匹配的mapScale 浮点型
 */
- (CGFloat) mapScaleFitsMapRect:(QMapRect)mapRect edgePadding:(UIEdgeInsets)insets;

/**
 * 计算与QCoordinateRegion相匹配的 mapScale
 * @warning mapScale与zoomLevel 没有对应关系, mapScale仅仅用于更精确的表示地图比例尺级别的变化
 * @param region QCoordinateRegion类型
 * @return 相匹配的mapScale 浮点型 mapScale 与
 */
- (CGFloat) mapScaleFitsRegion:(QCoordinateRegion)region;

/**
 * 计算与QCoordinateRegion相匹配的 mapScale
 * @warning mapScale与zoomLevel 没有对应关系, mapScale仅仅用于更精确的表示地图比例尺级别的变化
 * @param region QCoordinateRegion类型
 * @param insets mapRect四周要预留的边界大小
 * @return 相匹配的mapScale 浮点型
 */
- (CGFloat) mapScaleFitsRegion:(QCoordinateRegion)region edgePadding:(UIEdgeInsets)insets;

#pragma mark - Life circle & Memory

/**
 * 清理内存中的地图缓存
 */
-(void) mapHibernate;

/**
 * 在显示MapView的Controlller的ViewWillAppear中调用，开启地图的显示状态。
 */
- (void)viewWillAppear;

/**
 * 在地图消失后调用，停止地图的渲染。
 */
- (void)viewDidDisappear;

#pragma mark - Snapshot

/**
 * 返回当前mapview截图
 * @return UIImage
 */
-(UIImage *) mapViewToUIImage;

#pragma mark - User location

/**
 * 设定是否显示用户位置
 */
@property(nonatomic) BOOL showsUserLocation;

/**
 * 是否隐藏定位精度圈. 默认为NO.
 */
@property(nonatomic, assign) BOOL hideAccuracyCircle;

/**
 * 当前用户位置，返回坐标为经纬度坐标等,非导航下返回的是原始经纬度，导航下返回的是吸附后的经纬度
 */
@property(nonatomic, readonly) QUserLocation *userLocation;

/**
 * 当前用户位置View,可以设置用户位置图片
 */
@property(nonatomic, readonly) QUserLocationView *userLocationView;

/**
 * 返回定位坐标点是否在当前地图可视区域内
 */
@property(nonatomic, readonly, getter=isUserLocationVisible) BOOL userLocationVisible;

/**
 * 返回定位坐标点是否有效
 */
@property (nonatomic, readonly, getter=isUserLocationAvailable) BOOL userLocationAvailable;

/**
 * 返回当前定位点所在的城市
 */
@property (nonatomic, readonly) NSString *currentCity;

/**
 * 设置用户位置的跟踪模式
 */
@property (nonatomic) QMUserTrackingMode userTrackingMode;

/**
 * 设备更新位置信息的最小距离，默认是kCLDistanceFilterNone
 */
@property(assign, nonatomic) CLLocationDistance distanceFilter;

/**
 * 位置数据的精度,默认是kCLLocationAccuracyBest
 */
@property(assign, nonatomic) CLLocationAccuracy desiredAccuracy;

/**
 * 设置当朝向改变时，每隔多少度调用一次, 默认是1度
 * 只有当设备方向的改变值超过该属性值时才激发delegate的方法。
 */
@property(nonatomic, assign) CLLocationDegrees headingFilter;

/**
 * 是否允许后台定位。默认为 NO。
 * iOS 9.0 以上用户需要设置该选项并且在info.list里面Background Modes 中的 Location updates 处于选中状态才可以使用后台定位权限。
 * iOS 9.0之前可以直接申请总是使用的权限来获得后台定位。
 * 设置为 YES 的时候必须保证 Background Modes 中的 Location updates 处于选中状态，否则会抛出异常。
 */
@property (nonatomic, assign) BOOL allowsBackgroundLocationUpdates;


/**
 * 设定罗盘模式
 * @param userTrackingMode 用户跟随模式
 * @param animated 是否采用动画效果
 */
- (void)setUserTrackingMode:(QMUserTrackingMode)userTrackingMode animated:(BOOL)animated;

/**
 * 设定是否显示用户位置
 * @param bNeedCenterMap 显示用户位置后是否需要居中
 */
-(void)showsUserLocation:(BOOL)showsUserLocation withMapCenter:(BOOL)bNeedCenterMap;

#pragma mark - Region

/**
 * 当前地图的经纬度范围，设定的该范围可能会被调整为适合地图窗口显示的范围
 */
@property(nonatomic) QCoordinateRegion region;

/**
 * 设定当前地图的显示范围
 * @param region 要设定的地图范围，用经纬度的方式表示
 * @param animated 是否采用动画效果
 */
- (void)setRegion:(QCoordinateRegion)region animated:(BOOL)animated;

/**
 * 设定当前地图的显示范围
 * @param region 要设定的地图范围，用经纬度的方式表示
 * @param insets 指定的四周边界大小
 * @param animated 是否采用动画效果
 */
- (void)setRegion:(QCoordinateRegion)region
      edgePadding:(UIEdgeInsets)insets
         animated:(BOOL)animated;

/**
 * 根据当前地图View的窗口大小调整传入的region，返回适合当前地图窗口显示的region，调整过程会保证中心点不改变
 * @param region 待调整的经纬度范围
 * @return 调整后适合当前地图窗口显示的经纬度范围
 */
- (QCoordinateRegion)regionThatFits:(QCoordinateRegion)region;

#pragma mark - Center coordiante

/**
 * 当前地图的中心点，改变该值时，地图的比例尺级别不会发生变化
 */
@property(nonatomic) CLLocationCoordinate2D centerCoordinate;

/**
 * 设定地图中心点坐标
 * @param coordinate 要设定的地图中心点坐标，用经纬度表示
 * @param animated 是否采用动画效果
 */
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate animated:(BOOL)animated;

/**
 * 设定地图中心点坐标
 * @param coordinate 目标坐标
 * @param duration   动画时间 (小于等于0.0 无效, 当animated == YES 时有效)
 * @param animated   是否动画
 */
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate
                   duration:(NSTimeInterval)duration
                   animated:(BOOL)animated;

/**
 * 设定地图中心点坐标和显示级别
 * @param coordinate 要设定的地图中心点坐标，用经纬度表示
 * @param zoomLevel 地图的比例尺级别
 * @param animated 是否采用动画效果
 */
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate
                  zoomLevel:(int)zoomLevel
                   animated:(BOOL)animated;

/**
 * 设定地图中心点坐标和显示级别
 * @param coordinate 要设定的地图中心点坐标，用经纬度表示
 * @param zoomLevel 地图的比例尺级别
 * @param animated 是否采用动画效果
 * @param curveType 动画曲线类型
 * @param duration 动画执行时间，单位秒
 */
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate
                  zoomLevel:(int)zoomLevel
                   animated:(BOOL)animated
                  curveType:(QMapAnimationCurveType)curveType
                   duration:(NSTimeInterval)duration;

/**
 * 是否需要用聚焦的效果动画设定地图中心点坐标和显示级别,
 * @param coordinate 要设定的地图中心点坐标，用经纬度表示
 * @param zoomLevel 地图的比例尺级别
 * @param animated 是否采用动画效果
 * @param curveType 动画曲线类型
 * @param duration 动画执行时间，单位秒
 * @param bFocusEffect 聚焦效果，当设置前后中心点不在一个屏幕时，先缩小到能显示前后中心点的地图区域，然后再放大到设置后的地图区域, 当animationType 为QMapAnimationCurveNone 此设置无效。(经滴滴设计师确认，如果是聚焦效果，curveType请使用QMapAnimationCurveLinear，效果会比较好)。
 */
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate
                  zoomLevel:(int)zoomLevel
                   animated:(BOOL) animated
                  curveType:(QMapAnimationCurveType)curveType
                   duration:(NSTimeInterval)duration
                focusEffect: (BOOL) bFocusEffect;

/**
 * 以anchorPoint偏移设定地图中心点坐标和显示级别
 * @param coordinate 要设定的地图中心点坐标，用经纬度表示
 * @param anchorPoint 以屏幕anchorPoint作为实际的显示中心点（屏幕像素值）
 * @param zoomLevel 地图的比例尺级别
 * @param animated 是否采用动画效果
 * @param curveType 动画曲线类型
 * @param duration 动画执行时间，单位秒
 */
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate
                anchorPoint:(CGPoint)anchorPoint
                  zoomLevel:(int)zoomLevel
                   animated:(BOOL)animated
                  curveType:(QMapAnimationCurveType)curveType
                   duration:(NSTimeInterval)duration;

/**
 * 设置地图中心点(Anchor Point)下移（可用来根据地图可见区域，调整地图中心点）
 * @param offsetY 锚点的偏移量，正值往下偏移, 上(下)偏移的最大幅度为地图Frame高度的四分之一
 * @param curveType 动画曲线类型
 * @param duration 动画执行时间，单位秒，如果不想要动画，设置duration为0
 * @param completion 动画完成的回调,finished 动画是否完成, animated 是否动画
 */
- (void)setCenterOffsetY:(CGFloat)offsetY
               curveType:(QMapAnimationCurveType)curveType
                  duration:(NSTimeInterval)duration
                completion:(void (^)(BOOL finished, BOOL animated))completion;


#pragma mark - MapRect

/**
 * 当前地图范围，采用直角坐标系表示，向右向下增长
 */
@property(nonatomic) QMapRect visibleMapRect;

/**
 * 设定当前地图的显示范围,采用直角坐标系表示
 * @param mapRect 要设定的地图范围，用直角坐标系表示
 * @param animated 是否采用动画效果
 */
- (void)setVisibleMapRect:(QMapRect)mapRect animated:(BOOL)animated;

/**
 * 根据当前地图View的窗口大小调整传入的mapRect，返回适合当前地图窗口显示的mapRect，调整过程会保证中心点不改变
 * @param mapRect 待调整的地理范围，采用直角坐标系表示
 * @return 调整后适合当前地图窗口显示的地图范围，采用直角坐标系
 */
- (QMapRect)mapRectThatFits:(QMapRect)mapRect;

/**
 * 根据当前地图View的窗口大小调整传入的mapRect，返回适合当前地图窗口显示的mapRect，并且在该mapRect四周保留insets指定的边界区域
 * @param mapRect 待调整的地理范围，采用直角坐标系表示
 * @param insets mapRect四周要预留的边界大小
 * @return 调整后适合当前地图窗口显示的地理范围，采用直角坐标系
 */
- (QMapRect)mapRectThatFits:(QMapRect)mapRect edgePadding:(UIEdgeInsets)insets;

/**
 * 根据当前地图View的窗口大小调整传入的mapRect，返回适合当前地图窗口显示的mapRect，调整过程会保证中心点不改变
 * @param mapRect 待调整的地理范围，采用直角坐标系表示
 * @return 调整后适合当前地图窗口显示的地图范围，采用直角坐标系
 */
- (QMapRect)mapRectThatContainsCalloutView:(QMapRect)mapRect;

/**
 * 根据当前地图View的窗口大小调整传入的mapRect，返回适合当前地图窗口显示的mapRect，调整过程会保证中心点不改变
 * @param mapRect 待调整的地理范围，采用直角坐标系表示
 * @param insets mapRect四周要预留的边界大小
 * @return 调整后适合当前地图窗口显示的地图范围，采用直角坐标系
 */
- (QMapRect)mapRectThatContainsCalloutView:(QMapRect)mapRect edgePadding:(UIEdgeInsets)insets;

/**
 * 根据当前地图View的窗口大小调整传入的mapRect，返回适合当前地图窗口显示的mapRect，调整过程会保证中心点不改变
 * @param mapRect 待调整的地理范围，采用直角坐标系表示
 * @param bContainsCalloutView 计算的maprect是否需要包含calloutView
 * @param annotations 要包含的annotation 数组
 * @param insets mapRect四周要预留的边界大小
 * @return 调整后适合当前地图窗口显示的地图范围，采用直角坐标系
 */
- (QMapRect)mapRectThatFits: (QMapRect)mapRect
        containsCalloutView:(BOOL)bContainsCalloutView
                annotations:(NSArray*)annotations
                edgePadding:(UIEdgeInsets)insets;
    
/**
 * 设定地图的显示范围,并使mapRect四周保留insets指定的边界区域
 * @param mapRect 要设定的地图范围，用直角坐标系表示
 * @param insets 指定的四周边界大小
 * @param animated 是否采用动画效果
 */
- (void)setVisibleMapRect:(QMapRect)mapRect
              edgePadding:(UIEdgeInsets)insets
                 animated:(BOOL)animated;

/**
 * 设定地图的显示范围,并使mapRect四周保留insets指定的边界区域
 * @param mapRect 要设定的地图范围，用直角坐标系表示
 * @param insets 指定的四周边界大小
 * @param animated 是否采用动画效果
 * @param on2d 只在2d下处理可见区域
 */
- (void)setVisibleMapRect:(QMapRect)mapRect
              edgePadding:(UIEdgeInsets)insets
                 animated:(BOOL)animated
                     on2d:(BOOL)on2d;

/**
 * 设定地图的显示范围,并使mapRect四周保留insets指定的边界区域,如果不需要动画，请使用QMapAnimationCurveNone
 * @param mapRect 要设定的地图范围，用直角坐标系表示
 * @param insets 指定的四周边界大小
 * @param animationType 动画类型
 * @param duration 动画时间
 * @param bFocusEffect 聚焦效果，当设置前后中心点不在一个屏幕时，先缩小到能显示前后中心点的地图区域，然后再放大到设置后的地图区域, 当animationType 为QMapAnimationCurveNone 此设置无效。(经滴滴设计师确认，如果是聚焦效果，animationType请使用QMapAnimationCurveLinear，效果会比较好)。
 */
- (void)setVisibleMapRect:(QMapRect)mapRect
              edgePadding:(UIEdgeInsets)insets
            animationType:(QMapAnimationCurveType)animationType
                 duration:(NSTimeInterval)duration
              focusEffect:(BOOL) bFocusEffect;

#pragma mark - Converting Coordinate System

/**
 * 将经纬度坐标转换为View坐标
 * @param coordinate 待转换的经纬度坐标
 * @param view 指定相对的View
 * @return 转换后的View坐标
 */
- (CGPoint)convertCoordinate:(CLLocationCoordinate2D)coordinate toPointToView:(UIView *)view;

/**
 * 将View坐标转换成经纬度坐标
 * @param point 待转换的View坐标
 * @param view point坐标所在的view
 * @return 转换后的经纬度坐标
 */
- (CLLocationCoordinate2D)convertPoint:(CGPoint)point toCoordinateFromView:(UIView *)view;

/**
 * 将经纬度矩形区域转换为View矩形区域
 * @param region 待转换的经纬度矩形
 * @param view 指定相对的View
 * @return 转换后的View矩形区域
 */
- (CGRect)convertRegion:(QCoordinateRegion)region toRectToView:(UIView *)view;

/**
 * 将View矩形区域转换成经纬度矩形区域
 * @param rect 待转换的View矩形区域
 * @param view rect坐标所在的view
 * @return 转换后的经纬度矩形区域
 */
- (QCoordinateRegion)convertRect:(CGRect)rect toRegionFromView:(UIView *)view;

/**
 * 在当前缩放级别下，基于地图中心点，1 sreen point对应的距离
 * @return 对应的距离(单位为米)
 */
-(CGFloat)metersPerPointForCurrentZoomLevel;

/**
 * 获取反转偏移坐标
 * @param coordinate 原始经纬度(WGS84)
 * @return 转换后的坐标(GCJ02)
 **/
+(CLLocationCoordinate2D)coordinateOffset:(CLLocationCoordinate2D)coordinate;

#pragma mark - Annotation

/*
 * 点击地图是否清除calloutView, 默认为NO
 */
@property(nonatomic,assign)BOOL keepCallout;

/**
 * 当前地图View的已经添加的标注数组
 */
@property(nonatomic, readonly) NSArray *annotations;

/**
 * 当前选中的annotations
 */
@property (nonatomic, readonly) NSArray<id<QAnnotation>> *selectedAnnotations;

/**
 * 向地图窗口添加标注，需要实现QMapViewDelegate的-mapView:viewForAnnotation:函数来生成标注对应的View
 * @param annotation 要添加的标注
 */
- (BOOL)addAnnotation:(id <QAnnotation>)annotation;

/**
 * 向地图窗口添加标注，需要实现QMapViewDelegate的-mapView:viewForAnnotation:函数来生成标注对应的View
 * @param annotation 要添加的标注
 * @param animated 是否支持动画
 */
- (BOOL)addAnnotation:(id <QAnnotation>)annotation animated:(BOOL)animated;

/**
 * 向地图窗口添加一组标注，需要实现QMapViewDelegate的-mapView:viewForAnnotation:函数来生成标注对应的View
 * @param annotations 要添加的标注数组
 */
- (BOOL)addAnnotations:(NSArray *)annotations;

/**
 * 向地图窗口添加一组标注，需要实现QMapViewDelegate的-mapView:viewForAnnotation:函数来生成标注对应的View
 * @param annotations 要添加的标注数组
 * @param animated 是否支持动画
 */
- (BOOL)addAnnotations:(NSArray *)annotations animated:(BOOL)animated;

/**
 * 移除标注
 * @param annotation 要移除的标注
 */
- (void)removeAnnotation:(id <QAnnotation>)annotation;

/**
 * 移除一组标注
 * @param annotations 要移除的标注数组
 */
- (void)removeAnnotations:(NSArray *)annotations;

/**
 * 查找指定标注对应的View，如果该标注尚未显示，返回nil
 * @param annotation 指定的标注
 * @return 指定标注对应的View
 */
- (QAnnotationView *)viewForAnnotation:(id <QAnnotation>)annotation;

/**
 * 根据指定标识查找一个可被复用的标注View，一般在delegate中使用，用此函数来代替新申请一个View
 * @param identifier 指定标识
 * @return 返回可被复用的标注View
 */
- (QAnnotationView *)dequeueReusableAnnotationViewWithIdentifier:(NSString *)identifier;

/**
 * 将制定的annotation放在最上层渲染.
 *  @param annotation 指定的annotation
 */
- (void)bringAnnotationToFront:(id <QAnnotation>)annotation;

/**
 * 选中指定的标注
 * @param annotation 指定的标注
 * @param animated 是否支持动画
 */
- (void)selectAnnotation:(id <QAnnotation>)annotation animated:(BOOL)animated;

/**
 * 取消指定的标注的选中状态
 * @param annotation 指定的标注
 * @param animated 是否支持动画
 */
- (void)deselectAnnotation:(id <QAnnotation>)annotation animated:(BOOL)animated;

/**
 * 更新annotation的image和锚点,只对addAsSubview为N0的annotationView有效
 * @param annotation 要设定的annotation
 * @param imageName 更新的图片,必须带有扩展名
 * @param drawMode 图片的AnchorPoint
 */
-(void)updateAnnotation:(id<QAnnotation>)annotation
              imageName:(NSString*)imageName
               drawMode:(ImageDrawMode)drawMode;

/**
 * 更新annotation的image和锚点,只对addAsSubview为N0的annotationView有效
 * @param annotation 要设定的annotation
 * @param imageIcon 更新的图片
 * @param drawMode 图片的AnchorPoint
 */
-(void)updateAnnotation:(id<QAnnotation>)annotation
              imageIcon:(UIImage*)imageIcon
               drawMode:(ImageDrawMode)drawMode;

/**
 * 更新annotation的坐标
 * @param annotation 要设定的annotation
 * @param coordinate 移动后的坐标点
 */
-(void)updateAnnotation:(id<QAnnotation>)annotation coordinate:(CLLocationCoordinate2D)coordinate ;

/**
 * 更新annotation的坐标,若要同时更新角度，请使用updateAnnotation: coordinate:angle:duration:  animated: 方法
 * 只对addAsSubview为N0的annotationView有效
 * @param annotation 要设定的annotation
 * @param coordinate 移动后的坐标点
 * @param duration 动画持续的时间
 * @param bAnimated 是否动画
 */
-(void)updateAnnotation:(id<QAnnotation>)annotation
             coordinate:(CLLocationCoordinate2D)coordinate
               duration: (NSTimeInterval)duration
               animated:(BOOL) bAnimated;
/**
 * 更新annotation的旋转角度,只对addAsSubview为N0的annotationView有效
 * @param annotation 要设定的annotation annotation对应的AnnotationView的ImageDrawMode 必须为KIMAGE_MIDDLE_CENTER_MODE
 * @param angle 旋转角度
 */
-(void)updateAnnotation:(id<QAnnotation>)annotation angle:(CGFloat)angle;

/**
 * 更新annotation的旋转角度 ,若要同时更新位置，请使用updateAnnotation: coordinate:angle:duration:  animated: 方法
 * 只对addAsSubview为N0的annotationView有效
 * @param annotation 要设定的annotation annotation对应的AnnotationView的ImageDrawMode 必须为KIMAGE_MIDDLE_CENTER_MODE
 * @param angle 旋转角度
 * @param duration 动画持续的时间
 * @param bAnimated 是否动画
 */
-(void)updateAnnotation:(id<QAnnotation>)annotation
                  angle:(CGFloat)angle
               duration:(NSTimeInterval)duration
               animated:(BOOL) bAnimated;

/**
 * 更新annotation的位置和旋转角度
 * 只对addAsSubview为N0的annotationView有效
 * @param annotation 要设定的annotation annotation对应的AnnotationView的ImageDrawMode 必须为KIMAGE_MIDDLE_CENTER_MODE
 * @param coordinate 移动后的坐标点
 * @param angle 旋转角度
 * @param duration 动画持续的时间
 * @param bAnimated 是否动画
 */
-(void)updateAnnotation:(id<QAnnotation>)annotation
             coordinate:(CLLocationCoordinate2D)coordinate
                  angle:(CGFloat)angle
               duration: (NSTimeInterval)duration
               animated:(BOOL) bAnimated;

/**
 * 更新annotation的位置和旋转角度
 * 只对addAsSubview为N0的annotationView有效
 * @param annotation 要设定的annotation annotation对应的AnnotationView的ImageDrawMode 必须为KIMAGE_MIDDLE_CENTER_MODE
 * @param angle 旋转角度
 * @param duration 动画持续的时间
 * @param bAnimated 是否动画
 * @param completion 动画完成时的处理
 */
-(void)updateAnnotation:(id<QAnnotation>)annotation
                  angle:(CGFloat)angle
               duration: (NSTimeInterval)duration
               animated:(BOOL) bAnimated
             completion:(void (^)(BOOL finished))completion;

/**
 * 更新annotation的位置和旋转角度, 只对addAsSubview为N0的annotationView有效
 * @param annotation 要设定的annotation annotation对应的AnnotationView的ImageDrawMode 必须为KIMAGE_MIDDLE_CENTER_MODE
 * @param mapPoint 地图投影之后的平面坐标点
 * @param angle 旋转角度
 * @param duration 动画持续的时间
 * @param bAnimated 是否动画
 * @param completion 动画完成时的处理
 */
-(void)updateAnnotation:(id<QAnnotation>)annotation
               mapPoint:(QMapPoint)mapPoint
                  angle:(CGFloat)angle
               duration: (NSTimeInterval)duration
               animated:(BOOL) bAnimated
             completion:(void (^)(BOOL finished))completion;

/**
 * 更新annotation的位置和旋转角度, 只对addAsSubview为N0的annotationView有效
 * @param coordinate 移动后的坐标点
 * @param annotation 要设定的annotation annotation对应的AnnotationView的ImageDrawMode 必须为KIMAGE_MIDDLE_CENTER_MODE
 * @param angle 旋转角度
 * @param duration 动画持续的时间
 * @param bAnimated 是否动画
 * @param completion 动画完成时的处理
 */
-(void)updateAnnotation:(id<QAnnotation>)annotation
             coordinate:(CLLocationCoordinate2D)coordinate
                  angle:(CGFloat)angle
               duration: (NSTimeInterval)duration
               animated:(BOOL) bAnimated
             completion:(void (^)(BOOL finished))completion;

/**
 * 更新annotation的alpha值,只对addAsSubview为N0的annotationView有效
 * @param annotation 要设定的annotation 
 * @param alpha 目标alpha值
 */
- (void)updateAnnotation:(id<QAnnotation>)annotation alpha:(CGFloat)alpha;

/**
 * 更新annotation的alpha值,只对addAsSubview为N0的annotationView有效
 * @param annotation 要设定的annotation
 * @param alpha 目标alpha值
 * @param duration 动画持续的时间
 * @param bAnimated 是否动画
 */
- (void)updateAnnotation:(id<QAnnotation>)annotation
                   alpha:(CGFloat)alpha
                duration:(NSTimeInterval)duration
                animated:(BOOL)bAnimated;

/**
 * 更新annotation的dispLevel,只对addAsSubview为N0的annotationView有效
 * @param annotation 要设定的annotation
 * @param dispLevel annotation的优先级
 */
- (void)updateAnnotationDispLevel:(id<QAnnotation>)annotation dispLevel:(NSUInteger)dispLevel;

/**
 * 按比例缩放annotationView,只对addAsSubview为N0的annotationView有效
 * @param scale 放大的比例
 * @param duration 动画持续的时间
 * @param delay 延迟运行动画的时间
 * @param curveType 动画类型
 * @param completion 动画完成后的回调
 */
- (void)updateAnnotation:(id<QAnnotation>)annotation
                   scale:(CGFloat)scale
                duration:(NSTimeInterval)duration
                   delay:(NSTimeInterval)delay
               curveType:(QMapAnimationCurveType)curveType
              completion:(void (^)(BOOL finished))completion;

#pragma mark - Route

/**
 * 设置路线宽度
 * 传入的是乘过[UIScreen mainScreen].scale之后的值
 * 设置了QMapView的线宽，默认线宽值将失效，如果需要保持每条线的线宽不一致，需要在路线生成后重新设置线宽
 */
@property (nonatomic, assign) NSInteger lineWidth;



/**
 * 根据坐标点数组在底图绘制路线
 * @param routedots 经纬度坐标数组
 * @param count 点位个数
 */
- (void) showRoute:(CLLocationCoordinate2D *)routedots withCount:(int) count;

/**
 * 修改路线纹理绘制类型
 * @param routeDrawType      路线绘制类型
 * @param routeIndex         同时绘制多条路线时的路线索引值
 * @param routeGroupIndex    同时绘制多组路线的group索引值
 */
- (void)setRouteDrawType:(QMapRouteDrawType)routeDrawType routeIndex:(NSInteger)routeIndex routeGroupIndex:(NSInteger)routeGroupIndex;

/**
 * 设置彩虹蚯蚓线是否绘制两段半圆纹理
 * @param bValue             是否绘制端纹理
 * @param routeIndex         同时绘制多条路线时的路线索引值
 * @param routeGroupIndex    同时绘制多组路线的group索引值
 */
- (void)setRouteDrawCap:(BOOL)bValue routeIndex:(int)routeIndex routeGroupIndex:(NSInteger)routeGroupIndex;


/**
 * 修改路线纹理图片
 * @param textureName        路线纹理图片文件名，包括扩展名，纹理图片资源不能放在asset内需要工程载入图片资源
 * @param param2             设置彩虹蚯蚓纹理，则代表纹理的行数，设置点纹理，则代表纹理间距(icon的倍数)，虚线纹理未使用此参数
 * @param routeIndex         同时绘制多条路线时的路线索引值，-1则对同一groupIndex的所有路线都设置纹理属性
 * @param routeGroupIndex    同时绘制多组路线的group索引值
 * @param routeDrawType      路线绘制类型
 */
- (void)setRouteDrawTexture:(NSString*)textureName param2:(CGFloat)param2
                 routeIndex:(NSInteger)routeIndex routeGroupIndex:(NSInteger)routeGroupIndex routeDrawType:(QMapRouteDrawType)routeDrawType;


#pragma mark - Route Overlay

/**
 * 在一个已经存在的路线组里增加一条路线
 * routeOverlay         新增路线，之前的路线组里的路线还会保留
 * routeOverlayGroup    要新增路线的路线组
 */
- (void)addRouteOverlay:(QRouteOverlay*)routeOverlay routeOverlayGroup:(QRouteOverlayGroup*)routeOverlayGroup;

/**
 * 新增一个路线组
 * routeOverlayGroup    要新增路线的路线组，如果路线组已经增加过，则会清除重新添加路线信息
 */
- (void)addRouteOverlayGroup:(QRouteOverlayGroup*)routeOverlayGroup;

/**
 * 删除路线组，删除路线只能通过删除路线组来实现
 * routeOverlayGroup 需要删除的路线组信息
 */
- (void)removeRouteOverlayGroup:(QRouteOverlayGroup*)routeOverlayGroup;

/**
 * 删除路线组，删除路线只能通过删除路线组来实现
 * groupIndex 需要删除的路线组索引
 */
- (void)removeRouteOverlayGroupByIndex:(NSInteger)groupIndex;

/**
 * 更新routeOverlayGroup的dispLevel，同Annotation的DispLevel一样
 * 即 默认为0,1，2，3，4 ....优先级依次增加
 * 2.0的annotation, mapMask, routeOverlay 都有优先级的概念并且优先级可以相互影响
 * routeOverlayGroup 需要更新的路线组信息
 * dispLevel 优先级
 */
- (void)updateRouteOverlayGroup:(QRouteOverlayGroup*)routeOverlayGroup dispLevel: (NSUInteger)dispLevel;

/**
 * 更新routeOverlayGroup的dispLevel，同Annotation的DispLevel一样
 * 即 默认为0,1，2，3，4 ....优先级依次增加
 * 2.0的annotation, mapMask, routeOverlay 都有优先级的概念并且优先级可以相互影响
 * groupIndex routeOverlayGroup 的groupIndex
 * dispLevel 优先级
 */
- (void)updateRouteOverlayGroupIndex:(NSInteger)groupIndex dispLevel: (NSUInteger)dispLevel;

/**
 * 更新routeOverlayGroup中带箭头的routeOverlay箭头的spacing,间距会随着地图的放大缩小会在一定范围内变化，变化幅度为spacing 值的0.5 ~ 1.0倍 之间
 * spacing默认值为200，单位为point，所以变化间距为100~200point
 * routeOverlayGroup 需要更新的路线组信息
 * spacing 间距
 */
- (void)updateRouteOverlayGroup:(QRouteOverlayGroup*)routeOverlayGroup arrowSpacing: (CGFloat)spacing;

/**
 * 更新routeOverlayGroup中带箭头的routeOverlay箭头的spacing,间距会随着地图的放大缩小会在一定范围内变化，变化幅度为spacing 值的0.5 ~ 1.0倍 之间
 * spacing默认值为200，单位为point，所以变化间距为100~200point
 * groupIndex routeOverlayGroup 的groupIndex
 * spacing 间距
 */
- (void)updateRouteOverlayGroupIndex:(NSInteger)groupIndex arrowSpacing: (CGFloat)spacing;

/**
 * 更新routeOverlayGroup中Type为QMRouteDrawDottedLine的routeOverlay的spacing,间距会随着地图的放大缩小会在一定范围内变化，变化幅度为spacing 值的0.5 ~ 1.0 倍之间,不是这种类型的routeOverlay就不起作用
 * spacing 默认值为60，单位为point，所以变化间距为30~60point
 * routeOverlayGroup 需要更新的路线组信息
 * spacing 间距
 */
- (void)updateRouteOverlayGroup:(QRouteOverlayGroup*)routeOverlayGroup footPrintSpacing: (CGFloat)spacing;

/**
 * 更新routeOverlayGroup中Type为QMRouteDrawDottedLine的routeOverlay的spacing,间距会随着地图的放大缩小会在一定范围内变化，变化幅度为spacing 值的0.5 ~ 1.0 倍之间,不是这种类型的routeOverlay就不起作用
 * spacing 默认值为60，单位为point，所以变化间距为30~60point
 * groupIndex routeOverlayGroup 的groupIndex
 * spacing 间距
 */
- (void)updateRouteOverlayGroupIndex:(NSInteger)groupIndex footPrintSpacing: (CGFloat)spacing;

/**
 * 设置高亮的路线，高亮路线在蒙层上面绘制
 * @param bValue             是否设置高亮
 * @param routeIndex         设置高亮路线的路线索引值
 * @param routeGroupIndex    设置高亮路线的group索引值
 */
- (void)setHighLightRoute:(BOOL)bValue routeIndex:(int)routeIndex routeGroupIndex:(NSInteger)routeGroupIndex;

/**
 * 路线擦除或者置灰
 * @param pointIndex         擦除路线上点的索引
 * @param coordinate         当前位置坐标(吸附后的)
 * @param routeOverlayGroup  routeOverlayGroup
 * @param routeIndex         routeOverlayGroup 中需要擦除的路线的索引(routeOverlayGroup中可能有多条路线）
 * @param bClear             擦除(YES)或者置灰(NO)
 */
- (void)setRoutePassedPointIndex:(int) pointIndex
                     coordinates:(CLLocationCoordinate2D) coordinate
               routeOverlayGroup:(QRouteOverlayGroup*) routeOverlayGroup
                      routeIndex:(NSInteger) routeIndex
                          bClear:(BOOL) bClear;

#pragma mark - Map mask
/**
 * 设置底图蒙层(覆盖颜色)
 * @param red 覆盖颜色红色值(0.0~1.0f)
 * @param green 覆盖颜色绿色值(0.0~1.0f)
 * @param blue 覆盖颜色蓝色值(0.0~1.0f)
 * @param alpha 覆盖颜色alpha值(0.0~1.0f)
 * @param layer 覆盖颜色层级
 * @param curveType 动画曲线类型
 * @param animateSecond 动画时间，单位秒，0则不做动画
 */
- (void)setMapMaskColor:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha layer:(QMapMaskColorLayer)layer curveType:(QMapAnimationCurveType)curveType animateSecond:(CGFloat)animateSecond;

@end


/**
 * QMapView(OverlaysAPI):Overlay相关的API
 */
@interface QMapView (OverlaysAPI)

/**
 * 当前mapView中已经添加的Overlay数组
 */
@property (nonatomic, readonly) NSArray *overlays;

/**
 * 向地图窗口添加Overlay，需要实现QMapViewDelegate的-mapView:viewForOverlay:函数来生成标注对应的View
 * @param overlay 要添加的overlay
 */
- (void)addOverlay:(id <QOverlay>)overlay;

/**
 * 向地图窗口添加一组Overlay，需要实现QMapViewDelegate的-mapView:viewForOverlay:函数来生成标注对应的View
 * @param overlays 要添加的overlay数组
 */
- (void)addOverlays:(NSArray *)overlays;

/**
 * 移除Overlay
 * @param overlay 要移除的overlay
 */
- (void)removeOverlay:(id <QOverlay>)overlay;

/**
 * 移除一组Overlay
 * @param overlays 要移除的overlay数组
 */
- (void)removeOverlays:(NSArray *)overlays;

/**
 * 在指定的索引处添加一个Overlay
 * @param overlay 要添加的overlay
 * @param index 指定的索引
 */
- (void)insertOverlay:(id <QOverlay>)overlay atIndex:(NSUInteger)index;

/**
 * 在交换指定索引处的Overlay
 * @param index1 索引1
 * @param index2 索引2
 */
- (void)exchangeOverlayAtIndex:(NSUInteger)index1 withOverlayAtIndex:(NSUInteger)index2;

/**
 * 在指定的Overlay之上插入一个overlay
 * @param overlay 带添加的Overlay
 * @param sibling 用于指定相对位置的Overlay
 */
- (void)insertOverlay:(id <QOverlay>)overlay aboveOverlay:(id <QOverlay>)sibling;

/**
 * 在指定的Overlay之下插入一个overlay
 * @param overlay 带添加的Overlay
 * @param sibling 用于指定相对位置的Overlay
 */
- (void)insertOverlay:(id <QOverlay>)overlay belowOverlay:(id <QOverlay>)sibling;

/**
 * 查找指定overlay对应的View，如果该View尚未创建，返回nil
 * @param overlay 指定的overlay
 * @return 指定overlay对应的View
 */
- (QOverlayView *)viewForOverlay:(id <QOverlay>)overlay;

@end

/**
 *QMapViewDelegate:MapView的Delegate,mapView通过此类来通知用户对应的事件
 **/
@protocol QMapViewDelegate <NSObject>

@optional
/**
 * 根据anntation生成对应的View
 * @param mapView 地图View
 * @param annotation 指定的标注
 * @return 生成的标注View
 */
- (QAnnotationView *)mapView:(QMapView *)mapView viewForAnnotation:(id <QAnnotation>)annotation;

/**
 * 地图区域即将改变时会调用此接口
 * @param mapView 地图View
 * @param animated 是否动画
 * @param bGesture 是否由手势触发
 */
- (void)mapView:(QMapView *)mapView regionWillChangeAnimated:(BOOL)animated gesture:(BOOL)bGesture;

/**
 * 地图区域改变完成后会调用此接口,如果是由手势触发，当触摸结束且地图region改变的动画结束后才会触发此回调
 * @param mapView 地图View
 * @param animated 是否动画
 * @param bGesture region变化是否由手势触发
 */
- (void)mapView:(QMapView *)mapView regionDidChangeAnimated:(BOOL)animated gesture:(BOOL)bGesture;



/**
 * 当mapView新添加annotation views时，调用此接口
 * @param mapView 地图View
 * @param views 新添加的annotation views
 */
- (void)mapView:(QMapView *)mapView didAddAnnotationViews:(NSArray *)views;

/**
 * 当mapView新添加annotationview时，调用此接口
 * @param mapView 地图View
 * @param view 新添加的annotationview
 */
- (void)mapView:(QMapView *)mapView didAddAnnotationView:(QAnnotationView *)view;
/**
 * 当选中一个annotation view时，调用此接口
 * @param mapView 地图View
 * @param view 选中的annotation view
 */
- (void)mapView:(QMapView *)mapView didSelectAnnotationView:(QAnnotationView *)view;

/**
 * 当annotation view的calloutView重新调整后，调用此接口
 * @param mapView 地图View
 * @param view 选中的annotation view
 */
- (void)mapView:(QMapView *)mapView didLayoutCalloutView:(QAnnotationView *)view;


/**
 * 当取消选中一个annotation view时，调用此接口
 * @param mapView 地图View
 * @param view 取消选中的annotation view
 */
- (void)mapView:(QMapView *)mapView didDeselectAnnotationView:(QAnnotationView *)view;

/**
 * 在地图View将要启动定位时，会调用此函数
 * @param mapView 地图View
 */
- (void)mapViewWillStartLocatingUser:(QMapView *)mapView;

/**
 * 在地图View停止定位后，会调用此函数
 * @param mapView 地图View
 */
- (void)mapViewDidStopLocatingUser:(QMapView *)mapView;

/**
 *用户位置更新后，会调用此函数
 *@param mapView 地图View
 *@param userLocation 新的用户位置
 *@param bFromHeading 是否为heading 变化触发，如果为location变化触发,则为NO
 */
- (void)mapView:(QMapView *)mapView didUpdateUserLocation:(QUserLocation *)userLocation sender:(BOOL)bFromHeading;
/**
 * 定位失败后，会调用此函数
 * @param mapView 地图View
 * @param error 错误号，参考CLError.h中定义的错误号
 */
- (void)mapView:(QMapView *)mapView didFailToLocateUserWithError:(NSError *)error;

/**
 * 根据overlay生成对应的View
 * @param mapView 地图View
 * @param overlay 指定的overlay
 * @return 生成的覆盖物View
 */
- (QOverlayView *)mapView:(QMapView *)mapView viewForOverlay:(id <QOverlay>)overlay;

/**
 * 当mapView新添加overlay view时，调用此接口
 * @param mapView 地图View
 * @param overlayView 新添加的overlayview
 */
- (void)mapView:(QMapView *)mapView didAddOverlayView:(QOverlayView *)overlayView ;

/**
 * 当mapView新添加overlay views时，调用此接口
 * @param mapView 地图View
 * @param overlayViews 新添加的overlay views
 */
- (void)mapView:(QMapView *)mapView didAddOverlayViews:(NSArray *)overlayViews ;

/**
 * 当mapView中有Annotation进行显示时点击地图空白区域调用此接口
 */
-(void)touchesWithOutCallout;

/** 
 * user tracking mode 改变时delegate调用此函数
 *  @param mapView 地图View
 *  @param mode QMUserTrackingMode
 *  @param animated 是否以动画的形式
 */
- (void)mapView:(QMapView *)mapView didChangeUserTrackingMode:(QMUserTrackingMode)mode animated:(BOOL)animated;

/** 
 * AnnotationView CalloutView的accessory control 触摸的时候调用此函数
 * @param mapView 地图View
 * @param view QAnnotationView
 * @param control CalloutView的 left or right accessory control
 */
- (void)mapView:(QMapView *)mapView annotationView:(QAnnotationView *)view calloutAccessoryControlTapped:(UIControl *)control;

/** 
 * AnnotationView的 触摸的时候调用此函数
 * @param mapView 地图View
 * @param view QAnnotationView
 * @param control 被点击的CalloutView，不包括leftAccessoryControl 或者rightAccessoryControl
 */
- (void)mapView:(QMapView *)mapView annotationView:(QAnnotationView *)view calloutViewTapped:(UIControl *)control;


/** 
 * 长按地图屏幕是触发,获得触摸处的经纬度
 * @param mapView 地图View
 * @param coordinate 长按处的经纬度
 */
- (void)mapView:(QMapView *)mapView longPressAtCoordinate:(CLLocationCoordinate2D)coordinate;

/**
 * 地图的位置变化时会持续调用此接口
 * @param mapView 地图View
 */
- (void)mapPositionChanged:(QMapView*)mapView;

/**
 * annotation 动画完成之后的回调
 * @param mapView 地图View
 * @param annotation 运行动画的annotation
 * @param key 标记动画类型的key (位移旋转:position, 透明度:alpha)
 * @param finished 动画是否完成
 */
-(void)mapView:(QMapView *)mapView annotation:(QPointAnnotation*)annotation animationKey:(NSString *)key didFinishAnimation:(BOOL)finished;

/**
 * @brief  当地图缩放级别发生变化时的回调
 * @param mapView  地图实例
 * @param animated 是否需要动画
 */
- (void)mapView:(QMapView*)mapView didChangeScaleAnimated:(BOOL)animated;

/**
 * 点击地图空白区域回调
 * @param mapView  地图实例
 * @param coordinate 点击处的经纬度
 */
-(void)mapView:(QMapView *)mapView didTapAtCoordinate:(CLLocationCoordinate2D)coordinate;
@end

