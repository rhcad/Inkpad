//
//  WDBezierSegment.h
//  Inkpad
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//  Copyright (c) 2009-2013 Steve Sprang
//

#import <Foundation/Foundation.h>

extern const float kDefaultFlatness;    // 缺省平滑度，像素单位

@class WDBezierNode;

// 三次Bezier段，4个点
typedef struct {
    CGPoint a_, out_, in_, b_;          // 起点，起点的出向控制点，终点的入向控制点，终点
} WDBezierSegment;                      // a_=out_,in_=b_: 直线段

// 由两个端点节点构造一个三次Bezier曲线段，忽略起点的入向控制点、终点的出向控制点
WDBezierSegment WDBezierSegmentMake(WDBezierNode *a, WDBezierNode *b);

// 是否是退化(无效)的曲线段
BOOL WDBezierSegmentIsDegenerate(WDBezierSegment seg);

// 曲线段是否与矩形相交
BOOL WDBezierSegmentIntersectsRect(WDBezierSegment seg, CGRect rect);

// 直线段是否与矩形相交
BOOL WDLineInRect(CGPoint a, CGPoint b, CGRect test);

// 曲线段是否是直的，即两个控制点在起点和终点的直线上
BOOL WDBezierSegmentIsStraight(WDBezierSegment segment);

// 曲线段在给定容差下是否是平的
BOOL WDBezierSegmentIsFlat(WDBezierSegment seg, float tolerance);

// 将曲线段离散为折线
void WDBezierSegmentFlatten(WDBezierSegment seg, CGPoint **vertices, NSUInteger *size, NSUInteger *index);

// 在0.5参数处平分为两个Bezier段
CGPoint WDBezierSegmentSplit(WDBezierSegment seg, WDBezierSegment *L, WDBezierSegment *R);

// 在指定的参数(t=0..1)处平分为两个Bezier段
CGPoint WDBezierSegmentSplitAtT(WDBezierSegment seg, WDBezierSegment *L, WDBezierSegment *R, float t);

// 计算在指定的参数(t=0..1)处的曲线切线点，可用于沿线文本
CGPoint WDBezierSegmentTangetAtT(WDBezierSegment seg, float t);

// 计算外部点到曲线段的最近点及其曲线参数
BOOL WDBezierSegmentFindPointOnSegment(WDBezierSegment seg, CGPoint testPoint, float tolerance, CGPoint *nearestPoint, float *split);

// 计算曲线段的准确包络框
CGRect WDBezierSegmentBounds(WDBezierSegment seg);

// 仅根据曲线段的四点计算包络框
CGRect WDBezierSegmentGetSimpleBounds(WDBezierSegment seg);

// 计算在指定的参数(t=0..1)处的曲率
float WDBezierSegmentCurvatureAtT(WDBezierSegment seg, float t);

// 计算曲线段上指定弧长处的线上点、切线点和曲率
CGPoint WDBezierSegmentPointAndTangentAtDistance(WDBezierSegment seg, float distance, CGPoint *tangent, float *curvature);

// 计算曲线段的弧长
float WDBezierSegmentLength(WDBezierSegment seg);

// 计算外部点到曲线段的最近距离(error)、最近点的弧长(distance)，返回最近点
CGPoint WDBezierSegmentGetClosestPoint(WDBezierSegment seg, CGPoint test, float *error, float *distance);

// 两个曲线段拼接后是否形成尖点（不能光滑过渡），假定这两段已相接
BOOL WDBezierSegmentsFormCorner(WDBezierSegment a, WDBezierSegment b);

// 计算曲线段与给定的直线段相交处的参数
BOOL WDBezierSegmentGetIntersection(WDBezierSegment seg, CGPoint a, CGPoint b, float *tIntersect);

// 计算曲线段的终点切线角度，弧度
float WDBezierSegmentOutAngle(WDBezierSegment seg);

// 计算在指定参数(t=0..1)处的曲线点
CGPoint WDBezierSegmentCalculatePointAtT(WDBezierSegment seg, float t);

// 计算外部点到曲线段相距指定距离的曲线点和参数
BOOL WDBezierSegmentPointDistantFromPoint(WDBezierSegment segment, float distance, CGPoint pt, CGPoint *result, float *t);
