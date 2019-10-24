#ifndef _FIREWALL_H_
#define _FIREWALL_H_

//#include "llheader.h"
#include "db_comm.h"
#include "ui_comm.h"
#include "naive_filter.h"
#include "naive_sql_parser.h"
#include <thread>
#include <memory>


using namespace std;

extern atomic<bool> is_learning;
extern int listen_queue_size;

class firewall
{
private:
	logger log;
public:

	void start_firewall(int db_server_port=3306, int firewall_port=6666);

	void comm_with_web_UI(int db_server_port=3306, int ui_comm_port=6667);

};

#endif
