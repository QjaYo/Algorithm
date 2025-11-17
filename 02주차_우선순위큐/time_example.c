//#define time_example
#ifdef time_example

/* ---------------------------------------------------------------- */

/* 정리
정보가져오기(단위변환용) (예: 해당 CPU는 100tic = 1초 이다)
시작시간 기록 (예: 1000 tic)
끝시간 기록 (예: 1500 tic)
시간차 계산 (예: 1500-1000 = 500 tic)
틱단위를 초단위로 변환 (예: 500tic / 100 = 5초)
출력
*/

/* ---------------------------------------------------------------- */

//windows인 경우
#define windows
#ifdef windows
#include <windows.h>
#include <stdio.h>

int main(void)
{
  LARGE_INTEGER ticksPerSec;
  LARGE_INTEGER start, end, diff;

  //정보 가져오기
    //tick단위 : tick은 CPU가 측정할 수 있는 최소시간단위
    //CPU마다 tick단위가 다르기 때문에 tick을 나노초로 변환하기 위한 정보가 필요
  QueryPerformanceFrequency(&ticksPerSec);

  //시작시간 기록
  QueryPerformanceCounter(&start);

  //시간을 측정하고 싶은 작업을 이곳에 삽입
  for (int i = 0; i < 1000000; i++)
    ;

  //끝시간 기록
  QueryPerformanceCounter(&end);

  //시간차 계산(tick단위)
  diff.QuadPart = end.QuadPart – start.QuadPart;

  //(tick -> 초) 단위변환
  double diff_sec = (double)diff.QuadPart / (double)ticksPerSec.QuadPart;

  printf("time: [%f]sec\n\n", diff_sec);
  return 0;
}

// LARGE_INTEGER의 구조 (간략화)
union _LARGE_INTEGER {
  struct {
    DWORD LowPart;  // 하위 32비트
    LONG  HighPart; // 상위 32비트
  };
  LONGLONG QuadPart;      // 64비트 전체
};

#endif //windows

/* ---------------------------------------------------------------- */

//mac인 경우
#define mac
#ifdef mac

#include <mach/mach_time.h>
#include <stdio.h>

int main()
{
  mach_timebase_info_data_t timebase_info;
  uint64_t start, end, diff;

  //정보 가져오기
    //tick단위 : tick은 CPU가 측정할 수 있는 최소시간단위
    //CPU마다 tick단위가 다르기 때문에 tick을 나노초로 변환하기 위한 정보가 필요
  mach_timebase_info(&timebase_info);

  //시작시간 기록
  start = mach_absolute_time();

  //시간을 측정하고 싶은 작업을 이곳에 삽입
  for (int i = 0; i < 1000000; i++)
    ;

  //끝시간 기록
  end = mach_absolute_time();

  //시간차 계산(tick단위)
  diff = end - start;

  //(tick -> 나노초) 단위변환
    //numerator : 분자, denominator : 분모
  uint64_t diff_nsec = diff * (timebase_info.numer / timebase_info.denom);

  //(나노초 -> 초) 단위변환 (1.0e9 = 10억, 1초 = 10억 나노초)
  double diff_sec = (double)diff_nsec / 1.0e9;

  printf("time: [%f]sec\n", diff_sec);

  return 0;
}


#endif //mac

/* ---------------------------------------------------------------- */

#endif //time_example
