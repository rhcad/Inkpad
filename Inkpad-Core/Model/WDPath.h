//
//  WDPath.h
//  Inkpad
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Copyright (c) 2009-2013 Steve Sprang
//

#import <UIKit/UIKit.h>
#import "WDAbstractPath.h"
#import "WDPickResult.h"

@class WDBezierNode;
@class WDColor;
@class WDCompoundPath;
@class WDFillTransform;

// 可指定线段箭头形状的路径图形元素类
@interface WDPath : WDAbstractPath <NSCoding, NSCopying> {
    NSMutableArray      *nodes_;
    BOOL                closed_;
    BOOL                reversed_;
    
    CGMutablePathRef    pathRef_;
    CGMutablePathRef    strokePathRef_;
    CGRect              bounds_;
    BOOL                boundsDirty_;
    
    // arrowheads
    CGPoint             arrowStartAttachment_;
    float               arrowStartAngle_;
    BOOL                canFitStartArrow_;
    CGPoint             arrowEndAttachment_;
    float               arrowEndAngle_;
    BOOL                canFitEndArrow_;
    
    // to simplify rendering
    NSMutableArray      *displayNodes_;
    UIColor             *displayColor_;
    BOOL                displayClosed_;
}

@property (nonatomic, assign) BOOL closed;      // 是否闭合
@property (nonatomic, assign) BOOL reversed;    // 是否反向
@property (nonatomic, strong) NSMutableArray *nodes;    // 路径节点(WDBezierNode)序列
@property (weak, nonatomic, readonly) NSMutableArray *reversedNodes;    // 反向的路径节点序列
@property (nonatomic, weak) WDCompoundPath *superpath;  // 上级复合路径图形，如果有

// to simplify rendering
@property (nonatomic, strong) NSMutableArray *displayNodes; // 临时路径节点，用于动态变形显示
@property (nonatomic, strong) UIColor *displayColor;    // 临时显示颜色
@property (nonatomic, assign) BOOL displayClosed;       // 动态变形显示用的临时闭合标志

+ (WDPath *) pathWithRect:(CGRect)rect;                 // 构造一个矩形路径
+ (WDPath *) pathWithRoundedRect:(CGRect)rect cornerRadius:(float)radius;   // 构造一个圆角矩形路径
+ (WDPath *) pathWithOvalInRect:(CGRect)rect;           // 构造一个椭圆路径
+ (WDPath *) pathWithStart:(CGPoint)start end:(CGPoint)end; // 构造一个直线段路径

- (id) initWithRect:(CGRect)rect;                       // 初始化为一个矩形路径
- (id) initWithRoundedRect:(CGRect)rect cornerRadius:(float)radius; // 初始化为一个圆角矩形路径
- (id) initWithOvalInRect:(CGRect)rect;                 // 初始化为一个椭圆路径
- (id) initWithStart:(CGPoint)start end:(CGPoint)end;   // 初始化为一个直线段路径
- (id) initWithNode:(WDBezierNode *)node;               // 给定起点初始化

- (void) invalidatePath;                                // 清除缓存的路径对象，待重新缓存路径
- (void) reversePathDirection;                          // 路径反向

- (BOOL) canDeleteAnchors;                              // 返回选中的路径节点能否删除
- (void) deleteAnchor:(WDBezierNode *)node;             // 删除指定的路径节点
- (NSArray *) selectedNodes;                            // 返回选中的路径节点(WDBezierNode)
- (BOOL) anyNodesSelected;                              // 是否有选中的路径节点
- (BOOL) allNodesSelected;                              // 是否选择了所有路径节点

- (NSDictionary *) splitAtNode:(WDBezierNode *)node;    // 从指定的节点剪断，未闭合时可能变为本图形和一个新路径图形
- (NSDictionary *) splitAtPoint:(CGPoint)pt viewScale:(float)viewScale; // 从任意位置剪断，自动插入节点
- (WDBezierNode *) addAnchorAtPoint:(CGPoint)pt viewScale:(float)viewScale; // 插入一个路径节点
- (void) addAnchors;                                    // 在所有曲线段的中点处添加锚点
- (void) appendPath:(WDPath *)path;                     // 拼接曲线

- (void) replaceFirstNodeWithNode:(WDBezierNode *)node; // 替换起始节点
- (void) replaceLastNodeWithNode:(WDBezierNode *)node;  // 替换末尾节点
- (BOOL) addNode:(WDBezierNode *)node scale:(float)scale;   // 添加一个节点，在起始节点附近添加则闭合
- (void) addNode:(WDBezierNode *)node;                  // 添加一个节点

- (WDBezierNode *) firstNode;                           // 起始节点
- (WDBezierNode *) lastNode;                            // 末尾节点
- (NSMutableArray *) reversedNodes;                     // 反向的路径节点序列
- (NSSet *) nodesInRect:(CGRect)rect;                   // 返回矩形框内的节点集

- (WDBezierNode *) convertNode:(WDBezierNode *)node whichPoint:(WDPickResultType)whichPoint;    // 改变节点类型

- (CGRect) controlBounds;                               // 路径锚点包络框
- (void) computeBounds;                                 // 计算路径包络框

- (NSString *) nodeSVGRepresentation;                   // 返回SVG路径表达式，即M开头的串

- (void) setClosedQuiet:(BOOL)closed;                   // 设置是否闭合，不触发通知

- (WDStrokeStyle *) effectiveStrokeStyle;               // 返回描边属性对象，优先取上级组合图形的

@end

