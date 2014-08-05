//
//  WDStylable.h
//  Inkpad
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Copyright (c) 2011-2013 Steve Sprang
//

#import <Foundation/Foundation.h>
#import "WDElement.h"

@class WDFillTransform;
@class WDStrokeStyle;
@class WDXMLElement;

@protocol WDPathPainter;

// 可描边和填充的图形元素基类
@interface WDStylable : WDElement <NSCoding, NSCopying>

@property (nonatomic, strong) id<WDPathPainter> fill;           // 填充属性对象，initialFill非空时fill为临时属性
@property (nonatomic, strong) WDFillTransform *fillTransform;   // 渐变填充对象
@property (nonatomic, strong) WDStrokeStyle *strokeStyle;       // 描边属性对象，initialStroke非空时此为临时属性
@property (nonatomic, strong) NSArray *maskedElements;          // 掩码图形数组

// to simplify rendering
@property (nonatomic, strong) WDFillTransform *displayFillTransform;    // 临时渐变填充对象

// cache for color adjustments
@property (nonatomic, strong) id initialFill;                   // 动态调整前的填充属性对象
@property (nonatomic, strong) WDStrokeStyle *initialStroke;     // 动态调整前的描边属性对象

@property (nonatomic, readonly) BOOL isMasking;                 // 是否已用作掩码图形

// 假定描边属性从from变为to，返回有哪些属性将会改变
- (NSSet *) changedStrokePropertiesFrom:(WDStrokeStyle *)from to:(WDStrokeStyle *)to;
- (void) strokeStyleChanged;                                    // 描边属性改变的后处理

- (void) takeStylePropertiesFrom:(WDStylable *)obj;             // 复制描边和填充属性

- (void) addSVGFillAndStrokeAttributes:(WDXMLElement *)element; // 向SVG元素添加描边和填充属性
- (void) addSVGFillAttributes:(WDXMLElement *)element;          // 向SVG元素添加填充属性

- (void) setFillQuiet:(id<WDPathPainter>)fill;                  // 设置填充属性，不触发改变通知
- (void) setStrokeStyleQuiet:(WDStrokeStyle *)strokeStyle;      // 设置描边属性，不触发改变通知

@end
