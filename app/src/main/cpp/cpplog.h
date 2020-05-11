//
// Created by heweizhen on 2020/5/11.
//
#include <android/log.h>
#ifndef NDK_CPPLOG_H
#define NDK_CPPLOG_H

#endif //NDK_CPPLOG_H

#define LOG_TAG "99788"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
