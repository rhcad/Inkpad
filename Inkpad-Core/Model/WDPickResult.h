//
//  WDPickResult.h
//  Inkpad
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Copyright (c) 2010-2013 Steve Sprang
//

#import <Foundation/Foundation.h>

// 捕捉开关，用于选择图形或坐标捕捉
typedef enum {
    kWDSnapNodes            = 1 << 0,   // 允许吸附到点
    kWDSnapEdges            = 1 << 1,   // 允许吸附到边
    kWDSnapGrid             = 1 << 2,   // 允许吸附到网格
    kWDSnapFills            = 1 << 3,   // 允许在路径内部捕捉
    kWDSnapLocked           = 1 << 4,   // 允许捕捉锁定的图形
    kWDSnapSelectedOnly     = 1 << 5,   // 仅在当前选中的图形(含其上级图形)内捕捉
    kWDSnapSubelement       = 1 << 6,   // 允许穿透捕捉
    kWDSnapDynamicGuides    = 1 << 7    // 使用智能参考线定位坐标
} WDPickFlag;

// 点选结果类型
typedef enum {
    kWDEther,                           // 没有选中
    kWDInPoint,                         // 左控制手柄，位于锚点进入方向
    kWDAnchorPoint,                     // 锚点
    kWDOutPoint,                        // 右控制手柄，位于锚点出去方向
    kWDObjectFill,                      // 捕捉到路径内部
    kWDEdge,                            // 捕捉到边
    kWDLeftTextKnob,                    // 文本框左控制手柄
    kWDRightTextKnob,                   // 文本框右控制手柄
    kWDFillStartPoint,                  // 渐变开始控制手柄
    kWDFillEndPoint,                    // 渐变结束控制手柄
    kWDRectCorner,                      // 矩形角点
    kWDRectEdge,                        // 矩形的边
    kWDTextPathStartKnob                // 沿线文本的起始控制手柄，位于起始线顶端
} WDPickResultType;

// 点选结果的锚点位置类型
typedef enum {
    kWDMiddleNode,                      // 中间锚点
    kWDFirstNode,                       // 首锚点
    kWDLastNode                         // 末锚点
} WDPickNodePosition;

extern const float kNodeSelectionTolerance; // 选择容差，捕捉框宽度

@class WDElement;
@class WDBezierNode;

// 点选结果，用于选择图形或坐标捕捉
@interface WDPickResult : NSObject

@property (nonatomic, weak) WDElement *element;         // the element in which the tap occurred
@property (nonatomic, weak) WDBezierNode *node;         // the node hit by the tap -- could be nil
@property (nonatomic, assign) CGPoint snappedPoint;     // 捕捉到的坐标, snapped 为真时有效
@property (nonatomic, assign) WDPickResultType type;    // 点选结果类型
@property (nonatomic, assign) NSUInteger nodePosition;  // WDPickNodePosition, type 为 kWDAnchorPoint 时有效
@property (nonatomic, readonly) BOOL snapped;           // 是否捕捉到坐标

+ (WDPickResult *) pickResult;                          // 构造一个空的结果

@end
