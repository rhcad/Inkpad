//
//  UIImage+Additions.h
//  Inkpad
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Copyright (c) 2008-2013 Steve Sprang
//

#import <UIKit/UIKit.h>

@interface UIImage (WDAdditions)

// 充满显示到指定的矩形范围，居中显示，可以一个方向被截掉(不留空白)显示
- (void) drawToFillRect:(CGRect)bounds;

// 旋转图像，1：左转90度，2：转180度，3：右转90度
- (UIImage *) rotatedImage:(int)rotation;

// 缩小图像使其宽高不超过指定值，宽高太小则返回原图
- (UIImage *) downsampleWithMaxDimension:(float)constraint;

// 缩小图像使其面积不超过指定值，太小则返回原图
- (UIImage *) downsampleWithMaxArea:(float)constraint;

// 转换为指定的JPEG质量因子(0到1)的图像
- (UIImage *) JPEGify:(float)compressionFactor;

@end
