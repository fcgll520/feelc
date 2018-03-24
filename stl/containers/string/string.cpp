#include <string>
#include <stdio.h>
#include <stdint.h>

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

	printf("func operator[]\n");
	for (uint32_t i = 0; i < str.length(); ++i)
	{
		printf("%c", str[i]);
	}
	printf("\n\n");

	printf("func at\n");
	for (uint32_t i = 0; i < str.length(); ++i)
	{
		printf("%c", str.at(i));
	}
	printf("\n\n");


	printf("func size, length, capacity, max_size\n");
	printf("size: %u, length: %u, capacity: %u, max_size: %u\n", str.size(), str.length(),
		str.capacity(), str.max_size());
	printf("\n");

	//扩充或者截取字符串
	printf("func resize 10\n");
	str.resize(10, 'x');
	printf("str: %s, size: %u, capacity: %u\n", str.c_str(), str.size(), str.capacity());
	printf("func resize 3\n");
	str.resize(6);
	printf("str: %s, size: %u, capacity: %u\n\n", str.c_str(), str.size(), str.capacity());

	//增大 capacity
	printf("func reserve 100\n");
	str.reserve(100);
	printf("str: %s, size: %u, capacity: %u\n\n", str.c_str(), str.size(), str.capacity());

	//将 capacity 减少到和length一样大
	printf("func shrink_to_fit\n");
	str.shrink_to_fit();
	printf("str: %s, size: %u, %u, capacity: %u\n\n", str.c_str(), str.size(), str.capacity());

	printf("func back, front\n");
	str.back() = 'F';
	printf("str: %s\n", str.c_str());
	str.front() = 'A';
	printf("str: %s\n\n", str.c_str());

	str = "abcdef";
	printf("func c_str, data\n");
	printf("str: %s, %s\n\n", str.c_str(), str.data());

	printf("func get_allocator\n");
	{
		char *pos = str.get_allocator().allocate(5);
		for (int i = 0; i < 5; ++i)
		{
			str.get_allocator().construct(&pos[i], i+100);
		}
		for (int i = 0; i < 5; ++i)
		{
			printf("%d,", pos[i]);
		}
		printf("\n");
		printf("str: %s\n\n", str.c_str());
		for (int i = 0; i < 5; ++i)
		{
			str.get_allocator().destroy(&pos[i]);
		}
		str.get_allocator().deallocate(pos, 5);
	}

	printf("func copy\n");
	char buffer[20] = { '\0' };
	// 跳过3个字符，从第四个字符开始拷贝10个字节，返回拷贝成功的字节数
	size_t copy_len = str.copy(buffer, 10, 3);
	printf("buffer: %s, copy_len: %u\n\n", buffer, copy_len);

	printf("func find, rfind\n");
	{
		string search_str = "cde";
		size_t pos = str.find(search_str);
		printf("find string(%s), pos: %d, %c, npos: %0x\n", search_str.c_str(), pos, str[pos],
			string::npos);
		// 跳过3个字符
		pos = str.find(search_str, 3);
		printf("find string(%s), pos: %u\n", search_str.c_str(), pos);

		search_str = "def";
		pos = str.rfind(search_str);
		printf("rfind string(%s), pos: %d, %c\n\n", search_str.c_str(), pos, str[pos]);
	}

	printf("func find_first_of, find_last_of\n");
	{
		str = "abcdefabcdefabcdef";
		string search_str = "cde";
		size_t pos = str.find_first_of(search_str);
		printf("find_first_of string(%s), pos: %u, %c\n", search_str.c_str(), pos, str[pos]);

		pos = str.find_last_of(search_str);
		printf("find_last_of string(%s), pos: %u, %c\n\n", search_str.c_str(), pos, str[pos]);
	}

	printf("func find_first_not_of, find_last_not_of\n");
	{
		str = "abcdef-hijk";
		string search_str = "abcdefhijk";
		size_t pos = str.find_first_not_of(search_str);
		printf("find_first_not_of string(%s), pos: %u, %c\n", search_str.c_str(), pos, str[pos]);

		str = "abcdef-+hijk";
		pos = str.find_last_not_of(search_str);
		printf("find_last_not_of string(%s), pos: %u, %c\n\n", search_str.c_str(), pos, str[pos]);
	}

	printf("func substr\n");
	string sub_str = str.substr(1, 5);
	printf("substr %s\n\n", sub_str.c_str());

	printf("func compare\n");
	{
		string str = "abcdef";
		string str1 = "abcdef";
		printf("compare string(%s), %d\n", str1.c_str(), str.compare(str1));
		str1 = "abcde";
		printf("compare string(%s), %d\n", str1.c_str(), str.compare(str1));
		str1 = "abcdeg";
		printf("compare string(%s), %d\n\n", str1.c_str(), str.compare(str1));
	}

	printf("func operator+\n");
	{
		str = "abcdef";
		string add_string = "123";
		str = str + "+" + 'x' + '?' + add_string;
		printf("operator+ %s\n\n", str.c_str());
	}

	printf("func relational operators\n");
	{
		string str1 = "123";
		string str2 = "123";
		printf("operator == %d\n", str1 == str2);
		printf("operator != %d\n", str1 != str2);
		printf("operator >  %d\n", str1 >  str2);
		printf("operator >= %d\n", str1 >= str2);
		printf("operator <  %d\n", str1 <  str2);
		printf("operator <= %d\n", str1 <= str2);
		printf("\n");
	}

	printf("func swap\n");
	{
		string str1 = "123";
		string str2 = "abc";
		printf("swap befor: %s, %s\n", str1.c_str(), str2.c_str());
		swap(str1, str2);
		printf("swap after: %s, %s\n", str1.c_str(), str2.c_str());	
	}
	return 0;
}