#include "HookLoader.h"



HookLoader::HookLoader()
{
	lock_guard<mutex> lockGuard(m_mutex);

	if (m_objCount == 0)
	{
		MH_Initialize();
	}

	m_objCount++;
}

HookLoader::HookLoader(LPVOID srcFunAddr, LPVOID targetFunAddr)
{
	lock_guard<mutex> lockGuard(m_mutex);

	if (m_objCount == 0)
	{
		MH_Initialize();
	}

	MH_CreateHook(srcFunAddr, targetFunAddr, nullptr);

	m_srcFunAddr = srcFunAddr;
	m_targetFunAddr = targetFunAddr;

	m_objCount++;
}

HookLoader::~HookLoader()
{
	lock_guard<mutex> lockGuard(m_mutex);

	m_objCount--;
	if (m_objCount == 0)
	{
		MH_Uninitialize();
	}
}

mutex HookLoader::m_mutex;
int HookLoader::m_objCount = 0;

void HookLoader::reset(LPVOID srcFunAddr, LPVOID targetFunAddr)
{
	MH_DisableHook(m_srcFunAddr);

	MH_CreateHook(srcFunAddr, targetFunAddr, nullptr);

	m_srcFunAddr = srcFunAddr;
	m_targetFunAddr = targetFunAddr;
}

void HookLoader::enable()
{
	MH_EnableHook(m_srcFunAddr);
}

void HookLoader::disable()
{
	MH_DisableHook(m_srcFunAddr);
}