//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-14T14:28:17+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-15T01:19:30+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <DrumByte.h>
#include <Video.h>

Particule::Particule() {
	rect.setSize( sf::Vector2f(1, 1) );
}
Particule::Particule(sf::Color color) {
	rect.setSize( sf::Vector2f(1, 1) );
	rect.setFillColor(color);
}
Particule::~Particule() {}

void Particule::setLife(unsigned int l) {
	life = l;
}

void Particule::update(void) {
	life > 0 ? life -= 1 : 0 ;
}

void Particule::draw(sf::RenderWindow & window) {
	window.draw(rect);
}

Video::Video(size_t width, size_t height) :
	width(width), height(height),
	width_distribution(0, width - 1), height_distribution(0, height - 1),
	lifetime_distribution(0, 200), double_distribution(0.0, 1.0),
	color_distribution(0, colors.size() - 1),
	quantity(width),
	particules(quantity)
{
	image.create(width, height, sf::Color::Black);
	texture.create(width, height);
	texture.update(image);
	sprite.setTexture(texture);

	window.create(sf::VideoMode(width, height), "SFML window");

	for (size_t i = 0; i < quantity; i++) {
		particules[i].life = 0;
		particules[i].rect.setPosition(i % width, i / height);
		particules[i].rect.setFillColor(sf::Color::Red);
	}

	std::cout << width << " x " << height << " = " << quantity << std::endl;
};
Video::~Video() {}

void Video::run(sf::Mutex & mutex, CArray & bin) {
	while (window.isOpen())
	{
		sf::Event event;

		float currentTime = clock.restart().asSeconds();
		float fps = 1.f / currentTime;
		lastTime = currentTime;

		// std::cout << "fps: " << std::to_string(fps) << std::endl ;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			// if (event.type == sf::Event::KeyPressed)
			// 	std::cout << "fps: " << fps << std::endl;
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num1)) {
				double intensity = double_distribution(generator);
				size_t quantity = round(intensity * (width * height) / 100);
				std::cout << "bass drum" << std::endl;
				std::cout << intensity << std::endl;
				std::cout << quantity << std::endl;

				for (size_t i = 0; i < quantity; i++) {
					int w = width_distribution(generator);
					int h = height_distribution(generator);
					int life = lifetime_distribution(generator);
					particules[w + h * width].setLife( life );
				}
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num2)) {
				double intensity = double_distribution(generator);
				size_t quantity = round(intensity * (width * height) / 100);
				std::cout << "snare" << std::endl;
				std::cout << intensity << std::endl;
				std::cout << quantity << std::endl;

			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				image.create(width, height, sf::Color::Black);
		}


		window.clear();
		texture.update(image);
		window.draw(sprite);

		mutex.lock();
		size_t i = 0;

		float max = 1000 ;
		VA.clear();
		VA.setPrimitiveType(sf::Lines) ;
		for (size_t i = 0; i < 512 / 2; i++) {
			double h = abs(bin[i]) / max;

			VA.append( sf::Vertex( sf::Vector2f(i, height), sf::Color::White)) ;
			VA.append( sf::Vertex( sf::Vector2f(i, height - h),        sf::Color::White)) ;

			// particules[i].rect.setSize(sf::Vector2f(1, height * h));
			// particules[i].rect.setPosition(i, height - h);
			// particules[i].draw(window);
		}
		window.draw(VA) ;

		// std::for_each(particules.begin(), particules.end(), [&](Particule & p){
		// 	p.update();
		// 	i += 1;
		// });

		window.display();

		mutex.unlock();
	}
}

int Video::getWidthRandom(void) {
	return width_distribution(generator);
}
int Video::getHeightRandom(void) {
	return height_distribution(generator);
}
int Video::getLifetimeRandom(void) {
	return lifetime_distribution(generator);
}
double Video::getDoubleRandom(void) {
	return double_distribution(generator);
}
sf::Color Video::getColorRandom(void) {
	return colors[ color_distribution(generator) ];
}
