#ifndef __BROADSIGNALIMPL_H__
#define __BROADSIGNALIMPL_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>

#define SERVICE_PORT    (65001)

class BroadSignalImpl
{
    public:
        BroadSignalImpl() :
            m_fd(-1)
        {
            const char *server = "127.255.255.255"; /* change this to use a different server */

            if ((m_fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
                perror("socket created\n");

            int broadcast = 1;
            setsockopt(m_fd, SOL_SOCKET, SO_BROADCAST, &broadcast,sizeof broadcast);

            memset((char *) &remaddr, 0, sizeof(remaddr));
            remaddr.sin_family = AF_INET;
            remaddr.sin_port = htons(SERVICE_PORT);
            if (inet_aton(server, &remaddr.sin_addr)==0) {
                perror("inet_aton() failed\n");
            }

        }

        ~BroadSignalImpl()
        {
            if (m_fd != -1)
                close (m_fd);
        }

        void broadcast(const std::string& data)
        {
            if (sendto(m_fd, data.data(), data.length(), 0, (struct sockaddr *)&remaddr, sizeof(remaddr))==-1) {
                perror("sendto:");
            }
        }
    private:
        int m_fd;
        struct sockaddr_in remaddr;

};


#endif
