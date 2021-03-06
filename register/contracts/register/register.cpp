#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

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

        ///@abi table following i64

        struct following
        {
                account_name me;
                std::vector<account_name> tofollow;
                uint64_t primary_key() const {return me;}
                EOSLIB_SERIALIZE(following, (me)(tofollow))

        };

        typedef multi_index<N(following),following> following1;


	///@abi table like i64

	struct like
	{
		account_name lname;
		std::vector<uint64_t> like_c;
		uint64_t count;
		uint64_t primary_key() const {return lname;}
                EOSLIB_SERIALIZE(like, (lname)(like_c)(count))

	};

	typedef multi_index<N(like),like> like1;

        ///@abi table dislike i64

        struct dislike
        {
                account_name dname;
                std::vector<uint64_t> dislike_c;
                uint64_t count;
                uint64_t primary_key() const {return dname;}
                EOSLIB_SERIALIZE(dislike, (dname)(dislike_c)(count))

        };

        typedef multi_index<N(dislike),dislike> dislike1;

        ///@abi table share i64

        struct share
        {
                account_name poster;
		std::vector<account_name>sh_name;
                std::vector<uint64_t> time;
                uint64_t primary_key() const {return poster;}
                EOSLIB_SERIALIZE(share, (poster)(sh_name)(time))

        };

        typedef multi_index<N(share),share> share1;

        ///@abi table post_sh i64

        struct post_sh
        {
                account_name poster1;
                std::vector<account_name> po_name;
                std::vector<string> post_msg;
                uint64_t primary_key() const {return poster1;}
                EOSLIB_SERIALIZE(post_sh, (poster1)(po_name)(post_msg))

        };

        typedef multi_index<N(post_sh),post_sh> post_sh1;


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

                following1 twit7(_self,_self);

                auto i7 = twit7.find(ac_name);

                if(i7 == twit7.end())
                {
                        twit7.emplace(_self, [&](auto& following)
                        {
                                following.me = ac_name;
                        });
                }

                like1 twit8(_self,_self);

                auto i8 = twit8.find(ac_name);

                if(i8 == twit8.end())
                {
                        twit8.emplace(_self, [&](auto& like)
                        {
                                like.lname = ac_name;
                        });
                }

                dislike1 twit9(_self,_self);

                auto i9 = twit9.find(ac_name);

                if(i9 == twit9.end())
                {
                        twit9.emplace(_self, [&](auto& like)
                        {
                                like.dname = ac_name;
                        });
                }

                share1 twit10(_self,_self);

                auto i10 = twit10.find(ac_name);

                if(i10 == twit10.end())
                {
                        twit10.emplace(_self, [&](auto& share)
                        {
                                share.poster = ac_name;
                        });
                }

                post_sh1 twit11(_self,_self);

                auto i11 = twit11.find(ac_name);

                if(i11 == twit11.end())
                {
                        twit11.emplace(_self, [&](auto& post)
                        {
                                post.poster1 = ac_name;
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

		twitreg1 twitter(_self,_self);

                auto ii = twitter.find(ac_name);

		if(ii == twitter.end())
		{
			print("you're requested to create an account");
		}

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

		twitreg1 twitter(_self,_self);

                auto ii = twitter.find(fname);

                if(ii == twitter.end())
                {
                        print("you're requested to create an account");
                }


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

		twitreg1 twitter(_self,_self);

                auto ii = twitter.find(name);

                if(ii == twitter.end())
                {
                        print("you're requested to create an account");
                }


		follow1 twit(_self,_self);

		auto i = twit.find(name);

		if(i != twit.end())
		{
			twit.modify(i,_self,[&](auto& follow)
			{
				follow.name = name;
				follow.namef.push_back(namef);
			});

			followings(name,namef);
                }

	}


        ///@abi action

        void followings(account_name name,account_name namef)
        {

		twitreg1 twitter(_self,_self);

                auto ii = twitter.find(name);

                if(ii == twitter.end())
                {
                        print("you're requested to create an account");
                }


                follow1 twit1(_self,_self);

                auto i1 = twit1.find(name);

                if(i1 == twit1.end())
                {
                        print("you're requested to create an account");
                }

		following1 twit(_self,_self);

                auto i = twit.find(name);

                if(i != twit.end())
                {
                        twit.modify(i,_self,[&](auto& following)
                        {
                                following.me = name;
                                following.tofollow.push_back(namef);
                        });
                }
        }



        ///@abi action

	void unfollower(account_name uname,account_name unamef)
        {

               twitreg1 twitter(_self,_self);

               auto ii = twitter.find(uname);

               if(ii == twitter.end())
               {
                       print("you're requested to create an account");
               }

		follow1 twit(_self,_self);

		auto i1 = twit.find(uname);

		auto i2 = twit.get(uname);

		if(i1 != twit.end())
		{
			for(uint64_t i =0; i < i2.namef.size();i++)
			{
					if(unamef == i2.namef.at(i))
					 {
						twit.modify(i1,_self,[&](auto& unfollow)
						{
							unfollow.namef.erase( unfollow.namef.begin() + i);
						});
					}
			}
		}

        }

	///@abi action

	void unfollowing(account_name uname,account_name unamef)
	{

               twitreg1 twitter(_self,_self);

               auto ii = twitter.find(uname);

		if(ii == twitter.end())
		{
			print("you've to create an account");
		}

		following1 twit(_self,_self);

		auto i1 = twit.find(uname);

		auto i2 = twit.get(uname);

		if(i1 != twit.end())
		{
			twit.modify(i1,_self,[&](auto& unf)
			{
				for(uint64_t i = 0;i < i2.tofollow.size(); i++)
				{
					if(unamef == i2.tofollow.at(i))
					{
						unf.tofollow.erase( unf.tofollow.begin() + i);
					}
				}
			});
		}

	}

	///@abi action


	void liking(account_name lname,account_name liken,uint64_t time)
	{
                twitreg1 twitter(_self,_self);

                auto ii = twitter.find(lname);

                if(ii == twitter.end())
                {
                        print("you're requested to create an account");
                }


                twitmsg1 twit1(_self,_self);

                auto i1 = twit1.find(lname);

		auto i2 = twit1.get(lname);

                if(i1 == twit1.end())
                {
                        print("you're requested to create an account");
                }
                else
                {

		like1 twit(_self,_self);

		auto i3 = twit.find(lname);

		if(i3 != twit.end())
		{

			for(uint64_t j=0;j<i2.time.size();j++)
			{
				if(i2.time.at(j) == time)
				{
					auto i4 = twit.get(lname);

					for(uint64_t k=0;k<i4.like_c.size();k++)
					{
						if(liken == i4.like_c.at(k))
						{
							twit.modify(i3,_self,[&](auto& like)
							{
								like.like_c.push_back(liken);
								like.count += 1;
							});
						}
						else
						{
							twit.modify(i3,_self,[&](auto& like)
                                                        {
                                                                like.like_c.erase(like.like_c.begin() + k);
                                                                like.count -= 1;
                                                        });
						}
					}
				}
			}
		}
		}

	}


	///@abi action


	void disliking(account_name lname,account_name disliken,uint64_t time)
	{
                twitreg1 twitter(_self,_self);

                auto ii = twitter.find(lname);

                if(ii == twitter.end())
                {
                        print("you're requested to create an account");
                }


                twitmsg1 twit1(_self,_self);

                auto i1 = twit1.find(lname);

		auto i2 = twit1.get(lname);

                if(i1 == twit1.end())
                {
                        print("you're requested to create an account");
                }
                else
                {

		dislike1 twit(_self,_self);

		auto i3 = twit.find(lname);

		if(i3 != twit.end())
		{

			for(uint64_t j=0;j<i2.time.size();j++)
			{
				if(i2.time.at(j) == time)
				{
					auto i4 = twit.get(lname);

					for(uint64_t k=0;k<i4.dislike_c.size();k++)
					{
						if(disliken == i4.dislike_c.at(k))
						{
							twit.modify(i3,_self,[&](auto& like)
							{
								like.dislike_c.push_back(disliken);
								like.count += 1;
							});
						}
						else
						{
							twit.modify(i3,_self,[&](auto& like)
                                                        {
                                                                like.dislike_c.erase(like.dislike_c.begin() + k);
                                                                like.count -= 1;
                                                        });
						}
					}
				}
			}
		}
		}

	}

/*	  EOSLIB_SERIALIZE(share, (poster)(sh_name)(time))
                EOSLIB_SERIALIZE(post_sh, (poster1)(po_name)(post_msg))*/




	///@abi action

	void sharing(account_name poster,account_name sh_name,account_name po_name,string post_msg)
	{

                twitreg1 twitter(_self,_self);

                auto ii = twitter.find(poster);

                if(ii == twitter.end())
                {
                        print("you're requested to create an account");
                }

		auto ii1 = twitter.find(po_name);

                if(ii1 == twitter.end())
                {
                        print("you're requested to create an account");
                }

		auto ii2 = twitter.find(sh_name);

                if(ii2 == twitter.end())
                {
                        print("you're requested to create an account");
                }

		share1 twit(_self,_self);

		auto i = twit.find(poster);

		if(i != twit.end())
		{
			twit.modify(i,_self,[&](auto& share)
			{
				share.sh_name.push_back(sh_name);
				share.time.push_back(now());
			});

			post_sh1 twit1(_self,_self);

			auto i1 = twit1.find(poster);

			if(i1 != twit1.end())
			{
				twit1.modify(i1,_self,[&](auto& post)
				{
					post.po_name.push_back(po_name);
					post.post_msg.push_back(post_msg);
				});
			}

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

EOSIO_ABI(twitter, (tregister)(modifyreg)(personal)(chat)(follower)(followings)(unfollower)(unfollowing)(liking)(del)(disliking)(sharing));

