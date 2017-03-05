#include <string>
#include <vector>

#include <cstring>
#include <sys/socket.h> // This header should be in source file, i.e shall not
//be exposed through the API header
#include <netdb.h>
#include <arpa/inet.h>

#include <memory>
#include <utility>


enum SockAddrFamily { IPV4 =  AF_INET, IPV6 = AF_INET6, UNIX_SOCK = AF_UNIX, 
                      UNSPEC = AF_UNSPEC}; 

//set for addrinfo hints
enum AIProtocol { PASSIVE = AI_PASSIVE, V4MAPPED = AI_V4MAPPED, IDN = AI_IDN,
                  CANONIDN =  AI_CANONIDN };


class SocketException;
class AddrInfo;

using AddrInfoSeq = std::vector<AddrInfo>;

//-----------------------Data structures--------------------------------------|

//Private data structure

class SockAddress
{
    private:
        struct sockaddr* addr; 
        socklen_t addrlen;

        SockAddress(struct sockaddr* saddr , socklen_t len)
        {
            addr = saddr;
            addrlen = len;
        }

        friend AddrInfoSeq get_addr_info(std::string, std::string,
                           const std::shared_ptr<AddrInfo>&);
        friend std::pair<std::string,std::string> 
                    get_name_info(SockAddress& sockaddr, int flags);


        friend class AddrInfo;
        friend class Socket;

    public:
        ~SockAddress()
        {
        }


        //TODO getters for family, address and path(for unix domain)
};


//----------------------------Socket interface-------------------------------|

enum SockType { TCP = SOCK_STREAM, DGRAM = SOCK_DGRAM, SEQPACKET = SOCK_SEQPACKET,
                RAW = SOCK_RAW, RDM = SOCK_RDM}; 

struct AddrInfo
{
    //http://man7.org/linux/man-pages/man3/getaddrinfo.3.html for c addrinfo
    //datastructure.
    const SockAddrFamily& ai_family;
    int            ai_flags; //this could ored.
    int            ai_protocol;
    SockType       ai_socktype;
    std::string    ai_canonname;
    SockAddress    ai_addr;  

    AddrInfo(SockAddrFamily family,int flags,int protocol,SockType socktype,
            const std::string& canonname,SockAddress sockaddr)
            :ai_addr(sockaddr),ai_family(family)
    {
        ai_flags = flags; 
        ai_protocol = protocol; 
        ai_socktype = socktype;
        ai_canonname = canonname;
    }

};


class Socket
{
    public:
        Socket(SockAddrFamily domain, SockType type, int protocol = 0); //create a new socket
        ~Socket();

        void bind_c(SockAddress& addr); //bind to a well 
        // known address so that client can locket the socket
        void listen_c(); // Allows stream sockets(TCP) to accept incoming 
        // connection from others

        //TCP
        void accept_c(SockAddress& addr);  // Accepts connection
        // a connection from a peer on a listening stream and may return the 
        // address of the peer socket
        void connect_c(void); // Estabilishes connection with another socket

        void write(void);
        void read(void);

        //Datagram
        void sendto(void);
        //ssize_t sendto(int sockfd , const void * buffer , size_t length , int flags ,
        //        const struct sockaddr * dest_addr , socklen_t addrlen );
        //        returns number of bytes sent, -1 on error
        void receivefrom(void);
        //size_t recvfrom(int sockfd , void * buffer , size_t length , int flags ,
        //        struct sockaddr * src_addr , socklen_t * addrlen );
        //        returns number of bytes received, 0 on EOF, -1 on error

        void close(void);

    private:
        int _fd; // the file descriptor returned from the socket sys call
        int _fd_accept; // file descriptor of new socket created by kernel on 
        // connection accepted by this socket.
};

/*
class UDPSocket : public Socket
{
};
*/



class SocketException : std::exception
{

};

//-------------------DNS uitlity functions--------------------------|

AddrInfoSeq get_addr_info(std::string host, std::string service = "",
                          const std::shared_ptr<AddrInfo>& hints = nullptr);


/**
 * 
 * @param flags could be [NI_DGRAM | NI_NAMEREOD | NI_NOFODN | NI_NUMERICHOST |
 *                 NI_NUMERICSERV]
 */
std::pair<std::string,std::string> get_name_info(SockAddress& sockaddr, 
                                                 int flags = 0);


//-------------------IPV4/v6 utility functions------------------------------|

//int inet_pton(int domain , const char * src_str , void * addrptr );
////presentation to network conversion returns -1 on error, 0 if src_str is not
//in presentation format or -1 on errorvoid inet_pton(SockAddrFamily ipv , 
//                               const std::string& src, void * addrptr ); 
void presentation_to_network(SockAddrFamily af , const std::string& src,
                             SockAddress& addr ); 
//change addrptr. its a pointer to struct in_addr or in6_addr depending on
//iptv

//const char *inet_ntop(int domain , const void * addrptr , char * dst_str ,
//                      size_t len )
//len is size of buffer dst_str
//Returns pointer to dst_str on success, or NULL on error
std::string network_to_presentation(SockAddrFamily ipv , const void * addrptr,
                                    const std::string& dst); 
//try to use template instead of the third argument here. i.e conditional return type




