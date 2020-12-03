#include "std_base.h"
#include "graphic_base.h"
#include "sprite.h"

namespace fs = std::filesystem;

void sprite_t::on_initialize(GrDirectContext *_context) {
	context = _context;
}
void sprite_t::on_terminate() {
	context = { };
}

/**
 * @fn void on_tick(float, float)
 * @brief
 *
 * @param width
 * @param height
 */
void sprite_t::on_tick(float width, float height) {
}
/**
 * @fn void on_render(SkCanvas*)
 * @brief
 *
 * @param canvas
 */
void sprite_t::on_render(SkCanvas *canvas) {
}
/**
 * @fn bool accepts_controller(std::shared_ptr<controller_t>)
 * @brief
 *
 * @param o
 * @return
 */
void sprite_t::on_signal(std::shared_ptr<parameter_data_t> o) {
}

/**
 * @fn void scan_directory(std::string)
 * @brief
 *
 * @param prefix
 */
void parameter_data_filelist_t::scan_directory(std::string prefix) {
	// this is a simple fix for debugging where the path
	// to the resource directory is not located within the build output.
	// when debugging the resource directory is typcially right of the main source tree.
	// when when the program runs in debug mode, the directory is relative back some.
	fs::path adjusted_directory = resource_directory;
	if (!fs::is_directory(adjusted_directory)) {
		adjusted_directory = adjusted_directory.parent_path().parent_path()
				/ +"resources";
		if (!fs::is_directory(adjusted_directory)) {
			throw new std::runtime_error("resource directory not found.");
		}
	}

	for (auto &p : fs::directory_iterator(adjusted_directory)) {
		std::string s = p.path().stem();
		if (s.compare(0, prefix.size(), prefix) == 0)
			filelist.push_back(p);
	}
}

/**
 * @fn std::filesystem::path random_file()
 * @brief
 *
 * @return
 */
std::filesystem::path parameter_data_filelist_t::random_file() {
	if (filelist.size() <= 0)
		throw new std::runtime_error("no resource files found.");

	std::random_device rd; // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> rnd_file_idx(0, filelist.size() - 1);
	return filelist[rnd_file_idx(gen)];
}

/**
 * @fn  parameter_data_svg_t(std::filesystem::path_t&)
 * @brief
 *
 * @param svg_file
 */
parameter_data_svg_t::parameter_data_svg_t(
		const std::filesystem::path &svg_file) :
		svg_filename(svg_file) {
}

/**
 * @fn void load_svg(std::string&)
 * @brief
 *
 * @param filename
 */
void parameter_data_svg_t::load_svg() {
	return;
	SkFILEStream svgStream(svg_filename.generic_string().data());
	if (!svgStream.isValid()) {
		std::stringstream ss;
		ss << "file not found: " << svg_filename;
		throw new std::runtime_error(ss.str());
	}

	svg_dom = SkSVGDOM::MakeFromStream(svgStream);
	svg_dom->setContainerSize(SkSize::Make(700, 500));

	bool bhasobjects = { };
	if (svg_object_prefix.size() != 0)
		bhasobjects = true;

	SkPictureRecorder recorder;
	auto canvas = recorder.beginRecording(
			SkRect::MakeSize(svg_dom->containerSize()));
	svg_dom->render(canvas);

	if (bhasobjects) {

		for (int n = 1; n < svg_object_count; n++) {
			std::stringstream ss;
			ss << svg_object_prefix << n;

			SkRect object_bounds = { };
			if (svg_dom->objectBoundingBox(canvas, ss.str().data(),
					object_bounds)) {
				SkPictureRecorder object_recorder;
				auto object_record_canvas = object_recorder.beginRecording(
						object_bounds);
				svg_dom->render(object_record_canvas);
				auto ptr=object_recorder.finishRecordingAsPicture();
				svg_picture_objects.push_back(std::move(ptr));

			} else {
				std::stringstream sserror;
				sserror << "Error : object not found in svg." << svg_filename
						<< " - " << ss.str();
				throw new std::runtime_error(sserror.str());
			}
		}
	}

}

/**
 * @fn void render_subsvg(SkCanvas*)
 * @brief
 *
 * @param canvas
 */
void parameter_data_svg_t::render_svg(SkCanvas *canvas) {

	if (svg_dom) {
		svg_dom->render(canvas);
	}

}

/**
 * @fn void render_subsvg(SkCanvas*, std::string)
 * @brief
 *
 * @param canvas
 * @param id
 */
void parameter_data_svg_t::render_svg(SkCanvas *canvas, const u_int8_t id) {
	//std::size_t solid_id= static_cast<std::size_t>(id-1);
	//if (solid_id < svg_picture_objects.size())
		//svg_picture_objects[solid_id]->playback(canvas);

}

