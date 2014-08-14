//
//  UIColor+Additions.h
//  Inkpad
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Copyright (c) 2008-2013 Steve Sprang
//

#import <UIKit/UIKit.h>

@interface UIColor (WDAdditions)

// 返回随机颜色. includeAlpha为真时取0.5到1.0之间的透明度，否则透明度为1
+ (UIColor *) randomColor:(BOOL)includeAlpha;

// 返回随机色相值的HSB颜色，饱和度和亮度为固定值
+ (UIColor *) saturatedRandomColor;

// 应用颜色到OpenGL上下文中
- (void) openGLSet;

@end
