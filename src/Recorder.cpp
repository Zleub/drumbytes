//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-15T01:20:05+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-15T01:23:47+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <Recorder.h>

void fft(CArray & x)
{
	const int N = x.size();
	if (N <= 1)
		return;

	CArray even = x[std::slice(0, N / 2, 2)];
	CArray  odd = x[std::slice(1, N / 2, 2)];

	fft(even);
	fft(odd);

	for(int k = 0 ; k < N / 2 ; k++)
	{
		Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
		x[k] = even[k] + t;
		x[k + N / 2] = even[k] - t;
	}
}

Recorder::Recorder(sf::Mutex & mutex, CArray & bin) : bin(bin), mutex(mutex) {
	std::vector<std::string> devices = sf::SoundRecorder::getAvailableDevices();
	std::for_each(devices.begin(), devices.end(), [](std::string s){
		std::cout << s << std::endl;
	});

	setProcessingInterval(sf::Time::Zero);
}

Recorder::~Recorder() {
	stop();
}

bool Recorder::onStart() {
	std::cout << "record start" << std::endl;
	return true;
}

bool Recorder::onProcessSamples(const sf::Int16* samples, std::size_t sampleCount) {
	std::vector<Complex> sample ;
	size_t bufferSize = sampleCount > 512 ? 512 : sampleCount;

	std::cout << "record: " << bufferSize << std::endl;

	sample.resize(bufferSize) ;
	for (size_t i = 0; i < bufferSize; i++) {
		sample[i] = Complex(samples[i]);
	}

	mutex.lock();

	bin = CArray(sample.data(), bufferSize);
	fft(bin) ;

	mutex.unlock();

	return true;
}

void Recorder::onStop() {
	std::cout << "record end" << std::endl;
}
