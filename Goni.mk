LOCAL_PATH:= $(call my-dir)

# the device library
include $(CLEAR_VARS)

LOCAL_SRC_FILES := src/BroadMessage.cpp \
				src/BroadSignal.cpp \
				src/BroadReceive.cpp

LOCAL_CFLAGS += -std=gnu++0x

LOCAL_MODULE:= libbroadcast

LOCAL_C_INCLUDES += $(call include-path-for, system-core)/cutils \
					framework/native/include \
					external/dbus \
					$(LOCAL_PATH)/include

LOCAL_SHARED_LIBRARIES += liblog \
						  libicuuc \
						  libicui18n \
				          libutils \
						  libdbus

include $(BUILD_SHARED_LIBRARY)


# demo
include $(CLEAR_VARS)

LOCAL_SRC_FILES := test/signal.cpp

LOCAL_MODULE:= broad_signal

LOCAL_C_INCLUDES += $(call include-path-for, system-core)/cutils \
					$(LOCAL_PATH)/include

LOCAL_SHARED_LIBRARIES += libbroadcast \
				          libutils \

include $(BUILD_EXECUTABLE)

#
include $(CLEAR_VARS)

LOCAL_SRC_FILES := test/receive.cpp

LOCAL_MODULE:= broad_receive

LOCAL_C_INCLUDES += $(call include-path-for, system-core)/cutils \
					$(LOCAL_PATH)/include

LOCAL_SHARED_LIBRARIES += libbroadcast \
				          libutils \

include $(BUILD_EXECUTABLE)
