#include <cstring>
#include <fstream>

using namespace std;

int c;
int n, k;
bool win[1 << 13];

int main()
{
	ifstream fin("carti.in");
	ofstream fout("carti.out");

	fin >> c;
	while (c--)
	{
		fin >> n >> k;
		memset(win, 0, sizeof(win));

		for (int i = 0; i < (1 << 13); ++i)
			if (win[i] == false)
				for (int j = 1; j <= k; ++j)
				{
					int mask = 0;
					for (int l = 0; l < j; ++l) mask |= (1 << l);
					for (int l = 0; l <= 13 - j; ++l)
						if ((i & (mask << l)) == 0)
							win[i | (mask << l)] = true;
				}

		int init_mask = 0;
		char ch[2];
		for (int i = 1; i <= n; ++i)
		{
			fin >> ch;

			if (ch[0] == '1' && ch[1] == '0')
				ch[0] = 'X';
			switch (ch[0])
			{
				case 'A':
					init_mask |= 1;
					break;
				case 'J':
					init_mask |= (1 << 10);
					break;
				case 'Q':
					init_mask |= (1 << 11);
					break;
				case 'K':
					init_mask |= (1 << 12);
					break;
				case 'X':
					init_mask |= (1 << 9);
					break;
				default:
					init_mask |= (1 << (ch[0] - '0' - 1));
			}
		}
		if (win[init_mask] == true)
			fout << "Alice" << '\n';
		else
			fout << "Bob" << '\n';
	}

	fin.close();
	fout.close();
}
