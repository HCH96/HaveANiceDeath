#pragma once

// Singleton
#define SINGLE(classtype)  	private:\
								classtype();\
								~classtype();\
							friend class CSingleton<classtype>;

// Device
#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetContext()

// Time Manager
#define DT	CTimeMgr::GetInst()->GetDeltaTime()
#define DTd	CTimeMgr::GetInst()->GetDeltaTime_d()

#define DT_ENGINE	CTimeMgr::GetInst()->GetEngineDeltaTime()
#define DTd_ENGINE	CTimeMgr::GetInst()->GetEngineDeltaTime_d()

// Key Manager
#define KEY_CHECK(Key, State) CKeyMgr::GetInst()->GetKeyState(Key) == State
#define KEY_TAP(Key) KEY_CHECK(Key, TAP)
#define KEY_PRESSED(Key) KEY_CHECK(Key, PRESSED)
#define KEY_TAPORPRESS(Key)  (KEY_CHECK(Key, TAP)||KEY_CHECK(Key, PRESSED))

#define KEY_RELEASED(Key) KEY_CHECK(Key, RELEASED)
#define KEY_NONE(Key) KEY_CHECK(Key, NONE)
#define KEY_NONEORREL(Key)  (KEY_CHECK(Key, NONE)||KEY_CHECK(Key, RELEASED))

// Layer
#define LAYER_MAX 32

// Clone
#define CLONE(TYPE) virtual TYPE* Clone() { return new TYPE(*this); }
#define CLONE_DISABLE(TYPE) TYPE* Clone() { return nullptr; assert(nullptr); }\
							TYPE(const TYPE& _OriginBuffer) = delete;