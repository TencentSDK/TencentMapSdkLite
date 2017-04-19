# TencentMapLite
=============================================================
2.0.0.00.06
1. QAnnotationView 增加了addAsSubview属性，当为YES的时候以UIView的方式添加到mapView上，当为NO的时候将图片用Opengl的时候渲染到底图上。
2. QAnnotationView的anchorPoint属性改为跟CALayer的anchorPoint属性相同的意义,取值在0~1之前, 默认(0.5, 0.5)
3. QAnnotationView的dispLevel属性改为默认为0,值越大优先级越高,以前的逻辑为优先级最高是1，值越大优先级越低，默认0
4. 针对后台执行opengl代码导致crash加了保护
5. 删除了一部分(美团)用不到的资源

=============================================================
2.0.0.00.07
1. QAnnotationView增加了centerOffset属性
2. bug fix

=============================================================
2.0.0.00.08
1.增加以下属性

/**
* 是否支持2D模式下旋转. 默认为NO.
*/
@property (nonatomic, assign) BOOL rotate2DEnabled;

/*
* 当前地图的旋转角度
*/
@property(nonatomic, assign)CGFloat rotation;

/*
* 当前地图的俯视角度,0 ~ 50
*/
@property(nonatomic, assign)CGFloat overlooking;

/*
* 设置地图的旋转角度与俯视角度
*/
-(void)setRotation:(CGFloat)rotation overlooking:(CGFloat)overlooking animated:(BOOL)animated;

2. bug fix
