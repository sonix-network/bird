#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if.h>
#include <errno.h>

int main(int argc, const char* argv[]) {
    int sockfd;
    struct ifreq ifr;
    if (argc < 2) {
      printf("Usage: %s interface\n", argv[0]);
      exit(EXIT_FAILURE);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, argv[1], IFNAMSIZ - 1);

    // Bind the socket to the interface
    if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
        perror("setsockopt SO_BINDTODEVICE");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Socket successfully bound to interface \"%s\"\n", ifr.ifr_name);

    // Bind the socket to the interface
    if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
        perror("2nd try, setsockopt SO_BINDTODEVICE");
    } else {
        printf("2nd try, socket successfully bound to interface \"%s\"\n", ifr.ifr_name);
    }

    memset(&ifr, 0, sizeof(ifr));

    socklen_t len = sizeof(ifr.ifr_name);
    if (getsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, ifr.ifr_name, &len) < 0) {
        perror("getsockopt SO_BINDTODEVICE");
        exit(EXIT_FAILURE);
    }

    printf("Socket is currently bound to interface \"%s\"\n", ifr.ifr_name);
    return 0;
}
