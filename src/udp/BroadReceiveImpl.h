#ifndef __BROADRECEIVEIMPL_H__
#define __BROADRECEIVEIMPL_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <functional>

#include "BroadReceive.h"
#include "BroadMessageFactory.h"

#define SERVICE_PORT    (65001)


class BroadReceiveImpl
{
    public:
        BroadReceiveImpl(BroadReceiveMessageHandler *handler)
            : m_handler(handler)
            , m_fd(-1)
            , tid(-1)
        {
            struct sockaddr_in myaddr;

            if ((m_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                perror("cannot create socket\n");
            }

            /* set reuse */
            int optval = 1;
            setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

            memset((char *)&myaddr, 0, sizeof(myaddr));
            myaddr.sin_family = AF_INET;
            myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
            myaddr.sin_port = htons(SERVICE_PORT);

            if (::bind(m_fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
                perror("bind failed");
            }

            pthread_create(&tid, NULL, thread_run, this);
        }

        ~BroadReceiveImpl()
        {
            if (m_fd)
            {
                close(m_fd);
            }
        }

        void run()
        {
            while (1)
            {
                struct sockaddr_in recvaddr;
                socklen_t addrlen;
                char buf[1024];

                int recvlen = recvfrom(m_fd, buf, sizeof(buf), 0, (struct sockaddr*)&recvaddr, &addrlen);
                
                BroadMessageFactory factory;
                BroadMessageSp sp = factory.createMessage(buf, recvlen);

                if (std::find(m_filter.begin(), m_filter.end(), sp->getId()) != m_filter.end())
                {
                    m_handler->handleMessage(sp);
                }

            }
        }

        void filter(const std::vector<int>& f)
        {
            // TODO: thread!
            m_filter = f;
        }


        static void* thread_run(void* args);

    private:
        BroadReceiveMessageHandler* m_handler;
        int m_fd;
        pthread_t tid;

        std::vector<int> m_filter;
};


void* BroadReceiveImpl::thread_run(void* args)
{
    BroadReceiveImpl* impl = (BroadReceiveImpl*)args;
    impl->run();
}

#endif
