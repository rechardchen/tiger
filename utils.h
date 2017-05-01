#pragma once

#include <cstdint>
#include <cassert>

namespace tiger {

	inline bool isPowerof2(uint64_t value) {
		return value && !(value & (value - int64_t(1L)));
	}

	inline uintptr_t alignAddr(const void* addr, size_t align) {
		assert(isPowerof2(uint64_t(align)) && "alignment should be 2's power");
		return (uintptr_t(addr) + align - 1) & (~uintptr_t(align - 1));
	}

	inline size_t alignAdjustment(const void* ptr, size_t align) {
		return alignAddr(ptr, align) - (uintptr_t)ptr;
	}
}
