#include "std_base.h"
#include "graphic_base.h"
#include "sprite.h"
#include "gaming_sprites.h"

/**
 * @fn  score_card_t()
 * @brief
 *
 */
score_card_t::score_card_t() :
		sprite_t() {
	amount = 0;
}

/**
 * @fn void on_render(SkCanvas*)
 * @brief
 *
 * @param canvas
 */
void score_card_t::on_render(SkCanvas *canvas) {
	std::stringstream ss;
	ss << "score : " << amount;

	paint.setColor(SkColorSetARGB(50, 32, 255, 0));
	canvas->drawSimpleText(ss.str().data(), ss.str().size(),
			SkTextEncoding::kUTF8, 20.0, 64.0,
			SkFont(nullptr, 45.0f, 1.0f, 0.0f), paint);
}

/**
 * @fn  distant_background_t()
 * @brief
 *
 */
distant_background_t::distant_background_t() :
		sprite_t() {
	amount = 1;
}
/**
 * @fn void on_initialize()
 * @brief
 *
 */
void distant_background_t::on_initialize(GrDirectContext *_context) {
	std::string sfilename = random_file();
	context = _context;
	data = SkData::MakeFromFileName(sfilename.data());
	image = SkImage::MakeFromEncoded(data);

}

/**
 * @fn void on_signal(std::shared_ptr<parameter_data_t>)
 * @brief
 *
 * @param o
 */
void distant_background_t::on_signal(std::shared_ptr<parameter_data_t> o) {
	speed = o->speed;
	direction = o->direction;
}

/**
 * @fn void on_terminate()
 * @brief
 *
 */
void distant_background_t::on_terminate() {
	data.reset();
	image.reset();
}

/**
 * @fn void on_tick(float, float)
 * @brief
 *
 * @param width
 * @param height
 */
void distant_background_t::on_tick(float width, float height) {
	//ypos = ypos + speed / 50;
	ypos = ypos + speed / 25;
	if (ypos > height)
		ypos = 0;
}
/**
 * @fn void on_render(SkCanvas*)
 * @brief
 *
 * @param canvas
 */
void distant_background_t::on_render(SkCanvas *canvas) {
	paint.setAlpha(50);

	canvas->save();

	auto bounds = canvas->getBaseLayerSize();
	float centerx = bounds.width() / 2;
	float centery = bounds.height() / 2;

	canvas->rotate(direction, centerx, centery);

	canvas->scale(1.5, 1.5);
	canvas->translate(0, bounds.height() * .5);
	canvas->drawImage(image.get(), xpos, ypos, &paint);
	canvas->drawImage(image.get(), xpos, ypos - image->height(), &paint);

	canvas->restore();
}

/**
 * @fn bool on_key_press(int, int, int, int)
 * @brief A controller which changes the background to another random
 * one by pressing the key.
 * @param key
 * @param scancode
 * @param action
 * @param mods
 * @return
 */
bool distant_background_t::on_key_press(int key, int scancode, int action,
		int mods) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {

		switch (key) {
		case GLFW_KEY_B:
			on_initialize(context);
			break;
		}
	}
	return false;
}

/**
 * @fn  player_t()
 * @brief
 *
 */
player_t::player_t() :
		sprite_t(), controller_t(), parameter_data_svg_t(
				std::filesystem::path(
						"/home/anthony/eclipse-workspace/galactic/resources/fighters.svg")) {
	amount = 1;
	speed = 0.0;
	direction = 0.0;
}

/**
 * @fn void on_initialize()
 * @brief
 *
 */
void player_t::on_initialize(GrDirectContext *_context) {
	amount = 1;
	speed = 0.0;
	direction = 0.0;
}

/**
 * @fn void on_terminate()
 * @brief
 *
 */
void player_t::on_terminate() {
}

/**
 * @fn void on_tick(float, float)
 * @brief
 *
 * @param width
 * @param height
 */
void player_t::on_tick(float width, float height) {
	if (acceleration != 0.0) {
		if (acceleration < 0)
			acceleration -= .2;
		else
			acceleration -= .2;
	}
}

/**
 * @fn void on_render(SkCanvas*)
 * @brief
 *
 * @param canvas
 */
void player_t::on_render(SkCanvas *canvas) {

}

/**
 * @fn void on_key_press(int, int, int, int)
 * @brief
 *
 * @param key
 * @param scancode
 * @param action
 * @param mods
 */
bool player_t::on_key_press(int key, int scancode, int action, int mods) {
	bool bsignal = false;
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {

		switch (key) {
		case GLFW_KEY_UP:
			speed = speed + .2;
			bsignal = true;
			break;

		case GLFW_KEY_DOWN:
			speed = speed - .2;
			bsignal = true;
			break;

		case GLFW_KEY_RIGHT:
			acceleration += 0.5;
			if (acceleration > 10.0)
				acceleration = 10.0;
			bsignal = true;

			break;

		case GLFW_KEY_LEFT:
			direction -= 0.5;
			if (acceleration > 10.0)
				acceleration = 10.0;
			bsignal = true;
			break;
		}

	}
	return bsignal;

}

/**
 * @fn void on_cursor_position(double, double)
 * @brief
 *
 * @param xpos
 * @param ypos
 */
bool player_t::on_cursor_position(double xpos, double ypos) {
	direction += xpos;
	speed += ypos;
	return true;
}

/**
 * @fn  opponent_t()
 * @brief
 *
 */
opponent_t::opponent_t() :
		sprite_t(), parameter_data_svg_t(
				std::filesystem::path(
						"/home/anthony/eclipse-workspace/galactic/resources/ships.svg")) {
	amount = 10;
}

/**
 * @fn void on_initialize(GrDirectContext*)
 * @brief
 *
 * @param _context
 */
void opponent_t::on_initialize(GrDirectContext *_context) {

	svg_object_prefix = "ship_";
	svg_object_count = 11;
	load_svg();

	std::random_device rd; // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> rnd_ship_idx(1, 12);

	for (int i = 0; i < amount; i++) {
		SkMatrix pos;
		float xpos = 30 + static_cast<float>(i) * 75;
		float ypos = 20;

		pos.setRotate(180.0);
		pos.setTranslate(xpos, ypos);
		u_int8_t ship_id = 0xff;
		u_int8_t cnt = 0;
		while (ship_id > svg_picture_objects.size() - 1 && cnt < 10) {
			ship_id = rnd_ship_idx(gen);
			cnt++;
		}
		if (cnt >= 10)
			throw new std::runtime_error(
					"opponent_t::on_initialize - error rnd number.");

		ships.push_back(opponent_t::enemy_ship_t(ship_id, pos));

	}

}

/**
 * @fn void on_terminate()
 * @brief
 *
 */
void opponent_t::on_terminate() {
}

/**
 * @fn void on_tick(float, float)
 * @brief
 *
 * @param width
 * @param height
 */
void opponent_t::on_tick(float width, float height) {

	if (bmarchstate) {
		gridx += march_direction;
		if (gridx > 100)
			bmarchstate = false;
	} else {
		gridx -= march_direction;
		if (gridx < 0)
			bmarchstate = true;
	}

}

/**
 * @fn void on_render(SkCanvas*)
 * @brief
 *
 * @param canvas
 */
void opponent_t::on_render(SkCanvas *canvas) {
	canvas->save();
	canvas->translate(gridx, gridy);
	for (auto n : ships) {
		canvas->save();
		canvas->concat(n.position);
		canvas->scale(.3, .3);

		render_svg(canvas, n.id);

		canvas->restore();
	}
	canvas->restore();
}

/**
 * @fn void ship_t(const std::string&, const SkMatrix&)
 * @brief
 *
 * @param _id
 * @param _pos
 */
opponent_t::ship_t::ship_t(u_int8_t _ship_id, const SkMatrix &_pos) :
		id(_ship_id), position(_pos) {
}
