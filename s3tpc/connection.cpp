#include "connection.h"

#include "s3tpc.h"


namespace s3tpc {


constexpr const uint16_t Connection::NEW_CONNECTION_ID;


Connection::Connection(S3TPClient *parent)
	:
	parent{parent},
	id{Connection::NEW_CONNECTION_ID},
	initialized{false} {
}


Connection::~Connection() {
}


void Connection::initialize(uint16_t id) {
	if (!this->initialized) {
		this->initialized = true;
		this->id = id;
	}
}


int Connection::get_id() const {
	return this->id;
}


bool Connection::is_initialized() const {
	return this->initialized;
}


}