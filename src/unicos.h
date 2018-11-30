/*****************************************************************************************************************************
*                                                                                                                            *
*                     COPYRIGHT (C) 2009    ABB OY, DRIVES                                                                   *
*                                                                                                                            *
******************************************************************************************************************************
*                                                                                                                            *
*                                                                                                                            *
*                     U    U   N    N   I     CCC     OOO     SSSSS                                                          *
*                     U    U   NN   N   I    C      O    O   S                                                               *
*                     U    U   N N  N   I   C      O      O   SSSSSS                                                         *
*                     U    U   N  N N   I   C      O      O         S                                                        *
*                     U    U   N   NN   I    C      O    O   S      S                                                        *
*                      UUUU    N    N   I     CCC     OOO     SSSSSS                                                         *
*                                                                                                                            *
*                                UNICOS platform drive SW                                                                    *
*                                                                                                                            *
*                                                                                                                            *
*                  Subsystem:   -                                                                                            *
*                                                                                                                            *
$                 $Workfile::   unicos.h                                                                                     $
$                 $Revision::   1.6                                                                                          $
$                     $Date::   01 Mar 2012 17:13:42                                                                         $
*                                                                                                                            *
*                 Programmer:   Uni Cos                                                                                      *
*                     Target:   ?                                                                                            *
*                                                                                                                            *
******************************************************************************************************************************
*                                                                                                                            *
*   File description:                                                                                                        *
*   ----------------                                                                                                         *
*                                                                                                                            *
*   Global definitions for the UNICOS platform.                                                                              *
*                                                                                                                            *
*                                                                                                                            *
*   Related documents:                                                                                                       *
*   ------------------                                                                                                       *
*                                                                                                                            *
*   -                                                                                                                        *
*                                                                                                                            *
*                                                                                                                            *
******************************************************************************************************************************
*                                                                                                                            *
*   NOTE!                                                                                                                    *
*   ----                                                                                                                     *
*                                                                                                                            *
*   -                                                                                                                        *
*                                                                                                                            *
*****************************************************************************************************************************/
#ifndef UNICOS_H_INC  // Allow multiple inclusions 
#define UNICOS_H_INC

#define __CWCC__
//----------------------------------------------------------------------------------------------------------------------------
// 1) INCLUDE FILES
//----------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------
// 2) ABBREVIATIONS AND CONSTANTS
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
// Compilers and nicknames
//----------------------------------------------------------------------------------------------------------------------------

#if defined( __TMS320C28XX__)           // Texas Instruments, TMS320C28XX
    #define TI
#elif defined(__TMS320C28XX_FPU32__)    // Texas Instruments, TMS320C283XX
    #define TI
#elif defined(_MSC_VER)                 // Microsoft Visual
    #define VS
#elif defined(__CWCC__)                 // CodeWarrior Metrowerks compiler
    #define PPC
    #define __MPC83XX__ 1
    #define POWERPC
#elif defined(__GNUC__) && defined(_ARCH_PPC) // CodeWarrior GCC compiler
    #define PPCGCC                      // NOTE: __GNUC__ should be checked last because TI asm-compiler
    #define POWERPC                     //       also defines __GNUC__ (for some unknown reason)
    #undef PPC
#elif defined(__GNUC__) && defined(__ARM_ARCH) && !defined(__aarch64__)
    #define GCC_ARM
#endif
#if defined(__GNUC__) && defined(__aarch64__)
    #define GCC_ARM64
#endif
//----------------------------------------------------------------------------------------------------------------------------
// Universals
//----------------------------------------------------------------------------------------------------------------------------
#undef  FALSE
#define FALSE   0

#undef  TRUE
#define TRUE    1

#undef  NULL
#define NULL    0

#undef  RET_OK
#define RET_OK  0

#undef  UNUSED
#define UNUSED(expr)	(void)(expr)

//----------------------------------------------------------------------------------------------------------------------------
// Data type definitions, MAU
//----------------------------------------------------------------------------------------------------------------------------
typedef unsigned int    uindx;                  // data type for loop counters and table indexes
                                                // unsigned int is guaranteed to have at least 16 bits by C-standard

#ifdef  GCC_ARM
    #define MAU                 8              // Minimum addressable unit = 8 bits
    #define STRUCT_LITTLE_ENDIAN               // Bitfield order in structs
    #define WORD_LITTLE_ENDIAN                 // Byte order in words

    #define REAL32_IEC_559_BINARY32             // 'real32' binary format is IEC 60599 binary32 format

    typedef	unsigned int        boolean;
    typedef signed char         int8;   
    typedef unsigned char       uint8;  
    typedef signed short        int16;
    typedef unsigned short      uint16;
    typedef signed long         int32;
    typedef unsigned long       uint32;
    typedef signed long long    int64;
    typedef unsigned long long  uint64;
    typedef float               real32;
    typedef double              real64;
    typedef unsigned            bf;             // UNICOS assumes that 'bf' is at least 16 bits wide
    typedef unsigned short      bf16;
    typedef unsigned long       bf32;
    typedef unsigned long long  bf64;           
#endif

#ifdef  GCC_ARM64
    #define MAU                 8              // Minimum addressable unit = 8 bits
    #define STRUCT_LITTLE_ENDIAN               // Bitfield order in structs
    #define WORD_LITTLE_ENDIAN                 // Byte order in words

    #define REAL32_IEC_559_BINARY32            // 'real32' binary format is IEC 60599 binary32 format

    #if defined(__LP64__)                      // AArch64 compiler 64-bit data model
      typedef unsigned int        boolean;
      typedef signed char         int8;
      typedef unsigned char       uint8;
      typedef signed short        int16;
      typedef unsigned short      uint16;
      typedef signed int          int32;
      typedef unsigned int        uint32;
      typedef signed long         int64;
      typedef unsigned long       uint64;
      typedef float               real32;
      typedef double              real64;
      typedef unsigned            bf;
      typedef unsigned short      bf16;
      typedef unsigned int        bf32;
      typedef unsigned long       bf64;
    #elif defined(__ILP32__)                    // AArch64 compiler 32-bit data model: long and pointer are 32-bit
      typedef unsigned int        boolean;
      typedef signed char         int8;
      typedef unsigned char       uint8;
      typedef signed short        int16;
      typedef unsigned short      uint16;
      typedef signed long         int32;
      typedef unsigned long       uint32;
      typedef signed long long    int64;
      typedef unsigned long long  uint64;
      typedef float               real32;
      typedef double              real64;
      typedef unsigned            bf;
      typedef unsigned short      bf16;
      typedef unsigned long       bf32;
      typedef unsigned long long  bf64;              
    #else
      #error ARM64 data model not defined (ilp32 or lp64)
    #endif

#endif

#ifdef  TI
    #define MAU                 16              // Minimum addressable unit = 16 bits
    #define STRUCT_LITTLE_ENDIAN                // Bitfield order in structs
    #define WORD_LITTLE_ENDIAN                  // Byte order in words

    #define REAL32_IEC_559_BINARY32             // 'real32' binary format is IEC 60599 binary32 format

    typedef unsigned int        boolean;        // 16 bit MAU!
    typedef signed int          int8;           // 16 bit MAU!
    typedef unsigned int        uint8;          // 16 bit MAU!
    typedef signed int          int16;
    typedef unsigned int        uint16;
    typedef signed long         int32;
    typedef unsigned long       uint32;
    typedef signed long long    int64;
    typedef unsigned long long  uint64;
    typedef float               real32;
    typedef long double         real64;
    typedef unsigned int        bf;
    typedef unsigned int        bf16;
    typedef unsigned long       bf32;
    typedef unsigned long long  bf64;           // use of bf64 is not recommended!
#endif

#ifdef  VS
    #define MAU                 8               // Minimum addressable unit = 8 bits
    #define STRUCT_LITTLE_ENDIAN                // Bitfield order in structs
    #define WORD_LITTLE_ENDIAN                  // Byte order in words

    #define REAL32_IEC_559_BINARY32             // 'real32' binary format is IEC 60599 binary32 format

    typedef unsigned char       boolean;
    typedef char                int8;
    typedef unsigned char       uint8;
    typedef short               int16;
    typedef unsigned short      uint16;
    typedef long                int32;
    typedef unsigned long       uint32;
    typedef __int64             int64;
    typedef unsigned __int64    uint64;
    typedef float               real32;
    typedef double              real64;
    typedef unsigned short      bf;
    typedef unsigned short      bf16;
    typedef unsigned long       bf32;
    typedef unsigned __int64    bf64;
#endif

#ifdef POWERPC
    #define MAU                 8              // Minimum addressable unit = 8 bits
    #define STRUCT_BIG_ENDIAN                  // Bitfield order in structs
    #define WORD_BIG_ENDIAN                    // Byte order in words

    #define REAL32_IEC_559_BINARY32             // 'real32' binary format is IEC 60599 binary32 format

    typedef unsigned int        boolean;        
    typedef signed char         int8;           
    typedef unsigned char       uint8;          
    typedef signed short        int16;
    typedef unsigned short      uint16;
    typedef signed long         int32;
    typedef unsigned long       uint32;
    typedef signed long long    int64;
    typedef unsigned long long  uint64;
    typedef float               real32;
    typedef double              real64;
    typedef unsigned            bf;
    typedef unsigned short      bf16;
    typedef unsigned long       bf32;
    typedef unsigned long long  bf64;           // use of bf64 is not recommended!
#endif

//----------------------------------------------------------------------------------------------------------------------------
// LIMIT VALUES FOR DIFFERENT DATA TYPES
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
// Integers
//----------------------------------------------------------------------------------------------------------------------------
#define N8MAX   (127)
#define N8MIN   (-N8MAX-1)    
#define N16MAX  (32767)
#define N16MIN  (-N16MAX-1)    
#define N32MAX  (2147483647)
#define N32MIN  (-N32MAX-1)    
#define N64MAX  (9223372036854775807)
#define N64MIN  (-N64MAX-1)    


//----------------------------------------------------------------------------------------------------------------------------
// Unsigned integers
//----------------------------------------------------------------------------------------------------------------------------
#define U8MIN   (0u)
#define U8MAX   (255u)
#define U16MIN  (0u)
#define U16MAX  (65535u)
#define U32MIN  (0u)
#define U32MAX  (4294967295u)
#define U64MIN  (0u)
#define U64MAX  (18446744073709551615u)

//----------------------------------------------------------------------------------------------------------------------------
// Floats
//----------------------------------------------------------------------------------------------------------------------------
#define R32MIN  1.19209290e-38
#define R32MAX  3.4028235e+38
#define R64MIN  2.22507385e-308
#define R64MAX  1.79769313e+308

//----------------------------------------------------------------------------------------------------------------------------
// Variable and bit macros
//----------------------------------------------------------------------------------------------------------------------------
#define MAX( a, b)          ((a) > (b) ? (a) : (b))     // Select the bigger of two
#define MIN( a, b)          ((a) < (b) ? (a) : (b))     // Select the smaller of two
#define SETBIT(x,y)         ((x) |= (0x1<<(y)))         // Set bit y in variable x
#define CLEARBIT(x,y)       ((x) &= (~(0x1<<(y))))      // Clear bit y in variable x
#define CHECKBIT(x,y)       (((x) & (0x1<<(y))) != 0)   // Check if bit y is set in variable x, return 1 or 0

//------------------------------------------------------------------------------------------------------------------------
// Number of elements in an array
//------------------------------------------------------------------------------------------------------------------------
#define NUM_ELEMENTS(a)     (sizeof(a) / sizeof((a)[0]))  // Number of elements in an array

//------------------------------------------------------------------------------------------------------------------------
// Compile time assert
//------------------------------------------------------------------------------------------------------------------------
// Some helper macros to generate file name and line number as the assert error message
#define S1(x) #x
#define S2(x) S1(x)
#define ASSERT_LOCATION "File " __FILE__ " Line " S2(__LINE__)

// User macro STATIC_ASSERT(test)
#if __cplusplus >= 201103L
    #define STATIC_ASSERT(test) static_assert((test), ASSERT_LOCATION)
#elif __STDC_VERSION__ >= 201112L
    #define STATIC_ASSERT(test) _Static_assert((test), ASSERT_LOCATION)
#else
    #define STATIC_ASSERT(test) extern uint32 (*dummy_extern_for_static_assert(void)) [sizeof(uint32[1 - 2*!(test)])]
#endif


//----------------------------------------------------------------------------------------------------------------------------
// Disable/Enable Interrupts.
//----------------------------------------------------------------------------------------------------------------------------
#ifdef TI

    #ifdef __cplusplus
    extern "C" {
    #endif

    //------------------------------------------------------------------------------------------------------------------------
    // Common CPU Definitions:
    //------------------------------------------------------------------------------------------------------------------------

    extern cregister volatile unsigned int IFR;
    extern cregister volatile unsigned int IER;

    #define  ENAINT asm(" clrc INTM")
    #define  DISINT asm(" setc INTM")

    #ifdef __cplusplus
    }
    #endif /* extern "C" */

    //------------------------------------------------------------------------------------------------------------------------
    // Allocate space for the old status register value.
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_STORAGE   uint16  u16CPU_SR
    //------------------------------------------------------------------------------------------------------------------------
    // Define a variable for the old status register value.
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_STORAGE_VAR(A)   uint16 (A)
    //------------------------------------------------------------------------------------------------------------------------
    // Return the old status register value.
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_STATE   (u16CPU_SR)

    //------------------------------------------------------------------------------------------------------------------------
    // Disable Interrupts.
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_DC    {                                       \
                            u16CPU_SR = IER;                    \
                            IER = 0x0000;                       \
                        }

    //------------------------------------------------------------------------------------------------------------------------
    // Disable Interrupts.
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT                                               \
                        uint16  u16CPU_SR;                      \
                        u16CPU_SR = IER;                        \
                        IER = 0x0000;                                   
                    
    //------------------------------------------------------------------------------------------------------------------------
    // Enable Interrupts.
    //------------------------------------------------------------------------------------------------------------------------
    #define  EINT   {                                           \
                        IER = u16CPU_SR;                        \
                    }
    //------------------------------------------------------------------------------------------------------------------------
    // Trap debugger.
    //------------------------------------------------------------------------------------------------------------------------
    #define  TRAP_DEBUGGER  asm(" ESTOP0")
    #define  TRAP_DEBUGGER_IF(condition)

#endif

#ifdef VS

#ifdef __cplusplus
    extern "C" {
#endif
        extern void CPU_IntDis();
        extern void CPU_IntEn();
#ifdef __cplusplus
}
#endif
    //------------------------------------------------------------------------------------------------------------------------
    // Allocate space for the old status register value = no operations.
    //------------------------------------------------------------------------------------------------------------------------

    #ifdef __MINGW32__
        #define  DINT_STORAGE
    #else
        #define  DINT_STORAGE   uint16  u16CPU_SR = 0;
    #endif
    //------------------------------------------------------------------------------------------------------------------------
    // Define a variable for the old status register value.
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_STORAGE_VAR(A)   uint16 (A)
    //------------------------------------------------------------------------------------------------------------------------
    // Return the old status register value.
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_STATE   (u16CPU_SR)

#ifdef VIRTUALDRIVE 
    //------------------------------------------------------------------------------------------------------------------------
    // Disable Interrupts = no operations.
    //------------------------------------------------------------------------------------------------------------------------
    #define DINT_DC CPU_IntDis();
    #define ENAINT  CPU_IntEn();
    #define DISINT  CPU_IntDis();

    //------------------------------------------------------------------------------------------------------------------------
    // Disable Interrupts = no operations.
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT CPU_IntDis();

    //------------------------------------------------------------------------------------------------------------------------
    // Enable Interrupts = no operations.
    //------------------------------------------------------------------------------------------------------------------------
    #define  EINT CPU_IntEn();
#else
    #define DINT_DC
    #define ENAINT
    #define DISINT

    #define DINT
    #define EINT
#endif
    //------------------------------------------------------------------------------------------------------------------------
    // Trap debugger.
    //------------------------------------------------------------------------------------------------------------------------
    #include "assert.h"
    #define TRAP_DEBUGGER                   { assert(0); }
    #define TRAP_DEBUGGER_IF(condition)     if((condition)) { TRAP_DEBUGGER; }

    //------------------------------------------------------------------------------------------------------------------------
    // Remove when Chili code has been removed from virtual drive project...
    //------------------------------------------------------------------------------------------------------------------------
    #define MEM_BARRIER
    
    //------------------------------------------------------------------------------------------------------------------------
    // Windows specific code  
    //------------------------------------------------------------------------------------------------------------------------
    #ifdef _MSC_VER
        #pragma warning(disable: 4103)
        #pragma warning(disable: 4351) //  warning C4351: new behavior: elements of array '...' will be default initialized
    #endif // _MSC_VER
#endif

#ifdef GCC_ARM
    //------------------------------------------------------------------------------------------------------------------------
    // Allocate a storage variable for the status register value
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_STORAGE   uint32  u32CPU_SR = 0

    //------------------------------------------------------------------------------------------------------------------------
    // Define a storage variable for the status register value
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_STORAGE_VAR(A)   uint32 (A)

    //------------------------------------------------------------------------------------------------------------------------
    // Return the saved status register value.
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_STATE   (u32CPU_SR)

    //------------------------------------------------------------------------------------------------------------------------
    // Disable Interrupts: save interrupt enable state and disable interrupts
    //
    // Note: see https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html for the asm syntax
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_DC  \
             __asm__ __volatile__ ("mrs %[reg],cpsr\n" "cpsid if\n" "dsb\n" : [reg] "=r" (u32CPU_SR) :: "memory");

    //------------------------------------------------------------------------------------------------------------------------
    // Disable Interrupts: allocate storage variable, save interrupt enable state and disable interrupts
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT      DINT_STORAGE; DINT_DC

    //------------------------------------------------------------------------------------------------------------------------
    // Enable Interrupts: restore the saved interrupt enable state
    //------------------------------------------------------------------------------------------------------------------------
    #define  EINT  \
             __asm__ __volatile__ ("dsb\n" "msr cpsr_c,%[reg]\n" ::  [reg] "r" (u32CPU_SR) : "memory");

    //------------------------------------------------------------------------------------------------------------------------
    // Brute force enable and disable
    //------------------------------------------------------------------------------------------------------------------------
    #define  DISINT  \
             __asm__ __volatile__ ("cpsid if\n" "dsb\n" ::: "memory");
    #define  ENAINT  \
             __asm__ __volatile__ ("dsb\n" "cpsie if\n" ::: "memory");

    //------------------------------------------------------------------------------------------------------------------------
    // Memory barrier for the CPU and for the compiler optimizer
    //------------------------------------------------------------------------------------------------------------------------
    #define MEM_BARRIER  \
            __asm__ __volatile__ ("dsb" : : : "memory")

    //------------------------------------------------------------------------------------------------------------------------
    // Trap debugger.
    //------------------------------------------------------------------------------------------------------------------------
    #if defined(__ARM_ARCH_7A__)
        #define  TRAP_DEBUGGER  __asm__ __volatile__ ("BKPT #0\n" ::: "memory" );
    #elif defined(__ARM_ARCH_8A__)
        #ifdef __thumb__
            #define  TRAP_DEBUGGER  __asm__ __volatile__ ("HLT #0x3C\n" ::: "memory" );
        #else
            #define  TRAP_DEBUGGER  __asm__ __volatile__ ("HLT #0xF000\n" ::: "memory" );
        #endif
    #else
        #error  "Unknown ARM architecture"
    #endif

    #define  TRAP_DEBUGGER_IF(condition)

#endif

#ifdef GCC_ARM64
    //------------------------------------------------------------------------------------------------------------------------
    // Allocate a storage variable for the status register value
    //------------------------------------------------------------------------------------------------------------------------
    #if defined(__LP64__)                      // AArch64 compiler 64-bit data model
    #define  DINT_STORAGE   uint64  uCPU_SR = 0
    //------------------------------------------------------------------------------------------------------------------------
    // Define a storage variable for the status register value
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_STORAGE_VAR(A)   uint64 (A)

    #elif defined(__ILP32__)                    // AArch64 compiler 32-bit data model: long and pointer are 32-bit
    #define  DINT_STORAGE   uint32  uCPU_SR = 0
    //------------------------------------------------------------------------------------------------------------------------
    // Define a storage variable for the status register value
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_STORAGE_VAR(A)   uint32 (A)
    #endif
    //------------------------------------------------------------------------------------------------------------------------
    // Return the saved status register value.
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_STATE   (uCPU_SR)

    //------------------------------------------------------------------------------------------------------------------------
    // Disable Interrupts: save interrupt enable state and disable interrupts
    //
    // Note: see https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html for the asm syntax
    //------------------------------------------------------------------------------------------------------------------------

    #define  DINT_DC  \
             __asm__ __volatile__ ("mrs    %[sr_res], daif\r\n"  "msr    daifset, #3\r\n" "dsb sy\r\n" : [sr_res]"=r" (uCPU_SR):: "memory");

    //------------------------------------------------------------------------------------------------------------------------
    // Disable Interrupts: allocate storage variable, save interrupt enable state and disable interrupts
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT      DINT_STORAGE; DINT_DC

    //------------------------------------------------------------------------------------------------------------------------
    // Enable Interrupts: restore the saved interrupt enable state
    //------------------------------------------------------------------------------------------------------------------------
#if 1
    #ifdef __cplusplus
    extern "C" {
    #endif          
    #if defined(__LP64__)                       // AArch64 compiler 64-bit data model
    void    OS_CPU_SR_Restore(uint64);
    #elif defined(__ILP32__)                    // AArch64 compiler 32-bit data model: long and pointer are 32-bit
    void    OS_CPU_SR_Restore(uint32);
    #endif
    #ifdef __cplusplus
    }
    #endif

    #define  EINT  OS_CPU_SR_Restore(uCPU_SR);
#else
    #define  EINT  \
             __asm__ __volatile__ ("dsb sy\r\n" "msr daif, %[sr_val]\r\n" :: [sr_val]"r" (uCPU_SR) : "memory");
#endif
    //------------------------------------------------------------------------------------------------------------------------
    // Brute force enable and disable
    //------------------------------------------------------------------------------------------------------------------------

    #define  DISINT  \
             __asm__ __volatile__ ("msr daifset, #3\n" "dsb sy\n" ::: "memory");

    #define  ENAINT  \
             __asm__ __volatile__ ("msr daifclr, #3\r\n" "dsb sy\r\n" ::: "memory");

    //------------------------------------------------------------------------------------------------------------------------
    // Memory barrier for the CPU and for the compiler optimizer
    //------------------------------------------------------------------------------------------------------------------------
    #define MEM_BARRIER  \
            __asm__ __volatile__ ("dsb sy" ::: "memory")

    //------------------------------------------------------------------------------------------------------------------------
    // Trap debugger.
    //------------------------------------------------------------------------------------------------------------------------
    #define  TRAP_DEBUGGER  __asm__ __volatile__ ("hlt #0xf000\r\n" ::: "memory");
    #define  TRAP_DEBUGGER_IF(condition)
#endif


#ifdef POWERPC
    #define disable_int(x) ((x)=int_disable())

    //------------------------------------------------------------------------------------------------------------------------
    // Allocate space for the old status register value = no operations.
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_STORAGE   uint32 u32CPU_SR;

    //------------------------------------------------------------------------------------------------------------------------
    // Define a variable for the old status register value.
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_STORAGE_VAR(A)   uint32 (A)
    //------------------------------------------------------------------------------------------------------------------------
    // Return the old status register value.
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_STATE   (u32CPU_SR)

    //------------------------------------------------------------------------------------------------------------------------
    // Disable Interrupts
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT_DC        disable_int(u32CPU_SR);

    //------------------------------------------------------------------------------------------------------------------------
    // Disable Interrupts
    //------------------------------------------------------------------------------------------------------------------------
    #define  DINT           uint32  u32CPU_SR;                              \
                            disable_int(u32CPU_SR);

    #define  DISINT         uint32  u32CPU_SR;                              \
                            disable_int(u32CPU_SR);
                            
    //------------------------------------------------------------------------------------------------------------------------
    // Enable Interrupts 
    //------------------------------------------------------------------------------------------------------------------------
    #define  EINT               enable_int(u32CPU_SR);
    #define  ENAINT             enable_int(u32CPU_SR);

    //------------------------------------------------------------------------------------------------------------------------
    // NO protected registers in MPC 
    //------------------------------------------------------------------------------------------------------------------------
    #define  EDIS          
    #define  EALLOW         

#endif

#ifdef PPC

    //------------------------------------------------------------------------------------------------------------------------
    //  The following structure and macros allow reverse-endian operations to and from memory and I/O addresses
    //------------------------------------------------------------------------------------------------------------------------

    #pragma pack (0,0,1)
    typedef struct {unsigned short shrt; } *LES;
    typedef struct {unsigned long  lng; } *LEL;
    #pragma pack (0)

    #define RE_LONG(b)          ((LEL)(b))->lng
    #define RE_SHORT(b)         ((LES)(b))->shrt

#ifdef __cplusplus
extern "C" {
#endif

#pragma section code_type ".ICacheLock"
    asm unsigned long int_disable(void);
    asm void enable_int(register unsigned long);
#pragma section code_type ".text"

    #define INIT_SECTION_ATTRIB __declspec(section ".init")
    #define SECTION_DECL(x) __declspec(section x)

#ifdef __cplusplus
}
#endif

    //------------------------------------------------------------------------------------------------------------------------
    // Trap debugger.
    //------------------------------------------------------------------------------------------------------------------------
    #define  TRAP_DEBUGGER
    #define  TRAP_DEBUGGER_IF(condition)

#endif

#ifdef PPCGCC

    //------------------------------------------------------------------------------------------------------------------------
    //  The following structure and macros allow reverse-endian operations to and from memory and I/O addresses
    //------------------------------------------------------------------------------------------------------------------------
    #pragma pack (0)
    typedef struct {unsigned short shrt; } *LES;
    typedef struct {unsigned long  lng; } *LEL;
    #pragma pack (0)

    #define RE_LONG(b)          ((LEL)(b))->lng
    #define RE_SHORT(b)         ((LES)(b))->shrt

#ifdef __cplusplus
extern "C" {
#endif

    __attribute__ ((section (".ICacheLock"))) unsigned long int_disable(void);
    __attribute__ ((section (".ICacheLock"))) void enable_int(register unsigned long);

    #define INIT_SECTION_ATTRIB __attribute__ ((section (".init")))
    #define SECTION_DECL(x) __attribute__ ((section (#x)))

#ifdef __cplusplus
}
#endif

    //------------------------------------------------------------------------------------------------------------------------
    // Trap debugger.
    //------------------------------------------------------------------------------------------------------------------------
    #if defined(OFFICIAL_RELEASE) || defined(BASELINE_RELEASE) || defined (NDEBUG) || defined(TRAP_DEBUGGER_OFF)
        #define TRAP_DEBUGGER
        #define TRAP_DEBUGGER_IF(condition)
    #else
        #include "SSWSTDIO_api.h"
        #ifdef __cplusplus
        extern "C"
        {
        #endif
            extern void HALSTDIO_vWriteLedDisplay (E_DisplaySelect eDisplaySelect, uint16 u16DispChar);
        #ifdef __cplusplus
        }
        #endif
                                                // Stop task switching by disabling interrupts and wait in while loop.
        #define TRAP_DEBUGGER                   {                                                       \
                                                    DINT;                                               \
                                                    HALSTDIO_vWriteLedDisplay (DISP_CHANNEL_0, 't');    \
                                                    volatile boolean trap = TRUE;                       \
                                                    while(trap){};                                      \
                                                    HALSTDIO_vWriteLedDisplay (DISP_CHANNEL_0, 'o');    \
                                                    EINT;                                               \
                                                }


        #define TRAP_DEBUGGER_IF(condition)     if(condition)           \
                                                {                       \
        	                                        TRAP_DEBUGGER       \
                                                }
    #endif

#endif

//----------------------------------------------------------------------------------------------------------------------------
// 3) DATA STRUCTURES
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
// Time format structures
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
// Time format for time stamps used in communication.
//----------------------------------------------------------------------------------------------------------------------------
typedef struct time {
    uint32    u32Ticks;         // 1 = 100 us
    uint16    u16Days;          // 1.1.1980 = 1
} T_TIME;

//----------------------------------------------------------------------------------------------------------------------------
// New time format for time stamps.
//----------------------------------------------------------------------------------------------------------------------------
typedef struct time2 {
    uint32    u32Seconds;       // 1 = 1 s
    uint32    u32SubSeconds;    // 1 = 100 ns
    uint16    u16Days;          // 1.1.1980 = 1
} T_TIME2;

//----------------------------------------------------------------------------------------------------------------------------
// Optimized time format for fault logger to save 32-bit word
//----------------------------------------------------------------------------------------------------------------------------
typedef struct time3 {
    uint32    u32Ticks;         // 1 = 100 us
    uint16    u16Days;          // 1.1.1980 = 1
    uint16    u16Source;        // Time source (real / ticks?)
} T_TIME3;

//----------------------------------------------------------------------------------------------------------------------------
// Optimized time format for 16-bit fieldbus interface with three parameters.
//----------------------------------------------------------------------------------------------------------------------------
typedef struct time4 {
    uint16    u16MilliSeconds;  // 1 = 1 millisecond    0...59999
    uint16    u16Minutes;       // 1 = 1 minute         0...1439
    uint16    u16Days;          // 1.1.1980 = 1
} T_TIME4;

//----------------------------------------------------------------------------------------------------------------------------
// 4) GLOBAL VARIABLE DECLARATIONS
//----------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------
// 5) GLOBAL FUNCTION  DECLARATIONS
//----------------------------------------------------------------------------------------------------------------------------


#endif  // of UNICOS_H_INC

// EOF, no more - time for a nice session with Mac?
