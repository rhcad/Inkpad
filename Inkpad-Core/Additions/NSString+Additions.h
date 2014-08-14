//
//  NSString+Additions.h
//  Inkpad
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Copyright (c) 2011-2013 Steve Sprang
//

#import <CoreText/CoreText.h>
#import <Foundation/Foundation.h>

@interface NSString (WDAdditions)

// 将非空白XML转义字符还原为普通文本
- (NSString *) stringByUnescapingEntities;

// 对普通文本进行非空白XML实体字符转义
- (NSString *) stringByEscapingEntities;

// 对普通文本进行XML实体字符(含空白字符)转义
- (NSString *) stringByEscapingEntitiesAndWhitespace;

// 计算当前文本在指定的字体和限制宽高下的实际显示宽高
- (CGSize) sizeWithCTFont:(CTFontRef)fontRef constrainedToSize:(CGSize)constraint;

@end
