//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-15T01:08:45+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-06-13T20:36:18+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#ifndef DRUMBYTE_H
#define DRUMBYTE_H

extern "C" {
	#include <sys/stat.h>
	#include <dirent.h>
}

#include <fstream>
#include <iostream>
#include <complex>
#include <valarray>
#include <random>
#include <regex>

#define PI (3.141592653589793238460)

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define WIDTH (int)(600)
#define HEIGHT (int)(800)
#define ZOOM (int)(2)

#define BUFFSIZE (16384 / 2)
#define CALIBRATE_SIZE 256

void fft(CArray & x);

#include <json.hpp>

#endif
