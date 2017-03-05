#include "Socket.h"
#include <iostream>

AddrInfoSeq get_addr_info(std::string host, std::string service /*=""*/,
                          const std::shared_ptr<AddrInfo>& hints /*=nullptr*/)
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
        hint.ai_socktype =  SOCK_STREAM;
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

    // returns linked list bc, host might be
    // multihomed(http://searchnetworking.techtarget.com/definition/multihomed)
    // or over mutliple protocols( IPV4 and IPV6)
    // or from multiple socketypes ( SOCK_STREAM or SOCK_DGRAM)
    struct addrinfo * rp = result; 
    while( rp != NULL) {    
        SockAddress addr(rp->ai_addr, rp->ai_addrlen);
        std::string str(rp->ai_canonname == NULL ? "" : const_cast<const char*>
                                                        (rp->ai_canonname));
        AddrInfo addrinfo(static_cast<SockAddrFamily>(rp->ai_family), 
                          rp->ai_flags,
                          rp->ai_protocol,  
                          static_cast<SockType>(rp->ai_socktype),
                          str,
                          addr);

        addrinfseq.push_back(addrinfo);
        rp = rp->ai_next;
    }
   
    //freeaddrinfo(result); //TODO call this after mecopying th addr and
    //cannonmame otherwise it creates a problem.
    return addrinfseq;
}


std::pair<std::string,std::string> get_name_info(SockAddress& sockaddr, 
                                                 int flags/*= 0*/)
{
    char hostname[NI_MAXHOST], service[NI_MAXSERV]; 

    int rc = getnameinfo(sockaddr.addr, sockaddr.addrlen, hostname, NI_MAXHOST,
                         service, NI_MAXSERV, flags);

    if (rc != 0){
        const char * err_msg = gai_strerror(rc);
        std::cout << __FILE__ << " " << __LINE__ << '\n';
        throw std::runtime_error(err_msg);
    }

    //if (*hostname != '\0') return std::string(hostname);

    return std::make_pair(std::string(hostname), std::string(service)); 
}






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

void Socket::bind_c(SockAddress& sock_addr)
{
    /*
     * NOTE: Directly calling listen without bind is also possible in which case 
     * kernel assigns an ephemeral port to the server. Then server could get its
     * assigned address via calling getsocketname(). and client could get
     * address info via directory service applications.
     */
    int rc = bind(_fd, sock_addr.addr, sock_addr.addrlen);
    if ( rc != 0) throw std::runtime_error("Couldn't bind to the given address.");
}

void Socket::accept_c(SockAddress& sock_addr)
{
    int rc = accept(_fd, sock_addr.addr, &(sock_addr.addrlen));
    if ( rc != 0) throw std::runtime_error("Error while accpeting connection.");
    _fd_accept = rc;
}

#define LISTEN_BACKLOG  100
void Socket::listen_c()
{
    int rc = listen(_fd, LISTEN_BACKLOG);
    if ( rc != 0) throw std::runtime_error("Error while listening to connection.");
}
