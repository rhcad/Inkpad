//
//  NSArray+Additions.h
//  Inkpad
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Copyright (c) 2011-2013 Steve Sprang
//

#import <Foundation/Foundation.h>

@interface NSArray (WDAdditions)

// 返回对每个元素进行映射转换后的新数组
- (NSArray *) map:(id (^)(id obj))fn;

// 返回符合条件的元素所组成的子数组
- (NSArray *) filter:(BOOL (^)(id obj))predicate;

@end
