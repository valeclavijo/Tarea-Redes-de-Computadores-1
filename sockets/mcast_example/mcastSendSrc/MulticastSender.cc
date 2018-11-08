/*
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "YASL.h"  // For UDPSocket and SocketException
#include <iostream>           // For cout and cerr
#include <cstdlib>            // For atoi()

#ifdef WIN32
#include <windows.h>          // For ::Sleep()
void sleep(unsigned int seconds) {::Sleep(seconds * 1000);}
#else
#include <unistd.h>           // For sleep()
#endif


//using namespace std;

int main(int argc, char *argv[]) {
  if ((argc < 4) || (argc > 5)) {   // Test for correct number of arguments
    std::cerr << "Usage: " << argv[0] 
         << " <Destination Address> <Destination Port> <Send String> [<TTL>]\n";
    exit(EXIT_FAILURE);
  }

  std::string servAddress = argv[1];        // First arg: multicast address
  uint16_t    port        = atoi(argv[2]);  // Second arg: port
  std::string sendString  = argv[3];        // Third arg: string to echo

  uint8_t multicastTTL = 1;       // Default TTL
  if (argc == 5) {
    multicastTTL = atoi(argv[4]);       // Command-line TTL
  }

  try {
    UDPSocket sock;

    sock.setMulticastTTL(multicastTTL);

    // Repeatedly send the string to the server
    for (;;) {
      sock.sendTo(sendString.c_str(), sendString.length(), servAddress, port);
      sleep(3);
    }
  } catch (SocketException &e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
