/**

 clang testsk1.cpp glad.c -Iinc -o test -lGL -ldl -lglfw -lrt -lm -lskia -lstdc++
 -L/home/anthony/source/skia/out/Shared -I/home/anthony/source/skia

 Documentation:

 https://skia.org/user

 wget --recursive --no-clobber --page-requisites --html-extension --convert-links
 --restrict-file-names=windows --domains skia.org --no-parent  skia.org/user
 */

#ifndef GAME_WINDOW_H_DEFINED
#define GAME_WINDOW_H_DEFINED

/**
 * @class game_window_t
 * @brief
 *
 */
class game_window_t {
public:
	game_window_t();
	~game_window_t();

	void play();

public:
	std::string title = "Game Window";
	std::filesystem::path resource_directory = std::filesystem::current_path()
			/ "resources";
	float width = 800.0;
	float height = 600.0;

	/**
	 * @fn add_sprite
	 *
	 */
	template<typename T> std::shared_ptr<T> add() {
		scene_objects.emplace_back(std::make_shared<T>());

		// attaches to event dispatcher portion of sprite object
		if constexpr (std::is_base_of<controller_t, T>::value) {
			auto linked_ptr(scene_objects.back());
			auto typed_ptr = std::dynamic_pointer_cast < controller_t
					> (linked_ptr);
			controllers.emplace_back(typed_ptr);
		}

		if constexpr(std::is_base_of<parameter_data_filelist_t,T>::value) {
			auto typed_ptr = std::dynamic_pointer_cast < parameter_data_filelist_t
						> (scene_objects.back());
			resource_directory = typed_ptr->resource_directory;

			std::string file_prefix={};

			// read the file list according to the sprite object type.
			// the file list does not have to be only  images, just start with the prefix.
			// The file stem is searched, which is the name.
			if constexpr(std::is_same<distant_background_t,T>::value) {
				file_prefix="background_";
			}

			// read the resources that are applicable.
			typed_ptr->scan_directory(file_prefix);
		}

		scene_objects.back()->on_initialize(context);

		return std::dynamic_pointer_cast < T > (scene_objects.back());
	}
	void on_signal(std::shared_ptr<controller_t> o);

	void on_initialize();
	void on_terminate();

private:


	void initialize_skia();
	void terminate_skia();

	static void error_callback_internal(int error, const char *description);
	static void key_callback_internal(GLFWwindow *window, int key, int scancode,
			int action, int mods);
	static void cursor_position_callback_internal(GLFWwindow *window,
			double xpos, double ypos);

	GLFWwindow *window = { };
	GrDirectContext *context = { };
	SkSurface *surface = { };

	sprite_list_t scene_objects = { };
	std::vector<std::shared_ptr<controller_t>> controllers = { };
};

#endif
