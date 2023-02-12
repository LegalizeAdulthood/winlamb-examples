include(FindPackageHandleStandardArgs)

find_path(WINLAMB_INCLUDE_DIRS "winlamb/button.h")

if(WINLAMB_INCLUDE_DIRS)
	add_library(winlamb INTERFACE)
	target_compile_definitions(winlamb INTERFACE UNICODE)
	target_include_directories(winlamb INTERFACE "${WINLAMB_INCLUDE_DIRS}")
endif()

find_package_handle_standard_args(winlamb
	REQUIRED_VARS WINLAMB_INCLUDE_DIRS
)
