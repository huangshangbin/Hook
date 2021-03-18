#pragma once

#include "minhook/MinHook.h"

#include <mutex>

using namespace std;

class HookLoader
{
private:
	static mutex m_mutex;
	static int m_objCount;

private:
	LPVOID m_srcFunAddr;
	LPVOID m_targetFunAddr;

public:
	HookLoader();
	HookLoader(LPVOID srcFunAddr, LPVOID targetFunAddr);
	~HookLoader();

private:
	HookLoader(const HookLoader& obj) = delete;
	void operator = (const HookLoader& obj) = delete;
	HookLoader(HookLoader&& obj) = delete;
	void operator = (HookLoader&& obj) = delete;

public:
	void reset(LPVOID srcFunAddr, LPVOID targetFunAddr);

	void enable();
	void disable();
};

