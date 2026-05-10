#include "server.hpp"
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
int main() {
  struct addrinfo hints;
  struct addrinfo *servinfo;
  int status;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  if ((status = getaddrinfo("172.0.0.1", "80", &hints, &servinfo) != 0)) {
    std::cout << "Addrinfo failed: " << gai_strerror(status) << std::endl;
    exit(1);
  }
  int sock =
      socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
  if (sock == -1) {
    std::cout << "Socket failed" << std::endl;
    freeaddrinfo(servinfo);
    return (1);
  }
  if (bind(sock, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
    std::cout << "bind not possible" << std::endl;
  }
  // listen,then accept
}
