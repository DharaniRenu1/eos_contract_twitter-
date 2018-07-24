#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
 
using namespace eosio;

class summ : public eosio::contract
{
public:
        using contract::contract;

        void add(uint64_t a,uint64_t b)
        {
        uint64_t c=a+b;
        print("sum",a,b,c);
        }
};
EOSIO_ABI( summ, (add))

