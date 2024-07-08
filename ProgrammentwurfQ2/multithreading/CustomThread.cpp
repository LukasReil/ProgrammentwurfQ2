#include "CustomThread.h"


CustomThread::CustomThread(std::chrono::milliseconds executionInterval)
	: m_executionInterval(executionInterval) {}

/*
* Stops the underlying thread on destruction to avoid , memory leaks, etc.
*/
CustomThread::~CustomThread() {
	stopThread();
}

/*
* Start a detached thread for true multithreading. 
* If there is already a thread running, this function does nothing.
* The instance of the thread can be deleted, as it is now handled by the OS and not needed for stopping the thread.
*/
void CustomThread::startThread() {
	if (!m_running) {
		m_shutdown = false;
		std::thread thread(run, this);
		thread.detach();
	}
}

/*
* Stops the thread and blocks until it has finished execution.
* Does nothing, if thread is not running.
*/
void CustomThread::stopThread() {
	m_shutdown = true;
	while (m_running);
}

void CustomThread::run(CustomThread* pSelf) {
	pSelf->m_running = true;
	while (!pSelf->m_shutdown) {
		pSelf->threadTask();
		std::this_thread::sleep_for(pSelf->m_executionInterval);
	}
	pSelf->m_running = false;
}
