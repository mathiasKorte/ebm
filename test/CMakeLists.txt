# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(ebmTests LANGUAGES CXX)

# ---- Tests ----

add_executable(ebm_test src/ebm_test.cpp)
target_link_libraries(ebm_test PRIVATE ebm_lib)
target_compile_features(ebm_test PRIVATE cxx_std_11)

add_test(NAME ebm_test COMMAND ebm_test)

# ---- End-of-file commands ----

add_folders(Test)
