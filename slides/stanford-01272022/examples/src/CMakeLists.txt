add_executable(fd_prec fd_prec.cpp)

add_executable(fwd_ad fwd_ad.cpp)
target_link_libraries(fwd_ad PRIVATE ${EXAMPLES_LIBS})

add_executable(rv_ad rv_ad.cpp)
target_link_libraries(rv_ad PRIVATE ${EXAMPLES_LIBS})

add_executable(mle mle.cpp)
target_link_libraries(mle PRIVATE ${EXAMPLES_LIBS})

add_executable(kevin_senpai_mle kevin_senpai_mle.cpp)
target_link_libraries(kevin_senpai_mle PRIVATE ${EXAMPLES_LIBS})

add_executable(map map.cpp)
target_link_libraries(map PRIVATE ${EXAMPLES_LIBS})

add_executable(compare_fd compare_fd.cpp)
target_link_libraries(compare_fd PRIVATE ${EXAMPLES_LIBS})

add_executable(if_else if_else.cpp)
target_link_libraries(if_else PRIVATE ${EXAMPLES_LIBS})

add_executable(for_each for_each.cpp)
target_link_libraries(for_each PRIVATE ${EXAMPLES_LIBS})
