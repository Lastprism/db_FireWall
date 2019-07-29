#include "firewall/firewall.h"
#include "./utils/CJsonObject.hpp"
#include <thread>
#include <fstream>
using namespace std;
using namespace neb;

extern atomic<bool> is_learning;

int main()
{
	logger log;
	ifstream fin("db_FireWall.json");
	string json;
	string _s;
	while(getline(fin, _s))
	{
		json += _s;
	}

	CJsonObject oJson(json);

	int server_port;
	oJson.Get("server_port", server_port);
	if(server_port < 0 || server_port > 65535)
	{
		log.error("server_port should be in [0,65535]");
		exit(0);
	}

	int firewall_port;
	oJson.Get("firewall_port",firewall_port);
	if(firewall_port < 0 || firewall_port > 65535)
	{
		log.error("firewall_port should be in [0,65535]");
		exit(0);
	}

	int ui_comm_port;
	oJson.Get("ui_comm_port", ui_comm_port);
	if(ui_comm_port < 0 || ui_comm_port > 65535)
	{
		log.error("ui_comm_port should be in [0,65535]");
		exit(0);
	}

	if(server_port == firewall_port || server_port == ui_comm_port || firewall_port == ui_comm_port)
	{
		log.error("ports cannot be same!!");
		exit(0);
	}

	int _is_learning;
	oJson.Get("is_learning", _is_learning);

	is_learning.store(bool(_is_learning));

	thread t1([&,server_port, firewall_port, ui_comm_port](){
		firewall fw;
		logger log;
		log.high_debug("firewall start");
		fw.start_firewall(server_port, firewall_port);
	});
	
	thread t2([&,server_port, firewall_port, ui_comm_port](){
		firewall fw;
		logger log;
		log.high_debug("web_UI start");
		fw.comm_with_web_UI(server_port, ui_comm_port);
	});

	t2.join();
	t1.join();
	
	return 0;
}


