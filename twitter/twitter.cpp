#include<eosiolib/eosio.hpp>
#include<eosiolib/print.hpp>

using namespace eosio;
using namespace std;
using std::string;


class twitter : public eosio::contract
{
        public:
        using contract::contract;

        /// @abi table twitreg i64

        struct twitreg
	{
		account_name uname;
		uint64_t number;
		string name;
		uint64_t primary_key() const {return uname;}
	        EOSLIB_SERIALIZE(twitreg,(uname)(number)(name))

	};

	typedef multi_index<N(twitreg),twitreg> twitr;

	///@abi action

	void tregister(account_name uname,uint64_t number,string name)
	{
		twitr twit(_self,_self);
                auto i = twit.find(uname);
                if(i==twit.end())
                {
                        twit.emplace(_self,[&](auto& twitreg)
                        {
				twitreg.uname=uname;
				twitreg.number=number;
				twitreg.name=name;
			});
		}
	}
};
EOSIO_ABI(twitter, (tregister))


