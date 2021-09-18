#include <iostream>

template <typename T, typename S>
void UnitCompare(const T &lhs, const S &rhs) {
	if (lhs == rhs) {
		std::cout << "OK] " << lhs << " == " << rhs << std::endl;
	} else {
		std::cerr << "KO] " << lhs << " != " << rhs << std::endl;
	}
}