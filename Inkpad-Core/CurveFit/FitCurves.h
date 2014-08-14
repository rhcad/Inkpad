//
//  FitCurve.h
//  Inkpad
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Copyright (c) 2014 Steve Sprang
//

#import "WDBezierSegment.h"

// 根据给定的点(digitizedPts[nPts])得到光顺曲线 segments[result], segments 预分配大小为 nPts
int FitCurve(WDBezierSegment *segments, CGPoint *digitizedPts, int nPts, double error);
