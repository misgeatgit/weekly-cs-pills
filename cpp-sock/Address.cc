
#include "Address.h"

AddrInfo::AddrInfo(SockAddrFamily family,int flags,int protocol,SockType socktype,
        const std::string& canonname,SockAddress sockaddr)
    :ai_addr(sockaddr),ai_family(family)
{
    ai_flags = flags; 
    ai_protocol = protocol; 
    ai_socktype = socktype;
    ai_canonname = canonname;
}

SockAddress::SockAddress(struct sockaddr* saddr , socklen_t len)
{
    addr = saddr;
    addrlen = len;
}

SockAddress::~SockAddress()
{
}

SockAddress::SockAddress(unsigned short port_no, 
        unsigned long s_addr /*= INADDR_ANY*/)
{
    bzero(&addr_in, sizeof(addr_in));
    addr_in.sin_family = SockAddrFamily::IPV4;
    addr_in.sin_port = htons(port_no); // host to network conversion for byte ordering.
    addr_in.sin_addr.s_addr = s_addr; //get ip address of the machine

    addr = (struct sockaddr*)&addr_in;
    addrlen = sizeof(addr_in);
}
SockAddress::SockAddress(unsigned short port_no, struct in6_addr in6addr /*= in6addr_any*/)
{
    bzero(&addr_sin6, sizeof(addr_sin6));
    addr_sin6.sin6_family = SockAddrFamily::IPV6;
    addr_sin6.sin6_port = htons(port_no);
    addr_sin6.sin6_addr = in6addr;

    addr = (struct sockaddr*)&addr_sin6;
    addrlen = sizeof(addr_sin6);

}

std::string SockAddress::ip_address(void)
{
    char ipstr[INET6_ADDRSTRLEN];
    void* ip_addr;
    if (addr->sa_family == AF_INET) { // IPv4
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)addr;
        ip_addr = &(ipv4->sin_addr);
    } else { // IPv6
        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)addr;
        ip_addr = &(ipv6->sin6_addr);
    }

    inet_ntop(addr->sa_family, ip_addr, ipstr, sizeof ipstr);

    return std::string(ipstr);
}

unsigned int SockAddress::port_no(void)
{
    unsigned int port;

    if (addr->sa_family == AF_INET) { // IPv4
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)addr;
        port = ntohs(ipv4->sin_port);
    } else { // IPv6
        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)addr;
        port = ntohs(ipv6->sin6_port);
    }

    return port;
}

/**
 * 
 * @param flags could be [NI_DGRAM | NI_NAMEREOD | NI_NOFODN | NI_NUMERICHOST |
 *                 NI_NUMERICSERV]
 */

std::pair<std::string,std::string> SockAddress::get_name_info(SockAddress& sockaddr, 
        int flags /*= 0*/)
{
    char hostname[NI_MAXHOST], service[NI_MAXSERV]; 

    int rc = getnameinfo(addr, addrlen, hostname, NI_MAXHOST,
            service, NI_MAXSERV, flags);

    if (rc != 0){
        const char * err_msg = gai_strerror(rc);
        std::cout << __FILE__ << " " << __LINE__ << '\n';
        throw std::runtime_error(err_msg);
    }

    //if (*hostname != '\0') return std::string(hostname);

    return std::make_pair(std::string(hostname), std::string(service)); 
}



AddrInfoSeq SockAddress::get_addr_info(std::string host, std::string service /*=""*/,
        const std::shared_ptr<AddrInfo> hints /*=nullptr*/)
{
    AddrInfoSeq addrinfseq;

    struct addrinfo hint;
    memset(&hint, 0, sizeof(struct addrinfo)); 

    if(nullptr != hints){
        hint.ai_family = hints->ai_family ;
        hint.ai_socktype = hints->ai_socktype ;
        hint.ai_protocol = hints->ai_protocol ;
        hint.ai_flags = hints->ai_flags ;

    } else{
        hint.ai_family =  AF_UNSPEC;
        hint.ai_socktype =  0;//SOCK_STREAM;
        hint.ai_protocol =  0;
        hint.ai_flags = AI_CANONNAME; 
    }
    hint.ai_addr =  NULL;
    //hint.ai_canonname = NULL;
    hint.ai_next = NULL;

    struct addrinfo * result;
    int rc = getaddrinfo(host.c_str(), (service != "" ? service.c_str() : NULL),
            &hint, &result);

    if(rc != 0){
        const char * err_msg = gai_strerror(rc);
        std::cout << __FILE__ << " " << __LINE__ << '\n';
        throw std::runtime_error(err_msg);
    } 

    struct addrinfo * rp = result; 
    while( rp != NULL) {    
        SockAddress addr(rp->ai_addr, rp->ai_addrlen);
        std::string str(rp->ai_canonname == NULL ? "" : const_cast<const char*>(rp->ai_canonname));
        AddrInfo addrinfo(static_cast<SockAddrFamily>(rp->ai_family),
                rp->ai_flags,
                rp->ai_protocol,  
                static_cast<SockType>(rp->ai_socktype),
                str, addr);

        addrinfseq.push_back(addrinfo);
        rp = rp->ai_next;
    }

    //freeaddrinfo(result); //TODO call this after mecopying th addr and
    //cannonmame otherwise it creates a problem.
    return addrinfseq;
}

