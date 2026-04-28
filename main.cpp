#include <iostream>
#include "CgiHandler.hpp"
#include <poll.h>
#include <sys/epoll.h>

int main()
{

	//create event poll

	int epoll_fd = epoll_create1(0);
	if (epoll_fd == -1)
	{
		std::cerr << "epoll_error\n";
		exit(EXIT_FAILURE);
	}




    CgiHandler cgi;
	cgi.reqBuffer = "body";


    std::string errMsg;
    if (!cgi.setCgiEnv(CGI_HTTP_ACCEPT, "/www",& errMsg))
	{
		std::cout << errMsg << std::endl;
	}
    if (!cgi.setCgiEnv(CGI_REQUEST_METHOD, "GET",& errMsg))
	{
		std::cout << errMsg << std::endl;
	}
    if (!cgi.setCgiEnv(CGI_SCRIPT_NAME, "login.php",& errMsg))
	{
		std::cout << errMsg << std::endl;
	}
    

	
	if (!cgi.initCgi(epoll_fd, &errMsg))
		std::cout << errMsg << std::endl;

	struct epoll_event events[10];
	while (1)
	{
		int n = epoll_wait(epoll_fd, events, 10, 10);
		for(int i = 0; i < n; i++)
		{
			if(events[i].events & EPOLLIN)
			{
				char buff[4096] = {0};
				// cgi.reciveFromCgi();
				int n = read(events[i].data.fd, buff, 4096);
				
				if (n == 0 || n == -1)
				{
					std::cout << "read :" << n << std::endl;
					epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
					close(events[i].data.fd);
					continue;
				}
				buff[n] = '\0';
			
				std::cout << "'**" << buff << "**'" << std::endl;
			}
			
			 if (events[i].events & EPOLLOUT)
			{
				// cgi.sendToCgi();
				int n = write (events[i].data.fd, "hello", 6);
				epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
				close(events[i].data.fd);
			}
		}
	}
	cgi.putRes();


	//poll



}