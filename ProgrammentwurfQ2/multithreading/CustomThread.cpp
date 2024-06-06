#include "CustomThread.h"


CustomThread::CustomThread(std::chrono::milliseconds executionInterval)
	: m_executionInterval(executionInterval) {}

CustomThread::~CustomThread() {
	stopThread();
}

void CustomThread::startThread() {
	m_shutdown = false;
	std::thread thread(run, this);
	thread.detach();
}

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
