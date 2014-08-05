//
//  WDGroup.h
//  Inkpad
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Copyright (c) 2010-2013 Steve Sprang
//

#import <Foundation/Foundation.h>
#import "WDElement.h"

// 成组图形元素
@interface WDGroup : WDElement <NSCoding, NSCopying>

@property (nonatomic, strong) NSMutableArray *elements; // 子图形(WDElement)

@end

