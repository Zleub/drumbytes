 //           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-11T19:25:36+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-16T03:17:05+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <DrumByte.h>
#include <Recorder.h>
#include <Video.h>
#include <Player.h>

CArray bin(1024);
sf::Mutex mutex;

#include <fstream>

int main() {
	// Recorder record(mutex, bin);
	Player player(mutex, bin);
	Video v(WIDTH, HEIGHT);

	sf::SoundBuffer buffer;

	std::vector<std::string> files;
	std::string line;
	std::ifstream f("file_list");

	if (f.is_open()) {
	  while (!f.eof()) {
	    getline(f, line);
		files.push_back(std::string(line));
	  }
	  f.close();
	}

	// std::for_each(files.begin(), files.end(), [](std::string f) {
	// 	std::cout << f << std::endl;
	// });

	// buffer.loadFromFile("./samples/01 - Hi-hat.wav");
	// buffer.loadFromFile("./samples/02 - Ride.wav");
	// buffer.loadFromFile("./samples/03 - Crash.wav");
	buffer.loadFromFile("./samples/04 - Grosse Caisse.wav");
	// buffer.loadFromFile("drumkit/snare/snare-top28.wav");
	// buffer.loadFromFile("./samples/06 - Tom Basse.wav");
	// buffer.loadFromFile("./samples/sine1.wav");
	// buffer.loadFromFile("./samples/sinewave1.wav");

	player.load(buffer);
	player.play();

	// record.start();
	v.run(mutex, bin);

	return EXIT_SUCCESS;
}
