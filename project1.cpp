#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// from textbook display 8.8 - converts string to all lowercase
string makeLower(const string& s)
{
    string temp(s);
    for (int i = 0; i < s.length(); i++)
        temp[i] = tolower(s[i]);
    return temp;
}

// from textbook display 8.8 - removes punctutation characters from a string
string removePunct(const string& s, const string& punct)
{
    string noPunct;
    int sLength = s.length();
    int punctLength = punct.length();

    for (int i = 0; i < sLength; i++)
    {
        string aChar = s.substr(i,1);
        int location = punct.find(aChar, 0);
        if (location < 0 || location >= punctLength)
            noPunct = noPunct + aChar;
    }
    return noPunct;
}

//FUNCTION 1: read words from file, clean them up
void getWords(vector<string> &words, ifstream &file)
{
    string punct(",;:.?!'\" ");
    string word;

    while(file >> word)
    {
        word = makeLower(word);
        word = removePunct(word, punct);

        if (!word.empty())
            words.push_back(word);
    }
}

//FUNCTION 2: sort words alphabetically
void sortWords(vector<string> &words)
{
    sort(words.begin(), words.end());
}

//FUNCTION 3: count how many times each word appears
vector<pair<string, int>> getWordCount(vector<string> &words)
{
    vector<pair<string, int >> wordCounts;

    for (int i = 0; i < words.size(); i++)
    {
        if (i == 0 || words[i] != words[i-1])
        {
            wordCounts.push_back(make_pair(words[i], 1));
        }
        else
        {
            wordCounts.back().second++;
        }
    }

    return wordCounts;
}

int main()
{
    //open the file
    ifstream file("homes.txt");
    if (!file.is_open())
    {
        cout << "Error: Could not open homes.txt"<<endl;
        return 1;
    }
    //get words from file
    vector<string> words;
    getWords(words,file);
    file.close();

    //sort the words
    sortWords(words);

    //get word counts
    vector<pair<string, int >> wordCounts = getWordCount(words);


    //print results
    cout << "Word Frequencies in homes.txt" << endl;
    cout << "-----------------------------" << endl;
    for (int i = 0; i < wordCounts.size(); i++)
    {
        cout << wordCounts[i].first << ": " << wordCounts[i].second << endl;
    }

    return 0;

}
