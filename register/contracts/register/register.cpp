#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/vector.hpp>
using namespace eosio;
using namespace std;

class twitter : public contract
{
public :
        using contract :: contract;

        /// @abi table twitreg i64

        struct twitreg
        {
                account_name ac_name;
		string pass;
		string s_key;
		uint64_t primary_key() const { return ac_name; }

                EOSLIB_SERIALIZE(twitreg, (ac_name)(pass)(s_key))
        };

        typedef multi_index<N(twitreg),twitreg> twitreg1;


	///@abi table twitmsg i64

	struct twitmsg
	{
		account_name a_name;
		std::vector<uint64_t> time;
		std::vector<string> msg;
		uint64_t primary_key() const {return a_name;}

		EOSLIB_SERIALIZE(twitmsg, (a_name)(time)(msg))

	};

	typedef multi_index<N(twitmsg),twitmsg> twitmsg1;


        ///@abi table twitcou i64

        struct twitcou
        {
                account_name aname;
		uint64_t count;
                uint64_t primary_key() const {return aname;}

                EOSLIB_SERIALIZE(twitcou, (aname)(count))

        };

        typedef multi_index<N(twitcou),twitcou> twitcou1;


        ///@abi table from i64

        struct from
        {
                account_name fname;
                std::vector<uint64_t> ftime;
                std::vector<string> fmsg;
                uint64_t primary_key() const {return fname;}

                EOSLIB_SERIALIZE(from, (fname)(ftime)(fmsg))

        };

        typedef multi_index<N(from),from> from1;

        ///@abi table to i64

        struct to
        {
                account_name tname;
                std::vector<uint64_t> ttime;
                std::vector<string> tmsg;
                uint64_t primary_key() const {return tname;}

                EOSLIB_SERIALIZE(to, (tname)(ttime)(tmsg))

        };

        typedef multi_index<N(to),to> to1;

        ///@abi table follow i64

        struct follow
        {
                account_name name;
                std::vector<account_name> namef;
                uint64_t primary_key() const {return name;}

                EOSLIB_SERIALIZE(follow, (name)(namef))

        };

        typedef multi_index<N(follow),follow> follow1;

        ///@abi table unfollow i64

        struct unfollow
        {
                account_name uname;
                std::vector<account_name> unamef;
                uint64_t primary_key() const {return uname;}

                EOSLIB_SERIALIZE(unfollow, (uname)(unamef))

        };

        typedef multi_index<N(unfollow),unfollow> unfollow1;


	///@abi action

        void tregister(account_name ac_name, string pass, string s_key)
        {
                twitreg1 twit(_self,_self);

                auto i = twit.find(ac_name);

                if(i == twit.end())
                {
                        twit.emplace(_self, [&](auto& reg)
                        {
                                reg.ac_name = ac_name;
                                reg.pass = pass;
				reg.s_key = s_key;
                                print("Successfully Registered");
                        });
                }

		twitmsg1 twit1(_self,_self);

		auto i1 = twit1.find(ac_name);

		if(i1 == twit1.end())
		{
			twit1.emplace(_self, [&](auto& msg)
			{
				msg.a_name = ac_name;
			});
		}

		twitcou1 twit2(_self,_self);

		auto i2 = twit2.find(ac_name);

		if(i2 == twit2.end())
		{
			twit2.emplace(_self, [&](auto& cou)
			{
				cou.aname = ac_name;
				cou.count = 0;
			});
		}

		from1 twit3(_self,_self);

                auto i3 = twit3.find(ac_name);

                if(i3 == twit3.end())
                {
                        twit3.emplace(_self, [&](auto& from)
                        {
                                from.fname = ac_name;
                        });
                }

           	to1 twit4(_self,_self);

                auto i4 = twit4.find(ac_name);

                if(i4 == twit4.end())
                {
                        twit4.emplace(_self, [&](auto& to)
                        {
                                to.tname = ac_name;
                        });
                }

                follow1 twit5(_self,_self);

                auto i5 = twit5.find(ac_name);

                if(i5 == twit5.end())
                {
                        twit5.emplace(_self, [&](auto& follow)
                        {
                                follow.name = ac_name;
                        });
                }

                unfollow1 twit6(_self,_self);

                auto i6 = twit6.find(ac_name);

                if(i6 == twit6.end())
                {
                        twit6.emplace(_self, [&](auto& unfollow)
                        {
                                unfollow.uname = ac_name;
                        });
                }



        }


	///@abi action

	void modifyreg(account_name ac_name, string pass, string s_key)
	{
		twitreg1 twit(_self,_self);

		auto i = twit.find(ac_name);

		if(i != twit.end())
		{
			twit.modify(i,_self,[&](auto& mod)
			{
				if(mod.ac_name == ac_name && mod.s_key == s_key)
				{
					mod.pass = pass;
				}
			});
		}
	}

	///@abi action

	void chat(account_name ac_name,string msg)
	{

		twitcou1 twit(_self,_self);

		auto i = twit.find(ac_name);

		if(i == twit.end())
		{
			print("you're requested to create an account");
		}
		else
		{
			twit.modify(i,_self,[&](auto& cou)
			{
				cou.count += 1;
			});
		}


		twitmsg1 twit1(_self,_self);

		auto i1 = twit1.find(ac_name);

		if(i1 == twit1.end())
		{
			print("you're requested to create an account");
		}
		else
		{
			 twit1.modify(i1,_self,[&](auto& reg)
                        {
                                reg.msg.push_back(msg);
				reg.time.push_back(now());
                        });
		}
	}

	///@abi action

	void personal(account_name fname,account_name tname,string msg)
	{
		from1 twit(_self,_self);

		auto i = twit.find(fname);

		if(i == twit.end())
		{
			print("you're requested to create an account");
		}
		else
		{
			twit.modify(i,_self,[&](auto& from)
			{
				from.fname = fname;
				from.fmsg.push_back(msg);
				from.ftime.push_back(now());
			});
		}

                to1 twit1(_self,_self);

                auto i1 = twit1.find(tname);

                if(i1 == twit1.end())
                {
                        print("you're requested to create an account");
                }
                else
                {
                        twit1.modify(i1,_self,[&](auto& to)
                        {
                                to.tname = tname;
                                to.tmsg.push_back(msg);
				to.ttime.push_back(now());
                        });
                }

	}

	///@abi action

	void follower(account_name name,account_name namef)
	{
		follow1 twit(_self,_self);

		auto i = twit.find(name);

		if(i == twit.end())
		{
			print("you're requested to create an account");
		}
		else
		{
			twit.modify(i,_self,[&](auto& follow)
			{
				follow.name = name;
				follow.namef.push_back(namef);
			});
		}
	}

        ///@abi action

        void unfollower(account_name uname,account_name unamef)
        {
                unfollow1 twit(_self,_self);

                auto i = twit.find(uname);

                if(i == twit.end())
                {
                        print("you're requested to create an account");
                }
                else
                {
                        twit.modify(i,_self,[&](auto& unfollow)
                        {
                                unfollow.uname = uname;
                                unfollow.unamef.std::remove(unamef);
                        });
                }
        }

	///@abi action

        void del(account_name user)
        {
                twitreg1 twit(_self, _self);

                auto i = twit.find(user);

                if(i != twit.end())
                {
                        twit.erase(i);
                        print("Successfully Removed");
                }
                else
                {
                        print("Username ",name{user}," is invalid");
                }
        }
};

EOSIO_ABI(twitter, (tregister)(modifyreg)(personal)(chat)(follower)(unfollower)(del));

