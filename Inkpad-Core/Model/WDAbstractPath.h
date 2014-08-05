//
//  WDAbstractPath.h
//  Inkpad
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Copyright (c) 2011-2013 Steve Sprang
//

#import <Foundation/Foundation.h>
#import "WDStylable.h"

@protocol WDPathPainter;

@class WDFillTransform;
@class WDStrokeStyle;

// the fill rule can be passed directly to functions that take a bool indicating EO fill
typedef enum {
    kWDNonZeroWindingFillRule   = 0,        // 非零填充
    kWDEvenOddFillRule          = 1         // 奇偶填充
} WDFillRule;

// 具有矢量路径的图形元素基类
@interface WDAbstractPath : WDStylable <NSCoding, NSCopying>

@property (nonatomic, assign) WDFillRule fillRule;          // 填充规则
@property (nonatomic, readonly) CGPathRef pathRef;          // 缓存的路径对象
@property (nonatomic, readonly) CGPathRef strokePathRef;    // 有箭头等描边效果的路径对象

+ (WDAbstractPath *) pathWithCGPathRef:(CGPathRef)pathRef;  // 根据路径对象构造路径图形元素

- (NSUInteger) subpathCount;                                // 子路径个数, >=1
- (NSString *) nodeSVGRepresentation;                       // 路径的SVG片段，与描边效果无关
- (void) addSVGArrowheadsToGroup:(WDXMLElement *)group;     // 向SVG组元素添加箭头形状

- (BOOL) canOutlineStroke;                                  // 能否以轮廓模式绘制
- (WDAbstractPath *) outlineStroke;                         // 构造轮廓图形

// subclasses can override this to enhance the default outline
- (void) addElementsToOutlinedStroke:(CGMutablePathRef)pathRef; // 向路径对象添加箭头形状

- (NSArray *) erase:(WDAbstractPath *)erasePath;            // 返回橡皮擦除剩余的图形元素

- (void) simplify;                                          // 去掉共线点，用于 outlineStroke
- (void) flatten;                                           // 曲线离散为折线

- (WDAbstractPath *) pathByFlatteningPath;                  // 返回离散后的折线，不改变本图形

// so subclasses can override
- (void) renderStrokeInContext:(CGContextRef)ctx;           // 使用CGContext描边

@end

