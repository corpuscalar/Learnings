#pragma once

#include <stdint.h>

template<typename T, size_t COUNT>
class Pool_t
{
	struct ObjectHeader_t
	{
		void*	Ptr		= nullptr;
		bool	IsFree	= true;
	};
private:
	using TSelf			= Pool_t;
	using TObject		= T;
	using TObjectHeader	= ObjectHeader_t;
	using TByte			= unsigned char;
private:
	static constexpr const uint32_t ObjSize			= sizeof(TObject);
	static constexpr const uint32_t ObjPoolSize		= ObjSize * COUNT;
private:
	TObjectHeader mObjectHeaders[COUNT];
	TByte mPool[ObjPoolSize];
public:
	template<typename... TARGS> TObject* Create(TARGS... args) {
		TObjectHeader* header = __FindFreeHeader();
		if (header == nullptr) return nullptr;
		void* __ptr = ::operator new(ObjSize, header->Ptr);
		TObject* obj = new(__ptr) TObject(args...);
		header->IsFree = false;
		return obj;
	}

	void Destroy(TObject* obj) {
		obj->~TObject();
		::operator delete(obj);
	}

	void Init() {
		__BindHeaders();

	}
private:
	TObjectHeader* __FindFreeHeader() {
		for (auto& header : mObjectHeaders) if (header.IsFree) return &header;
		return nullptr;
	}

	TObjectHeader* __FindHeader(TObject* obj) {
		for (auto& header : mObjectHeaders) if (header.Ptr == obj) return &header;
		return nullptr;
	}

	void __BindHeaders() {
		TObject* arr = reinterpret_cast<TObject*>(mPool);
		for (size_t i = 0; i < COUNT; i++) mObjectHeaders[i].Ptr = &arr[i];
	}
public:
	Pool_t() 
	{
	}
};