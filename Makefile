#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := smartled

# COMPONENT_ADD_INCLUDEDIRS := components/include

EXTRA_COMPONENT_DIRS += $(IDF_PATH)/esp-mqtt

CONFIG_ENABLE_MQTT_CFLAGS:=y

# include $(IOT_SOLUTION_PATH)/Makefile
include $(IDF_PATH)/make/project.mk