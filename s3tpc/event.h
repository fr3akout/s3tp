#ifndef S3TPC_EVENT_H_
#define S3TPC_EVENT_H_


#include <condition_variable>
#include <mutex>


namespace s3tpc {


class Dispatcher;


class Event {
private:
	std::mutex mutex;
	std::condition_variable resolver;

public:
	Event() = default;
	virtual ~Event() = default;

	void wait_for_resolution();

	virtual void dispatch(Dispatcher *dispatcher) = 0;

protected:
	void resolve();
};


}


#endif