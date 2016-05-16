#include "s3tpc_c.h"

#include <system_error>
#include "connection.h"
#include "s3tpc.h"


extern "C" {


int s3tp_init(const char *socket_path) {
	try {
		s3tpc::S3TPClient &client = s3tpc::S3TPClient::get_instance();
		client.connect_to_s3tpd(socket_path);
		client.start();
	} catch(const std::system_error &e) {
		// negative value of the internal errno
		return -e.code().value();
	}
	return 0;
}


void s3tp_destroy() {
	try {
		s3tpc::S3TPClient &client = s3tpc::S3TPClient::get_instance();
		client.stop();
	} catch(const std::system_error &e) {
		// ignore error
	}
}


int s3tp_create() {
	s3tpc::S3TPClient &client = s3tpc::S3TPClient::get_instance();
	auto connection = client.create_connection();
	if (!connection->has_state(s3tpc::ConnectionState::NEW)) {
		return connection->get_id();
	}
	return -1;
}


int s3tp_connect(int connection, uint16_t port) {
	s3tpc::S3TPClient &client = s3tpc::S3TPClient::get_instance();
	// TODO exception handling
	if (client.connect(connection, port)) {
		return 0;
	}
	return -1;
}


int s3tp_listen(int connection, uint16_t port) {
	return 0;
}


int s3tp_send(int connection, const char *data, size_t length) {
	return 0;
}


int s3tp_receive(int connection, char *data, size_t length) {
	return 0;
}


int s3tp_close(int connection) {
	s3tpc::S3TPClient &client = s3tpc::S3TPClient::get_instance();
	// TODO exception handling
	if (client.close_connection(connection)) {
		return 0;
	}
	return -1;
}


int s3tp_local_port(int connection) {
	s3tpc::S3TPClient &client = s3tpc::S3TPClient::get_instance();
	auto conn = client.get_connection(connection);
	if (conn && conn->has_state(s3tpc::ConnectionState::INITIALIZED)) {
		return conn->get_local_port();
	}
	return -1;
}


int s3tp_remote_port(int connection) {
	s3tpc::S3TPClient &client = s3tpc::S3TPClient::get_instance();
	auto conn = client.get_connection(connection);
	if (conn && conn->has_state(s3tpc::ConnectionState::INITIALIZED)) {
		return conn->get_remote_port();
	}
	return -1;
}


}
