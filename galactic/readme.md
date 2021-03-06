#1. Install Linux Xfce as a UEFI operating system.
Do you need the machine setup for a minimum platform? If your
machine has 4gb, this section is for you. If you cannot upgrade
your memory, this is the trimmest, fastest and full IDE featured
setup to allow development/debug/learning. The Linux Xfce
desktop is a trim, fast performer, easy to use with most modern
hardware supported.

Download the latest Xfce release of the Linux .iso. Google it. I
like xfce I have tried many except for bsd. Dragonfly is also an
interesting distribution but may be difficult to configure. Use
dd to burn a USB boot-able image stick. The two main things 
are burning the image with dd (Linux command) or similar 
program if you are switching and booting from the USB stick 
in non legacy mode. 

After it is installed on your system, the build environment, tools and
compilers will have to be installed. Make sure your at a good
internet connection. This is not the primary reason for this
text, so please refer to setting up Linux up for more detailed
steps elsewhere. If you decided to install Linux Xfce, there is
some further tweaking you may want to use if you have a minimal
platform like mine. 

By reducing the running services, and removing advanced features 
such as software management, updating, apport, whoopsie, apparmor, 
file searching and cataloging, about five hundred megabytes can 
be saved. This brings the memory usage to about 330mb after 
booting. As well after setting up the desktop with application 
launchers, the window panel manager can be disabled. That is 
the task bar and gadget features. This allows for a browser 
window to be opened for documentation viewing, an IDE instance, 
and several source windows. Here is a list below which notes the 
services running from using the “servicectl” command in the 
console.


* accounts-daemon.service
* acpid.service
* alsa-restore.service
* binfmt-support.service
* blk-availability.service
* bluetooth.service
* console-setup.service
* dbus.service
* grub-common.service
* keyboard-setup.service
* kmod-static-nodes.service
* lightdm.service
* lm-sensors.service
* lvm2-monitor.service
* lvm2-pvscan@8:2.service
* networkd-dispatcher.service
* NetworkManager.service
* polkit.service
* rtkit-daemon.service
* setvtrgb.service
* smartmontools.service
* systemd-backlight@backlight:intel_backlight.service
* systemd-fsck@dev-disk-by\x2duuid-0D9E\x2d0EE9.service
* systemd-journal-flush.service
* systemd-journald.service
* systemd-logind.service
* systemd-modules-load.service
* systemd-random-seed.service
* systemd-remount-fs.service
* systemd-resolved.service
* systemd-sysctl.service
* systemd-sysusers.service
* systemd-tmpfiles-setup-dev.service
* systemd-tmpfiles-setup.service
* systemd-udev-trigger.service
* systemd-udevd.service
* systemd-update-utmp.service
* systemd-user-sessions.service
* thermald.service
* tlp.service
* udisks2.service
* ufw.service
* unattended-upgrades.service
* upower.service
* user-runtime-dir@1000.service
* user@1000.service
* wpa_supplicant.service

The system is comfortable but there are a few extras. However
taking some of them such as the logging service down, will
change the underlying function so that the routing is sent to a
null device file, yet it will still be listed in the services
running list. tlp is a service for managing battery life. It
cuts some devices off, circuit configurations for WiFi, and
changes the CPU frequency governor. Plus a lot more. But at
times this can be troublesome to setup for types of platforms.

This might be critical on machines that have only 4gb for
build.The recommended memory
should be at least 8gb for development and learning. Most likely
16gb would be a good system level by the necessities of modern
day. This does reduce the RAM usage after several iterations of
disabling services and uninstalling software. For light machine
usage, the abi word is much lighter than the LibreOffice. Some
laptop models require this even though it may sound strange and
unrelated. For example, my laptop, a Lenovo idea pad S340 15iwl,
originally had Linux installed using the legacy setting within
the boot mode. When I added a HDMI TV to it, the HDMI output
could not be recognized. So, this step The Linux image .ISO
file, when burned to the USB stick can automatically handle
installing as
a UEFI operating system. However some bios settings make it so
that windows is the default
banded one. This can be change to software controlled while
leaving the bios settings to UEFI.

Here are some references:
* https://www.Xfce.org/download

#2. Install Linux base c++ compiler tool chain
The build essential package is the useful start. The package
also comes with some other useful tools such as objdump, ld, ar,
and much more. The package is typically install on most c/c++
developers and also some users. Simply, sudo apt-get install
build-essential

##2.1. install latest clang using
Clang has many advanced and fast technologies such as parsing
and the ability to use the output within the diagnostic workings
of the source code semantic linting. This happens while you are
entering source in a lazy manner unobtrusively. What code
suggestions and automatic formatting can occur. Most times it is
better to have these features active on a key combination rather
than automatically. Eclipse does come with formatting as well.
Installing clang makes some parts of Eclipse CPP faster. During
the complex times of working on semantic compile source issues
in your code, it is useful to have a second opinion on error
messages at times. That is. the wording between g++ and clang do
offer the same meaning, but may spark an alternate path of
comprehension.

###Install the latest clang using the script from:
####https://apt.llvm.org/

###install clang format

##2.2 install opengl-dev
The openGL development tools.
####https://www.wikihow.com/Install-Mesa-(OpenGL)-on-Linux-Mint

##2.3 install GLWF 
An open source for many forms of openGL, GL ES, Vulcan. And cross platform
gaming device input events.
 
####https://www.glfw.org/

#3. Get and Compile skia.
BEFORE Compiling this program, you MUST configure and compile
skia. Follow the build
instructions for skia to produce the Release version of shared
library. The debug version is not useful for application
development using skia. The debug version is for working with
the
internals of skia. So the documentation refers to the developer
of skia applications as "user"
which might be confusing. The option you should choose is
"is_official_build=true". Compiling is using the "is_official_build=true" 
option allows use of the library in the capacity that chrome, 
JavaScript or other games use it in their run-time. You will still 
be able to debug your application, just not step into the skia source code.
Ultimately debugging the skia code requires advanced tools
memory and hardware on top of knowing the internal architecture.
But, you can use skia on low end devices once it is compiled.

Additionally the following options are useful to have enabled within 
the arguments list of the compile. That way, you get it out of the way 
imediately. 

is_official_build=true
is_skia_standalone=true
skia_enable_svg=true
skia_enable_tools=true
skia_enable_gpu=true
skia_enable_ccpr=true
skia_compile_processors=true 
skia_build_fuzzers=true 
cxx="clang++"
skia_enable_svg=true
skia_enable_tools=true

Compile it for release. The compilation is intensive for small
computers but will complete within several minutes. Make sure
that you are not running any other applications and have swap
memory enabled if you have a minimum platform like 4gb, linking
at the end takes some time. I had to edit the swappiness value
even. On my low end laptop, 4gb of memory duel core, it takes
less than twenty minutes. You should compile it as a shared
library which is the typical usage. See skia.org for their build
instructions. 


gn gen out/Shared --args='is_official_build=true is_component_build=true 
	is_skia_standalone=true cxx="clang++"  skia_enable_svg=true 
	skia_enable_tools=true skia_enable_gpu=true  skia_enable_ccpr=true 
	skia_compile_processors=true skia_build_fuzzers=true 
	extra_cflags_cc=["-O3"] extra_ldflags=["-Wl","-s"]'


* https://skia.org/user/build

below is the command that I used after careful study. I often
 though about enabling the avx, and then avx512, bit it seems ok without it. 

##3.1. Persistent use or rebuild skia again easily.

The header files and location of the .so or .dll file must be
known about at compile time
specifically by build systems - meson. The previous part of
building skia was the first major step, however there are a few
more things to do before the compile system will work with the
.so library as a pkg-config library. That is pkg-config is used
to find the location and parameters used for the compiler
arguments. Search path, and linker name. Traditional packages
are installed within system ares of the directory. Yet for
builds such as this, it makes sense to place them into a portion
labeled as such to not mix packages. The directory
/usr/local/lib/pkgconfig may bot exist on your system. Create it
using the sudo command.

###3.1.1. Make local package config directory
```
sudo mkdir /usr/local/lib/pkgconfig
```

###3.1.2. Edit “skia.pc” file to match your build system
Edit the skia.pc file within this project directory. Change the
line "prefix" to point to the source location of the skia
project. It should be the base directory. Notice the "libdir" as
well. This is where the .so file is located as a finalized
compete path concatenated. The convention used here is the same
that is presented within the skia build process. That is, using
"/out/Shared". Within the directory should be the skia.a and
skia.so along with the other components of skia. There are other
shared libraries that are built within the process, and are
loaded by linking to the primary skia.so library. So there is no
need to worry about linking the others, just skia. The file
looks like the text below. This text file names "skia.pc" will
be copied or saved to "/usr/local/lib/ pkgconfig", the directory
that was just created.

###3.1.1. “skia.pc” file
```
prefix=/home/anthony/source/skia
exec_prefix=${prefix}
includedir=${prefix}/include
libdir=${exec_prefix}/out/Shared
Name: skia package file
Description: The skia library by goggle
Version: 1.89.0
Cflags: -I${includedir}
Libs: -L${libdir} -lskia
```


Now the .pc file is in the right location, now pkg-config must
be told about local development
installed libraries. The environmental variable
"PKG_CONFIG_PATH" is the one that it uses for this. To make
setting the variable last in persistence, after reboot etc, the
profile of your user account should be modified to include the
build tools for skia, and the path. A convenient way to order
the execution of the profile is to use two of them as their
meaning are different based upon the type of settings.
.bash_profile is for setting user resources and other security
features while .profile is for adhoc persistent settings such as
environmental variables. Both of these files must be edited
using the super user command "sudo". Put ". ~/.profile" in it.

###3.1.2. edit the bash profile
```
sudo nano ~/.bash_profile
```

###3.1.3. add the following and save
```
. ~/.profile
```

###3.1.4. Edit your user profile. ~/.profile
Next edit the ~/.profile file using the sudo permission as well.
The PATH environmental variable is modified to include the the
skia build tools, as well as pkg-config path to include
skia.pc.
```
sudo nano ~/,profile
```

###3.1.5. Add paths to user profile
The file should contain the following adapted to your path
build environment:

```
PATH=/home/anthony/.local/bin:/home/anthony/source/depot_tools:$PATH
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
```

Now save the file and exit nano.

###3.1.6. Activate changes or reboot
The files have been set to point to the build system and also so
that you can build skia tailored for specific uses. This project
uses the GL definition and more, so the default library
is recommended. More advanced usage will be next as you find
ease working with the skia documentation and examples. The
project starts with a simple class construction to separate
functionalities of a compelling yet simple space view game. For
learning purposes, the initial phase will incorporate starting
the skia system in conjunction with an openGL window allocated
and initialized by GWLF. After this, using the command
"pkg-config --cflags --libs skia" should produce results that
link to skia on your drive.

#4. Meson Build System
The meson build system is by far the most useful and cross
platform tool chain library with
future support included. It is different in all forms compared
to other build systems and offers a syntax that is delectable in
assuring multiple line capability, simplicity and easy
maintenance. 

One interesting aspect of the operating of the
meson build system is that the plan is to use an independent
language within its format. Its text. The file is names
meson.build. It is distributed with your source code. At the end
of the day, the other developer runs meson build && meson
compile && meson test. 

The syntax form is formally tied to data input
of three distinct data types, int, string and array. It supports comments.
Software dependencies such as gl, gtk or other packages can be
successfully integrated in a cross platform manner using the
system specific compiler tool chain. And thus either simply,
debug build, release builds are easy had without command line 
fumbling.
 
The actual program that provides the environment of compiler
invocation / capture is ninja build. So, meson handles the
project settings to decide what commands should be invoked while
ninja checks the state, provides incremental compilation. Other 
features are to use .pch distribution for template libraries as well.
Prominently the number of cores is set to six. 
Just clicking the hammer build icon does this at a cat’s speed.

This tutorial uses the rudimentary novice level of meson scripts. 


*https://mesonbuild.com/ 

When you add files to a meson project, make sure that you update
the meson.build file to include it when compiling. So instead of
the IDE controlling the build, the meson.build, file controls
the entire process. This is meant to be self documenting as per
the meson file format. The meson system will automatically
adjust the file.

#5. Eclipse IDE
Using eclipse is a good solution for having very advanced
editing and compiling features that are fault tolerant in the
usage. That is, Eclipse is a stable platform IDE. However, you
should be wary of adding too many plugins to it. Some features
are accessible still using the command line like git or github
but the plugin makes it very user friendly. Making a .sh file
that executes a python script to do git commits is also a
flexible low cost solution perhaps. I still use it along with
many extras in a tiny 4gb machine. Most of the default plugins
are good to have anyway. That is, the main purpose is writing
code. Within the tool set that is going to be set up on your
system, there will be plenty of robust features that provide
every functionality desired for debugging, writing code.

##5.1. Install
Install Eclipse IDE using the eclipse installer. The website is
https://www.eclipse.org/IDE/
* setup as a c++ IDE.
* install meson CDT preview build from the list of available
using “Install Software” in the
help menu.
* install eclipse color themes from the eclipse market place,
which is different than install
software. Eclipse Color Themes is the search words. Use Eclipse
Market place. The website is https://marketplace.eclipse.org/content/eclipse-color-theme

##5.2. Integrating the meson code process into the build system.

Using the CDT meson build preview works well once meson and the
compilers are installed. It is not fully integrated, but the
best and most useful features are very stable. There are a few
tweaks to remember when you are setting up a new project within
eclipse that will use meson. 

Basically there are two wizard
which let you either create a project with a simple script or an
empty one in which you supply the meson.build. The script that
it produces is a very defaulted one in which you would have to
edit after adding some files, shared libraries or something. 
At most times when you import a project that is an existing meson
project, just create an empty meson project and use the import
file system path. 

When the project is created as a meson
project, the eclipse user interface options link to the command
which invoke meson. That is the clean, build, release and debug
all tied into those nice toolbar icons and short cut menus.
Ultimately this brings a lot of power such as also running
python scripts that others have written. 

Yet setting the compiler options within a UI page is not present. 
No need to really worry about it either because meson handles all of the
settings that you might need. If you need to, you add them
directly to the meson project. Within the CDT panel, there is a
nice meson tab page displaying all of the options that is used
in place of compiler command line settings. See the meson panel
within project settings. Its located at
Project->Properties->Meson.

##5.3. Good Options
Some options that are nice to set up within the IDE but may be
hard to find.

###5.3.1. error, warning and info annotations

When working with terribly written source code, that is the
various states that exist before it  shall compile, it is often
necessary to batch organize and simplify changes. It is useful
to have these annotations appear within the editor along with
the source code in a slightly modified visual appearance. When
you start correcting the errors, the text pops away after
several seconds of laziness.

So as logic goes, perhaps you might fix several of these issues
with one swoop. Rather than
moving back and forth between the Problem View, you can
sequentially plow through a file
perhaps defaulting and correcting syntax that was played out
while you were prototyping, relying on a distant memory of a
third party interface. You can follow the code down more
logically straightening up routine by routine. This allows you
to develop what you can conceive first, and then actually work
out more details later. So you write more exploratory code. And
then when at a breaking point, syntax compile the code.

To activate these options use General->Text Editors->Annotation.
Within this list is a small little combo box labeled “Show code
minings for problem annotations:”. There are a few different
combinations, I like the Errors, Warnings, and Infos options for
the reason when compilations errors occur in std libraries, it
is useful to track it back to where it occurred in the project.
In short, all of the information is there in one click when you
have lots of errors. You can even change the maximum amount to
larger, but it is not as useful. About 100 at a time is good.

###5.3.2. doxygen comment generator
Code block comments designed for the doxygen documentation
system provides not only that
aspect. Many in the industry have eyes for these blocks and
their visual signature to know when routines begin and end. It
provides a separation between items for this purpose. And as
well, some formatting aspects that related directly to naming
conventions provide that within class header files, the
commenting may be a lot lighter. Such as when interfaces are
only declared or a prototype.

The ability to snap a /** and hit the enter key and have a nice,
future planned, comment is a
quick all inclusive feature that can be difficult to find, to
enable. I once was so please it was
turned on, had to rebuild, and could not find it again. I had to
resort to writing the stuff by hand. Can be a time saver when
you are monotonously adding comment blocks to a file. So it is
activated using the following menu items within the project
settings using Project->Properties>Code Templates.

###5.3.3. code spelling dictionary
At times the squiggle on spelling errors might be pleasurable to
not see. Especially since the
reaction and scanning of it is for syntax errors and such. One
may be dismayed at its sign
between quotes. And perhaps removal of the mark temporarily due
to apparent misspellings is
delightful. So it can be made so. Those command line tools that
use abbreviated mnemonics have many of these. My code has these.
And of course some words do not exist initially such as
superlatives and chimp words. Or how about not having your last
name not underlined in red. Geez. Just such for “spelling” in
the search box. The list tree will show
Window->Preferences->General->Editors->Text Editors->Spelling.
Along with making sure it is enabled, change the User defined
dictionary to a file stored within your source or documents. A
good name could be
~/Documents/user_code_spelling_dictionary.txt. Maybe add “skia”
and your last name. It could also be something people just tune
out and do this kind of thing later. Easy peazy.

##5.4. debugging with meson builds
Setting up the debugger for launching a build built as a debug
build from meson. should be done using the configure debug
build. Change the executable path “application” to point inside
the build directory of the meson build folder. When selecting a
project to be built as a debug version from the
project->properties->c++->meson tab, there are a few options to
check. Such as std::library debugging which creates symbols for
the c++ std objects. That is hover over debugging shows the
contents of std containers and objects using pretty printing.
A short cut to the launch configuration for debugging in eclipse
is accomplished by right clicking on the project and selecting
“Debug As”. From there select debug configuration. The most
important setting along with the familiar ones that should be
set appropriately for meson is the C/C++ Application. Its the
executable that is generated by the build. First you should have
built it. Click “Search Project...” and find the elf64 file
name. Or you can choose browse and find it. Normally this is set
to the CDT default location of “Binaries”. So it has to be
changed.

#6. install media tools and resource files.
Optionally, or most likely later you might install some of these
good tools. Software components, graphic editor, and an audio
editor.

##6.1. install flatpak
Is a useful tool for application packaging and distribution. The
packaging system of the meson script can be configured to output
such a package where others may run your program by the binary.
The package includes a distributed unit. There are many features
additionally to find about flatpak files. Some references are
below. The command is used in place of sudo apt-get and has
other repositories. The applications can also be linked to the
firefox web browser. as a platform feature.

https://flatpak.org/
https://flatpak.org/setup/Ubuntu/

##6.2. gimp

The package is an image editor supporting many formats and image
filters and operations. It can be used to edit media to change
the lighting, contrast, cropping and transparent areas. As well
converting multiple image formats to a desired input. The
possibilities of making media and formatted for graphic input to
rendering systems is endless. Not long ago, memory in computer
games and performance were more severely attached to mechanism
such as inline blitting and image compositions consisting of
tiled images for views of the object. I am glad that we do not
have to waste time on those little things now, yet there is
somehow more to consider with skia and its abilities.

https://www.gimp.org/

##6.3 inkscape
inkscape is a drawing package that supports svg drawing. There is a team of artists,
some good tutorials and existing content (.svg) files you can tweak. One part of the program
allows you to edit object properties such as the string id. This is is one that you will use in the 
program to name a particular segment or submodel. It is useful to have several assets defined in 
one place.  


##6.4. audacity
An audio editor with excellent digital signal processing
filters. When using sound in games, the input source should be
cleaned, equalized, and at least processed with a limiter. Noise
removal, boosting some frequencies, and using a limiter are easy
with this program. It does support the native Linux sound
processing.

https://www.audacityteam.org/

Advanced audio editing and effects:
* https://calf-studio-gear.org/
	audio dsp high end stuff
* https://lv2plug.in/
	audio plugin
* https://www.audiopluginsforfree.com/Linux/lv2/
	high en audio processing
* blender although going beyond the scope of this introductory tutorial, the package is 
	nice and shouldn't be neglected. 
* lmms
	music production, make pattern beats and panio 
	roll for note editing. Loops made by you.

