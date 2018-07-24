#include<eosiolib/eosio.hpp>
#include<eosiolib/print.hpp>

using namespace eosio;

using std::string;

class Hospital : public eosio::contract
{
	using contract::contract;

	struct doctor
	{
		uint64_t id;
		account_name name;

		uint64_t primary_key() const {return name;}

		EOSLIB_SERIALIZE(doctor, (id)(name));

	};

	typedef multi_index<N(doctor),doctor>  doctor1;

	public:
         void doctor(uint64_t id1,account_name name1)
	{

	doctor1 doctor(_self,_self);

	auto i = doctor.find(name1);

	if(i==doctor.end())
	{
		doctor.emplace(_self,[&](auto& doctor)
		{
			doctor.id=id1;
			doctor.name=name1;
		});


	}
	else
	{
		print("Hello");
	}
	}

};
EOSIO_ABI(Hospital, (doctor))
