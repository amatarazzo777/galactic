#ifndef GAME_SPRITE_CPP
#define GAME_SPRITE_CPP

/**
 * @class parameter_data_t
 * @brief
 *
 */
class parameter_data_t {
public:
	u_int16_t amount = 100;
	u_int8_t depth = 30;
	float direction = 0.0;
	float speed = 1;

};

/**
 * @class parameter_data_filelist_t
 * @brief
 *
 */
class parameter_data_filelist_t {
public:

	std::filesystem::path resource_directory = { };
	std::vector<std::filesystem::path> filelist = { };

	void scan_directory(std::string prefix);
	std::filesystem::path random_file();

};

/**
 * @class parameter_data_svg_t
 * @brief
 *
 */
class parameter_data_svg_t {
public:
	std::filesystem::path svg_filename = { };
	parameter_data_svg_t() = delete;
	parameter_data_svg_t(const std::filesystem::path & svg_file);
	void load_svg();
	void render_svg(SkCanvas *canvas);
	void render_svg(SkCanvas *canvas, const u_int8_t id);

	sk_sp<SkSVGDOM> svg_dom={};
	sk_sp<SkPicture> svg_picture = {};
	std::vector<sk_sp<SkPicture>> svg_picture_objects = {};

	std::string svg_object_prefix = {};
	u_int8_t svg_object_count = {};
};

/**
 * @class sprite_t
 * @brief
 *
 */
class sprite_t: public parameter_data_t {
public:
	sprite_t() {
	}
	virtual ~sprite_t() {
	}
	virtual void on_initialize(GrDirectContext *_context);
	virtual void on_terminate();
	virtual void on_tick(float width, float height);
	virtual void on_render(SkCanvas *canvas);
	virtual void on_signal(std::shared_ptr<parameter_data_t> o);
	GrDirectContext *context = { };
};

/**
 * @class controller_t
 * @brief additionally sprites may derrive and implement this interface.
 * inwhich they must interpret the data.
 *
 */
class controller_t {
public:
	controller_t() {
	}
	virtual ~controller_t() {
	}

	virtual bool on_key_press(int key, int scancode, int action, int mods) {
		return false;
	}
	virtual bool on_cursor_position(double xpos, double ypos) {
		return false;
	}
};

typedef std::vector<std::shared_ptr<sprite_t>> sprite_list_t;

#endif
