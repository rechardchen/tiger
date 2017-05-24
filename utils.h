#pragma once

#include <cstdint>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <stdarg.h>

namespace tiger {
	//
	//void reportError(const char* translation_unit, const char* msg, int line, int col) {
	//TODO: do not call exit
	inline void reportErr(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		vfprintf(stderr, fmt, args);
		va_end(args);
		fprintf(stderr, "\n");
		//exit(-1);
	}

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

	inline uint64_t nextPowerOf2(uint64_t a) {
		a |= (a >> 1);
		a |= (a >> 2);
		a |= (a >> 4);
		a |= (a >> 8);
		a |= (a >> 16);
		a |= (a >> 32);
		return a + 1;
	}
}
