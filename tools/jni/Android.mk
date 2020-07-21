LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
APP_PLATFORM := 21
LOCAL_MODULE := thoth
LOCAL_LDLIBS += -lm
LOCAL_SRC_FILES := ./thoth.cpp ../../src/thoth.cpp ../../src/language.cpp ../../src/rand.cpp
include $(BUILD_SHARED_LIBRARY)
