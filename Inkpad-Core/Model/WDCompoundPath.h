//
//  WDCompoundPath.h
//  Inkpad
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Copyright (c) 2010-2013 Steve Sprang
//

#import <Foundation/Foundation.h>
#import "WDAbstractPath.h"

@class WDPath;

// 复合路径图形类
@interface WDCompoundPath : WDAbstractPath <NSCoding, NSCopying> {
    CGMutablePathRef    pathRef_;
    CGMutablePathRef    strokePathRef_;
}

@property (nonatomic, strong) NSMutableArray *subpaths; // 子路径(WDPath)序列

- (void) invalidatePath;                                // 清除缓存的路径对象，待重新缓存路径
- (void) addSubpath:(WDPath *)path;                     // 追加子路径
- (void) removeSubpath:(WDPath *)path;                  // 移除子路径

- (void) setSubpathsQuiet:(NSMutableArray *)subpaths;   // 重新设置子路径序列，不触发通知

@end

