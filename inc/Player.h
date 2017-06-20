//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-15T22:40:30+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-06-14T00:23:24+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#ifndef PLAYER_H
#define PLAYER_H

#include <DrumByte.h>

class Player : public sf::SoundStream {
public:
	Player(sf::Mutex &, CArray &);
	void load(const sf::SoundBuffer&);

private:
	sf::Mutex & mutex;
	CArray & bin;

	std::vector<sf::Int16> m_samples;
	std::size_t m_currentSample;

	bool onGetData(Chunk &);
	void onSeek(sf::Time);
};

#endif
