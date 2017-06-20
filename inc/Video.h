//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-14T14:30:42+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-06-14T00:27:34+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <DrumByte.h>
#include <Recorder.h>
#include <Player.h>

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
	struct Audio {
		CArray bin;
		sf::Mutex mutex;

		Recorder *record;
		Player *player;
	};

	CArray bin;
	sf::Mutex mutex;
	Recorder record;


	std::vector<Audio *> players;

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
	std::vector<int> shadow_positions;

	float lastTime = 0;

	struct Threshold {
		double bin_start;
		double bin_end;
		double bin_low;
		double bin_high;
	};

	enum Pieces {
		KICK,
		SNARE,
		BASS_TOM,
		HI_HAT,
		RIDE,
		CRASH,
		ENSEMBLE,
		NBR_PIECES
	};

	enum Mode {
		CALIBRATE,
		NOTHING
	};

	Video(size_t, size_t, Mode) ;
	virtual ~Video() ;

	int getWidthRandom(void);
	int getHeightRandom(void);
	int getLifetimeRandom(void);
	double getDoubleRandom(void);

	sf::Color getColorRandom(void);

	Pieces record_piece;
	std::vector<nlohmann::json> memory;

	std::vector<bool> pieces_bool;
	std::vector<sf::RectangleShape> rects;
	std::vector<sf::Image *> images;

	int image_ptr;

	Pieces string_to_pieces(std::string);
	static std::string pieces_to_string(Pieces);
	std::string mode_to_string(Mode);

	void loadImages(void);
	void loadMemory(void);

	void run(void) ;
	void draw(void) ;
	void event(void) ;

	void kick(double intensity) ;
	void snare(double intensity) ;
	void bass_tom(double intensity) ;
	void hi_hat(double intensity) ;
	void ride(double intensity) ;
	void crash(double intensity) ;

private:
	Mode mode;
	size_t width;
	size_t height;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> width_distribution;
	std::uniform_int_distribution<int> height_distribution;
	std::uniform_int_distribution<int> lifetime_distribution;
	std::uniform_real_distribution<double> double_distribution;

	std::uniform_int_distribution<int> color_distribution;
};
