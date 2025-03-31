#include <fstream>

int main()
{
	std::ofstream out("xd.txt");

	for (int i = 0; i < 4997; ++i)
	{
		out << "1 ";
	}
	out << "1 " << "14 " << "27\n";

	return 0;
}