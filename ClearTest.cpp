#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <map>

using namespace std;
//����һ����һɫС��Ϸ

bool isValidCombination(vector<int> hand) //����һ����һ���ƺ�ȥ����һ�����ӵ����ƣ�����Ϊ12.
{
	sort(hand.begin(), hand.end());
	for (int i = 1; i <= 4; i++) //���Բ���ĴΣ�ÿ�β��һ�����ӻ���һ��˳��
	{
		bool found = false; //��־��������ʾ�Ƿ��ҵ����ӻ�˳��
		for (int j = 0; j < hand.size() - 2; j++) //������������
		{
			int p1, p2;
			for (p1 = j + 1; p1 < hand.size(); p1++)
			{
				for (p2 = p1 + 1; p2 < hand.size(); p2++)
				{
					if (hand[j] == hand[p1] && hand[j] == hand[p2]) //����һ������
					{
						hand.erase(hand.begin() + p2);
						hand.erase(hand.begin() + p1);
						hand.erase(hand.begin() + j);
						found = true;
						break;
					}
					else if (hand[j] == hand[p1] - 1 && hand[j] == hand[p2] - 2) // ����һ��˳��
					{
						hand.erase(hand.begin() + p2);
						hand.erase(hand.begin() + p1);
						hand.erase(hand.begin() + j);
						found = true;
						break;
					}
				}
				if (found) break; //����ҵ����ӻ�˳�ӣ�����ѭ��
			}
			if (found) break; //����ҵ����ӻ�˳�ӣ�����ѭ��
		}
		if (!found) return false; //�����һ����û���ҵ����ӻ�˳�ӣ�����false
	}
	return true; // �ɹ�����ĴΣ�����true
}
bool isSevenDouble(vector<int> hand)
{
	sort(hand.begin(), hand.end());
	for (int i = 1; i <= 6; i++)//���Բ��6�Σ�ÿ�β��һ������
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
	return true;//���6�κ󷵻�true
}

bool deleteDoubleAndCheck(vector<int> hand)//����һ������һ���Ƶ����ƣ���ҪѰ��һ�����Ӳ�����������Ϊ14
{
	sort(hand.begin(), hand.end());
	for (int i = 0; i < hand.size() - 1; ++i)
	{
		if (hand[i] == hand[i + 1])//���Ҷ���
		{
			vector<int> remainingHand = hand;
			remainingHand.erase(remainingHand.begin() + i, remainingHand.begin() + i + 2);
			if (isValidCombination(remainingHand) || isSevenDouble(remainingHand))
			{
				return true;
			}
		}
	}
	return false;//����������еĶ��Ӷ��޷��ɹ���⣬��˵�����ܺ��ơ�
}
vector<int> getWinningCards(vector<int> hand)//����һ���������Ƶ�13������ϣ���������
{
	map<int, int> originalCount;
	for (int num : hand)//����һ���������ÿ�������Ѿ���������
	{
		++originalCount[num];
	}
	vector<int> winningCards;
	for (int i = 1; i <= 9; ++i)
	{
		if (originalCount[i] < 4)//������С��4��
		{
			hand.push_back(i);//����������
			if (deleteDoubleAndCheck(hand))//�������������֮����ˣ��ͽ������Ƽ��������б�
			{
				winningCards.push_back(i);
			}
			hand.pop_back();//ɾ���������Խ�����һ�β�������
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
		// ��������1��9��ÿ�����ָ�4��������
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
		sort(hand.begin(), hand.end());//�������������飬ȡǰ13���õ�����
		winningCards = getWinningCards(hand);

	} while (winningCards.size()<=3);//�����ɵĲ������ƣ����ظ����ɡ�
	cout << "���������: " << endl;
	for (int i = 0; i < 13; ++i)
	{
		cout << hand[i] << " ";
	}
	vector<int> guessWinningCards;
	int input;
	cout << "����µ����ƣ�����-1������" << endl;
	cin >> input;
	while (input != -1)
	{
		guessWinningCards.push_back(input);
		cin >> input;
	}
	sort(guessWinningCards.begin(), guessWinningCards.end());
	if (isEqual(guessWinningCards, winningCards))
	{
		cout << "�¶��ˣ�����Ϊ��" << endl;
	}
	else
	{
		cout << "�´��ˣ�����Ϊ��" << endl;
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
	cout << "�밴˳������13���Ƶ�����" << endl;
	for (int i = 0; i < 13; i++)
	{
		cin >> num;
		hand.push_back(num);
	}
	cout << "���������: " << endl;
	for (int i = 0; i < 13; ++i)
	{
		cout << hand[i] << " ";
	}
	vector<int> winningCards = getWinningCards(hand);
	if (!winningCards.empty()) {
		cout << "�⸱�ƿ������ƣ���: ";
		for (int tile : winningCards)
		{
			cout << tile << " ";
		}
		cout << endl;
	}
	else {
		cout << "�⸱�Ʋ��������ơ�" << endl;
	}
}
int main()
{
	srand(time(nullptr));
	cout << "----��һɫС����----" << endl;
	cout << "1.�Զ��������Ʋ���\n2.�ֶ��������Ʋ�������" << endl;

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
