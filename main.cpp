 //           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-11T19:25:36+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-15T01:19:50+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#define WIDTH (int)(512)
#define HEIGHT (int)(300)

#include <DrumByte.h>
#include <Recorder.h>
#include <Video.h>

CArray bin(1024);
sf::Mutex mutex;

int main() {
	Recorder record(mutex, bin);
	Video v(WIDTH, HEIGHT);

	record.start();
	v.run(mutex, bin);

	return EXIT_SUCCESS;
}
