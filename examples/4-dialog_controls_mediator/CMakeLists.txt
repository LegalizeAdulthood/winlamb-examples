add_subdirectory(mediator)
add_example(4-dialog_controls_mediator
    RESOURCES 4-dialog_controls_mediator.rc
    SOURCES
        resource.h
    LIBRARIES
        mediator
)
