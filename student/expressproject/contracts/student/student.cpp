#include<eosiolib/eosio.hpp>
#include<eosiolib/print.hpp>

using namespace eosio;

class student1 : public eosio::contract
{
	public:
	using contract::contract;

	/// @abi table student i64
	struct student
	{
	uint64_t sid;
	account_name sname;
	uint64_t tam;
	uint64_t eng;
	uint64_t mat;
	uint64_t sci;
	uint64_t ss;
	uint64_t tot;
	uint64_t avg;
	uint64_t primary_key() const {return sname;}
	EOSLIB_SERIALIZE(student,(sid)(sname)(tam)(eng)(mat)(sci)(ss)(tot)(avg))
	};
	typedef multi_index<N(student),student> stud;
	/// @abi action
	void stureg(uint64_t id,account_name name,uint64_t tam,uint64_t eng,uint64_t mat,uint64_t sci,uint64_t ss)
	{
		stud stu(_self,_self);
		auto i = stu.find(name);
		if(i==stu.end())
		{
			stu.emplace(_self,[&](auto& student)
			{
                                student.sid=id;
                                student.sname=name;
                                student.tam=tam;
                                student.eng=eng;
                                student.mat=mat;
                                student.sci=sci;
                                student.ss=ss;
                                student.tot=tam+eng+mat+sci+ss;
                                student.avg=student.tot/5;

			});
		}
	}
	///@abi action
        void stumod(account_name name,uint64_t sub,uint64_t mc)
        {
                stud stu(_self,_self);
                auto i = stu.find(name);
                if(i!=stu.end())
                {
                        stu.modify(i,_self,[&](auto& student)
                        {
				  switch(sub)
                                {
                                case 1:
                                student.tam=mc;
                                break;
                                case 2:
                                student.eng=mc;
                                break;
                                case 3:
                                student.mat=mc;
                                break;
                                case 4:
                                student.sci=mc;
                                break;
                                case 5:
                                student.ss=mc;
                                break;
                                }
                                student.tot=student.tam+student.eng+student.mat+student.sci+student.ss;
                                student.avg=student.tot/5;

                        });
                }
        }
        /// @abi action
        void stuera(account_name name)
        {
                stud stu(_self,_self);
                auto i = stu.find(name);
                if(i!=stu.end())
		{
                	stu.erase(i);
		}
        }



};
EOSIO_ABI(student1, (stureg)(stumod)(stuera))
