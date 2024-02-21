#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <iomanip>

// Какой-то хуевый код

std::map<char, std::string> huffmanCode(std::multimap<int, std::string> stringTable);
std::string makehuffmancode(const std::string &);
std::string makehammingcode(std::string &);
std::string decodehammingcode(std::string &);

// Ты кто
// Два мертвых пидораса это, вот кто

int main()
{
    std::string strin;
    std::getline(std::cin, strin);
    auto new_strin = makehuffmancode(strin);
    auto hammingED = makehammingcode(new_strin);
    // auto fixed = decodehammingcode(hammingED_2);
    std::cout << std::endl
              << strin << " : " << new_strin << std::endl;
    std::cout << "( WORD = 16 BIT / 21 SYMBOL ) Hamming: " << hammingED << std::endl;
    // std::cout << "( WORD = 16 BIT / 21 SYMBOL ) Hamming: " << hammingED_2 << std::endl; Декодер всё ещё ломаный, чёртово разбиение на слова
    return 0;
}

// Готово, уверен, что работает

std::map<char, std::string> huffmanCode(std::multimap<int, std::string> stringTable)
{
    std::map<char, std::string> table;
    std::pair<int, std::string> least; // Шизоидальная пара, потрачено десять минут, чтобы понять, почему она не инсертится

    while (stringTable.size() != 1)
    {
        std::string code = stringTable.begin()->second;
        int freq = stringTable.begin()->first;
        stringTable.erase(stringTable.begin());
        std::string code2 = stringTable.begin()->second;
        int freq2 = stringTable.begin()->first;
        stringTable.erase(stringTable.begin());

        // два самым редко встречающихся элемента вместе, частотность складываем

        least = std::make_pair(freq + freq2, code + code2);

        for (auto it : code)
        {
            auto elem = table.find(it);

            if (elem != table.end())
                elem->second += "1";
            else
                table.insert(std::make_pair(it, "1"));
        }

        for (auto it : code2)
        {
            auto elem = table.find(it);

            if (elem != table.end())
                elem->second += "0";
            else
                table.insert(std::make_pair(it, "0"));
        }

        // Одна пара
        stringTable.insert(least);
    }
    std::cout << std::setw(24) << "HUFFMAN TABLE" << std::endl;
    for (auto it : table)
        std::cout << "| " << std::setw(4) << it.first << " | " << std::setw(21) << std::right << it.second << " | " << std::endl;
    return table;
}

std::string makehuffmancode(const std::string &strin)
{
    std::string _encoded = "";
    std::multimap<int, std::string> stringTable;
    std::multimap<std::string, int> reverseTable;

    for (auto it : strin)
    {
        auto elem = reverseTable.find(std::string{it});
        if (elem == reverseTable.end())
        {
            reverseTable.insert(std::make_pair(std::string{it}, 1));
        }
        else
        {
            reverseTable.insert(std::make_pair(std::string{it}, elem->second + 1));
            reverseTable.erase(elem);
        }
    }

    for (auto it : reverseTable)
    {
        stringTable.insert(std::make_pair(it.second, it.first));
    }

    // до сюда работотает нормально точно

    auto huffmanTable = huffmanCode(stringTable);

    for (auto it : strin)
    {
        _encoded += huffmanTable.find(it)->second;
    }

    return _encoded;
}

std::string makehammingcode(std::string &str)
{
    std::vector<std::pair<std::string, int>> words;
    std::vector<std::string> readywords;
    std::string tmpstr;

    int ctr1, ctr2, ctr4, ctr8, ctr16 = 0; // я ебанутый, бегите))))00)

    int j = 0;

    for (int i = 0; i < str.length(); i++)
    {
        tmpstr += str[i];
        j++;
        if (i % 16 == 15)
        {
            tmpstr.insert(0, "0");
            tmpstr.insert(1, "0");
            tmpstr.insert(3, "0");
            tmpstr.insert(7, "0");
            tmpstr.insert(15, "0");
            words.push_back(std::make_pair(tmpstr, 21));
            tmpstr = "";
            j = 0;
        }
    }
    if (!tmpstr.empty())
    {
        tmpstr.insert(0, "0");
        if (tmpstr.length() > 1)
            tmpstr.insert(1, "0");
        if (tmpstr.length() > 4)
            tmpstr.insert(3, "0");
        if (tmpstr.length() > 8)
            tmpstr.insert(7, "0");
        if (tmpstr.length() > 16)
            tmpstr.insert(15, "0");
        words.push_back(std::make_pair(tmpstr, j));
    }

    for (auto it : words)
    {
        for (int i = 0; i < it.first.length(); i += 2)
            if (it.first[i] == '1')
                ctr1++;

        for (int i = 0; i < it.first.length(); i += 2)
            for (int i = 0; i < it.first.length(); i += 4)
                for (int j = 0; j < 2; j++)
                    if (it.first[i + j] == '1')
                        ctr2++;

        if (it.first.length() >= 4)
            for (int i = 0; i < it.first.length(); i += 8)
                for (int j = 0; j < 4; j++)
                    if (it.first[i + j] == '1')
                        ctr4++;

        if (it.first.length() >= 8)
            for (int i = 2; i < it.first.length(); i += 16)
                for (int j = 0; j < 8; j++)
                    if (it.first[i + j] == '1')
                        ctr8++;

        if (it.first.length() >= 15)
            for (int i = 16; i < it.first.length(); i += 32)
                for (int j = 0; j < 16; j++)
                    if (it.first[i + j] == '1')
                        ctr16++;

        it.first[0] = ctr1 % 2 == 1 ? '1' : '0';
        it.first[1] = ctr2 % 2 == 1 ? '1' : '0';
        it.first[3] = ctr4 % 2 == 1 ? '1' : '0';
        it.first[7] = ctr8 % 2 == 1 ? '1' : '0';
        it.first[15] = ctr16 % 2 == 1 ? '1' : '0';

        readywords.push_back(it.first);
    }

    tmpstr = "";
    std::cout << std::setw(24) << "HAMMING WORDS" << std::endl;
    for (auto it : readywords)
    {
        std::cout << "| WORD | " << std::setw(21) << std::left << it << " |" << std::endl;
        tmpstr += it;
    }

    return tmpstr;
}

// Готово, правда, не уверен, что работает правильно

std::string decodehammingcode(std::string &str)
{
    std::vector<std::string> corrupted;
}
