#pragma once

// Singleton
#define SINGLE(classtype)  	private:\
								classtype();\
								~classtype();\
							friend class CSingleton<classtype>;

// Device
#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetContext()


// Clone
#define CLONE(TYPE) virtual TYPE* Clone() { return new TYPE(*this); }
#define CLONE_DISABLE(TYPE) TYPE* Clone() { return nullptr; assert(nullptr); }\
							TYPE(const TYPE& _OriginBuffer) = delete;