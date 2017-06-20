//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-15T22:40:18+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-06-14T00:22:29+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <Player.h>

Player::Player(sf::Mutex & mutex, CArray & bin) : mutex(mutex), bin(bin) {}

void Player::load(const sf::SoundBuffer& buffer) {
	m_samples.assign(buffer.getSamples(), buffer.getSamples() + buffer.getSampleCount());
	m_currentSample = 0;
	initialize(buffer.getChannelCount(), buffer.getSampleRate());
}

bool Player::onGetData(Chunk& data) {
	const int samplesToStream = BUFFSIZE;

	data.samples = &m_samples[m_currentSample];
	size_t bufferSize = samplesToStream;
	if (m_currentSample + samplesToStream <= m_samples.size()) {
		std::vector<Complex> sample ;

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
		mutex.lock();

		bin = CArray(Complex(0), bufferSize);

		mutex.unlock();


		data.sampleCount = m_samples.size() - m_currentSample;
		m_currentSample = m_samples.size();
		return false;
	}
}

void Player::onSeek(sf::Time timeOffset) {
	m_currentSample = static_cast<std::size_t>(timeOffset.asSeconds() * getSampleRate() * getChannelCount());
}
