#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class hello : public eosio::contract
{
    public:
        using contract::contract;
	/// @abi table sample3 i64
        struct sample3
        {
	    uint64_t id;
            account_name to;
            uint64_t a1;
	    uint64_t a2;
	    uint64_t primary_key() const {return to;}
	    EOSLIB_SERIALIZE(sample3,(to)(id)(a1)(a2))
        };
	typedef multi_index<N(sample3),sample3> samp_struct;

	/// @abi action
        void hi(account_name user)
        {
            samp_struct samples(_self,_self);

 	    uint64_t temp = 60;

            auto i=samples.find(user);

            if(i==samples.end())

            {
                print("need insert\t");

                samples.emplace(_self,[&](auto& sample)
                {
		    sample.id = user;
                    sample.to = user;
		    sample.a1 = temp++;
		    sample.a2 = temp++;
                });
            }
            else
            {
                print("data already exist\t");
            }
            print("hello, world : ", name{user}, " 6");
        }
};

EOSIO_ABI(hello,(hi))

