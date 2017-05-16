//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-14T16:29:09+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-15T16:40:41+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <DrumByte.h>

class Recorder : public sf::SoundRecorder
{
private:
	CArray & bin;
	sf::Mutex & mutex;
public:
	Recorder(sf::Mutex &, CArray &) ;
	~Recorder() ;

	bool onStart() ;
	bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount) ;
	void onStop() ;
};
