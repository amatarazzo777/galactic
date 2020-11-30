#include "std_base.h"
#include "graphic_base.h"
#include "sprite.h"
#include "space_sprites.h"

/**
 * @fn  star_field_t()
 * @brief
 *
 */
star_field_t::star_field_t() :
		sprite_t() {
	amount = 1000;
	speed=0;
}

/**
 * @fn void on_initialize()
 * @brief
 *
 */
void star_field_t::on_initialize(GrDirectContext *_context) {

	star_t star { };
	speed=0;
	double dmax = static_cast<double>(_context->maxRenderTargetSize());
	for (int i = 0; i < amount; i++) {
		star.generate(dmax,dmax);
		stars.emplace_back(star);
	}
}

/**
 * @fn void on_terminate()
 * @brief
 *
 */
void star_field_t::on_terminate() {}

/**
 * @fn void on_tick(float, float)
 * @brief
 *
 * @param w
 * @param h
 */
void star_field_t::on_tick(float w, float h) {
	// scale the speed to a pixel multiplier ratio,
	// Probably should be tied to dpi or screen size. Its hard coded.
	float speed_scale = ((float) speed);
	for (auto &o : stars) {
		float move_distance = o.depth * speed_scale;

		o.y = o.y + move_distance;
		if (o.y > h && o.y > w)
			o.generate(w*2,0);
	}

}

/**
 * @fn void on_render(SkCanvas*)
 * @brief
 *
 * @param canvas
 */
void star_field_t::on_render(SkCanvas *canvas) {
	SkPaint paint { };
	canvas->save();
	auto bounds = canvas->getBaseLayerSize();
	float centerx =  bounds.width()/2;
	float centery =  bounds.height()/2;

	canvas->rotate(direction, centerx, centery);
	auto it = stars.begin();
	while (it != stars.end()) {
		float radius = it->depth * 4;

		// compute color that is a third darker. The HSV color format
		// represents color is hue/saturation and value.
		SkScalar hsv[3]={};
		SkColorToHSV(it->color, hsv);
		hsv[2]=hsv[2] - hsv[2]/3;

		paint.setColor(it->color);

		canvas->drawCircle(it->x, it->y, radius, paint);
		it++;
	}
	canvas->restore();
}

/**
 * @fn void on_signal(std::shared_pointer<parameter_data_t>)
 * @brief
 *
 * @param o
 */
void star_field_t::on_signal(std::shared_ptr<parameter_data_t> o) {
	// grab the information from the signal object
	depth = o->depth;
	direction = o->direction;
	speed = o->speed;
}

/**
 * @fn void generate(float, float)
 * @brief
 *
 * @param w
 * @param h
 */
void star_field_t::star_t::generate(float w, float h) {
	std::random_device rd; // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> rnd_width(-1 * w, w);
	std::uniform_real_distribution<> rnd_height(-1*h, h);
	std::uniform_int_distribution<> rnd_color_component(20, 255);
	std::uniform_real_distribution<> rnd_depth(0.0, 1.0);
	x = rnd_width(gen);
	if(h==0.0)
		y=0.0;
	else
	y = rnd_height(gen);

	u_int8_t a = rnd_color_component(gen);
	u_int8_t r = rnd_color_component(gen);
	u_int8_t g = rnd_color_component(gen);
	u_int8_t b = rnd_color_component(gen);
	color = SkColorSetARGB(a, r, g, b);
	depth = rnd_depth(gen);
}

/**
 * @fn  streaking_comet_t()
 * @brief
 *
 */
streaking_comet_t::streaking_comet_t() {
	amount = 2;
}

/**
 * @fn void on_initialize()
 * @brief
 *
 */
void streaking_comet_t::on_initialize() {
}

/**
 * @fn void on_terminate()
 * @brief
 *
 */
void streaking_comet_t::on_terminate() {
}

/**
 * @fn void on_tick(float, float)
 * @brief
 *
 * @param w
 * @param h
 */
void streaking_comet_t::on_tick(float w, float h) {
}

/**
 * @fn void on_render(SkCanvas*)
 * @brief
 *
 * @param canvas
 */
void streaking_comet_t::on_render(SkCanvas *canvas) {
}
