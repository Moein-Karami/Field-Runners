#include <iostream>
#include <vector>
#include <string>

class A
{
	private:
		int x;
		int y;
		std::string s;
		std::vector<int> v;
	public:
		A(int x_=0,int y_=0, std::string s_="s", std::vector<int> v_={});
		void print();

};

class B
{
	private:
		int b;
		std::string t;
		A a;
	public:
		B( int b_=0, std::string t_="");
		void print(){a.print();}
};