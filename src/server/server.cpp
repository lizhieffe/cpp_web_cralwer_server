/*
 * Server.cpp
 *
 *  Created on: Oct 17, 2015
 *      Author: zhili
 */

#include "server.h"

//#include <boost/thread.hpp>
//#include <boost/shared_ptr.hpp>
//#include <functional>
//#include <iostream>
//#include <thread>
//#include <vector>
//
//namespace http {
//namespace server3 {
//
//server::server(const std::string& address,
//							 const std::string& port,
//							 const std::string& doc_root,
//							 std::size_t thread_pool_size)
//		: address_(address),
//			port_(port),
//			thread_pool_size_(thread_pool_size),
//			acceptor_(io_service_),
//			new_connection_(new connection(io_service_, request_handler_)),
//			request_handler_(doc_root) {
//  // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
//  boost::asio::ip::tcp::resolver resolver(io_service_);
//  boost::asio::ip::tcp::resolver::query query(address, port);
//  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
//  acceptor_.open(endpoint.protocol());
//  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
//  acceptor_.bind(endpoint);
//  acceptor_.listen();
//  acceptor_.async_accept(new_connection_->socket(),
//      boost::bind(&server::handle_accept, this,
//        boost::asio::placeholders::error));
//}
//
//void server::run() {
//	std::cout << "Server starting on " << address_ << ":" << port_ << " using "
//			<< thread_pool_size_ << " threads..." << std::endl;
//  // Create a pool of threads to run all of the io_services.
//  std::vector<boost::shared_ptr<boost::thread> > threads;
//  for (std::size_t i = 0; i < thread_pool_size_; ++i) {
//    boost::shared_ptr<boost::thread> thread(new boost::thread(
//    		boost::bind(static_cast<size_t (boost::asio::io_service::*)()>(
//    				&boost::asio::io_service::run), &io_service_)));
//    threads.push_back(thread);
//  }
//  std::cout << "Server started successfully!" << std::endl;
//
//  // Wait for all threads in the pool to exit.
//  for (std::size_t i = 0; i < threads.size(); ++i) {
//    threads[i]->join();
//  }
//}
//
//void server::stop() {
//  io_service_.stop();
//}
//
//void server::handle_accept(const boost::system::error_code& e) {
//  if (!e) {
//    new_connection_->start();
//    std::cout << "Received new data on thread "
//    		<< std::this_thread::get_id()	<< std::endl;
//    std::cout << "Finished handling data" << std::endl;
//    new_connection_.reset(new connection(io_service_, request_handler_));
//    acceptor_.async_accept(new_connection_->socket(),
//        boost::bind(&server::handle_accept, this,
//          boost::asio::placeholders::error));
//  }
//}
//
//} // namespace server3
//} // namespace http




#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <thread>
#include <vector>

namespace http {
namespace server3 {

server::server(const std::string& address, const std::string& port,
    const std::string& doc_root, std::size_t thread_pool_size)
  : address_(address),
		port_(port),
		thread_pool_size_(thread_pool_size),
    signals_(io_service_),
    acceptor_(io_service_),
    new_connection_(),
    request_handler_(doc_root)
{
  // Register to handle the signals that indicate when the server should exit.
  // It is safe to register for the same signal multiple times in a program,
  // provided all registration for the specified signal is made through Asio.
  signals_.add(SIGINT);
  signals_.add(SIGTERM);
#if defined(SIGQUIT)
  signals_.add(SIGQUIT);
#endif // defined(SIGQUIT)
  signals_.async_wait(boost::bind(&server::handle_stop, this));

  // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
  boost::asio::ip::tcp::resolver resolver(io_service_);
  boost::asio::ip::tcp::resolver::query query(address, port);
  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
  acceptor_.open(endpoint.protocol());
  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  acceptor_.bind(endpoint);
  acceptor_.listen();

  start_accept();
}

void server::run()
{
	std::cout << "Server starting on " << address_ << ":" << port_ << " using "
				<< thread_pool_size_ << " threads..." << std::endl;
  // Create a pool of threads to run all of the io_services.
  std::vector<boost::shared_ptr<boost::thread> > threads;
  for (std::size_t i = 0; i < thread_pool_size_; ++i)
  {
  	boost::shared_ptr<boost::thread> thread(new boost::thread(
				boost::bind(static_cast<size_t (boost::asio::io_service::*)()>(
						&boost::asio::io_service::run), &io_service_)));
    threads.push_back(thread);
  }
  std::cout << "Server started successfully!" << std::endl << std::endl;

  // Wait for all threads in the pool to exit.
  for (std::size_t i = 0; i < threads.size(); ++i)
    threads[i]->join();
}

void server::start_accept()
{
  new_connection_.reset(new connection(io_service_, request_handler_));
  acceptor_.async_accept(new_connection_->socket(),
      boost::bind(&server::handle_accept, this,
        boost::asio::placeholders::error));
}

void server::handle_accept(const boost::system::error_code& e)
{
  if (!e) {
  	std::cout << "server::handle_accept()... on thread "
				<< std::this_thread::get_id()	<< std::endl;
  	std::cout << "Receiving new data." << std::endl;
    new_connection_->start();
  }

  start_accept();
}

void server::handle_stop()
{
  io_service_.stop();
}

} // namespace server3
} // namespace http
