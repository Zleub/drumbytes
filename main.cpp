 //           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-11T19:25:36+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-13T04:53:57+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <iostream>
#include <random>
#include <array>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define WIDTH (800 * 2)
#define HEIGHT (600 * 2)

extern "C" {
	#include <kiss_fft.h>
};

std::default_random_engine generator;
std::uniform_int_distribution<int> width_distribution(0, WIDTH - 1);
std::uniform_int_distribution<int> height_distribution(0, HEIGHT - 1);
std::uniform_int_distribution<int> lifetime_distribution(0, 200);
std::uniform_real_distribution<double> double_distribution(0.0,0.5);

std::vector<sf::Color> colors = {
	sf::Color::White,
	sf::Color::Red,
	sf::Color::Green,
	sf::Color::Blue,
	sf::Color::Yellow,
	sf::Color::Magenta,
	sf::Color::Cyan
};
std::uniform_int_distribution<int> color_distribution(1, colors.size());

typedef struct s_particule t_particule;
struct s_particule {
	sf::RectangleShape rect;
	double life;
};

int main(void) {

	sf::Image image;
	image.create(WIDTH, HEIGHT, sf::Color::Black);

	sf::Texture texture;
	texture.create(WIDTH, HEIGHT);
	texture.update(image);

	sf::Sprite sprite(texture);

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML window");

	sf::Clock clock;
	float lastTime = 0;

	kiss_fft_cfg cfg = kiss_fft_alloc( 512 ,0 ,0,0 );
	(void)cfg;

	t_particule * particules = (t_particule *)malloc(sizeof(t_particule) * WIDTH * HEIGHT );
	(void)particules;

	for (size_t i = 0; i < WIDTH * HEIGHT; i++) {
		particules[i].life = 0;
		sf::RectangleShape * r = &(particules[i].rect);
		sf::Vector2f s(10, 10);
		r->setSize( s );
		r->setPosition(i % WIDTH, i / WIDTH);
	}

	std::cout << WIDTH << " x " << HEIGHT << " = " << WIDTH * HEIGHT << std::endl;

	while (window.isOpen())
	{
		sf::Event event;

		float currentTime = clock.restart().asSeconds();
		float fps = 1.f / (currentTime - lastTime);
		lastTime = currentTime;

		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				std::cout << "fps: " << fps << std::endl;
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num1)) {
				double intensity = double_distribution(generator);
				size_t quantity = round(intensity * (WIDTH * HEIGHT) / 100);
				std::cout << "bass drum" << std::endl;
				std::cout << intensity << std::endl;
				std::cout << quantity << std::endl;

				for (size_t i = 0; i < quantity; i++) {
					int w = width_distribution(generator);
					int h = height_distribution(generator);
					int life = lifetime_distribution(generator);
					particules[w + h * WIDTH].life = life;
				}
 			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num2)) {
				double intensity = double_distribution(generator);
				size_t quantity = round(intensity * (WIDTH * HEIGHT) / 100);
				std::cout << "snare" << std::endl;
				std::cout << intensity << std::endl;
				std::cout << quantity << std::endl;

			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				image.create(WIDTH, HEIGHT, sf::Color::Black);
		}

		// for (size_t i = 0; i < WIDTH * HEIGHT; i++) {
		// 	particules[i] -= 1;
		// 	if (particules[i] < 0)
		// 		image.setPixel(i % WIDTH, floor(i / WIDTH), sf::Color::Black);
		// 	i += 1;
		// }

		window.clear();
		texture.update(image);
		window.draw(sprite);
		// for (size_t i = 0; i < WIDTH * HEIGHT; i++) {
			// particules[i].draw(&window);
		// }
		window.display();
	}

	return EXIT_SUCCESS;
}
