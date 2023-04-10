add_library(mediator
	dialog.h
	mediator.cpp
	mediator.h
)
target_include_directories(mediator PUBLIC .)
target_link_libraries(mediator PUBLIC winlamb)
set_property(TARGET mediator PROPERTY FOLDER "Examples/Libs")

add_subdirectory(tests)
