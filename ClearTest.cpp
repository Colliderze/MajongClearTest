#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <map>

using namespace std;
//这是一个清一色小游戏

bool isValidCombination(vector<int> hand) //输入一个补一张牌后去掉了一个对子的手牌，长度为12.
{
	sort(hand.begin(), hand.end());
	for (int i = 1; i <= 4; i++) //尝试拆解四次，每次拆解一个刻子或者一个顺子
	{
		bool found = false; //标志变量，表示是否找到刻子或顺子
		for (int j = 0; j < hand.size() - 2; j++) //遍历整个手牌
		{
			int p1, p2;
			for (p1 = j + 1; p1 < hand.size(); p1++)
			{
				for (p2 = p1 + 1; p2 < hand.size(); p2++)
				{
					if (hand[j] == hand[p1] && hand[j] == hand[p2]) //发现一个刻子
					{
						hand.erase(hand.begin() + p2);
						hand.erase(hand.begin() + p1);
						hand.erase(hand.begin() + j);
						found = true;
						break;
					}
					else if (hand[j] == hand[p1] - 1 && hand[j] == hand[p2] - 2) // 发现一个顺子
					{
						hand.erase(hand.begin() + p2);
						hand.erase(hand.begin() + p1);
						hand.erase(hand.begin() + j);
						found = true;
						break;
					}
				}
				if (found) break; //如果找到刻子或顺子，跳出循环
			}
			if (found) break; //如果找到刻子或顺子，跳出循环
		}
		if (!found) return false; //如果在一轮中没有找到刻子或顺子，返回false
	}
	return true; // 成功拆解四次，返回true
}
bool isSevenDouble(vector<int> hand)
{
	sort(hand.begin(), hand.end());
	for (int i = 1; i <= 6; i++)//尝试拆解6次，每次拆解一个对子
	{
		bool found = false;
		for (int j = 0; j < hand.size() - 1; j++)
		{
			if (hand[j] == hand[j + 1])
			{
				hand.erase(hand.begin() + j + 1);
				hand.erase(hand.begin() + j);
				found = true;
			}
			if (found)break;
		}
		if (!found)return false;
	}
	return true;//拆解6次后返回true
}

bool deleteDoubleAndCheck(vector<int> hand)//输入一个补了一张牌的手牌，需要寻找一个对子并消除。长度为14
{
	sort(hand.begin(), hand.end());
	for (int i = 0; i < hand.size() - 1; ++i)
	{
		if (hand[i] == hand[i + 1])//查找对子
		{
			vector<int> remainingHand = hand;
			remainingHand.erase(remainingHand.begin() + i, remainingHand.begin() + i + 2);
			if (isValidCombination(remainingHand) || isSevenDouble(remainingHand))
			{
				return true;
			}
		}
	}
	return false;//如果消除所有的对子都无法成功拆解，则说明不能胡牌。
}
vector<int> getWinningCards(vector<int> hand)//传入一个可能听牌的13张牌组合，查找听牌
{
	map<int, int> originalCount;
	for (int num : hand)//生成一个表来存放每个手牌已经存在数量
	{
		++originalCount[num];
	}
	vector<int> winningCards;
	for (int i = 1; i <= 9; ++i)
	{
		if (originalCount[i] < 4)//这种牌小于4张
		{
			hand.push_back(i);//加入这张牌
			if (deleteDoubleAndCheck(hand))//如果加入这张牌之后胡了，就将这张牌加入听牌列表。
			{
				winningCards.push_back(i);
			}
			hand.pop_back();//删掉这张牌以进行下一次查找听牌
		}
	}
	return winningCards;
}
bool isEqual(vector<int>a, vector<int> b)
{
	if (a.size() != b.size()) {
		return false;
	}
	for (size_t i = 0; i < a.size(); ++i) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}
void spawnAHandToGuess()
{
	vector<int> winningCards;
	vector<int> hand;
	do
	{
		hand.clear();
		winningCards.clear();
		// 创建包含1到9，每个数字各4个的数组
		vector<int> numbers;
		for (int i = 1; i <= 9; ++i) {
			for (int j = 0; j < 4; ++j) {
				numbers.push_back(i);
			}
		}
		random_shuffle(numbers.begin(), numbers.end());
		for (int i = 0; i < 13; i++)
		{
			hand.push_back(numbers[i]);
		}
		sort(hand.begin(), hand.end());//随机打乱这个数组，取前13个得到手牌
		winningCards = getWinningCards(hand);

	} while (winningCards.size()<=3);//若生成的不可听牌，则重复生成。
	cout << "你的手牌是: " << endl;
	for (int i = 0; i < 13; ++i)
	{
		cout << hand[i] << " ";
	}
	vector<int> guessWinningCards;
	int input;
	cout << "输入猜的听牌，输入-1结束：" << endl;
	cin >> input;
	while (input != -1)
	{
		guessWinningCards.push_back(input);
		cin >> input;
	}
	sort(guessWinningCards.begin(), guessWinningCards.end());
	if (isEqual(guessWinningCards, winningCards))
	{
		cout << "猜对了！听牌为：" << endl;
	}
	else
	{
		cout << "猜错了！听牌为：" << endl;
	}
	for (int tile : winningCards) 
	{
		cout << tile << " ";
	}
	cout << endl;

}
void showAndCheck()
{
	int num;
	vector<int> hand;
	cout << "请按顺序输入13张牌的数字" << endl;
	for (int i = 0; i < 13; i++)
	{
		cin >> num;
		hand.push_back(num);
	}
	cout << "你的手牌是: " << endl;
	for (int i = 0; i < 13; ++i)
	{
		cout << hand[i] << " ";
	}
	vector<int> winningCards = getWinningCards(hand);
	if (!winningCards.empty()) {
		cout << "这副牌可以听牌，听: ";
		for (int tile : winningCards)
		{
			cout << tile << " ";
		}
		cout << endl;
	}
	else {
		cout << "这副牌不可以听牌。" << endl;
	}
}
int main()
{
	srand(time(nullptr));
	cout << "----清一色小测试----" << endl;
	cout << "1.自动生成手牌猜听\n2.手动输入手牌查找听牌" << endl;

	int input;
	cin >> input;
	if (input == 1)
	{
		spawnAHandToGuess();
	}
	else if (input == 2)
	{

		showAndCheck();
	}
	return 0;
}
