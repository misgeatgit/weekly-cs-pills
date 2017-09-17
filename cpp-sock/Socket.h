
#include <sys/socket.h> // This header should be in source file, i.e shall not

#define LISTEN_BACKLOG 50

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

class Socket
{

    public:
        const SockType sock_type;
        const SockAddrFamily sock_domain;

        Socket(SockAddrFamily domain, SockType type, int protocol = 0) :
                  sock_domain(domain), sock_type(type) //create a new socket
        {
            _fd = socket(sock_domain, sock_type, protocol); // XXX Not sure the meaning of third argument.

            if(_fd < 0 )
                throw std::runtime_error( "ERROR while creating socket \n");
        }

        ~Socket(){
           // Close all the files.
           close(_fd);
           //for(int fd : _fd_accept) 
           //    close(fd);       // Must be destroyed by the socket caller.
        }

        int bind(SockAddress& saddr) //bind to a well 
        {
            int rc = bind(_fd, saddr.addr, sizeof(saddr.addr));

            return rc;
        }
        
    protected:
        int _fd; // the file descriptor returned from the socket sys call
};

class TcpSocket : public Socket{
    // writes up to count bytes from the buffer pointed buf to the
    // file referred to by the file descriptor fd.
    // http://man7.org/linux/man-pages/man2/write.2.html
    int write(const Socket& sock, char * buffer, size_t buflen)
    {
        int rc = write(sock._fd, buffer, buflen);

        return rc;
    }

    int read(char * buffer, size_t buflen)
    {
        ssize_t n = read(accept_fd, buffer, buflen);

        return n;
    }
    // known address so that client can locket the socket
    // @param listen_backlog maximum number of requests to que up
    int listen(int listen_backlog = 100) // Allows stream sockets(TCP) to accept incoming
    {
        int rc = listen(socket_fd, listen_backlog);
        
        return rc;
    } 
    
    // a connection from a peer on a listening stream and may return the 
    // address of the peer socket
    int accept(SockAddress& addr)  
    {
        fdacpt = accept(_fd, addr.addr, addr.addrlen);

        if(fdacpt < 0 )
            _fd_accept.push_back(fdacpt);

        return fdacpt;
    }
    // Estabilishes connection with another socket
    int connect( SockAddress& addr)
    {
        // The connect() system call connects the socket referred to by the file
        // descriptor sockfd to the address specified by addr
        int rc = connect(socket_fd, addr.addr, addr.addrlen );

        return rc;
    }
    
    private:
    std::vector<int> _fd_accept; // file descriptor of new socket created by kernel on 
    // connection accepted by this socket.

};

class UDPSocket : public Socket{
    //ssize_t sendto(int sockfd , const void * buffer , size_t length , int flags ,
    //        const struct sockaddr * dest_addr , socklen_t addrlen );
    //        returns number of bytes sent, -1 on error
    int sendto(SocketAddress& addr, char * buffer, size_t buflen){
        int rc = sendto(_fd, buffer, buflen, 0, addr.adddr, addr.addrlen);
        
        return rc;
    }

    //size_t recvfrom(int sockfd , void * buffer , size_t length , int flags ,
    //        struct sockaddr * src_addr , socklen_t * addrlen );
    //        returns number of bytes received, 0 on EOF, -1 on error
    int receivefrom(SocketAddress& addr, char * buffer, size_t buflen){
         int rc = recvfrom(_fd, reading_buffer, buffer, buflen, 0, addr.addr, addr.addrlen);
         
         return rc;
    }

};


