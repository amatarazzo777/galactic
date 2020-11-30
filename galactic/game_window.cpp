#include "std_base.h"
#include "graphic_base.h"
#include "sprite.h"
#include "gaming_sprites.h"
#include "space_sprites.h"
#include "game_window.h"

/**
 * @fn  game_window_t()
 * @brief constructor
 *
 */
game_window_t::game_window_t() {

}

/**
 * @fn  ~game_window_t()
 * @brief
 *
 */
game_window_t::~game_window_t() {

}

/**
 * @fn void game_window_t::play() {
 */
void game_window_t::play() {
	std::uniform_real_distribution<> dist_step(0, 10);


	// initialize sprites that are listening to any controllers.
	// no rendering functions
	for(auto o : controllers)
		for(auto sprite : scene_objects)
			sprite->on_signal(std::dynamic_pointer_cast<parameter_data_t>(o));

	while (!glfwWindowShouldClose(window)) {

		// NOTE: OpenGL error checks have been omitted for brevity
		// Draw to the surface via its SkCanvas.
		SkCanvas *canvas = surface->getCanvas();

		glfwPollEvents();
		//	glfwWaitEvents();
		SkPaint paint;

		paint.setColor(SK_ColorBLACK);
		canvas->drawPaint(paint);

		float w = surface->width();
		float h = surface->height();
		for (auto &obj : scene_objects) {
			obj->on_tick(w, h);
			obj->on_render(canvas);
		}

		context->flush();
		glfwSwapBuffers(window);

	}

	on_terminate();

}

/**
 * @fn void on_signal(std::shared_ptr<controller_t>)
 * @brief
 *
 * @param o
 */
void game_window_t::on_signal(std::shared_ptr<controller_t> o) {
	auto sprite = std::dynamic_pointer_cast<sprite_t>(o);
	for(auto n : scene_objects)
		if(n!=sprite)
			n->on_signal(std::dynamic_pointer_cast<parameter_data_t>(sprite));

}


/**
 * @fn void error_callback_internal(int, const char*)
 * @brief
 *
 * @param error
 * @param description
 */
void game_window_t::error_callback_internal(int error,
		const char *description) {
	fprintf(stderr, "Error: (%d) -  %s\n", error, description);
}

/**
 * @fn void key_callback_internal(GLFWwindow*, int, int, int, int)
 * @brief
 *
 * @param window
 * @param key
 * @param scancode
 * @param action
 * @param mods
 */
void game_window_t::key_callback_internal(GLFWwindow *window, int key,
		int scancode, int action, int mods) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		if (key == GLFW_KEY_ESCAPE) {

			glfwSetWindowShouldClose(window, GLFW_TRUE);
		} else {
			auto obj =
					reinterpret_cast<game_window_t*>(glfwGetWindowUserPointer(
							window));

			for (auto o : obj->controllers)
				if(o->on_key_press(key, scancode, action, mods))
					obj->on_signal(o);

		}
	}
}

/**
 * @fn void cursor_position_callback_internal(GLFWwindow*, double, double)
 * @brief
 *
 * @param window
 * @param xpos
 * @param ypos
 */
void game_window_t::cursor_position_callback_internal(GLFWwindow *window,
		double xpos, double ypos) {
	return;
	auto obj =
			reinterpret_cast<game_window_t*>(glfwGetWindowUserPointer(window));

	for (auto n : obj->controllers)
		n->on_cursor_position(xpos, ypos);

}

/**
 * @fn void on_initialize()
 * @brief
 *
 */
void game_window_t::on_initialize() {
	glfwSetErrorCallback(error_callback_internal);

	if (!glfwInit())
		throw new std::runtime_error("glfwInit error.");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(width, height, title.data(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		throw new std::runtime_error("glfwInit error.");
	}

	// set the use pointer to the this to dereference the pointer from the static
	// event member
	glfwSetWindowUserPointer(window, this);

	// setup event callback handlers
	glfwSetKeyCallback(window, key_callback_internal);
	glfwSetCursorPosCallback(window, cursor_position_callback_internal);

	// sets the interpretation of mouse events as endless
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// start window
	glfwMakeContextCurrent(window);
	gladLoadGL();
	initialize_skia();
	glfwSwapInterval(1);

}

/**
 * @fn void on_terminate()
 * @brief
 *
 */
void game_window_t::on_terminate() {
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	terminate_skia();
	glfwDestroyWindow(window);
	glfwTerminate();
}

/**
 * @fn void initialize_skia()
 * @brief
 *
 */
void game_window_t::initialize_skia() {
	GrContextOptions options;
	context = GrDirectContext::MakeGL(nullptr, options).release();

	GrGLFramebufferInfo framebufferInfo;
	framebufferInfo.fFBOID = 0; // assume default framebuffer
	framebufferInfo.fFormat = GL_SRGB8_ALPHA8;
	SkSurfaceProps surfaceProps = { };

	GrBackendRenderTarget backendRenderTarget(width, height, 0, // sample count
			0, // stencil bits
			framebufferInfo);

	surface = SkSurface::MakeFromBackendRenderTarget(context,
			backendRenderTarget, kBottomLeft_GrSurfaceOrigin,
			kRGBA_8888_SkColorType, SkColorSpace::MakeSRGB(), &surfaceProps,
			nullptr).release();
	if (surface == nullptr)
		throw new std::runtime_error(
				"Error - skia surface render backend creation.");
}

/**
 * @fn void terminate_skia()
 * @brief
 *
 */
void game_window_t::terminate_skia() {
	delete surface;
	delete context;
}
