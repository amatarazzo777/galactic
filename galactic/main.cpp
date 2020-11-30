/**
   galactic_space - a tutorial using the skia library. The process goes through:

   1) Setting up the environment from several points within the development life cycle.
   2) Using the meson build system in conjunction with skia by configuring pkg-config 
   to find the compiled source. 
   3) Modifying the profile paths for the user to provide
   4) context saving of the build system tools path for both skia, pkg-config and meson.
   5) Attaining GLWF, a cross platform openGL library.
   6) Compiling a minimum example of window start up, rendering with draw canvas, closing skia.
   7) Compiling galactic_space.


Space ship are traced from https://2dgameartguru.com/space-ships-starting-with-the-design/
into drawing commands for paths.

*/

#include "std_base.h"
#include "graphic_base.h"
#include "sprite.h"
#include "gaming_sprites.h"
#include "space_sprites.h"
#include "game_window.h"


int main(void) {
  auto game = game_window_t();

  game.title = "Galactic Space";
  game.width = 1000.0;
  game.height = 700.0;

  game.resource_directory = "resources";
  game.on_initialize();

  game.add<star_field_t>();
  game.add<distant_background_t>();
  game.add<streaking_comet_t>();
  game.add<player_t>();
  game.add<opponent_t>();
  game.add<score_card_t>();

  game.play();

  exit(EXIT_SUCCESS);
}
