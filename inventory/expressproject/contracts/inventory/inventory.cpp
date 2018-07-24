#include<eosiolib/eosio.hpp>
#include<eosiolib/print.hpp>

using namespace eosio;
using namespace std;
using std::string;

class invent : public eosio::contract
{
	public:
	using contract::contract;
	///@abi table admin i64

	 struct admin
	{
		account_name id;
		string name;
		uint64_t amount;
		uint64_t primary_key() const {return id; }
	};

	EOSLIB_SERIALIZE(admin,(id)(name)(amount))

 	typedef multi_index<N(admin),admin> admin1;

	 ///@abi action

        void adminreg(account_name id,string name)
        {
                admin1 ad(_self,_self);
                auto i = ad.find(id);
                if(i==ad.end())
                {
                        ad.emplace(_self,[&](auto& admin)
                        {
				admin.id=id;
                                admin.name=name;
				admin.amount=0;
                        });
                }

        }


	  ///@abi table cust i64

         struct cust
        {
                account_name id;
		string name;
		uint64_t amount;
                uint64_t primary_key() const {return id; }
        };

        EOSLIB_SERIALIZE(cust,(id)(name)(amount))

        typedef multi_index<N(cust),cust> cust1;

	///@abi action

	void customer(account_name id,string name,uint64_t amount)
	{


		cust1 ad(_self,_self);
		auto i = ad.find(id);
		if(i==ad.end())
		{
			ad.emplace(_self,[&](auto& cust)
               		{
				cust.id=id;
				cust.name=name;
				cust.amount=amount;
			});
		}

	}

	 ///@abi table sp i64

         struct sp
        {
                account_name id;
		string pname;
		uint64_t qty;
                uint64_t price;
                uint64_t primary_key() const {return id; }
        };

        EOSLIB_SERIALIZE(sp,(id)(pname)(qty)(price))

        typedef multi_index<N(sp),sp> sp1;

	///@abi action

	void setproducts(account_name id,account_name aid,string name,uint64_t qty,uint64_t price)
	{

		admin1 ad1(_self,_self);
		auto i1 = ad1.find(aid);
		if(i1!=ad1.end())
		{
 		sp1 ad(_self,_self);
		auto i = ad.find(id);
		if(i==ad.end())
		{
			ad.emplace(_self,[&](auto& sp)
			{
				sp.id=id;
				sp.pname=name;
				sp.qty=qty;
				sp.price=price;
			});
		}
		}

	}

	///@abi action

	void getproducts(account_name id,account_name aid,account_name cid,uint64_t qty,uint64_t amt)
	{
		sp1 ad(_self,_self);
		auto i = ad.find(id);
		if(i!=ad.end())
		{
			ad.modify(i,_self,[&](auto& sp)
			{
				if(sp.id==id)
				{
					sp.qty-=qty;
				}
			});
		}

		int a=0;
		cust1 ad1(_self,_self);
		auto it = ad1.find(cid);
		if(it!=ad1.end())
		{
			ad1.modify(it,_self,[&](auto& cust)
			{
				cust.amount-=amt;
				a=1;
			});
		}

		admin1 ad2(_self,_self);
                auto itr = ad2.find(aid);
                if(itr!=ad2.end())
                {
                        ad2.modify(itr,_self,[&](auto& admin)
                        {
				if(a==1)
				{
                                	admin.amount=+amt;
	                        }
                        });
                }
	}
};
EOSIO_ABI(invent,(adminreg)(customer)(setproducts)(getproducts))

