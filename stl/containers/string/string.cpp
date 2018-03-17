#include <string>
#include <stdio.h>

using std::string;

int main(int argc, char const *argv[])
{
	string str = "abcdef";

	printf("func begin, end\n");
	for (string::iterator it = str.begin(); it != str.end(); ++it)
	{
		printf("%c ", *it);
	}
	printf("\n\n");

	printf("func rbegin, rend\n");
	for (string::reverse_iterator it = str.rbegin(); it != str.rend(); ++it)
	{
		printf("%c ", *it);
	}
	printf("\n\n");

	printf("func cbegin, cend\n");
	for (string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		printf("%c ", *it);
	}
	printf("\n\n");

	printf("func crbegin, crend\n");
	for (string::const_reverse_iterator it = str.crbegin(); it != str.crend(); ++it)
	{		
		printf("%c", *it);
	}
	printf("\n\n");

	printf("func size, length, capacity, max_size\n");
	printf("size: %u, length: %u, capacity: %u, max_size: %u\n", str.size(), str.length(),
		str.capacity(), str.max_size());
	printf("\n");

	printf("func resize 10\n");
	str.resize(10, 'x');
	printf("str: %s, size: %u, capacity: %u\n", str.c_str(), str.size(), str.capacity());
	printf("func resize 3\n");
	str.resize(3);
	printf("str: %s, size: %u, capacity: %u\n", str.c_str(), str.size(), str.capacity());
	

	return 0;
}