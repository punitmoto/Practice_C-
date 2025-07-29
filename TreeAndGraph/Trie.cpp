#include<iostream>

using namespace std;
// With End Flag
#ifdef 0
struct Node {
    Node* links[26];
    bool flag;

    Node():flag(false){
        for (int i = 0; i < 26; i++) {
            links[i] = nullptr;
		}
    }

    bool containsKey(char ch) {
        return links[ch - 'a']!=nullptr;
    }

    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    void setFlag() {
        flag = true;
    }

    bool isEndFlag() {
        return flag;
    }
};

class Trie {
    private:
        Node* root;
    public:
        Trie() {
            root = new Node();
        }

        void insertWord(string word) {
            Node* node = root;
            for(int i = 0; i < word.length(); i++) {
                if(!node->containsKey(word[i])) {                    
                    node->put(word[i], new Node());
                }
                node = node->get(word[i]);
            }
            node->setFlag();
        }

        bool searchWord(string word) {
            Node* node = root;

            for(int i = 0; i < word.length(); i++) {
                if(!node->containsKey(word[i])) {
                    return false;
                }
                node = node->get(word[i]);
            }
            return node->isEndFlag();
        }

        // Returns if there is any word in the
        // trie that starts with the given prefix
        bool startWith(string prefix) {
            Node* node = root;

            for(int i = 0; i < prefix.length(); i++) {
                if(!node->containsKey(prefix[i])) {
                    return false;
                }
                node = node->get(prefix[i]);
            }
            return true;
        }
    };

    int main() {
        Trie* trie = new Trie();
        trie->insertWord("strive");
        trie->insertWord("striver");
        trie->insertWord("striving");
        trie->insertWord("striker");

        cout << "Search if Strawberry exists in trie: " <<(trie->searchWord("strawberry") ? "True" : "False")<< endl;    
        cout << "Search if Strike exists in trie: " <<( trie->searchWord("strike") ? "True" : "False" )<< endl;    
        cout << "If words in Trie start with Stri: " <<(trie->startWith("stri") ? "True" : "False" )<< endl;

        return 0;
    }
#else
    // With end and prefix counter
    struct Node {
    Node* links[26];
    //bool flag;
    int endCounter;
	int prefixCounter;

    Node() :endCounter(0),prefixCounter(0) {
        for (int i = 0; i < 26; i++) {
            links[i] = nullptr;
		}
    }

    bool containsKey(char ch) {
        return links[ch - 'a'] != nullptr;
    }

    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    void increamentEndCounter() {
		endCounter++;   
    }

    void decreamentEndCounter() {
		endCounter--;
    }

    void increamentPrefixCounter() {
		prefixCounter++;
    }

    void decreamentPrefixCounter() {
		prefixCounter--;    
    }
};

class Trie {
private:
    Node* root;
public:
    Trie() {
        root = new Node();
    }

    void insertWord(string word) {
        Node* node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                node->put(word[i], new Node());                
            }
             node = node->get(word[i]);
             node->increamentPrefixCounter();
        }
        node->increamentEndCounter();
    }

    bool searchWord(string word) {
        Node* node = root;

        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                return false;
            }
            node = node->get(word[i]);
        }
        if (node->endCounter > 0)
            return true;
        return false;
     }

    // Returns if there is any word in the
    // trie that starts with the given prefix
    bool startWith(string prefix) {
        Node* node = root;

        for (int i = 0; i < prefix.length(); i++) {
            if (!node->containsKey(prefix[i])) {
                return false;
            }
            node = node->get(prefix[i]);
        }
        return true;
    }

     // Function to count the number
    // of words equal to a given word
    int countWordsEqualTo(string word) {
        Node* node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                return 0;
            }
            node = node->get(word[i]);
        }
        return node->endCounter;
	}

    // Function to count the number of
    // words starting with a given prefix
    int countWordStartingWith(string word) {
        Node* node = root;
        for (int i = 0; i < word.length(); i++) {
            if(!node->containsKey(word[i])) {
                return 0;
            }
            node = node->get(word[i]);  
        }
        return node->prefixCounter;
    }

     // Function to erase a
    // word from the trie
    void erase(string word) {
        Node* node = root;
        for (int i = 0; i < word.length(); i++) {
            if(!node->containsKey(word[i])) {
                return;
            }
            node = node->get(word[i]);
            node->decreamentPrefixCounter();       

        }
        node->decreamentEndCounter();
    }
};

int main() {
    Trie* trie = new Trie();
    trie->insertWord("strive");
    trie->insertWord("striver");
    trie->insertWord("striving");
    trie->insertWord("striker");

    cout << "Search if Strawberry exists in trie: " << (trie->searchWord("strawberry") ? "True" : "False") << endl;
    cout << "Search if Strike exists in trie: " << (trie->searchWord("strike") ? "True" : "False") << endl;
    cout << "If words is Trie start with Stri: " << (trie->startWith("stri") ? "True" : "False") << endl;

    cout << "Count Words Equal to 'strive': ";
    cout << trie->countWordsEqualTo("strive") << endl;
    cout << "Count Words Starting With 'str': ";
    cout << trie->countWordStartingWith("str") << endl;
    cout << "Erasing word 'str' from trie" << endl;
    trie->erase("str");
    cout << "Count Words Equal to 'striv': ";
    cout << trie->countWordsEqualTo("striv") << endl;
    cout << "Count Words Starting With 'striv': ";
    cout << trie->countWordStartingWith("striv") << endl;

    return 0;
}
#endif
