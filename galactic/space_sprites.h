#ifndef SPACE_SPRITES_DEFINED 
#define SPACE_SPRITES_DEFINED

// predefined game ornamental types
class star_field_t : public sprite_t {
public:
   star_field_t();
  virtual ~star_field_t() {}

  void on_initialize(GrDirectContext *_context);
  void on_terminate();
  void on_tick(float width,float height);
  void on_render(SkCanvas *canvas);
  void on_signal(std::shared_ptr<parameter_data_t> o);

private:
  class star_t {
  public:
    float x{}, y{}, depth{}, color{};
    void generate(float w, float h);
  };

  std::list<star_t> stars{};
};

/**
 * 
 */
class streaking_comet_t : public sprite_t {
public:
 streaking_comet_t();
virtual ~streaking_comet_t(){}
  void on_initialize();
  void on_terminate();
  void on_tick(float width,float height);
  void on_render(SkCanvas *canvas);
};


#endif
