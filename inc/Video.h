//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-14T14:30:42+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-16T01:54:24+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <DrumByte.h>

class Video;

class Particule {
public:
	sf::RectangleShape rect;
	unsigned int life;

	Particule() ;
	Particule(sf::Color) ;
	virtual ~Particule() ;

	void setLife(unsigned int) ;
	void update(void) ;
	void draw(sf::RenderWindow &) ;
};

class Video {
public:
	sf::Font font;

	std::vector<sf::Color> colors = {
		sf::Color::White,
		sf::Color::Red,
		sf::Color::Green,
		sf::Color::Blue,
		sf::Color::Yellow,
		sf::Color::Magenta,
		sf::Color::Cyan
	};

	size_t quantity;
	sf::RenderWindow window;
	sf::Clock clock;

	sf::VertexArray VA;
	std::vector<int> life;
	std::vector<int> positions;

	float lastTime = 0;

	Video(size_t, size_t) ;
	virtual ~Video() ;

	void run(sf::Mutex & mutex, CArray & bin) ;

	int getWidthRandom(void);
	int getHeightRandom(void);
	int getLifetimeRandom(void);
	double getDoubleRandom(void);

	sf::Color getColorRandom(void);

	enum Pieces {
		KICK,
		SNARE,
		BASS_TOM,
		HI_HAT,
		RIDE,
		CRASH,
		NBR_PIECES
	};

	std::string pieces_to_string(Pieces);

	std::vector<bool> pieces_bool;
	std::vector<sf::RectangleShape> rects;

private:
	size_t width;
	size_t height;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> width_distribution;
	std::uniform_int_distribution<int> height_distribution;
	std::uniform_int_distribution<int> lifetime_distribution;
	std::uniform_real_distribution<double> double_distribution;

	std::uniform_int_distribution<int> color_distribution;
};
