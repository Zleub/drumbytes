//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-14T14:28:17+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-06-20T16:39:35+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <DrumByte.h>
#include <Video.h>

#include <queue>
#include <csignal>

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

#define RECT_WIDTH (WIDTH / 10)

Video::Video(size_t width, size_t height, Mode mode) :
	mode(mode),
	width(width), height(height),
	record(mutex, bin),
	players(NBR_PIECES),
	width_distribution(0, width - 1), height_distribution(0, height - 1),
	lifetime_distribution(0, 200), double_distribution(0.0, 1.0),
	color_distribution(0, colors.size() - 1),
	quantity(width * height),
	memory(NBR_PIECES),
	pieces_bool(NBR_PIECES),
	rects(NBR_PIECES)
{
	window.create(sf::VideoMode(width, height), "SFML window");
	window.setSize(sf::Vector2u(width * ZOOM, height * ZOOM));
	window.setFramerateLimit(60);

	font.loadFromFile("Roboto-Regular.ttf");

	loadImages();

	image_ptr = 0;

	VA.setPrimitiveType(sf::Points);
	for (size_t i = 0; i < width * height; i++) {
		VA.append( sf::Vertex( sf::Vector2f(i % width, i / width), sf::Color::Black) );
		life.push_back(0);
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

	std::cerr << width << " x " << height << " = " << quantity << std::endl;

	for (size_t i = 0; i < NBR_PIECES; i++) {
		players[i] = new Audio();
		players[i]->player = new Player(players[i]->mutex, players[i]->bin);
		// players[i]->record = new Recorder(players[i]->mutex, players[i]->bin);
	}
};

Video::~Video() {}

void Video::loadImages(void) {
	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir ("./images")) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			if (std::string(ent->d_name) != "." && std::string(ent->d_name) != "..") {
				std::string filename(ent->d_name);
				std::cout << "Loading " << filename << std::endl;

				sf::Image *i = new sf::Image;
				i->loadFromFile("./images/" + filename);
				images.push_back(i);

			}
		}
		closedir (dir);
	}
	else
		std::cout << "Could not open directory" << std::endl;
}

void Video::loadMemory(void) {
	struct stat s;

	if (stat("./memory", &s) == -1) {
		std::cout << "Warning: No memory directory" << std::endl;
	}

	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir ("./memory")) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			if (std::string(ent->d_name) != "." && std::string(ent->d_name) != "..") {
				std::string filename(ent->d_name);
				std::cout << filename << std::endl;

				std::smatch sm;
				std::regex_match(filename, sm, std::regex("([A-z]+)\\.([A-z]+)"));
				std::cout << "\t" << sm[1] << std::endl;

				std::ifstream i("./memory/" + filename);
				i >> memory[string_to_pieces(sm[1])];
				std::cout << string_to_pieces(sm[1]) << std::endl;
			}
		}
		closedir (dir);
	}
	else
		std::cout << "Could not open directory" << std::endl;
}

void Video::kick(double intensity) {
	size_t quantity = round(intensity * (width * height) / 10);
	std::cout << "bass drum: " << intensity << std::endl;

	for (size_t i = 0; i < quantity; i++) {
		int w = width_distribution(generator);
		int h = height_distribution(generator);
		int l = lifetime_distribution(generator);

		sf::Color c = images[image_ptr]->getPixel(w, h);
		double _c = ((c.r + c.g + c.b) / 3) / 127;

		// std::cout << _c << std::endl;
		if (_c > 0.5) {
			VA[(w + h * width)].color = sf::Color::White;
			life[w + h * width] = l;
			positions.push_back(w + h * width);
		}
	}

	image_ptr += 1;
	if (image_ptr >= images.size())
		image_ptr = 0;
}

void Video::snare(double intensity) {
	int quantity = round((intensity * height));
	std::cout << "snare: " << intensity << std::endl;

	std::for_each(positions.begin(), positions.end(), [&](int & i) {

		sf::Color color = getColorRandom();
		int l = lifetime_distribution(generator);
		for (int _ = 0; _ < quantity / 16; _++) {
			int pos = i + _ * width;
			int _pos = i - _ * width;

			if (pos > 0 && pos < width * height) {
				VA[pos].color = sf::Color::White;
				life[pos] = l;
				shadow_positions.push_back(pos);
			}
			if (_pos > 0 && _pos < width * height) {
				VA[_pos].color = sf::Color::White;
				life[_pos] = l;
				shadow_positions.push_back(_pos);
			}
		}
	});
}

void Video::bass_tom(double intensity) {
	int quantity = round((intensity * height));
	std::cout << "bass tom" << std::endl;

	std::for_each(positions.begin(), positions.end(), [&](int & i) {

		sf::Color color = getColorRandom();
		int l = lifetime_distribution(generator);
		for (int _ = 0; _ < quantity / 8; _++) {
			int pos = i + _ ;
			int _pos = i - _ ;

			if (pos > 0 && pos < width * height) {
				VA[pos].color = sf::Color::White;
				life[pos] = l;
				shadow_positions.push_back(pos);
			}
			if (_pos > 0 && _pos < width * height) {
				VA[_pos].color = sf::Color::White;
				life[_pos] = l;
				shadow_positions.push_back(_pos);
			}
		}
	});
}

void Video::hi_hat(double intensity) {
	int quantity = round((intensity * height));
	std::cout << "hi_hat" << std::endl;

	std::for_each(positions.begin(), positions.end(), [&](int & i) {
			VA[i].color.g = intensity * 255;
			VA[i].color.b = intensity * 255;
	});
	std::for_each(shadow_positions.begin(), shadow_positions.end(), [&](int & i) {
			VA[i].color.g = intensity * 255;
			VA[i].color.b = intensity * 255;
	});
}

void Video::ride(double intensity) {
	int quantity = round((intensity * height));
	std::cout << "ride" << std::endl;

	std::for_each(positions.begin(), positions.end(), [&](int & i) {
			VA[i].color.r = intensity * 255;
			VA[i].color.b = intensity * 255;
	});
	std::for_each(shadow_positions.begin(), shadow_positions.end(), [&](int & i) {
			VA[i].color.r = intensity * 255;
			VA[i].color.b = intensity * 255;
	});
}

void Video::crash(double intensity) {
	int quantity = round((intensity * height));
	std::cout << "crash" << std::endl;

	std::for_each(positions.begin(), positions.end(), [&](int & i) {
			VA[i].color.g = intensity * 255;
			VA[i].color.r = intensity * 255;
	});
	std::for_each(shadow_positions.begin(), shadow_positions.end(), [&](int & i) {
			VA[i].color.g = intensity * 255;
			VA[i].color.r = intensity * 255;
	});
}

void Video::event() {
	sf::Event event;

	float currentTime = clock.restart().asSeconds();
	float fps = 1.f / currentTime;
	lastTime = currentTime;

	if (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num1)) {
			double intensity = double_distribution(generator);
			kick(intensity);
		}
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num2)) {
			double intensity = double_distribution(generator);
			snare(intensity);
		}
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num3)) {
			double intensity = double_distribution(generator);
			bass_tom(intensity);
		}
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num4)) {
			double intensity = double_distribution(generator);
		}
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num5)) {
			double intensity = double_distribution(generator);
			ride(intensity);
		}
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num6)) {
			double intensity = double_distribution(generator);
			crash(intensity);
		}
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
			std::ofstream o("./memory/" + pieces_to_string(record_piece) + ".json");
			o << std::setw(4) << memory[record_piece] << std::endl;
			record.stop();
			exit(0);
		}

		// if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
		// 	if (mode == CALIBRATE)
		// 		mode = NOTHING;
		// 	else
		// 		mode = CALIBRATE;
		// }
	}
}

void Video::run() {
	int __ = 0;

	std::vector<std::string> buffers = {
		"/Volumes/ADEBRAY/Downloads/Samples Batterie/07-Ensemble Brut/01-kick.wav",
		"/Volumes/ADEBRAY/Downloads/Samples Batterie/07-Ensemble Brut/02-snare.wav",
		"/Volumes/ADEBRAY/Downloads/Samples Batterie/07-Ensemble Brut/03-tombass.wav",
		"/Volumes/ADEBRAY/Downloads/Samples Batterie/07-Ensemble Brut/04-hihat.wav",
		"/Volumes/ADEBRAY/Downloads/Samples Batterie/07-Ensemble Brut/06-ride.wav",
		"/Volumes/ADEBRAY/Downloads/Samples Batterie/07-Ensemble Brut/05-crash.wav"
	};

	if (mode == NOTHING) {
		loadMemory();

		// std::vector<sf::SoundBuffer> bufferVector(buffers.size());

		// for (size_t i = 0; i < buffers.size(); i++) {
		// 	if (buffers[i] != "") {
		// 		bufferVector[i].loadFromFile(buffers[i]);
		// 		players[i]->player->load(bufferVector[i]);
		// 	}
		// }

		// for (size_t i = 0; i < buffers.size(); i++) {
		// 	if (buffers[i] != "") {
		// 		players[i]->player->play();
		// 	}
		// }

		record.start();

		std::cout << "Loaded buffers" << std::endl;

	}
	else {
		record_piece = SNARE;

		// sf::SoundBuffer buffer;
		//
		// buffer.loadFromFile(buffers[__]);
		//
		// players[record_piece]->player->load(buffer);
		// players[record_piece]->player->play();

		record.start();
	}

	std::vector< std::pair<double, int> > timeline(NBR_PIECES, {0, 0});

	while (window.isOpen())
	{
		event();


		if (mode == CALIBRATE) {

			if (record.bin.size() > 0) {
				record.mutex.lock();

				std::priority_queue<std::pair<int, int>> q;
				for (size_t i = 0; i < 4000; i += 1) {
					q.push(std::pair<int, int>( abs( record.bin[i] ), i) );
				}

				record.mutex.unlock();

				int k = CALIBRATE_SIZE;

				for (int j = 0; j < k; ++j) {
					if (q.top().first > 1500) {
						if (memory[record_piece][q.top().second] != nullptr && q.top().first > (int)memory[record_piece][q.top().second]) {
							memory[record_piece][q.top().second] = q.top().first;
						}
						else
							memory[record_piece][q.top().second] = q.top().first;

						q.pop();
					}
				}

			}

		}
		else if (mode == NOTHING) {

			std::priority_queue<std::pair<int, int>> q;
			if (record.bin.size() != 0) {
				record.mutex.lock();

				for (size_t j = 0; j < 4000; j += 1) {
					q.push(std::pair<int, int>( abs( record.bin[j] ), j) );
				}

				record.mutex.unlock();

				for (size_t i = 0; i < NBR_PIECES; i++) {
					std::priority_queue<std::pair<int, int>> _q(q);
					int match = 0;
					double max = _q.top().first;

					for (size_t _ = 0; _ < CALIBRATE_SIZE; _ += 1) {
						int k = _q.top().second;
						if (_q.top().first > 1500 && memory[i] != nullptr && memory[i][k] != nullptr) {
							match += 1;
						}

						_q.pop();
					}
					if (match > CALIBRATE_SIZE / 2) {
						// std::cout << i << " : " << match << std::endl;
						if (max != timeline[i].first || match != timeline[i].second) {
							if (i == 0)
								kick( max / 5000000. );
							else if (i == 1)
								snare( max / 1000000. );
							else if (i == 2)
								bass_tom( max / 5000000. );
							else if (i == 3)
								hi_hat( max / 5000000. );
							else if (i == 4)
								ride( max / 5000000. );
							else if (i == 5)
								crash( max / 5000000. );
							timeline[i] = {max, match};
						}
					}
				}
			}
		}

		draw();
	}
}

void Video::draw() {
	window.clear();

	std::for_each(positions.begin(), positions.end(), [&](int & i) {
		life[i] -= 1;
		if (life[i] < 0) {
			VA[i].color = sf::Color::Black;
		}
	});

	positions.erase(
    	std::remove_if( positions.begin(), positions.end(), [&](int & i) -> bool { return life[i] < 0; } ),
    	positions.end()
	);

	std::for_each(shadow_positions.begin(), shadow_positions.end(), [&](int & i) {
		life[i] -= 1;
		if (life[i] < 0) {
			VA[i].color = sf::Color::Black;
		}
	});

	shadow_positions.erase(
    	std::remove_if( shadow_positions.begin(), shadow_positions.end(), [&](int & i) -> bool { return life[i] < 0; } ),
    	shadow_positions.end()
	);

	VA.setPrimitiveType(sf::Points) ;
	window.draw(VA) ;
	window.display();
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

Video::Pieces Video::string_to_pieces(std::string p) {
	if (p == "kick") { return KICK ; }
	if (p == "snare") { return SNARE ; }
	if (p == "bass_tom") { return BASS_TOM ; }
	if (p == "hi_hat") { return HI_HAT ; }
	if (p == "ride") { return RIDE ; }
	if (p == "crash") { return CRASH ; }
	return NBR_PIECES ;
}

std::string Video::mode_to_string(Mode m) {
	switch (m) {
		case CALIBRATE : return "CALIBRATE" ; break ;
		case NOTHING : return "NOTHING" ; break ;
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
