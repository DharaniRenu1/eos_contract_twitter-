#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class summ : public eosio::contract
{
public:
        using contract::contract;

        void add(uint32_t a,uint32_t b)
        {
        uint32_t c=a+b;
        print("sum",a,b,c);
        }
};
EOSIO_ABI( summ, (add))

