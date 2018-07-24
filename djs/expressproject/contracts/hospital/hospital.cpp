#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class user : public eosio::contract 
{
    public:
        using contract::contract;
        /// @abi table details i64
        struct details
        {
                uint64_t id;
                 account_name name;
  		uint64_t primary_key() const {return name;}
		 EOSLIB_SERIALIZE(details,(id)(name))
	};

	 typedef multi_index<N(details),details> detail;
	///@abi action
	void account(uint64_t id1,account_name name1) 
	{
		detail det(_self,_self);
		auto i = det.find(name1);
		if(i==det.end())
		{
			det.emplace(_self,[&](auto& details)
			{
				details.id=id1;
				details.name=name1;

			});
		}
	}
          //@abi action
        void modify1(uint64_t id1,account_name _name){


                 detail cantabs(_self,_self);

                auto iter = cantabs.find(_name);


                         if(iter == cantabs.end()){

                                print("just modified");
                }else{

                cantabs.modify(iter,_self,[&](auto& details){


                details.id = id1;

                });


                }


        }


};
EOSIO_ABI(user, (account)(modify1))

