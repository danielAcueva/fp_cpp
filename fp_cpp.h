#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <math.h>
#include <iterator>
#include <variant>
#include <cmath>
#include <optional>
#include <functional>

//////////////////////////////////////////////////////////////////////////////
// List Recursion
//////////////////////////////////////////////////////////////////////////////

// sumlist. Compute the sum of all of the elements of a list
// Uses list recursion
// Use iterators to track the head of the list
template<typename T, typename input_iterator>
T sumlist(input_iterator list_head, input_iterator list_end)
{
    // When the head and end iterators equal, we have finished our recursion (base case)
    // Otherwise add the head to the recursive result of the remainder of the list to compute sum
    return (list_head == list_end)  ? 0
                                    : *list_head + sumlist<T, input_iterator>(list_head+1, list_end); 
}

//////////////////////////////////////////////////////////////////////////////
// List Tail Recursion
//////////////////////////////////////////////////////////////////////////////

// sumlist. Compute the sum of all of the elements of a list
// Uses tail recursion on the list
// Use iterators to track the head of the list
template<typename T, typename input_iterator>
T sumlist_tail(input_iterator list_head, input_iterator list_end, T accumulator = 0)
{
    // When the head and end iterators equal, we have finished our recursion (base case)
    // Otherwise add the head to the current result in an accumulator, while recursively working through the list 
    return (list_head == list_end)  ? accumulator
                                    : sumlist_tail<T, input_iterator>(list_head+1, list_end, *list_head + accumulator); 
}

//////////////////////////////////////////////////////////////////////////////
// High Order FUnctions (HOF). Haskell map and foldr equivalent
//////////////////////////////////////////////////////////////////////////////

// inclist_HOF. increment each element of a list by 1
// Uses a High Order Function (HOF) to complete task. for_each is equivalent to Haskell map
template<typename T>
void inclist_HOF(std::vector<T>& in_list)
{
    // apply the lambda function (which increments the element) over the entire list
    // Applying a function in for_each is equivalent to applying a function via Haskell map.
    // The function will be applied to each element of the list
    std::for_each(in_list.begin(), in_list.end(), [](T& x){x = x + 1;});
}

// sumlist_HOF. Compute the sum of all of the elements of a list
// Uses a High Order Function (HOF) to complete task. accumulate is equivelent to Haskell foldr
template<typename T>
T sumlist_HOF(std::vector<T>& in_list)
{
    // apply the lambda function (which adds elements to a sum) over the entire list
    // Applying a function in accumulate is equivalent to applying a function via Haskell foldr
    // The function will be applied (folding) starting with a base value to each element in the list
    return std::accumulate(in_list.begin(), in_list.end(), 0.0, [](T a, T b){return a + b;});
}

// Algebraic Data Types (ADTs)
// ADT for shape
class Shape
{
public:
    struct circle
    {
        double radius;
    };
    struct square
    {
        double side;
    };
    struct rectangle
    {
        double length;
        double width;
    };
    struct ellipse
    {
        // Axis relative to the center
        double axis_1;
        double axis_2;
    };
    struct cylinder
    {
        double radius;
        double height;
    };
};

//////////////////////////////////////////////////////////////////////////////
// Algebraic Data Types (ADTs) using sum types
//////////////////////////////////////////////////////////////////////////////

// std::variant used to create an ADT sum type
// The adt_shape sum type can be any of the shapes referenced below
using adt_shape = std::variant<Shape::circle, Shape::square, Shape::rectangle, Shape::ellipse, Shape::cylinder>;

// Overloaded function which separates implementations for different sum types
// Necessary for pattern matching with std::variant
template <typename... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
template <typename... Ts> overloaded(Ts...) -> overloaded<Ts...>;

//////////////////////////////////////////////////////////////////////////////
// Pattern Matching using ADT
//////////////////////////////////////////////////////////////////////////////

// Compute the area of any of the allowable shapes
// Pattern matching is used to determine which area computation to use, 
// depending on the shape
double compute_area(const adt_shape& shape)
{
    double area;
    std::visit(overloaded
    {
        [&area](const Shape::circle& circle) { 
            area = M_PI * pow(circle.radius, 2.0); },
        [&area](const Shape::square& square) { 
            area = pow(square.side, 2.0); },
        [&area](const Shape::rectangle& rectangle) { 
            area = rectangle.length * rectangle.width; },
        [&area](const Shape::ellipse& ellipse) { 
            area = M_PI * ellipse.axis_1 * ellipse.axis_2; },
        [&area](const Shape::cylinder& cylinder) { 
            area = 2 * M_PI * cylinder.radius * 
                (cylinder.radius + cylinder.height); }
    }, shape);
    return area;
}

//////////////////////////////////////////////////////////////////////////////
// Function Currying. Create functions that return functions that can be curried
//////////////////////////////////////////////////////////////////////////////

// Curry Function. Create an output lambda function that adds the number
// passed in from the original with whatever else is used as the output function argument
template<typename T>
auto add(T first_in)
{
    return [first_in](T second_in) {return first_in + second_in;};
}

// Use currying to eaily create new functions
auto inc = add(1.0);
auto add2 = add(2.0);
auto add3 = add(3.0);

// Curry Function. Create an output lambda function that multiplies the number
// passed in from the original with whatever else is used as the output function argument
template<typename T>
auto mult(T first_in)
{
    return [first_in](T second_in) {return first_in * second_in;};
}

// Use currying to eaily create new functions
auto times2 = mult(2.0);
auto triple = mult(3.0);
auto quadruple = mult(4.0);

// Curry Function. Create an output lambda function that computes a tip based the number (percentage)
// passed in from the original with whatever else is used as the output function argument (total)
auto compute_tip(double tip_percent)
{
    return [tip_percent](double subtotal) {return (tip_percent / 100.0) * subtotal;};
}

// Use currying to eaily create new functions
auto compute_low_tip = compute_tip(10.0);
auto compute_avg_tip = compute_tip(15.0);
auto compute_high_tip = compute_tip(20.0);

//////////////////////////////////////////////////////////////////////////////
// Lazy evaluation. Only compute fibonacci sequence when needed and not done before
//////////////////////////////////////////////////////////////////////////////

// Lazy evaluation must be done explicitly in C++,
// since it is not part of the language
// A fibonacci class performs a lazy evaluation of the fibonacci sequence
class Fibonacci
{
public: 
    // when a fibonacci number is requested, it will either be returned (if previously computed)
    // or the function will add fibonacci numbers to the stored sequence until it computes the number
    // This prevents any computation until necessary, and recpomputation
    uint64_t get_fib_num(uint16_t fib_index)
    {
        if ((m_fibonacci.size() -1) >=  fib_index)
        {
            return m_fibonacci[fib_index];
        }
        else
        {
            m_fibonacci.push_back(m_fibonacci[m_fibonacci.size()-1] + m_fibonacci[m_fibonacci.size()-2]);
            // Note: print added for understanding when running tests. It can be removed if desired
            std::cout << "Add Fibonacci Number " << m_fibonacci.size()-1 << ": " << m_fibonacci[m_fibonacci.size()-1] << std::endl;
            return get_fib_num(fib_index);
        }
    }
private:
    // A stored sequence is used to prevent re-computation
    std::vector<uint64_t> m_fibonacci = {0,1};
};

//////////////////////////////////////////////////////////////////////////////
// Maybe Monad. Error handling using std::optional
//////////////////////////////////////////////////////////////////////////////

// Bind operation for the maybe monad, using std::optional
// The boilerplate process of checking the optional value, and passing
// along the value is abstracted in this bind operation
// Credit: Maybe and Either Monads in Plain C++ 17 (Timothy A.V Teatro et. al.)
template <typename T, typename F>
auto bind_maybe(std::optional<T> m, F f)
        -> decltype(std::invoke(f, *m)) {
    if (m)
        return std::invoke(f, *m);
    else
        return {};
}

// The | operator is used to perform the bind for better syntax
// Credit: Maybe and Either Monads in Plain C++ 17 (Timothy A.V Teatro et. al.)
template <typename optional_maybe, typename F>
auto operator|(optional_maybe &&m, F &&f) {
    return bind_maybe(std::forward<optional_maybe>(m),
                    std::forward<F>(f));};

// Divide optional monad function which fails when the demoninator is 0
std::optional<double> divide(double num, double denom)
{
    // Note: print added for understanding when running tests. It can be removed if desired
    std::cout << "Running divide function..." << std::endl;
    if (denom == 0.0)
        return std::nullopt;
    else
        return num / denom;
}

// Square root optional monad function which fails when the value to root is negative
std::optional<double> square_root(double num)
{
    // Note: print added for understanding when running tests. It can be removed if desired
    std::cout << "Running square root function..." << std::endl;
    if (num < 0)
        return std::nullopt;
    else
        return sqrt(num);
}

// Double optional monad. No failure. Just performs the double operation
std::optional<double> double_opt(double num)
{
    // Note: print added for understanding when running tests. It can be removed if desired
    std::cout << "Running double function..." << std::endl;
    return num * 2;
}
