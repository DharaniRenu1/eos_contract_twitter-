#include <eosiolib/eosio.hpp>

#include <eosiolib/print.hpp>
using namespace eosio;

class hello : public eosio::contract {
  public:
      using contract::contract;


      void hi( account_name user ) {
         print( "Hello, World", name{user} );
      }
	void hello1()
	{
	print("Hello World");
	}
};

EOSIO_ABI( hello, (hi)(hello1) )
