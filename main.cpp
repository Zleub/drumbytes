 //           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-11T19:25:36+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-06-14T22:41:28+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <DrumByte.h>
#include <Video.h>

#include <fstream>

int main() {
	Video v(HEIGHT, WIDTH, Video::NOTHING);

	v.run();
	return EXIT_SUCCESS;
}
