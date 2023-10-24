#include "RE/B/BSTSTLAllocators.h"


namespace RE{

void * BSTHeapSTLAllocatorBase::allocate(std::size_t a_size, std::size_t a_alignment)
{
	using func_t = decltype(&BSTHeapSTLAllocatorBase::allocate);
	REL::Relocation<func_t> func{ REL::ID(34039) };
	return func(a_size, a_alignment);
}

void BSTHeapSTLAllocatorBase::deallocate(void* a_ptr, size_t a_size)
{
	using func_t = decltype(&BSTHeapSTLAllocatorBase::deallocate);
	REL::Relocation<func_t> func{ REL::ID(34440) };
	return func(this, a_ptr, a_size);
}

}