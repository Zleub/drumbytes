//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-15T22:40:30+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-16T02:04:51+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#ifndef PLAYER_H
#define PLAYER_H

#include <DrumByte.h>

class Player : public sf::SoundStream {
public:
	Player(sf::Mutex & mutex, CArray & bin) : mutex(mutex), bin(bin) {};

	void load(const sf::SoundBuffer& buffer) {
		m_samples.assign(buffer.getSamples(), buffer.getSamples() + buffer.getSampleCount());
		m_currentSample = 0;
		initialize(buffer.getChannelCount(), buffer.getSampleRate());
	}

private:
	virtual bool onGetData(Chunk& data) {
		const int samplesToStream = BUFFSIZE;

		data.samples = &m_samples[m_currentSample];
		if (m_currentSample + samplesToStream <= m_samples.size()) {
			std::vector<Complex> sample ;
			size_t bufferSize = samplesToStream;

			sample.resize(bufferSize) ;
			for (size_t i = 0; i < bufferSize; i++) {
				sample[i] = Complex(m_samples[i + m_currentSample]);
			}

			mutex.lock();

			bin = CArray(sample.data(), bufferSize);
			fft(bin) ;

			mutex.unlock();

			data.sampleCount = samplesToStream;
			m_currentSample += samplesToStream;

			return true;
		}
		else {
			data.sampleCount = m_samples.size() - m_currentSample;
			m_currentSample = m_samples.size();
			return false;
		}
	}

	virtual void onSeek(sf::Time timeOffset) {
		m_currentSample = static_cast<std::size_t>(timeOffset.asSeconds() * getSampleRate() * getChannelCount());
	}

	std::vector<sf::Int16> m_samples;
	std::size_t m_currentSample;

	sf::Mutex & mutex;
	CArray & bin;
};

#endif
