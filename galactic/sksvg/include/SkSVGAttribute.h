/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSVGAttribute_DEFINED
#define SkSVGAttribute_DEFINED

#include "SkSVGTypes.h"
#include "src/core/SkTLazy.h"

class SkSVGRenderContext;

enum class SkSVGAttribute {
    kClipRule,
    kColor,
    kCx, // <circle>, <ellipse>, <radialGradient>: center x position
    kCy, // <circle>, <ellipse>, <radialGradient>: center y position
    kD,
    kFill,
    kFillOpacity,
    kFillRule,
    kFilter,
    kFilterUnits,
    kFontFamily,
    kFontSize,
    kFontStyle,
    kFontWeight,
    kFx, // <radialGradient>: focal point x position
    kFy, // <radialGradient>: focal point y position
    kGradientUnits,
    kGradientTransform,
    kHeight,
    kHref,
    kOffset,
    kOpacity,
    kPatternTransform,
    kPoints,
    kPreserveAspectRatio,
    kR,  // <circle>, <radialGradient>: radius
    kRx, // <ellipse>,<rect>: horizontal (corner) radius
    kRy, // <ellipse>,<rect>: vertical (corner) radius
    kSpreadMethod,
    kStopColor,
    kStopOpacity,
    kStroke,
    kStrokeDashArray,
    kStrokeDashOffset,
    kStrokeOpacity,
    kStrokeLineCap,
    kStrokeLineJoin,
    kStrokeMiterLimit,
    kStrokeWidth,
    kTransform,
    kText,
    kTextAnchor,
    kViewBox,
    kVisibility,
    kWidth,
    kX,
    kX1, // <line>: first endpoint x
    kX2, // <line>: second endpoint x
    kY,
    kY1, // <line>: first endpoint y
    kY2, // <line>: second endpoint y

    kUnknown,
};

struct SkSVGPresentationAttributes {
    static SkSVGPresentationAttributes MakeInitial();

    // TODO: SkSVGProperty adds an extra ptr per attribute; refactor to reduce overhead.

    SkSVGProperty<SkSVGPaint     , true> fFill;
    SkSVGProperty<SkSVGNumberType, true> fFillOpacity;
    SkSVGProperty<SkSVGFillRule  , true> fFillRule;
    SkSVGProperty<SkSVGFillRule  , true> fClipRule;

    SkSVGProperty<SkSVGPaint     , true> fStroke;
    SkSVGProperty<SkSVGDashArray , true> fStrokeDashArray;
    SkSVGProperty<SkSVGLength    , true> fStrokeDashOffset;
    SkSVGProperty<SkSVGLineCap   , true> fStrokeLineCap;
    SkSVGProperty<SkSVGLineJoin  , true> fStrokeLineJoin;
    SkSVGProperty<SkSVGNumberType, true> fStrokeMiterLimit;
    SkSVGProperty<SkSVGNumberType, true> fStrokeOpacity;
    SkSVGProperty<SkSVGLength    , true> fStrokeWidth;

    SkSVGProperty<SkSVGVisibility, true> fVisibility;

    SkSVGProperty<SkSVGColorType , true> fColor;

    SkSVGProperty<SkSVGFontFamily, true> fFontFamily;
    SkSVGProperty<SkSVGFontStyle , true> fFontStyle;
    SkSVGProperty<SkSVGFontSize  , true> fFontSize;
    SkSVGProperty<SkSVGFontWeight, true> fFontWeight;
    SkSVGProperty<SkSVGTextAnchor, true> fTextAnchor;

    // TODO(tdenniston): add SkSVGStopColor

    // uninherited
    SkSVGProperty<SkSVGNumberType, false> fOpacity;
    SkSVGProperty<SkSVGClip      , false> fClipPath;
    SkSVGProperty<SkSVGFilterType, false> fFilter;
};

#endif // SkSVGAttribute_DEFINED
