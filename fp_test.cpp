#include "fp_cpp.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <optional>

// Determine test results for integer results
int check_test_int(std::string test_name, int result, int expected)
{
    int failed_tests = 0;
    std::cout << test_name << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    if (result == expected)
    {
        std::cout << "TEST PASSED!" << std::endl;
    }
    else
    {
        std::cout << "TEST FAILED!" << std::endl;
        std::cout << "result:   " << result << std::endl;
        std::cout << "expected: " << expected << std::endl;
        failed_tests++;
    }
    std::cout << "****************************************" << std::endl;
    return failed_tests;
}

// Determine test results for double results
int check_test_double(std::string test_name, double result, double expected)
{
    int failed_tests = 0;
    std::cout << test_name << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    // Floats are hard to compare. Allow a 0.1 tolerance in the comparison
    if (fabs(result - expected) < 0.1)
    {
        std::cout << "TEST PASSED!" << std::endl;
    }
    else
    {
        std::cout << "TEST FAILED!" << std::endl;
        std::cout << "result:   " << result << std::endl;
        std::cout << "expected: " << expected << std::endl;
        failed_tests++;
    }
    std::cout << "****************************************" << std::endl;
    return failed_tests;
}

// Determine test results for list results
template <typename T>
int check_test_list(std::string test_name, T result, T expected)
{
    int failed_tests = 0;
    std::cout << test_name << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    if (result == expected)
    {
        std::cout << "TEST PASSED!" << std::endl;
    }
    else
    {
        std::cout << "TEST FAILED!" << std::endl;
        std::cout << "result:   ";
        for (auto i : result)
            std::cout << i << " ";
        std::cout << std::endl;
        std::cout << "expected: ";
        for (auto i : expected)
            std::cout << i << " ";
        std::cout << std::endl;
        failed_tests++;
    }
    std::cout << "****************************************" << std::endl;
    return failed_tests;
}

// Determine test results for optional<double> results
int check_test_optional_double(std::string test_name, std::optional<double> result, 
                                double expected, bool expect_pass)
{
    int failed_tests = 0;
    std::cout << test_name << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << std::boolalpha;
    if (result.has_value() != expect_pass)
    {
        std::cout << "TEST FAILED!" << std::endl;
        std::cout << "Actual result has value?:   " << result.has_value() << std::endl;
        std::cout << "Expected result has value?: " << expect_pass << std::endl;
        failed_tests++;
    }
    else if (!result.has_value())
    {
        std::cout << "TEST PASSED!" << std::endl;
        std::cout << "As expected, the result does not have a value. Returned empty optional" << std::endl;
    }
    // Floats are hard to compare. Allow a 0.1 tolerance in the comparison
    else if (fabs(result.value() - expected) < 0.1)
    {
        std::cout << "TEST PASSED!" << std::endl;
    }
    else
    {
        std::cout << "TEST FAILED!" << std::endl;
        std::cout << "result:   " << result.value() << std::endl;
        std::cout << "expected: " << expected << std::endl;
        failed_tests++;
    }
    std::cout << "****************************************" << std::endl;
    return failed_tests;
}

// Run the sumlist tests (list recursion, tail recursion and HOF)
int sumlist_tests()
{
    int failed_tests = 0;
    // sumlist test 1
    std::vector<int> sumlist_1{};
    int sumlist_1_exp = 0;

    int sumlist_1_res = sumlist<int, std::vector<int>::iterator>(sumlist_1.begin(), sumlist_1.end());
    failed_tests += check_test_int("Sumlist Test 1: List Recursion", sumlist_1_exp, sumlist_1_res);
    sumlist_1_res = sumlist_tail<int, std::vector<int>::iterator>(sumlist_1.begin(), sumlist_1.end());
    failed_tests += check_test_int("Sumlist Test 1: Tail Recursion", sumlist_1_exp, sumlist_1_res);
    sumlist_1_res = sumlist_HOF<int>(sumlist_1);
    failed_tests += check_test_int("Sumlist Test 1: High Order Function", sumlist_1_exp, sumlist_1_res);

    // sumlist test 2
    std::vector<int> sumlist_2{1,2,3};
    int sumlist_2_exp = 6;

    int sumlist_2_res = sumlist<int, std::vector<int>::iterator>(sumlist_2.begin(), sumlist_2.end());
    failed_tests += check_test_int("Sumlist Test 2: List Recursion", sumlist_2_exp, sumlist_2_res);
    sumlist_2_res = sumlist_tail<int, std::vector<int>::iterator>(sumlist_2.begin(), sumlist_2.end());
    failed_tests += check_test_int("Sumlist Test 2: Tail Recursion", sumlist_2_exp, sumlist_2_res);
    sumlist_2_res = sumlist_HOF<int>(sumlist_2);
    failed_tests += check_test_int("Sumlist Test 2: High Order Function", sumlist_2_exp, sumlist_2_res);

    // sumlist test 3
    std::vector<int> sumlist_3{-3,2,5};
    int sumlist_3_exp = 4;

    int sumlist_3_res = sumlist<int, std::vector<int>::iterator>(sumlist_3.begin(), sumlist_3.end());
    failed_tests += check_test_int("Sumlist Test 3: List Recursion", sumlist_3_exp, sumlist_3_res);
    sumlist_3_res = sumlist_tail<int, std::vector<int>::iterator>(sumlist_3.begin(), sumlist_3.end());
    failed_tests += check_test_int("Sumlist Test 3: Tail Recursion", sumlist_3_exp, sumlist_3_res);
    sumlist_3_res = sumlist_HOF<int>(sumlist_3);
    failed_tests += check_test_int("Sumlist Test 3: High Order Function", sumlist_3_exp, sumlist_3_res);

    // sumlist test 4
    std::vector<double> sumlist_4{3.3,2.8,-1.2};
    double sumlist_4_exp = 3.3 + 2.8 + -1.2;

    double sumlist_4_res = sumlist<double, std::vector<double>::iterator>(sumlist_4.begin(), sumlist_4.end());
    failed_tests += check_test_double("Sumlist Test 4: List Recursion", sumlist_4_exp, sumlist_4_res);
    sumlist_4_res = sumlist_tail<double, std::vector<double>::iterator>(sumlist_4.begin(), sumlist_4.end());
    failed_tests += check_test_double("Sumlist Test 4: Tail Recursion", sumlist_4_exp, sumlist_4_res);
    sumlist_4_res = sumlist_HOF<double>(sumlist_4);
    failed_tests += check_test_double("Sumlist Test 4: High Order Function", sumlist_4_exp, sumlist_4_res);
    
    return failed_tests;
}

// Run the inclist tests (HOF)
int inclist_tests()
{
    int failed_tests = 0;
    // inclist_HOF test 1
    std::vector<int> inclist_HOF_1{1,2,3,4};
    std::vector<int> inclist_HOF_1_exp{2,3,4,5};

    inclist_HOF<int>(inclist_HOF_1);
    failed_tests += check_test_list("Inclist Test 1: High Order Function", inclist_HOF_1, inclist_HOF_1_exp);

    // inclist_HOF test 2
    std::vector<int> inclist_HOF_2{-2,4,5,1};
    std::vector<int> inclist_HOF_2_exp{-1,5,6,2};

    inclist_HOF<int>(inclist_HOF_2);
    failed_tests += check_test_list("Inclist Test 2: High Order Function", inclist_HOF_2, inclist_HOF_2_exp);

    // inclist_HOF test 3
    std::vector<double> inclist_HOF_3{2.3,4.5,7.6};
    std::vector<double> inclist_HOF_3_exp{3.3,5.5,8.6};

    inclist_HOF<double>(inclist_HOF_3);
    failed_tests += check_test_list("Inclist Test 3: High Order Function", inclist_HOF_3, inclist_HOF_3_exp);

    return failed_tests;
}

// Run the compute_area tests
// ADT and pattern matching
int compute_area_tests()
{
    int failed_tests = 0;

    // Compute circle areas
    adt_shape shape = Shape::circle{2.0};
    failed_tests += check_test_double("Compute Area (ADT/Pattern Matching) Test 1: Circle 1", 
                                        compute_area(shape), 12.566);
    shape = Shape::circle{0.0};
    failed_tests += check_test_double("Compute Area (ADT/Pattern Matching) Test 2: Circle 2", 
                                        compute_area(shape), 0);
    // Compute square areas
    shape = Shape::square{12.5};
    failed_tests += check_test_double("Compute Area (ADT/Pattern Matching) Test 3: Square 1", 
                                        compute_area(shape), 156.25);
    shape = Shape::square{0.0};
    failed_tests += check_test_double("Compute Area (ADT/Pattern Matching) Test 4: Square 2", 
                                        compute_area(shape), 0);
    // Compute rectangle areas
    shape = Shape::rectangle{4.6, 7.2};
    failed_tests += check_test_double("Compute Area (ADT/Pattern Matching) Test 5: Rectangle 1", 
                                        compute_area(shape), 33.12);
    shape = Shape::rectangle{0.0, 0.0};
    failed_tests += check_test_double("Compute Area (ADT/Pattern Matching) Test 6: Rectangle 2", 
                                        compute_area(shape), 0);
    // Compute ellipse areas
    shape = Shape::ellipse{8.2, 4.3};
    failed_tests += check_test_double("Compute Area (ADT/Pattern Matching) Test 7: Ellipse 1", 
                                        compute_area(shape), 110.77);
    shape = Shape::ellipse{0.0, 0.0};
    failed_tests += check_test_double("Compute Area (ADT/Pattern Matching) Test 8: Ellipse 2", 
                                        compute_area(shape), 0);
    // Compute cylinder areas
    shape = Shape::cylinder{3.1, 8.8};
    failed_tests += check_test_double("Compute Area (ADT/Pattern Matching) Test 9: Cylinder 1", 
                                        compute_area(shape), 231.787);
    shape = Shape::cylinder{0.0, 0.0};
    failed_tests += check_test_double("Compute Area (ADT/Pattern Matching) Test 10: Cylinder 2", 
                                        compute_area(shape), 0);

    return failed_tests;
}

// Currying tests. Test curryed function calls
int currying_tests()
{
    int failed_tests = 0;

    // Currying add tests, using add and the other functions created from
    // add (inc, add2, add3)
    failed_tests += check_test_int("Currying Add Test 1", add(3)(3), 6);
    failed_tests += check_test_int("Currying Add Test 2", inc(7), 8);
    failed_tests += check_test_int("Currying Add Test 3", add2(7), 9);
    failed_tests += check_test_int("Currying Add Test 4", add3(7), 10);
    failed_tests += check_test_double("Currying Add Test 5", add(3.3)(3.3), 6.6);
    failed_tests += check_test_double("Currying Add Test 6", inc(7.7), 8.7);
    failed_tests += check_test_double("Currying Add Test 7", add2(7.7), 9.7);
    failed_tests += check_test_double("Currying Add Test 8", add3(7.7), 10.7);
 
    // Currying mult tests, using mult and the other functions created from
    // mult (times2, triple, quadruple)
    failed_tests += check_test_int("Currying Multiply Test 1", mult(3)(3), 9);
    failed_tests += check_test_int("Currying Multiply Test 2", mult(3)(0), 0);
    failed_tests += check_test_int("Currying Multiply Test 3", times2(7), 14);
    failed_tests += check_test_int("Currying Multiply Test 4", triple(7), 21);
    failed_tests += check_test_int("Currying Multiply Test 5", quadruple(7), 28);
    failed_tests += check_test_double("Currying Multiply Test 6", mult(3.3)(3.3), 10.89);
    failed_tests += check_test_double("Currying Multiply Test 7", times2(1.5), 3.0);
    failed_tests += check_test_double("Currying Multiply Test 8", triple(1.5), 4.5);
    failed_tests += check_test_double("Currying Multiply Test 9", quadruple(1.5), 6.0);
    failed_tests += check_test_double("Currying Multiply Test 10", quadruple(0), 0.0);
 
    // Currying tip tests, using compute_tip and other functions created from
    // compute_tip (compute_low_tip, compute_avg_tip, compute_high_tip)
    failed_tests += check_test_double("Currying Tip Test 1", compute_tip(15.67)(100), 15.67);
    failed_tests += check_test_double("Currying Tip Test 1", compute_tip(15.67)(0), 0.0);
    failed_tests += check_test_double("Currying Add Test 2", compute_low_tip(122.75), 12.275);
    failed_tests += check_test_double("Currying Add Test 3", compute_avg_tip(122.75), 18.413);
    failed_tests += check_test_double("Currying Add Test 4", compute_high_tip(122.75), 24.55);

    return failed_tests;
}

// Lazy computation of the fibonacci sequence
int lazy_fibonacci_tests()
{
    int failed_tests = 0;

    // Create the fibonacci object
    Fibonacci fib;
    std::cout << std::endl;
    std::cout << "***** Lazy Fibonacci Tests " << std::endl;
    std::cout << "Note: The computation of the fibonacci sequence is only done when needed." << std::endl;
    std::cout << "      New numbers should be printed to the console to show the computation." << std::endl;
    std::cout << "      0 and 1 are already initialized. When a number is requested that has" << std::endl;
    std::cout << "      been computed, it'll be returned with no computation. Otherwise, " << std::endl;
    std::cout << "      computations will only take place as needed and when not done before" << std::endl;
    std::cout << std::endl;

    // Lazy Fibonacci tests
    failed_tests += check_test_int("Lazy Fibonacci Test 1: Fibonacci number 10", 
                                    fib.get_fib_num(10), 55);
    failed_tests += check_test_int("Lazy Fibonacci Test: Fibonacci number 4", 
                                    fib.get_fib_num(4), 3);
    failed_tests += check_test_int("Lazy Fibonacci Test 2: Fibonacci number 8", 
                                    fib.get_fib_num(8), 21);
    failed_tests += check_test_int("Lazy Fibonacci Test 3: Fibonacci number 12", 
                                    fib.get_fib_num(12), 144);
    failed_tests += check_test_int("Lazy Fibonacci Test 4: Fibonacci number 11", 
                                    fib.get_fib_num(11), 89);
    failed_tests += check_test_int("Lazy Fibonacci Test 5: Fibonacci number 15", 
                                    fib.get_fib_num(15), 610);
    failed_tests += check_test_int("Lazy Fibonacci Test 6: Fibonacci number 1", 
                                    fib.get_fib_num(1), 1);

    return failed_tests;
}

// Math computation with error handling, using optional (Maybe) monad
int maybe_optional_monad_tests()
{
    int failed_tests = 0;

    std::optional<double> result;
    std::cout << std::endl;
    std::cout << "***** Maybe/Optional Monad Tests " << std::endl;
    std::cout << "Note: Each of these tests will perform the following computation: " << std::endl;
    std::cout << "      2 * square_root(x / y). Order: 1) divide, 2) square root, 3) Multiply" << std::endl;
    std::cout << "      std::optional is used as the Maybe monad, to allow computation error." << std::endl;
    std::cout << "      Divide will fail if the denominator is 0, and square root will fail on negative numbers." << std::endl;
    std::cout << "      Once a failure is reached, the computation will kick out and not go any furthe.r" << std::endl;
    std::cout << "      View the print statements to ensure the computation is stopped after a failure." << std::endl;
    std::cout << std::endl;
    result = divide(10.0, 5.0) | square_root | double_opt;
    failed_tests += check_test_optional_double("Maybe/Optional Monad Test 1: Valid computation",
                                               result, 2.828, true); 
    result = divide(12.0, 3.0) | square_root | double_opt;
    failed_tests += check_test_optional_double("Maybe/Optional Monad Test 2: Valid computation",
                                               result, 4.0, true); 
    result = divide(10.0, 0.0) | square_root | double_opt;
    failed_tests += check_test_optional_double("Maybe/Optional Monad Test 3: Divide Failure (x/0)",
                                               result, 0.0, false); 
    result = divide(-10.0, 5.0) | square_root | double_opt;
    failed_tests += check_test_optional_double("Maybe/Optional Monad Test 4: Square Root Failure (Negative)",
                                               result, 0.0, false); 

    return failed_tests;
}

// Print a summary and the number of failed tests
void test_summary(int failed_tests)
{
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "             TEST SUMMARY" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << failed_tests << " tests failed. See above detail" << std::endl;
    std::cout << "========================================" << std::endl;
}

int main ()
{
    // Keep track of the number of failed tests
    int failed_tests = 0;
    
    failed_tests += sumlist_tests();

    failed_tests += inclist_tests();

    failed_tests += compute_area_tests();

    failed_tests += currying_tests();

    failed_tests += lazy_fibonacci_tests();
    
    failed_tests += maybe_optional_monad_tests();

    // Print out the test summary. Notify of any failures.
    test_summary(failed_tests);
}
