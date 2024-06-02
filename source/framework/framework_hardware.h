/* CPU ARCHITECTURE */
#if defined(__x86_64__) || defined(_M_X64)
#define RANBAM_x86_64
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
#define RANBAM_x86_32
#elif defined(__arm__)
#define RANBAM_ARM_32
#elif defined(__aarch64__) || defined(_M_ARM64)
#define RANBAM_ARM_64
#elif defined(mips) || defined(__mips__) || defined(__mips)
#define RANBAM_MIPS
#elif defined(__sh__)
#define RANBAM_SUPERH
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
#define RANBAM_POWERPC_32
#elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
#define RANBAM_POWERPC_64
#elif defined(__sparc__) || defined(__sparc)
#define RANBAM_SPARC
#elif defined(__m68k__)
#define RANBAM_M68K
#elif defined(__risc) || defined(__riscv32) || defined(__riscv__) || defined(_riscv)
#define RANBAM_RISCV
#else
static_assert(false, "Unknown Architecture");
#endif

/* OPERATING SYSTEM */
#if defined(unix) || defined(__unix) || defined(__unix__) || defined(__linux__)
#define RANBAM_UNIX
#endif
#if defined(__APPLE__)
#define RANBAM_APPLE
#endif
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#define RANBAM_WINDOWSS
#else
static_assert(false, "Unknown Compiler")
#endif