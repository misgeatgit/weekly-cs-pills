
#include <sys/socket.h> // This header should be in source file, i.e shall not

#define LISTEN_BACKLOG 50

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

enum SockType { TCP = SOCK_STREAM, DGRAM = SOCK_DGRAM, SEQPACKET = SOCK_SEQPACKET,
                RAW = SOCK_RAW, RDM = SOCK_RDM}; 


class Socket
{

    public:
        SockType sock_type;
        SockAddrFamily sock_domain;

        int socket_fd;
        int accept_fd;
        char * reading_buffer[1024];
        char * writing_buffer[1024];

        Socket(SockAddrFamily domain, SockType type, int protocol = 0) //create a new socket
        {
            socket_fd = socket(sock_domain, sock_type, 0); // XXX Not sure the meaning of third argument.

            if(socket_fd < 0 )
                throw std::runtime_error( "ERROR while creating socket \n");
        }

        ~Socket();

        void bind(SockAddress& saddr) //bind to a well 
        {
            if (bind(socket_fd, saddr.addr, sizeof(saddr.addr)) < 0) 
                throw std::runtime_error( "ERROR while creating socket \n");
        }
        // known address so that client can locket the socket
        int listen() // Allows stream sockets(TCP) to accept incoming
        {
            int rc = listen(socket_fd, LISTEN_BACKLOG);
            return rc;
        } 
        // connection from others

        //TCP
        // a connection from a peer on a listening stream and may return the 
        // address of the peer socket
        void accept(SockAddress& addr)  
        {
            accept_fd = accept(socket_fd, addr.addr, addr.addrlen);
            if(accept_fd < 0 )
                throw std::runtime_error( "ERROR while estabilishing a connection.\n");
        }
        // Estabilishes connection with another socket
        void connect( SockAddress& addr)
        {
            // The connect() system call connects the socket referred to by the file
            // descriptor sockfd to the address specified by addr
            int rc = connect(socket_fd, addr.addr, addr.addrlen );

        }

        // writes up to count bytes from the buffer pointed buf to the
        // file referred to by the file descriptor fd.
        // http://man7.org/linux/man-pages/man2/write.2.html
        void write(const Socket& sock)
        {
            int rc = write(sock.socket_fd, writing_buffer, 1024);
        }

        void read(void)
        {
            ssize_t n = read(accept_fd, reading_buf, 1024);
        }


        //Datagram

        //ssize_t sendto(int sockfd , const void * buffer , size_t length , int flags ,
        //        const struct sockaddr * dest_addr , socklen_t addrlen );
        //        returns number of bytes sent, -1 on error

        void sendto(void);
        //size_t recvfrom(int sockfd , void * buffer , size_t length , int flags ,
        //        struct sockaddr * src_addr , socklen_t * addrlen );
        //        returns number of bytes received, 0 on EOF, -1 on error


        void receivefrom(void);
        void close(void);

    private:
        int _fd; // the file descriptor returned from the socket sys call
        int _fd_accept; // file descriptor of new socket created by kernel on 
        // connection accepted by this socket.
};


