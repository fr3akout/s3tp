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
	uint32_t id;
	bool succeeded;

public:
	Event();
	Event(uint32_t id);
	virtual ~Event() = default;

	void wait_for_resolution();

	virtual void dispatch(Dispatcher *dispatcher) = 0;

	uint32_t get_id() const;

	bool has_succeeded() const;

protected:
	void resolve();
	void reject();
};


}


#endif
