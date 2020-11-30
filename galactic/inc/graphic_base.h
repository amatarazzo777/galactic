#ifndef GAME_SYSTEM_BASE_DEFINED
#define GAME_SYSTEM_BASE_DEFINED

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "glad/glad.h"

#define SK_GL

#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/GrTypes.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkColor.h"
#include "include/core/SkSurface.h"
#include "include/core/SkImage.h"
#include "include/core/SkPictureRecorder.h"

#include "src/core/SkReadBuffer.h"
#include "src/core/SkWriteBuffer.h"

#include "include/core/SkPicture.h"
#include "include/core/SkRect.h"

#include "include/core/SkData.h"
#include "include/core/SkTextBlob.h"
#include "include/effects/SkDiscretePathEffect.h"
#include "include/effects/SkGradientShader.h"

#include "include/utils/SkParse.h"
#include "include/utils/SkParsePath.h"

#include "sksvg/include/SkSVGRenderContext.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkStream.h"
#include "sksvg/include/SkSVGNode.h"
#include "sksvg/include/SkSVGDOM.h"
#include "samplecode/Sample.h"
#include "src/core/SkOSFile.h"
#include "src/utils/SkOSPath.h"
#include "src/xml/SkDOM.h"

#endif
