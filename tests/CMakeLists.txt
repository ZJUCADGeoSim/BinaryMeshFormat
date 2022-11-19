enable_testing()
CPMAddPackage(
    NAME "doctest"
    GIT_REPOSITORY "https://__mirror:mirror@ryon.ren:2443/mirrors/doctest.git"
    GIT_TAG "v2.4.9")
add_executable(BMF-test
    ./test.cpp)
add_test(NAME BMF-test COMMAND BMF-test)
target_link_libraries(BMF-test PRIVATE
    doctest::doctest zjucad::BMF)