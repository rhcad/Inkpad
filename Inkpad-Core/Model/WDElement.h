//
//  WDElement.h
//  Inkpad
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Copyright (c) 2009-2013 Steve Sprang
//

#import <Foundation/Foundation.h>
#import "WDDrawing.h"
#import "WDXMLElement.h"

#if TARGET_OS_IPHONE
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#else 
#import <OpenGL/gl.h>
#endif

typedef enum {
    WDAlignLeft,
    WDAlignCenter,
    WDAlignRight,
    WDAlignTop,
    WDAlignMiddle,
    WDAlignBottom
} WDAlignment;

typedef enum {
    WDColorAdjustStroke = 1 << 0,
    WDColorAdjustFill   = 1 << 1,
    WDColorAdjustShadow = 1 << 2
} WDColorAdjustmentScope;

@class WDGroup;
@class WDLayer;
@class WDPickResult;
@class WDPropertyManager;
@class WDShadow;
@class WDXMLElement;

// 可见的图形元素基类
@interface WDElement : NSObject <NSCoding, NSCopying> {
    CGRect      dirtyBounds_;
}

@property (nonatomic, weak) WDLayer *layer;             // 所在的层
@property (nonatomic, weak) WDGroup *group;             // 所在的组元素，属于某个组时有效
@property (nonatomic, assign) float opacity;            // 不透明度，0~1，0全透明，1不透明
@property (nonatomic, assign) CGBlendMode blendMode;    // 颜色混合模式
@property (nonatomic, strong) WDShadow *shadow;         // 阴影参数，initialShadow非空时shadow为临时阴影
@property (nonatomic, strong) WDShadow *initialShadow;  // 动态调整前的阴影参数
@property (weak, nonatomic, readonly) NSUndoManager *undoManager;   // 所在层的绘图Undo管理器
@property (weak, nonatomic, readonly) WDDrawing *drawing;   // 所在层的图形文档
@property (weak, nonatomic, readonly) NSSet *inspectableProperties; // 支持的各个属性，见 WDInspectableProperties.h

- (void) awakeFromEncoding;                             // 解码后确保某些数据已注册到图形文档且不是重复实例

- (CGRect) bounds;                                      // 图形几何范围，由子类实现
- (CGRect) styleBounds;                                 // 根据样式对bounds扩大后的图形范围
- (WDShadow *) shadowForStyleBounds;                    // 计算 styleBounds 所用的阴影参数，默认为 self.shadow
- (CGRect) expandStyleBounds:(CGRect)rect;              // 计算根据样式对bounds扩大后的图形范围

- (CGRect) subselectionBounds;                          // 部分选中的子集图形范围
- (void) clearSubselection;                             // 清除部分选中状态(暂未用)

- (BOOL) containsPoint:(CGPoint)pt;                     // 是否包含一个坐标，可用于点选
- (BOOL) intersectsRect:(CGRect)rect;                   // 是否与一个矩形相交，可用于框选

- (void) renderInContext:(CGContextRef)ctx metaData:(WDRenderingMetaData)metaData;  // 使用CGContext绘图

- (void) cacheDirtyBounds;                              // 标记整个图形范围待重绘
- (void) postDirtyBoundsChange;                         // 通知画布应用待重绘范围

- (void) tossCachedColorAdjustmentData;
- (void) restoreCachedColorAdjustmentData;
- (void) registerUndoWithCachedColorAdjustmentData;

// OpenGL-based selection rendering
- (void) drawOpenGLZoomOutlineWithViewTransform:(CGAffineTransform)viewTransform visibleRect:(CGRect)visibleRect;
- (void) drawOpenGLAnchorAtPoint:(CGPoint)pt transform:(CGAffineTransform)transform selected:(BOOL)selected;
- (void) drawOpenGLHighlightWithTransform:(CGAffineTransform)transform viewTransform:(CGAffineTransform)viewTransform;
- (void) drawOpenGLHandlesWithTransform:(CGAffineTransform)transform viewTransform:(CGAffineTransform)viewTransform;
- (void) drawOpenGLAnchorsWithViewTransform:(CGAffineTransform)transform;
- (void) drawGradientControlsWithViewTransform:(CGAffineTransform)transform;
- (void) drawTextPathControlsWithViewTransform:(CGAffineTransform)viewTransform viewScale:(float)viewScale;

// 几何变形，返回已选中节点(WDBezierNode)的变形结果
- (NSSet *) transform:(CGAffineTransform)transform;
- (void) adjustColor:(WDColor * (^)(WDColor *color))adjustment scope:(WDColorAdjustmentScope)scope;

// 对齐到矩形的某条参考线，返回已选中节点(WDBezierNode)的变形结果
- (NSSet *) alignToRect:(CGRect)rect alignment:(WDAlignment)align;

// 点中测试
- (WDPickResult *) hitResultForPoint:(CGPoint)pt viewScale:(float)viewScale snapFlags:(int)flags;
// 坐标捕捉
- (WDPickResult *) snappedPoint:(CGPoint)pt viewScale:(float)viewScale snapFlags:(int)flags;

- (void) addBlendablesToArray:(NSMutableArray *)array;  // 收集可混合颜色的填充属性对象(WDPathPainter)
- (void) addElementsToArray:(NSMutableArray *)array;    // 收集所有图形元素(WDElement)

- (WDXMLElement *) SVGElement;                          // 导出SVG元素
- (void) addSVGOpacityAndShadowAttributes:(WDXMLElement *)element;  // 向SVG元素添加不透明度和阴影属性

- (BOOL) canMaskElements;                               // 是否可用作掩码图形
- (BOOL) hasEditableText;                               // 是否有可编辑文本
- (BOOL) canPlaceText;                                  // 是否可粘帖入文本
- (BOOL) isErasable;                                    // 是否可擦除
- (BOOL) canAdjustColor;                                // 是否可调整颜色

// inspection
- (void) setValue:(id)value forProperty:(NSString *)property propertyManager:(WDPropertyManager *)propertyManager;
- (id) valueForProperty:(NSString *)property;           // 返回属性值
- (NSSet *) inspectableProperties;                      // 能从本图形吸取的属性集
- (BOOL) canInspectProperty:(NSString *)property;       // 能否从本图形吸取指定的属性值
- (void) propertyChanged:(NSString *)property;          // 通知画布本图形的某个属性已改变
- (void) propertiesChanged:(NSSet *)property;           // 通知画布本图形的某些属性已改变
- (id) pathPainterAtPoint:(CGPoint)pt;                  // 在指定点的颜色(WDColor)，用于吸管
- (BOOL) hasFill;                                       // 是否有填充对象

- (BOOL) needsToSaveGState:(float)scale;                // 是否需要调用 CGContextSaveGState
- (BOOL) needsTransparencyLayer:(float)scale;           // 是否需要调用 CGContextBeginTransparencyLayer

- (void) beginTransparencyLayer:(CGContextRef)ctx metaData:(WDRenderingMetaData)metaData;
- (void) endTransparencyLayer:(CGContextRef)ctx metaData:(WDRenderingMetaData)metaData;

@end

extern NSString *WDElementChanged;
extern NSString *WDPropertyChangedNotification;
extern NSString *WDPropertiesChangedNotification;

extern NSString *WDPropertyKey;
extern NSString *WDPropertiesKey;
extern NSString *WDTransformKey;
extern NSString *WDFillKey;
extern NSString *WDFillTransformKey;
extern NSString *WDStrokeKey;

extern NSString *WDTextKey;
extern NSString *WDFontNameKey;
extern NSString *WDFontSizeKey;
