#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := smartled
COMPONENT_ADD_INCLUDEDIRS := components/include

include component_conf.mk
include $(IDF_PATH)/make/project.mk