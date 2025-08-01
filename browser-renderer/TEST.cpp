#include "headers.h"

#include "shared_function.h"

//int test()
//{
//
//	renderer::SharedDataFunction<int> sharedFunc;
//	sharedFunc.add_function([](std::shared_ptr<int> state) {
//		*state += 10;
//		std::cout << "State updated to: " << *state << std::endl;
//		});
//
//	sharedFunc.add_function([](std::shared_ptr<int> state) {
//		*state += 100;
//		std::cout << "State updated to: " << *state << std::endl;
//		});
//	// Call all functions in the shared data function
//	sharedFunc.call_all();
//	return 0;
//}
//
//int main()
//{
//	test();
//	return 0;
//}