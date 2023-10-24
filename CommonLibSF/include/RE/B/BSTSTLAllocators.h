#include "RE/M/MemoryManager.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTList.h"
#include <memory>
namespace RE
{
	class BSTHeapSTLAllocatorBase
	{
    public:
		static void* allocate(std::size_t a_size, std::size_t a_alignment = 0);
        void deallocate(void* a_ptr, size_t a_size);
	};

    // implements c++17 std::allocator_traits
    // This has a second template parameter (size_t N), but it's always set to 2 in practice and allocator_traits blows up if I try and put it here
    template <class T>
    class BSTHeapSTLAllocator : public BSTHeapSTLAllocatorBase
    {
    public:
        using value_type = T;
        using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
        using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::true_type;

        // removed in c++20
        pointer address(reference a_ref) const noexcept {
            return std::addressof(a_ref);
        }

        pointer allocate(size_type a_count, [[maybe_unused]] const void * _hint = 0){
            return static_cast<pointer>(BSTHeapSTLAllocatorBase::allocate(a_count * sizeof(value_type), alignof(value_type)));
        }

        // So that C++23 compilers can use this allocator
        constexpr std::allocation_result<T*, std::size_t> allocate_at_least( std::size_t n ){
            return std::allocation_result<T*, std::size_t>{static_cast<pointer>(BSTHeapSTLAllocatorBase::allocate(n * sizeof(value_type), alignof(value_type))), n};
        }

        void deallocate(pointer a_ptr, size_type a_count){
            BSTHeapSTLAllocatorBase::deallocate(a_ptr, a_count * sizeof(value_type));
        }
        
        // removed in c++20
        size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max() / sizeof(value_type);
        }

        // removed in c++20
        template<class U, class... Args>
        void construct(U* a_ptr, Args&&... a_args){
            new (a_ptr) U(std::forward<Args>(a_args)...);
        }

        // removed in c++20
        template<class U>
        void destroy(U* a_ptr){
            a_ptr->~U();
        }
  
    };

    template <class T, class U>
    bool operator==(const BSTHeapSTLAllocator<T>&, const BSTHeapSTLAllocator<U>&) noexcept
    {
        return true;
    }

    template <class T, class U>
    bool operator!=(const BSTHeapSTLAllocator<T>&, const BSTHeapSTLAllocator<U>&) noexcept
    {
        return false;
    }
    

}