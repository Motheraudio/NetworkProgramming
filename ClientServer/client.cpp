#include "client.hpp"
#include "string.h"
#include <iostream>
#include <netdb.h>
#include <string>
int main()
{
  int status;
  struct addrinfo *clientinfo;
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  if ((status = getaddrinfo("127.0.0.1", "4343", &hints, &clientinfo)) != 0)
    return (1);
  struct addrinfo *p = clientinfo;
  int sock;
  while (p != NULL)
  {
    sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (sock != -1)
      break;
  }
  if ((connect(sock, p->ai_addr, p->ai_addrlen) != 0))
    return (1);
  std::string message;
  std::string slen;
  while (1)
  {
    getline(std::cin, message);
    slen = std::to_string(message.length());
    send(sock, slen.c_str(), slen.length(), 0);
    send(sock, message.c_str(), message.length(), 0);
  }
}
