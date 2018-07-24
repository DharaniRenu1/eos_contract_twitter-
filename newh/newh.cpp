#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class abc : public eosio::contract 
{
    public:
        using contract::contract;
        /// @abi table newtab i64
        struct newtab
        {
            uint64_t ac_no;
            account_name name;
            uint64_t amt;

            uint64_t primary_key() const {return name;}
            EOSLIB_SERIALIZE(newtab,(ac_no)(name)(amt))
        };
        typedef multi_index<N(newtab),newtab> new_tab;

        /// @abi action
        void create(uint64_t ac_no, account_name uname, uint64_t amt)
        {
            new_tab newtabs(_self,_self);

            auto i=newtabs.find(uname);
            if(i==newtabs.end())
            { 
                newtabs.emplace(_self,[&](auto& newtab)
                {
                    newtab.ac_no = ac_no;
                    newtab.name = uname;
                    newtab.amt = amt;

                });
                printf("Account created successfully\t");
            }
            else
            {
                print("Account already exist\t");
            }
        }
};

EOSIO_ABI(abc,(create))


