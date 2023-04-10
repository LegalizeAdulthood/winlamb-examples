find_package(GTest CONFIG REQUIRED)

add_executable(test-mediator test_mediator.cpp)
target_link_libraries(test-mediator PUBLIC mediator GTest::gmock_main)
set_property(TARGET test-mediator PROPERTY FOLDER "Examples/Tests")
