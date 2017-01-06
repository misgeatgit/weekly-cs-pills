
#include "Socket.h"
#include <iostream>

int main()
{
AddrInfoSeq infos = get_addr_info("www.facebook.com", "", nullptr);

for (auto info : infos)
{
    //std::cout << info.ai_canonname << std::endl;
   auto hostname = get_name_info(info.ai_addr); 
   std::cout << hostname << std::endl;
}

}
