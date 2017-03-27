
#include "Address.h"
#include <iostream>

int main(int argc, char** args)
{

    std::cout << " Name info for " << args[1] << "on port " <<  args[2] << '\n';
    //AddrInfoSeq infos = get_addr_info("www.facebook.com", "", nullptr);
    AddrInfoSeq infos = SockAddress::get_addr_info(args[1], args[2], nullptr);

    for (auto info : infos)
    {
        std::cout << info.ai_canonname << "  " << info.ai_addr.ip_address() << "\n ";
    }

}
