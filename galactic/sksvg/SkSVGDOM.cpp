/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "include/core/SkCanvas.h"
#include "include/core/SkFontMgr.h"
#include "include/core/SkString.h"
#include "include/private/SkTo.h"
#include "include/utils/SkParsePath.h"
#include "SkSVGAttributeParser.h"
#include "SkSVGCircle.h"
#include "SkSVGClipPath.h"
#include "SkSVGDOM.h"
#include "SkSVGDefs.h"
#include "SkSVGEllipse.h"
#include "SkSVGFeColorMatrix.h"
#include "SkSVGFeComposite.h"
#include "SkSVGFeTurbulence.h"
#include "SkSVGFilter.h"
#include "SkSVGG.h"
#include "SkSVGLine.h"
#include "SkSVGLinearGradient.h"
#include "SkSVGNode.h"
#include "SkSVGPath.h"
#include "SkSVGPattern.h"
#include "SkSVGPoly.h"
#include "SkSVGRadialGradient.h"
#include "SkSVGRect.h"
#include "SkSVGRenderContext.h"
#include "SkSVGSVG.h"
#include "SkSVGStop.h"
#include "SkSVGText.h"
#include "SkSVGTypes.h"
#include "SkSVGUse.h"
#include "SkSVGValue.h"
#include "src/core/SkTSearch.h"
#include "src/xml/SkDOM.h"

namespace {

bool SetColorAttribute(const sk_sp<SkSVGNode> &node, SkSVGAttribute attr,
		const char *stringValue) {
	SkSVGColorType color;
	SkSVGAttributeParser parser(stringValue);
	if (!parser.parseColor(&color)) {
		return false;
	}

	node->setAttribute(attr, SkSVGColorValue(color));
	return true;
}

bool SetIRIAttribute(const sk_sp<SkSVGNode> &node, SkSVGAttribute attr,
		const char *stringValue) {
	auto parseResult = SkSVGAttributeParser::parse<SkSVGIRI>(stringValue);
	if (!parseResult.isValid()) {
		return false;
	}

	node->setAttribute(attr, SkSVGStringValue(parseResult->fIRI));
	return true;
}

bool SetPathDataAttribute(const sk_sp<SkSVGNode> &node, SkSVGAttribute attr,
		const char *stringValue) {
	SkPath path;
	if (!SkParsePath::FromSVGString(stringValue, &path)) {
		return false;
	}

	node->setAttribute(attr, SkSVGPathValue(path));
	return true;
}

bool SetStringAttribute(const sk_sp<SkSVGNode> &node, SkSVGAttribute attr,
		const char *stringValue) {
	SkString str(stringValue, strlen(stringValue));
	SkSVGStringType strType = SkSVGStringType(str);
	node->setAttribute(attr, SkSVGStringValue(strType));
	return true;
}

bool SetTransformAttribute(const sk_sp<SkSVGNode> &node, SkSVGAttribute attr,
		const char *stringValue) {
	auto parseResult = SkSVGAttributeParser::parse<SkSVGTransformType>(
			stringValue);
	if (!parseResult.isValid()) {
		return false;
	}

	node->setAttribute(attr, SkSVGTransformValue(*parseResult));
	return true;
}

bool SetLengthAttribute(const sk_sp<SkSVGNode> &node, SkSVGAttribute attr,
		const char *stringValue) {
	auto parseResult = SkSVGAttributeParser::parse<SkSVGLength>(stringValue);
	if (!parseResult.isValid()) {
		return false;
	}

	node->setAttribute(attr, SkSVGLengthValue(*parseResult));
	return true;
}

bool SetNumberAttribute(const sk_sp<SkSVGNode> &node, SkSVGAttribute attr,
		const char *stringValue) {
	SkSVGNumberType number;
	SkSVGAttributeParser parser(stringValue);
	if (!parser.parseNumber(&number)) {
		return false;
	}

	node->setAttribute(attr, SkSVGNumberValue(number));
	return true;
}

bool SetViewBoxAttribute(const sk_sp<SkSVGNode> &node, SkSVGAttribute attr,
		const char *stringValue) {
	SkSVGViewBoxType viewBox;
	SkSVGAttributeParser parser(stringValue);
	if (!parser.parseViewBox(&viewBox)) {
		return false;
	}

	node->setAttribute(attr, SkSVGViewBoxValue(viewBox));
	return true;
}

bool SetStopColorAttribute(const sk_sp<SkSVGNode> &node, SkSVGAttribute attr,
		const char *stringValue) {
	SkSVGStopColor stopColor;
	SkSVGAttributeParser parser(stringValue);
	if (!parser.parseStopColor(&stopColor)) {
		return false;
	}

	node->setAttribute(attr, SkSVGStopColorValue(stopColor));
	return true;
}

bool SetObjectBoundingBoxUnitsAttribute(const sk_sp<SkSVGNode> &node,
		SkSVGAttribute attr, const char *stringValue) {
	auto parseResult = SkSVGAttributeParser::parse<SkSVGObjectBoundingBoxUnits>(
			stringValue);
	if (!parseResult.isValid()) {
		return false;
	}

	node->setAttribute(attr, SkSVGObjectBoundingBoxUnitsValue(*parseResult));
	return true;
}

bool SetPointsAttribute(const sk_sp<SkSVGNode> &node, SkSVGAttribute attr,
		const char *stringValue) {
	SkSVGPointsType points;
	SkSVGAttributeParser parser(stringValue);
	if (!parser.parsePoints(&points)) {
		return false;
	}

	node->setAttribute(attr, SkSVGPointsValue(points));
	return true;
}

bool SetPreserveAspectRatioAttribute(const sk_sp<SkSVGNode> &node,
		SkSVGAttribute attr, const char *stringValue) {
	SkSVGPreserveAspectRatio par;
	SkSVGAttributeParser parser(stringValue);
	if (!parser.parsePreserveAspectRatio(&par)) {
		return false;
	}

	node->setAttribute(attr, SkSVGPreserveAspectRatioValue(par));
	return true;
}

SkString TrimmedString(const char *first, const char *last) {
	SkASSERT(first);
	SkASSERT(last);
	SkASSERT(first <= last);

	while (first <= last && *first <= ' ') {
		first++;
	}
	while (first <= last && *last <= ' ') {
		last--;
	}

	SkASSERT(last - first + 1 >= 0);
	return SkString(first, SkTo<size_t>(last - first + 1));
}

// Breaks a "foo: bar; baz: ..." string into key:value pairs.
class StyleIterator {
public:
	StyleIterator(const char *str) :
			fPos(str) {
	}

	std::tuple<SkString, SkString> next() {
		SkString name, value;

		if (fPos) {
			const char *sep = this->nextSeparator();
			SkASSERT(*sep == ';' || *sep == '\0');

			const char *valueSep = strchr(fPos, ':');
			if (valueSep && valueSep < sep) {
				name = TrimmedString(fPos, valueSep - 1);
				value = TrimmedString(valueSep + 1, sep - 1);
			}

			fPos = *sep ? sep + 1 : nullptr;
		}

		return std::make_tuple(name, value);
	}

private:
	const char* nextSeparator() const {
		const char *sep = fPos;
		while (*sep != ';' && *sep != '\0') {
			sep++;
		}
		return sep;
	}

	const char *fPos;
};

bool set_string_attribute(const sk_sp<SkSVGNode> &node, const char *name,
		const char *value);

bool SetStyleAttributes(const sk_sp<SkSVGNode> &node, SkSVGAttribute,
		const char *stringValue) {

	SkString name, value;
	StyleIterator iter(stringValue);
	for (;;) {
		std::tie(name, value) = iter.next();
		if (name.isEmpty()) {
			break;
		}
		set_string_attribute(node, name.c_str(), value.c_str());
	}

	return true;
}

template<typename T>
struct SortedDictionaryEntry {
	const char *fKey;
	const T fValue;
};

struct AttrParseInfo {
	SkSVGAttribute fAttr;
	bool (*fSetter)(const sk_sp<SkSVGNode> &node, SkSVGAttribute attr,
			const char *stringValue);
};

SortedDictionaryEntry<AttrParseInfo> gAttributeParseInfo[] = { { "color", {
		SkSVGAttribute::kColor, SetColorAttribute } }, { "cx", {
		SkSVGAttribute::kCx, SetLengthAttribute } }, { "cy", {
		SkSVGAttribute::kCy, SetLengthAttribute } }, { "d", {
		SkSVGAttribute::kD, SetPathDataAttribute } }, { "fill-opacity", {
		SkSVGAttribute::kFillOpacity, SetNumberAttribute } }, { "filterUnits", {
		SkSVGAttribute::kFilterUnits, SetObjectBoundingBoxUnitsAttribute } },
		// focal point x & y
		{ "fx", { SkSVGAttribute::kFx, SetLengthAttribute } }, { "fy", {
				SkSVGAttribute::kFy, SetLengthAttribute } }, { "height", {
				SkSVGAttribute::kHeight, SetLengthAttribute } }, { "offset", {
				SkSVGAttribute::kOffset, SetLengthAttribute } }, { "opacity", {
				SkSVGAttribute::kOpacity, SetNumberAttribute } }, {
				"patternTransform", { SkSVGAttribute::kPatternTransform,
						SetTransformAttribute } }, { "points", {
				SkSVGAttribute::kPoints, SetPointsAttribute } }, {
				"preserveAspectRatio", { SkSVGAttribute::kPreserveAspectRatio,
						SetPreserveAspectRatioAttribute } }, { "r", {
				SkSVGAttribute::kR, SetLengthAttribute } }, { "rx", {
				SkSVGAttribute::kRx, SetLengthAttribute } }, { "ry", {
				SkSVGAttribute::kRy, SetLengthAttribute } }, { "stop-color", {
				SkSVGAttribute::kStopColor, SetStopColorAttribute } }, {
				"stop-opacity", { SkSVGAttribute::kStopOpacity,
						SetNumberAttribute } }, { "stroke-dashoffset", {
				SkSVGAttribute::kStrokeDashOffset, SetLengthAttribute } }, {
				"stroke-miterlimit", { SkSVGAttribute::kStrokeMiterLimit,
						SetNumberAttribute } }, { "stroke-opacity", {
				SkSVGAttribute::kStrokeOpacity, SetNumberAttribute } }, {
				"stroke-width", { SkSVGAttribute::kStrokeWidth,
						SetLengthAttribute } }, { "style", {
				SkSVGAttribute::kUnknown, SetStyleAttributes } }, { "text", {
				SkSVGAttribute::kText, SetStringAttribute } }, { "transform", {
				SkSVGAttribute::kTransform, SetTransformAttribute } }, {
				"viewBox", { SkSVGAttribute::kViewBox, SetViewBoxAttribute } },
		{ "width", { SkSVGAttribute::kWidth, SetLengthAttribute } }, { "x", {
				SkSVGAttribute::kX, SetLengthAttribute } }, { "x1", {
				SkSVGAttribute::kX1, SetLengthAttribute } }, { "x2", {
				SkSVGAttribute::kX2, SetLengthAttribute } }, { "xlink:href", {
				SkSVGAttribute::kHref, SetIRIAttribute } }, { "y", {
				SkSVGAttribute::kY, SetLengthAttribute } }, { "y1", {
				SkSVGAttribute::kY1, SetLengthAttribute } }, { "y2", {
				SkSVGAttribute::kY2, SetLengthAttribute } }, };

SortedDictionaryEntry<sk_sp<SkSVGNode> (*)()> gTagFactories[] = { { "a",
		[]() -> sk_sp<SkSVGNode> {
			return SkSVGG::Make();
		} }, { "circle", []() -> sk_sp<SkSVGNode> {
	return SkSVGCircle::Make();
} }, { "clipPath", []() -> sk_sp<SkSVGNode> {
	return SkSVGClipPath::Make();
} }, { "defs", []() -> sk_sp<SkSVGNode> {
	return SkSVGDefs::Make();
} }, { "ellipse", []() -> sk_sp<SkSVGNode> {
	return SkSVGEllipse::Make();
} }, { "feColorMatrix", []() -> sk_sp<SkSVGNode> {
	return SkSVGFeColorMatrix::Make();
} }, { "feComposite", []() -> sk_sp<SkSVGNode> {
	return SkSVGFeComposite::Make();
} }, { "feTurbulence", []() -> sk_sp<SkSVGNode> {
	return SkSVGFeTurbulence::Make();
} }, { "filter", []() -> sk_sp<SkSVGNode> {
	return SkSVGFilter::Make();
} }, { "g", []() -> sk_sp<SkSVGNode> {
	return SkSVGG::Make();
} }, { "line", []() -> sk_sp<SkSVGNode> {
	return SkSVGLine::Make();
} }, { "linearGradient", []() -> sk_sp<SkSVGNode> {
	return SkSVGLinearGradient::Make();
} }, { "path", []() -> sk_sp<SkSVGNode> {
	return SkSVGPath::Make();
} }, { "pattern", []() -> sk_sp<SkSVGNode> {
	return SkSVGPattern::Make();
} }, { "polygon", []() -> sk_sp<SkSVGNode> {
	return SkSVGPoly::MakePolygon();
} }, { "polyline", []() -> sk_sp<SkSVGNode> {
	return SkSVGPoly::MakePolyline();
} }, { "radialGradient", []() -> sk_sp<SkSVGNode> {
	return SkSVGRadialGradient::Make();
} }, { "rect", []() -> sk_sp<SkSVGNode> {
	return SkSVGRect::Make();
} }, { "stop", []() -> sk_sp<SkSVGNode> {
	return SkSVGStop::Make();
} }, { "svg", []() -> sk_sp<SkSVGNode> {
	return SkSVGSVG::Make();
} }, { "text", []() -> sk_sp<SkSVGNode> {
	return SkSVGText::Make();
} }, { "use", []() -> sk_sp<SkSVGNode> {
	return SkSVGUse::Make();
} }, };

struct ConstructionContext {
	ConstructionContext(SkSVGIDMapper *mapper) :
			fParent(nullptr), fIDMapper(mapper) {
	}
	ConstructionContext(const ConstructionContext &other,
			const sk_sp<SkSVGNode> &newParent) :
			fParent(newParent.get()), fIDMapper(other.fIDMapper) {
	}

	SkSVGNode *fParent;
	SkSVGIDMapper *fIDMapper;
};

bool set_string_attribute(const sk_sp<SkSVGNode> &node, const char *name,
		const char *value) {
	if (node->parseAndSetAttribute(name, value)) {
		// Handled by new code path
		return true;
	}

	const int attrIndex = SkStrSearch(&gAttributeParseInfo[0].fKey,
			SkTo<int>(SK_ARRAY_COUNT(gAttributeParseInfo)), name,
			sizeof(gAttributeParseInfo[0]));
	if (attrIndex < 0) {
#if defined(SK_VERBOSE_SVG_PARSING)
        SkDebugf("unhandled attribute: %s\n", name);
#endif
		return false;
	}

	SkASSERT(SkTo<size_t>(attrIndex) < SK_ARRAY_COUNT(gAttributeParseInfo));
	const auto &attrInfo = gAttributeParseInfo[attrIndex].fValue;
	if (!attrInfo.fSetter(node, attrInfo.fAttr, value)) {
#if defined(SK_VERBOSE_SVG_PARSING)
        SkDebugf("could not parse attribute: '%s=\"%s\"'\n", name, value);
#endif
		return false;
	}

	return true;
}

void parse_node_attributes(const SkDOM &xmlDom, const SkDOM::Node *xmlNode,
		const sk_sp<SkSVGNode> &svgNode, SkSVGIDMapper *mapper) {
	const char *name, *value;
	SkDOM::AttrIter attrIter(xmlDom, xmlNode);
	while ((name = attrIter.next(&value))) {
		// We're handling id attributes out of band for now.
		if (!strcmp(name, "id")) {
			mapper->set(SkString(value), svgNode);
			continue;
		}
		set_string_attribute(svgNode, name, value);
	}
}

sk_sp<SkSVGNode> construct_svg_node(const SkDOM &dom,
		const ConstructionContext &ctx, const SkDOM::Node *xmlNode) {
	const char *elem = dom.getName(xmlNode);
	const SkDOM::Type elemType = dom.getType(xmlNode);

	if (elemType == SkDOM::kText_Type) {
		SkASSERT(dom.countChildren(xmlNode) == 0);
		// TODO: add type conversion helper to SkSVGNode
		if (ctx.fParent->tag() == SkSVGTag::kText) {
			static_cast<SkSVGText*>(ctx.fParent)->setText(
					SkString(dom.getName(xmlNode)));
		}
		return nullptr;
	}

	SkASSERT(elemType == SkDOM::kElement_Type);

	const int tagIndex = SkStrSearch(&gTagFactories[0].fKey,
			SkTo<int>(SK_ARRAY_COUNT(gTagFactories)), elem,
			sizeof(gTagFactories[0]));
	if (tagIndex < 0) {
#if defined(SK_VERBOSE_SVG_PARSING)
        SkDebugf("unhandled element: <%s>\n", elem);
#endif
		return nullptr;
	}

	SkASSERT(SkTo<size_t>(tagIndex) < SK_ARRAY_COUNT(gTagFactories));
	sk_sp<SkSVGNode> node = gTagFactories[tagIndex].fValue();
	parse_node_attributes(dom, xmlNode, node, ctx.fIDMapper);

	ConstructionContext localCtx(ctx, node);
	for (auto *child = dom.getFirstChild(xmlNode, nullptr); child;
			child = dom.getNextSibling(child)) {
		sk_sp<SkSVGNode> childNode = construct_svg_node(dom, localCtx, child);
		if (childNode) {
			node->appendChild(std::move(childNode));
		}
	}

	return node;
}

} // anonymous namespace

SkSVGDOM::Builder& SkSVGDOM::Builder::setFontManager(sk_sp<SkFontMgr> fmgr) {
	fFontMgr = std::move(fmgr);
	return *this;
}

sk_sp<SkSVGDOM> SkSVGDOM::Builder::make(SkStream &str) const {
	SkDOM xmlDom;
	if (!xmlDom.build(str)) {
		return nullptr;
	}

	SkSVGIDMapper mapper;
	ConstructionContext ctx(&mapper);

	auto root = construct_svg_node(xmlDom, ctx, xmlDom.getRootNode());
	if (!root || root->tag() != SkSVGTag::kSvg) {
		return nullptr;
	}

	return sk_sp<SkSVGDOM>(
			new SkSVGDOM(
					sk_sp<SkSVGSVG>(static_cast<SkSVGSVG*>(root.release())),
					std::move(fFontMgr), std::move(mapper)));
}

SkSVGDOM::SkSVGDOM(sk_sp<SkSVGSVG> root, sk_sp<SkFontMgr> fmgr,
		SkSVGIDMapper &&mapper) :
		fRoot(std::move(root)), fFontMgr(std::move(fmgr)), fIDMapper(
				std::move(mapper)), fContainerSize(
				fRoot->intrinsicSize(SkSVGLengthContext(SkSize::Make(0, 0)))) {
}

void SkSVGDOM::render(SkCanvas *canvas) const {
	if (fRoot) {
		SkSVGLengthContext lctx(fContainerSize);
		SkSVGPresentationContext pctx;
		fRoot->render(
				SkSVGRenderContext(canvas, fFontMgr, fIDMapper, lctx, pctx,
						nullptr));
	}
}

bool SkSVGDOM::objectBoundingBox(SkCanvas *canvas, const char *id, SkRect &r) {
	bool bret=false;

	SkString idStr(id);
	auto n = this->fIDMapper.find(idStr);
	if (n) {
		SkSVGLengthContext lctx(fContainerSize);
		SkSVGPresentationContext pctx;
		SkPath pth = n->get()->asPath(SkSVGRenderContext(canvas, fFontMgr, fIDMapper, lctx, pctx,
						nullptr));
		r=pth.getBounds();

		bret=true;
	}
	return bret;
}

const SkSize& SkSVGDOM::containerSize() const {
	return fContainerSize;
}

void SkSVGDOM::setContainerSize(const SkSize &containerSize) {
	// TODO: inval
	fContainerSize = containerSize;
}

sk_sp<SkSVGNode>* SkSVGDOM::findNodeById(const char *id) {
	SkString idStr(id);
	return this->fIDMapper.find(idStr);
}

// TODO(fuego): move this to SkSVGNode or its own CU.
bool SkSVGNode::setAttribute(const char *attributeName,
		const char *attributeValue) {
	return set_string_attribute(sk_ref_sp(this), attributeName, attributeValue);
}
