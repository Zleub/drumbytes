//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-14T14:28:17+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-16T03:51:59+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <DrumByte.h>
#include <Video.h>

#include <queue>

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

#define RECT_WIDTH 200

Video::Video(size_t width, size_t height) :
	width(width), height(height),
	width_distribution(0, width - 1), height_distribution(0, height - 1),
	lifetime_distribution(0, 200), double_distribution(0.0, 1.0),
	color_distribution(0, colors.size() - 1),
	quantity(width * height),
	pieces_bool(NBR_PIECES),
	rects(NBR_PIECES)
{
	window.create(sf::VideoMode(width, height), "SFML window");
	window.setSize(sf::Vector2u(width * ZOOM, height * ZOOM));

	font.loadFromFile("Roboto-Regular.ttf");

	VA.setPrimitiveType(sf::Points);
	for (size_t i = 0; i < width; i++) {
		VA.append( sf::Vertex( sf::Vector2f(i % width, i / width), sf::Color::White) );
		VA.append( sf::Vertex( sf::Vector2f(i % width, i / width), sf::Color::White) );
		// VA.append( sf::Vertex( sf::Vector2f(i % width + 1, i / width + 1), sf::Color::Black) );
		// VA.append( sf::Vertex( sf::Vector2f(i % width + 1, i / width + 0), sf::Color::Black) );
		// life.push_back(0);
	}

	int i = 0;
	std::for_each(rects.begin(), rects.end(), [&](sf::RectangleShape & r) {
		r.setSize( sf::Vector2f(RECT_WIDTH, 42) );
		r.setPosition( width - RECT_WIDTH - 1 - i * RECT_WIDTH, 0);
		r.setFillColor(sf::Color::Black);
		r.setOutlineColor(sf::Color::White);
		r.setOutlineThickness(4);
		i += 1;
	});

	std::cout << width << " x " << height << " = " << quantity << std::endl;
};
Video::~Video() {}

void Video::run(sf::Mutex & mutex, CArray & bin) {
	while (window.isOpen())
	{
		sf::Event event;

		float currentTime = clock.asSeconds();
		float fps = 1.f / currentTime;
		lastTime = currentTime;

		// std::cout << "fps: " << std::to_string(fps) << std::endl ;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num1)) {
				double intensity = double_distribution(generator);
				size_t quantity = round(intensity * (width * height) / 100);
				std::cout << "bass drum" << std::endl;
				std::cout << intensity << std::endl;
				std::cout << quantity << std::endl;

				for (size_t i = 0; i < quantity; i++) {
					int w = width_distribution(generator);
					int h = height_distribution(generator);
					int l = lifetime_distribution(generator);
					VA[w + h * width].color = getColorRandom();
					life[w + h * width] = l;
					positions.push_back(w + h * width);
				}

			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num2)) {
				double intensity = double_distribution(generator);
				size_t quantity = round(intensity * (width * height) / 100);
				std::cout << "snare" << std::endl;
				std::cout << intensity << std::endl;
				std::cout << quantity << std::endl;

			}
		}


		// texture.update(image);
		// window.draw(sprite);

		window.clear();

		mutex.lock();
		// size_t i = 0;
		//
		float divisor = 30000 ;
		// VA.setPrimitiveType(sf::Lines) ;
		size_t w = 0;

		// exit(0);
		int imax = -1;
		int max = -1;
		std::priority_queue<std::pair<int, int>> q;
		for (size_t i = 0; i < BUFFSIZE / 2; i += 2) {

			q.push(std::pair<int, int>(abs(bin[i]), i));

			double h = abs(bin[i]) / divisor;
			int indx = ((float)WIDTH / (float)BUFFSIZE) * i ;
			// if (indx - 1 > 0)
			VA[indx].position = sf::Vector2f(w / 32, height);
			// VA[indx].position = sf::Vector2f(w, height - h * 8);
			w += 1;
		}
		//
		int k = 129;
		w = 0;
		for (int j = 0; j < k; ++j) {
		    int ki = q.top().second;

			int i = ((float)WIDTH / (float)BUFFSIZE) * ki ;
			// std::cout << q.top().first << std::endl;
			// std::cout << BUFFSIZE / WIDTH << std::endl;
			std::cout << currentTime << " : " << ki << std::endl;
			double h = abs(bin[i]) / divisor;
			VA[i].position = sf::Vector2f(w * 4, height - h * 8);
			// VA[i + 1].position = sf::Vector2f(w * 4, height - h * 8);

		    q.pop();
			w += 1;
		  }



		// 	// VA[i].color = sf::Color::Black;
		// 	// VA[i + 1].color = sf::Color::Black;
		// 	// particules[i].rect.setSize(sf::Vector2f(1, height * h));
		// 	// particules[i].rect.setPosition(i, height - h);
		// 	// particules[i].draw(window);

		// std::cout << imax << std::endl;

		mutex.unlock();



		int i = 0;
		std::for_each(pieces_bool.begin(), pieces_bool.end(), [&](bool b) {
			if (b)
				rects[i].setOutlineColor(sf::Color::Red);
			else
				rects[i].setOutlineColor(sf::Color::White);
			window.draw(rects[i]);
			sf::Text text;
			text.setFont(font);
			text.setString(pieces_to_string(Pieces(i)));
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::White);
			text.setPosition( width - RECT_WIDTH - 1 - i * RECT_WIDTH + 10, 0);
			window.draw(text);
			i += 1;
		});

		// std:for_each(positions.begin(), positions.end(), [&](int & i) {
		// 	life[i] -= 1;
		// 	if (life[i] < 0) {
		// 		VA[i].color = sf::Color::Black;
		// 	}
		// });

		window.draw(VA) ;
		window.display();

	}
}

std::string Video::pieces_to_string(Pieces p) {
	switch (p) {
		case KICK : return "kick" ; break ;
		case SNARE : return "snare" ; break ;
		case BASS_TOM : return "bass_tom" ; break ;
		case HI_HAT : return "hi_hat" ; break ;
		case RIDE : return "ride" ; break ;
		case CRASH : return "crash" ; break ;
		default : return "NULL" ; break ;
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
