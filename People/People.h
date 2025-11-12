#include <string>
using namespace std;

class People {
private:
    string ID;
    string ten;
    string key;        
public:
    People();
    void nhapTen();
    void taoID();
    void taoKey();
    void luuKey();
    // chế độ đoán
    void nhapTenDoan();
    bool doanKey(const string& keyToGuess);
    // lấy key để người khác đoán
    string getKey() const;
};


