/*
 * Main.cpp
 *
 *  Created on: Oct 17, 2015
 *      Author: zhili
 */

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "server.h"

#if !defined(_WIN32)

#include <pthread.h>
#include <signal.h>

int main(int argc, char* argv[])
{
  try {
    // Check command line arguments.
    if (argc != 5) {
      std::cerr << "Usage: http_server <address> <port> <threads> <doc_root>\n";
      std::cerr << "  For IPv4, try:\n";
      std::cerr << "    web_crawler_server 0.0.0.0 80 1 .\n";
      std::cerr << "  For IPv6, try:\n";
      std::cerr << "    web_crawler_server 0::0 80 1 .\n";
      return 1;
    }

    // Initialise the server.
		std::size_t num_threads = boost::lexical_cast<std::size_t>(argv[3]);
		http::server3::server s(argv[1], argv[2], argv[4], num_threads);

		// Run the server until stopped.
		s.run();
  }
  catch (std::exception& e) {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}

#endif // !defined(_WIN32)
