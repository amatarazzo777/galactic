project('galactic space', 'c', 'cpp',
    default_options : ['c_std=c17', 'cpp_std=c++17'], 
    version :'1.0.0')
    
   
cpp = meson.get_compiler('cpp')
dl_dep = cpp.find_library('dl', required : true)
glfw_dep = cpp.find_library('glfw', required : true)
stdcpp_dep = cpp.find_library('stdc++', required : true)
expat_dep = dependency('expat')
skia_dep = dependency('skia')
thread_dep = dependency('threads') 

inc = include_directories('inc','sksvg/include')

source_files = [
            'main.cpp',
            'game_window.cpp',
            'sprite.cpp', 
            'space_sprites.cpp',
            'gaming_sprites.cpp',
            'glad.c']

sksvg_source_files = ['sksvg/SkSVGAttribute.cpp',
'sksvg/SkSVGAttributeParser.cpp',
'sksvg/SkSVGCircle.cpp',
'sksvg/SkSVGClipPath.cpp',
'sksvg/SkSVGContainer.cpp',
'sksvg/SkSVGDOM.cpp',
'sksvg/SkSVGEllipse.cpp',
'sksvg/SkSVGFeColorMatrix.cpp',
'sksvg/SkSVGFeComposite.cpp',
'sksvg/SkSVGFe.cpp',
'sksvg/SkSVGFeTurbulence.cpp',
'sksvg/SkSVGFilterContext.cpp',
'sksvg/SkSVGFilter.cpp',
'sksvg/SkSVGGradient.cpp',
'sksvg/SkSVGLinearGradient.cpp',
'sksvg/SkSVGLine.cpp',
'sksvg/SkSVGNode.cpp',
'sksvg/SkSVGPath.cpp',
'sksvg/SkSVGPattern.cpp',
'sksvg/SkSVGPoly.cpp',
'sksvg/SkSVGRadialGradient.cpp',
'sksvg/SkSVGRect.cpp',
'sksvg/SkSVGRenderContext.cpp',
'sksvg/SkSVGShape.cpp',
'sksvg/SkSVGStop.cpp',
'sksvg/SkSVGSVG.cpp',
'sksvg/SkSVGText.cpp',
'sksvg/SkSVGTransformableNode.cpp',
'sksvg/SkSVGUse.cpp',
'sksvg/SkTSearch.cpp',
'sksvg/SkArenaAlloc.cpp',
'xml/SkDOM.cpp',
'xml/SkXMLParser.cpp',
'xml/SkXMLWriter.cpp'

]

  
executable('galactic', 
		[source_files,sksvg_source_files] , 
		dependencies : [skia_dep, dl_dep, glfw_dep, stdcpp_dep, expat_dep, thread_dep], 
		include_directories : inc,
		install : true)


