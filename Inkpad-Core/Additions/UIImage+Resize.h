// UIImage+Resize.h
// Created by Trevor Harmon on 8/5/09.
// Free for personal or commercial use, with or without modification.
// No warranty is expressed or implied.

#import <UIKit/UIKit.h>

// Extends the UIImage class to support resizing/cropping
@interface UIImage (Resize)

// 缩放图像到指定的大小，图像方向为 UIImageOrientationUp
- (UIImage *)resizedImage:(CGSize)newSize
     interpolationQuality:(CGInterpolationQuality)quality;

// 保持比例缩放图像到指定的大小，图像方向为 UIImageOrientationUp
// contentMode: UIViewContentModeScaleAspectFill or UIViewContentModeScaleAspectFit
- (UIImage *)resizedImageWithContentMode:(UIViewContentMode)contentMode
                                  bounds:(CGSize)bounds
                    interpolationQuality:(CGInterpolationQuality)quality;

@end
