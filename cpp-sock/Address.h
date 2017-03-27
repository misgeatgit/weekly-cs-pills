#include <string>
#include <vector>

#include <cstring>
//be exposed through the API header
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory>
#include <netinet/in.h>
#include <utility>

#include <iostream>

enum SockAddrFamily { IPV4 =  AF_INET, IPV6 = AF_INET6, UNIX_SOCK = AF_UNIX, 
    UNSPEC = AF_UNSPEC}; 

//set for addrinfo hints
enum AIProtocol { PASSIVE = AI_PASSIVE, V4MAPPED = AI_V4MAPPED, IDN = AI_IDN,
    CANONIDN =  AI_CANONIDN };

enum SockType { TCP = SOCK_STREAM, DGRAM = SOCK_DGRAM, SEQPACKET = SOCK_SEQPACKET,
                RAW = SOCK_RAW, RDM = SOCK_RDM}; 

class AddrInfo;
using AddrInfoSeq = std::vector<AddrInfo>;

//-----------------------Data structures--------------------------------------|

class SockAddress
{
    private:
        struct sockaddr* addr; 
        struct sockaddr_in addr_in;
        struct sockaddr_in6 addr_sin6;
        socklen_t addrlen;

        friend class AddrInfo;

        SockAddress(struct sockaddr* saddr , socklen_t len);
        
    public:
        ~SockAddress();

        SockAddress(unsigned short port_no, 
                unsigned long s_addr = INADDR_ANY);
        SockAddress(unsigned short port_no, struct in6_addr in6addr = in6addr_any);
        std::string ip_address(void);
        unsigned int port_no(void);
        /**
         * 
         * @param flags could be [NI_DGRAM | NI_NAMEREOD | NI_NOFODN | NI_NUMERICHOST |
         *                 NI_NUMERICSERV]
         */
        std::pair<std::string,std::string> get_name_info(SockAddress& sockaddr, 
                int flags = 0);
        static AddrInfoSeq get_addr_info(std::string host, std::string service ="",
                const std::shared_ptr<AddrInfo> hints =nullptr);
};


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
            const std::string& canonname,SockAddress sockaddr);
};


