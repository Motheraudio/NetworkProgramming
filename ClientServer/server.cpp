#include "server.hpp"
#include <cstdlib>
#include <iostream>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
int main()
{
  struct addrinfo hints;
  struct addrinfo *servinfo;
  int status;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  if ((status = getaddrinfo(NULL, "4343", &hints, &servinfo) != 0))
  {
    std::cout << "Addrinfo failed: " << gai_strerror(status) << std::endl;
    exit(1);
  }
  int sock =
      socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
  if (sock == -1)
  {
    std::cout << "Socket failed" << std::endl;
    freeaddrinfo(servinfo);
    return (1);
  }
  if (bind(sock, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
  {
    std::cout << "bind not possible: " << errno << std::endl;
    freeaddrinfo(servinfo);
    return (1);
  }
  if (listen(sock, 1) == -1)
  {
    std::cout << "listen not possible: " << errno << std::endl;
    freeaddrinfo(servinfo);
    return (1);
  }
  struct addrinfo client;
  socklen_t csize = sizeof(client);
  int commfd = accept(sock, (struct sockaddr *)&client, &csize);
  std::cout << "Connection Successful" << std::endl;
  char *buff;
  while (1)
  {
    char *size = (char *)malloc(10);
    if (!size)
      return (1);
    recv(commfd, size, 10, 0);
    int isize = std::atoi(size);
    free(size);
    buff = (char *)malloc(isize);
    if (!buff)
      return (1);
    recv(commfd, buff, isize, 0);
    std::cout << buff << std::endl;
    free(buff);
  }
}
