macro(compile_test name)
    add_executable(${name}_test "${name}.test.c")
    target_link_libraries(${name}_test clogger)
    add_test(${name}_test ${name}_test)
endmacro(compile_test)

compile_test(console_transport)
compile_test(file_transport)
compile_test(default_logger)
