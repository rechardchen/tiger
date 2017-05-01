#pragma once
#include "utils.h"

#include <cstdlib>
#include <cstdint>
#include <vector>

namespace tiger {
	template <typename DerivedT> class AllocatorBase {
	public:
		void *Allocate(size_t size, size_t align) {
			return static_cast<DerivedT*>(this)->Allocate(size, align);
		}
		void Deallocate(const void* ptr, size_t size) {
			static_cast<DerivedT>(this)->Deallocate(ptr, size);
		}
		template <typename T>
		T* Allocate(size_t num = 1) {
			return static_cast<T*>(Allocate(num * sizeof(T), alignof(T)));
		}
		template <typename T>
		void Deallocate(const T* ptr, size_t num = 1) {
			Deallocate(static_cast<const void*>(ptr), num * sizeof(T));
		}
	};

	class MallocAllocator : public AllocatorBase<MallocAllocator> {
	public:
		void *Allocate(size_t size, size_t) {
			return malloc(size);
		}
		void Deallocate(const void* ptr, size_t) {
			free(const_cast<void*>(ptr));
		}
	};

	template <typename AllocatorT = MallocAllocator, size_t SlabSize = 4096, 
		size_t SizeThreshold = SlabSize>
		class BumpPtrAllocatorImpl : public AllocatorBase<BumpPtrAllocatorImpl<AllocatorT, SlabSize, SizeThreshold>> {

		static_assert(SizeThreshold <= SlabSize, "SizeThreshold must not be greater than SlabSize.");

		public:
			//BumpPtrAllocatorImpl();
			~BumpPtrAllocatorImpl() {
				for (auto ptr : mSlabs) {
					mRawAllocator.Deallocate(ptr, SlabSize);
				}
				mSlabs.clear();
				for (auto& entry : mCustomizedBlocks) {
					mRawAllocator.Deallocate(entry.first, entry.second);
				}
				mCustomizedBlocks.clear();
			}

			void* Allocate(size_t size, size_t align) {
				size_t adjust = alignAdjustment(mCurPtr, align);

				if (adjust + size <= size_t(mEndPtr - mCurPtr)) {
					char* alignedPtr = mCurPtr + adjust;
					mCurPtr = alignedPtr + size;
					return alignedPtr;
				}
				size_t paddedSize = size + align - 1;
				if (paddedSize > SizeThreshold) {
					char* ptr = (char*)mRawAllocator.Allocate(paddedSize, 0);
					mCustomizedBlocks.push_back({ ptr, paddedSize });
					size_t adjust = alignAdjustment(ptr, align);
					return ptr + adjust;
				}
				StartNewSlab();
				adjust = alignAdjustment(mCurPtr, align);
				char* alignedPtr = mCurPtr + adjust;
				mCurPtr = alignedPtr + size;
				return alignedPtr;
			}

			using AllocatorBase::Allocate;

			void Deallocate(const void* ptr, size_t size) {
				//empty
			}
			
		protected:
			void StartNewSlab() {
				char *ptr = (char*)mRawAllocator.Allocate(SlabSize, 0);
				mSlabs.push_back(ptr);
				mCurPtr = ptr;
				mEndPtr = ptr + SlabSize;
			}

			AllocatorT mRawAllocator;

			char* mCurPtr = nullptr;
			char* mEndPtr = nullptr;
			std::vector<char*> mSlabs;
			std::vector<std::pair<char*, size_t>> mCustomizedBlocks;
	};

	typedef BumpPtrAllocatorImpl<> BumpPtrAllocator;
}

template<typename AllocatorT, size_t SlabSize, size_t SizeThreshold>
void * operator new(size_t size, tiger::BumpPtrAllocatorImpl<AllocatorT, SlabSize, SizeThreshold>& allocator) {
	return nullptr;
}

template<typename AllocatorT, size_t SlabSize, size_t SizeThreshold>
void operator delete(const void* ptr, tiger::BumpPtrAllocatorImpl<AllocatorT, SlabSize, SizeThreshold>& allocator) {

}
