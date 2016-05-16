#include "connection.h"

#include "s3tpc.h"


namespace s3tpc {


constexpr const uint16_t Connection::NEW_CONNECTION_ID;


Connection::Connection(S3TPClient *parent)
	:
	parent{parent},
	id{Connection::NEW_CONNECTION_ID},
	state{ConnectionState::NEW} {
}


void Connection::register_with_id(uint16_t id, const std::shared_ptr<Connection> &tracked_self) {
	if (this->has_state(ConnectionState::NEW)) {
		this->state = ConnectionState::REGISTERED;
		this->id = id;
		this->parent->register_connection(tracked_self);
	}
}


void Connection::initialize_ports(uint16_t local_port, uint16_t remote_port) {
	if (this->has_state(ConnectionState::REGISTERED)) {
		this->state = ConnectionState::INITIALIZED;
		this->local_port = local_port;
		this->remote_port = remote_port;
	}
}


void Connection::close() {
	if (!this->has_state(ConnectionState::CLOSED)) {
		this->state = ConnectionState::CLOSED;
		this->parent->deregister_connection(this->get_id());
	}
}


uint16_t Connection::get_id() const {
	return this->id;
}


uint16_t Connection::get_local_port() const {
	return this->local_port;
}


uint16_t Connection::get_remote_port() const {
	return this->remote_port;
}


bool Connection::has_state(const ConnectionState &state) const {
	return this->state == state;
}


ConnectionState Connection::get_state() const {
	return this->state;
}


}
