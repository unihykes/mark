/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
// ValidipUT
//

class ValidipUT : public testing::Test
{
protected:
	static void SetUpTestCase(){}
	static void TearDownTestCase(){}
	virtual void SetUp(){}
	virtual void TearDown(){}
	
protected:
	
};

bool isIPValid(string ipstr)
{
	//字符串长度[7-15]
	if(ipstr.size() < 7) {
		return false;
	}
	if(ipstr.size() > 15) {
		return false;
	}
	
	//点的个数不等于3
	auto count = std::count(ipstr.begin(),ipstr.end(), '.');
	if(count != 3) {
		return false;
	}
	
	//存在空白符
	if(ipstr.find_first_of(' ') != string::npos) {
		return false;
	}
	
	//第一个字符就为’.’
	if(ipstr.front() == '.') {
		return false;
	}
	
	//最后一个字符就为’.’
	if(ipstr.back() == '.') {
		return false;
	}
	
	//连续2个或3个'.'在一起
	if(ipstr.find("..") != string::npos) {
		return false;
	}
	
	//拆分子字符串
	vector<string> vStr;
	string::size_type pos = 0;
	do {
		pos = ipstr.find_first_of('.');
		//第4段
		if(pos == string::npos) {
			vStr.push_back(ipstr);
			break;
		}
		//第1,2,3段
		else {
			vStr.push_back(ipstr.substr(0, pos));
			ipstr = ipstr.substr(++pos);
		}
	}while(true);
	
	for(const auto& elem: vStr) {
		//字符串为空
		if(elem.empty()) {
			return false;
		}
		
		//字符串起始为0
		if(elem.size() >1 && elem[0] == '0') {
			return false;
		}
		
		int val = 0;
		try {
			val = stoi(elem);
		}
		catch(...) {
			return false;
		}
		
		//<0
		if(val < 0) {
			return false;
		}
		
		//>255
		if(val > 255) {
			return false;
		}
	}
	
	return true;
}

TEST_F(ValidipUT, Validip)
{
	string ipstr = "4.0.2.34";
	bool ret = isIPValid(ipstr);
	cout << boolalpha<<ret << endl;
}

