add_test([=[FunctionTest.CanStoreAndCallVoidLambda]=]  D:/ClionProject/kiloLab/cmake-build-debug/test/kiloLab_test_17.exe [==[--gtest_filter=FunctionTest.CanStoreAndCallVoidLambda]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FunctionTest.CanStoreAndCallVoidLambda]=]  PROPERTIES WORKING_DIRECTORY D:/ClionProject/kiloLab/cmake-build-debug/test SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[FunctionTest.CanStoreAndCallParameterizedLambda]=]  D:/ClionProject/kiloLab/cmake-build-debug/test/kiloLab_test_17.exe [==[--gtest_filter=FunctionTest.CanStoreAndCallParameterizedLambda]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FunctionTest.CanStoreAndCallParameterizedLambda]=]  PROPERTIES WORKING_DIRECTORY D:/ClionProject/kiloLab/cmake-build-debug/test SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  kiloLab_test_17_TESTS FunctionTest.CanStoreAndCallVoidLambda FunctionTest.CanStoreAndCallParameterizedLambda)
