#ifndef S3TPC_S3TPC_H_
#define S3TPC_S3TPC_H_


#include <memory>
#include <string>

#include "dispatcher.h"


namespace s3tpc {


class S3TPClient {
private:
	int control_socket;
	Dispatcher dispatcher;

public:
	S3TPClient();
	virtual ~S3TPClient();

	void connect(const std::string &socket_path);
	void start();
	void stop();

	int get_control_socket() const;

private:
	int init_socket();
	void unblock_socket(int sock);

private:
	static std::unique_ptr<S3TPClient> instance;

public:
	static S3TPClient &get_instance();
};


}


#endif