//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-15T01:08:45+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-16T03:42:04+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#ifndef DRUMBYTE_H
#define DRUMBYTE_H

#include <iostream>
#include <complex>
#include <valarray>
#include <random>

#define PI (3.141592653589793238460)

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define WIDTH (int)(2048)
#define HEIGHT (int)(300)
#define ZOOM (int)(1)

#define BUFFSIZE 16384

void fft(CArray & x);

#endif
