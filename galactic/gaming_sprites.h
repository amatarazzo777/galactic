#ifndef GAMING_SPRITES_DEFINED
#define GAMING_SPRITES_DEFINED

/**
 * @class score_card_t
 * @brief
 *
 */
class score_card_t: public sprite_t {
public:
	score_card_t();
	virtual ~score_card_t() {
	}
	void on_render(SkCanvas *canvas);
	SkPaint paint = { };
};

/**
 * @class distant_background_t
 * @brief
 *
 */
class distant_background_t: public sprite_t,
		public parameter_data_filelist_t,
		public controller_t {
public:
	distant_background_t();
	virtual ~distant_background_t() {
	}
	void on_initialize(GrDirectContext *_context);
	void on_terminate();
	void on_tick(float width, float height);
	void on_render(SkCanvas *canvas);
	void on_signal(std::shared_ptr<parameter_data_t> o);
	bool on_key_press(int key, int scancode, int action, int mods);

	sk_sp<SkData> data = { };
	sk_sp<SkImage> image = { };
	SkBitmap bitmap = { };
	SkPaint paint = { };
	float xpos = { };
	float ypos = { };
	std::vector<std::filesystem::path> backgrounds = { };
};

/**
 * @class player_t
 * @brief
 *
 */
class player_t: public sprite_t, public controller_t, public parameter_data_svg_t {
public:
	player_t();
	virtual ~player_t() {
	}

	void on_initialize(GrDirectContext *_context);
	void on_terminate();
	void on_tick(float width, float height);
	void on_render(SkCanvas *canvas);
	bool on_key_press(int key, int scancode, int action, int mods);
	bool on_cursor_position(double xpos, double ypos);
	float acceleration = 0.0;
};

/**
 * @class opponent_t
 * @brief
 *
 */
class opponent_t: public sprite_t, public parameter_data_svg_t {
public:

	opponent_t();

	virtual ~opponent_t() {
	}

	void on_initialize(GrDirectContext *_context);
	void on_terminate();
	void on_tick(float width, float height);
	void on_render(SkCanvas *canvas);

	sk_sp<SkSVGDOM> fDom={};
	std::filesystem::path svg_ships_file = { };

	class ship_t {
	public:
		ship_t(u_int8_t _ship_id,const SkMatrix &_pos);
		u_int8_t id={};
		SkMatrix position=SkMatrix::I();
	};

	class enemy_ship_t : public ship_t {
	public:
		using ship_t::ship_t;

	};

	std::vector<ship_t> ships;
	float march_direction=1.0;
	bool bmarchstate=true;
	float gridx=0.0;
	float gridy=0.0;
};

#endif
