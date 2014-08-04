//
//  WDBezierNode.h
//  Inkpad
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Copyright (c) 2010-2013 Steve Sprang
//

#import <Foundation/Foundation.h>
#import "WDPickResult.h"

#if !TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

// 曲线段的控制手柄对称关系
typedef enum {
    WDReflect,                      // 两控制手柄关于锚点对称
    WDIndependent,                  // 两控制手柄可独立移动
    WDReflectIndependent            // 两控制手柄在锚点两边，三点共线
} WDBezierNodeReflectionMode;

// 锚点渲染类型
typedef enum {
    kWDBezierNodeRenderOpen,
    kWDBezierNodeRenderClosed,
    kWDBezierNodeRenderSelected
} WDBezierNodeRenderMode;

// 三次Bezier节点
@interface WDBezierNode : NSObject <NSCoding, NSCopying> {
    CGPoint     inPoint_;
    CGPoint     anchorPoint_;
    CGPoint     outPoint_;
    BOOL        selected_;
}

@property (nonatomic, readonly) CGPoint inPoint;        // 入向手柄
@property (nonatomic, readonly) CGPoint anchorPoint;    // 锚点
@property (nonatomic, readonly) CGPoint outPoint;       // 出向手柄

@property (nonatomic, readonly) WDBezierNodeReflectionMode reflectionMode;  // 手柄对称关系

@property (nonatomic, readonly) BOOL hasInPoint;        // 是否有入向手柄，没有时入向曲线段在终端只有位置约束
@property (nonatomic, readonly) BOOL hasOutPoint;       // 是否有出向手柄，没有时出向曲线段在起端只有位置约束
@property (nonatomic, readonly) BOOL isCorner;          // 是否是尖角，即不光滑过渡

// some helper state... not strictly part of the model, but makes many operations simpler
@property (nonatomic, assign) BOOL selected;            // 是否选中，临时状态

// 构造一个没有控制手柄的独立点，可作为绘图中图形的起始状态
+ (WDBezierNode *) bezierNodeWithAnchorPoint:(CGPoint)pt;

// 给定出入控制点和锚点构造一个曲线段
+ (WDBezierNode *) bezierNodeWithInPoint:(CGPoint)inPoint anchorPoint:(CGPoint)pt outPoint:(CGPoint)outPoint;

- (id) initWithAnchorPoint:(CGPoint)pt;
- (id) initWithInPoint:(CGPoint)inPoint anchorPoint:(CGPoint)pt outPoint:(CGPoint)outPoint;

- (WDBezierNode *) transform:(CGAffineTransform)transform;  // 返回几何变形后的新对象
- (WDBezierNode *) chopHandles;                             // 锚点对象
- (WDBezierNode *) chopOutHandle;                           // 去掉出向手柄的对象
- (WDBezierNode *) chopInHandle;                            // 去掉入向手柄的对象

// 返回指定入向手柄的对称位置的新对象，用于曲线闭合时计算首段的入向手柄位置
- (WDBezierNode *) setInPoint:(CGPoint)pt reflectionMode:(WDBezierNodeReflectionMode)reflectionMode;

// 返回移动某个手柄(kWDInPoint 或 kWDOutPoint)到指定位置后的新对象
- (WDBezierNode *) moveControlHandle:(WDPickResultType)pointToTransform toPoint:(CGPoint)pt reflectionMode:(WDBezierNodeReflectionMode)reflectionMode;

- (WDBezierNode *) flippedNode;                             // 方向后的对象

- (void) getInPoint:(CGPoint *)inPoint anchorPoint:(CGPoint *)anchorPoint
           outPoint:(CGPoint *)outPoint selected:(BOOL *)selected;  // 获取各点

@end

@interface WDBezierNode (GLRendering)
// 以GL方式绘制控制点、锚点及其连线
- (void) drawGLWithViewTransform:(CGAffineTransform)transform color:(UIColor *)color mode:(WDBezierNodeRenderMode)mode;
@end

