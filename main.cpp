//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-11T19:25:36+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-11T22:15:14+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <stk/SineWave.h>
#include <stk/RtAudio.h>


#define WIDTH 512
#define HEIGHT 300

int tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		 double streamTime, RtAudioStreamStatus status, void *dataPointer ) {
	 (void)inputBuffer;
	 (void)streamTime;
	 (void)status;
	 (void)outputBuffer;
	 (void)dataPointer;

	 stk::StkFloat *samples = (stk::StkFloat *) inputBuffer;
	 std::vector<sf::RectangleShape*> v = *reinterpret_cast<std::vector<sf::RectangleShape*>*>(dataPointer);
	 for ( unsigned int i=0; i<nBufferFrames; i++ ) {
		 v[i]->setPosition(i, HEIGHT - HEIGHT * (samples[i]) - 1);
		 v[i]->setSize(sf::Vector2f(1, HEIGHT * (samples[i])));
	 }

	 return 0;
}

int main(void) {

	RtAudio dac;

	std::cout << "---- ---- ---- ----" << std::endl;
	std::cout << dac.getDeviceCount() << " input devices." << std::endl;

	for (size_t i = 0; i < dac.getDeviceCount(); i++) {
		RtAudio::DeviceInfo di = dac.getDeviceInfo(i);
		std::cout << "---- ---- ---- ----" << std::endl;
		std::cout << "probed: " << di.probed << std::endl;
		std::cout << "name: " << di.name << std::endl;
		std::cout << "outputChannels: " << di.outputChannels << std::endl;
		std::cout << "inputChannels: " << di.inputChannels << std::endl;
		std::cout << "duplexChannels: " << di.duplexChannels << std::endl;
		std::cout << "isDefaultOutput: " << di.isDefaultOutput << std::endl;
		std::cout << "isDefaultInput: " << di.isDefaultInput << std::endl;
		std::cout << "preferredSampleRate: " << di.preferredSampleRate << std::endl;
	}

	std::cout << "---- ---- ---- ----" << std::endl;
	std::cout << "DefaultInputDevice: " << dac.getDeviceInfo(dac.getDefaultInputDevice()).name << std::endl;
	std::cout << "---- ---- ---- ----" << std::endl;


	std::vector<sf::RectangleShape *> v;
	for (size_t i = 0; i < WIDTH; i++) {
		sf::RectangleShape *r = new sf::RectangleShape();
		r->setSize(sf::Vector2f(1, HEIGHT));
		r->setPosition(i, WIDTH);

		v.push_back( r );
	}

	stk::SineWave sine;
	RtAudio::StreamParameters parameters;
	parameters.deviceId = dac.getDefaultInputDevice();
	parameters.nChannels = 2;
	RtAudioFormat format = ( sizeof(stk::StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
	unsigned int bufferFrames = stk::RT_BUFFER_SIZE;
	dac.openStream( NULL, &parameters, format, 48000, &bufferFrames, &tick, (void *)&v );
	dac.startStream();

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML window");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
		std::for_each( v.begin(), v.end(), [&](sf::RectangleShape *r){
			window.draw(*r);
		});

        window.display();
    }

    return EXIT_SUCCESS;
}
