#include <string>
#include <vector>

#include <cstring>
#include <sys/socket.h> // This header should be in source file, i.e shall not
                        //be exposed through the API header
#include <netdb.h>
#include <arpa/inet.h>

#include <memory>

enum SockType { TCP = SOCK_STREAM, DGRAM = SOCK_DGRAM }; 

enum SockAddrFamily { IPV4 =  AF_INET, IPV6 = AF_INET6, UNIX_SOCK = AF_UNIX, 
                      UNSPEC = AF_UNSPEC}; 

//set for addrinfo hints
enum AIProtocol { PASSIVE = AI_PASSIVE, V4MAPPED = AI_V4MAPPED, IDN = AI_IDN,
                  CANONIDN =  AI_CANONIDN };


class SocketException;

//-----------------------Data structures--------------------------------------|

struct SockAddress
{
        struct sockaddr * addr; //make this a shared ptr?
        socklen_t addrlen;

        SockAddress(struct sockaddr* saddr = NULL, socklen_t len = 0)
        {
            addr = saddr;
            addrlen = len;
        }
        
        ~SockAddress()
        {
        }

        //TODO getters for family, address and path(for unix domain)
};

struct AddrInfo
{
   //http://man7.org/linux/man-pages/man3/getaddrinfo.3.html for c addrinfo
   //datastructure.
   SockAddrFamily ai_family;
   int            ai_flags; //this could ored.
   int            ai_protocol;
   SockType       ai_socktype;
   std::string    ai_canonname;
   SockAddress    ai_addr;  

   AddrInfo(SockAddrFamily family,int flags,int protocol,SockType socktype,
            const std::string& canonname,SockAddress sockaddr)
   {
       ai_family = family;
       ai_flags = flags; 
       ai_protocol = protocol; 
       ai_socktype = socktype;
       ai_canonname = canonname;
       ai_addr = sockaddr;
   }

   ~AddrInfo()
   {
   }
};

using AddrInfoSeq = std::vector<AddrInfo>;


//-------------------DNS uitlity functions--------------------------|

AddrInfoSeq get_addr_info(std::string host, std::string service = "",
                          const std::shared_ptr<AddrInfo>& hints = nullptr)
{
    AddrInfoSeq addrinfseq;
    
    struct addrinfo hint;
    memset(&hint, 0, sizeof(struct addrinfo)); 
    hint.ai_family = (nullptr != hints ? hints->ai_family : AF_UNSPEC);
    hint.ai_socktype = (nullptr != hints ? hints->ai_socktype : SOCK_STREAM);
    hint.ai_protocol = (nullptr != hints ?  hints->ai_protocol : 0);
    hint.ai_flags = (nullptr !=hints ? hints->ai_flags : AI_CANONNAME);
    hint.ai_addr =  NULL;
    hint.ai_addrlen = 0;
    hint.ai_next = NULL;

    struct addrinfo * result;

    int rc = getaddrinfo(host.c_str(), (service == "" ? NULL : service.c_str()),
                         &hint, &result);

    if(rc != 0) return addrinfseq; //TODO exception?

    // returns linked list bc, host might be
    // multihomed(http://searchnetworking.techtarget.com/definition/multihomed)
    // or over mutliple protocols( IPV4 and IPV6)
    // or from multiple socketypes ( SOCK_STREAM or SOCK_DGRAM)
    for (struct addrinfo * rp = result; rp != NULL; rp = rp->ai_next) {
        SockAddress addr(rp->ai_addr, rp->ai_addrlen);
        std::string str(rp->ai_canonname == NULL ? "" : rp->ai_canonname);
        
        AddrInfo addrinfo(static_cast<SockAddrFamily>(rp->ai_family), rp->ai_flags,
                          rp->ai_protocol,  static_cast<SockType>(rp->ai_socktype),
                          str, addr);

        addrinfseq.push_back(addrinfo);
    }

    return addrinfseq;
}

std::string get_name_info(const SockAddress& sockaddr, std::string service = "",
                          int flags = 0)
{
    char hostname[1025] = "";
    int rc = getnameinfo(sockaddr.addr, sockaddr.addrlen, hostname, 1025,
            service == "" ? NULL : const_cast<char*>(service.c_str()),
            service.length() , flags); 
    if (rc != 0)
    {
        //TODO print the apporpriate error message.
        fprintf(stderr, "error in getnameinfo:\n");
        return "";
    }

    if (*hostname != '\0') return std::string(hostname);

    return ""; 
}



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
//                      size_t len );
//len is size of buffer dst_str
//Returns pointer to dst_str on success, or NULL on error
std::string network_to_presentation(SockAddrFamily ipv , const void * addrptr,
                                    const std::string& dst); 
//try to use template instead of the third argument here. i.e conditional return type





//----------------------------Socket interface-------------------------------|

class Socket
{
    public:
        Socket(SockAddrFamily domain, SockType type, int protocol); //create a new socket
        ~Socket();

        void bind_c(const std::shared_ptr<SockAddress>& addr); //bind to a well 
        // known address so that client can locket the socket
        void listen_c(); // Allows stream sockets(TCP) to accept incoming 
                         // connection from others

        //TCP
        void accept_c(std::shared_ptr<SockAddress>& addr);  // Accepts connection
       // a connection from a peer on a listening stream and may return the 
       // address of the peer socket
        void connect_c(); // Estabilishes connection with another socket

        void write();
        void read();

        //Datagram
        void sendto();
        //ssize_t sendto(int sockfd , const void * buffer , size_t length , int flags ,
        //        const struct sockaddr * dest_addr , socklen_t addrlen );
        //        returns number of bytes sent, -1 on error
        void receivefrom();
        //size_t recvfrom(int sockfd , void * buffer , size_t length , int flags ,
        //        struct sockaddr * src_addr , socklen_t * addrlen );
        //        returns number of bytes received, 0 on EOF, -1 on error

        void close();

    private:
        int _fd; // the file descriptor returned from the socket sys call
        int _fd_accept; // file descriptor of new socket created by kernel on 
                        // connection accepted by this socket.
};


class SocketException : std::exception
{

};


Socket::Socket(SockAddrFamily domain, SockType type, int protocol)
{
    // exception.
    int rc = socket(domain, type, protocol);

    if ( rc  == -1 ) throw std::runtime_error("Can't create socket.");

    _fd = rc;

}

Socket::~Socket()
{
    // release file descriptor
    // close socket
}

void Socket::bind_c(const std::shared_ptr<SockAddress>& addr)
{
    /*
     * NOTE: Directly calling listen without bind is also possible in which case 
     * kernel assigns an ephemeral port to the server. Then server could get its
     * assigned address via calling getsocketname(). and client could get
     * address info via directory service applications.
     */
    int rc = bind(_fd, addr->addr, addr->addrlen);
    if ( rc != 0) throw std::runtime_error("Couldn't bind to the given address.");
}

void Socket::accept_c(std::shared_ptr<SockAddress>& addr)
{
    int rc = accept(_fd, addr->addr, &(addr->addrlen));
    if ( rc != 0) throw std::runtime_error("Error while accpeting connection.");
    _fd_accept = rc;
}

#define LISTEN_BACKLOG  100
void Socket::listen_c()
{
    int rc = listen(_fd, LISTEN_BACKLOG);
    if ( rc != 0) throw std::runtime_error("Error while listening to connection.");
}

