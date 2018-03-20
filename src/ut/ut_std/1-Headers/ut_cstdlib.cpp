/***************************************************************************************************
Author:liu.hao

Time:2018-2

info:

***************************************************************************************************/

#include <mkheaders.h>
#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//

class ut_cstdlib : public testing::Test
{
protected:
    static void SetUpTestCase(){}
    static void TearDownTestCase(){}
    virtual void SetUp(){}
    virtual void TearDown(){}
};

//标准库头文件 <cstdlib>
#if 0
    namespace std {
      using size_t = /*see description*/ ;
      using div_t = /*see description*/ ;
      using ldiv_t = /*see description*/ ;
      using lldiv_t = /*see description*/ ;
    }
    
    #define NULL /*see description*/
    #define EXIT_FAILURE /*see description*/
    #define EXIT_SUCCESS /*see description*/
    #define RAND_MAX /*see description*/
    #define MB_CUR_MAX /*see description*/
    
    namespace std {
      // 仅为说明的函数类型别名
      extern "C" using /*c-atexit-handler*/ = void(); // 仅为说明
      extern "C++" using /*atexit-handler*/ = void(); // 仅为说明
      extern "C" using /*c-compare-pred*/ = int(const void* , const void*); // 仅为说明
      extern "C++" using /*compare-pred*/ = int(const void* , const void*); // 仅为说明
      
      // 开始与终止
      [[noreturn]] void abort() noexcept;
      int atexit(/*c-atexit-handler*/ * func) noexcept;
      int atexit(/*atexit-handler*/ * func) noexcept;
      int at_quick_exit(/*c-atexit-handler*/ * func) noexcept;
      int at_quick_exit(/*atexit-handler*/ * func) noexcept;
      [[noreturn]] void exit(int status);
      [[noreturn]] void _Exit(int status) noexcept;
      [[noreturn]] void quick_exit(int status) noexcept;
      char* getenv(const char* name);
      int system(const char* string);
      
      // C 标准库内存分配
      void* aligned_alloc(size_t alignment, size_t size);
      void* calloc(size_t nmemb, size_t size);
      void free(void* ptr);
      void* malloc(size_t size);
      void* realloc(void* ptr, size_t size);
      double atof(const char* nptr);
      int atoi(const char* nptr);
      long int atol(const char* nptr);
      long long int atoll(const char* nptr);
      double strtod(const char* nptr, char** endptr);
      float strtof(const char* nptr, char** endptr);
      long double strtold(const char* nptr, char** endptr);
      long int strtol(const char* nptr, char** endptr, int base);
      long long int strtoll(const char* nptr, char** endptr, int base);
      unsigned long int strtoul(const char* nptr, char** endptr, int base);
      unsigned long long int strtoull(const char* nptr, char** endptr, int base);
      
      // 多字节/宽字符串及字符转换函数
      int mblen(const char* s, size_t n);
      int mbtowc(wchar_t* pwc, const char* s, size_t n);
      int wctomb(char* s, wchar_t wchar);
      size_t mbstowcs(wchar_t* pwcs, const char* s, size_t n);
      size_t wcstombs(char* s, const wchar_t* pwcs, size_t n);
      
      // C 标准库算法
      void* bsearch(const void* key, const void* base,
                    size_t nmemb, size_t size, /*c-compare-pred*/ * compar);
      void* bsearch(const void* key, const void* base,
                    size_t nmemb, size_t size, /*compare-pred*/ * compar);
      void qsort(void* base, size_t nmemb, size_t size, /*c-compare-pred*/ * compar);
      void qsort(void* base, size_t nmemb, size_t size, /*compare-pred*/ * compar);
      
      // 低质量随机数生成
      int rand();
      void srand(unsigned int seed);
      
      // 绝对值
      int abs(int j);
      long int abs(long int j);
      long long int abs(long long int j);
      float abs(float j);
      double abs(double j);
      long double abs(long double j);
      long int labs(long int j);
      long long int llabs(long long int j);
      div_t div(int numer, int denom);
      ldiv_t div(long int numer, long int denom);
      lldiv_t div(long long int numer, long long int denom); 
      ldiv_t ldiv(long int numer, long int denom);
      lldiv_t lldiv(long long int numer, long long int denom);
    }

#endif