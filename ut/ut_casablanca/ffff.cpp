// ffff.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "containerstream.h"
#include "filestream.h"
#include "http_client.h"
#include "json.h"
#include "producerconsumerstream.h"


#pragma comment(lib,"casablanca120.lib")
using namespace std;
using namespace ::pplx;
using namespace utility;
using namespace concurrency::streams;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;



int _tmain(int argc, _TCHAR* argv[])
{
	// http
	http_client cli(U("http://192.168.240.55:7070"));

	// uri
	uri_builder builder(U("/service/versions"));
	//builder.append_query(U("Host"),U("http://192.168.240.55:7443"));
	builder.append_query(U("Accept"), U("application/json;charset=UTF-8"));
	auto path_query = builder.to_string();


	//get
	auto task = cli.request(methods::GET, path_query).then([](http_response response)
	{
		cout << "error code:" << response.error_code() << endl;
		cout << "status code:" << response.status_code() << endl;

		//body
		
		auto bodystream = response.body();
		streams::stringstreambuf sbuff;
		bodystream.read_to_end(sbuff).get();
		std::wostringstream stream;
		stream.str(std::wstring());
		stream << sbuff.collection().c_str();
		std::wcout << stream.str() << endl;
	}
	);

	// 阻塞
	task.wait();
	system("pause");

	return 0;
}

