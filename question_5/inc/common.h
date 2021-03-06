#ifndef COMMON_H
#define COMMON_H

#include <pthread.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

static const uint32_t HRES = 640;
static const uint32_t VRES = 480;

static const char* window_name[] = {
    "Edge Detector Transform",
    "Hough Line Transform",
    "Hough Elliptical Transform"};

enum threads_e
{
   THREAD_CANNY = 0,
   THREAD_HOUGHL,
   THREAD_HOUGHE,
   THREAD_LOGGER,
   THREAD_MAIN,
   THREAD_MAX = THREAD_MAIN
};

struct threadConfig_s
{
   char* threadName[ 50 ];
   pthread_t thread;
   pthread_attr_t atrributes;
   struct sched_param params;
   bool isAlive;
   bool isActive;
};

extern threadConfig_s* threadConfigs;

extern pthread_mutex_t captureLock;
extern pthread_mutex_t windowLock;

extern CvCapture* capture;

#endif // COMMON_H