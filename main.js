#!/usr/bin/env node

//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-05-31T15:55:38+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-05-31T16:05:12+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

const http = require('http');
const fs = require('fs');

const server = http.createServer((req, res) => {
	let {url} = req

	if (url == "/") url = "/index.html"
	fs.readFile("." + url, (err, data) => {
	  if (err)
	  	res.end("", 404);
	  res.end(data);
	});
});

server.listen(8000);
