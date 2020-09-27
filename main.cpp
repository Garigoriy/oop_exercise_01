#include<iostream>
#include<bitset>
#include<fstream>
#include<string>

using namespace std;

class BitString {
private:
    unsigned long long old;
    unsigned int jun;
public:
    BitString(){};
    BitString(unsigned long long lhs, unsigned int rhs) : old(lhs), jun(rhs) {}
    unsigned long long Getold(){return old;}
    unsigned int Getjun() {return jun;}
    friend int Countbin(const BitString);
    friend bool Inclusion(const BitString lhs, const BitString rhs);
    friend BitString Compare(const string data);

    friend BitString operator^(const BitString lhs, const BitString rhs);
    friend BitString operator&(const BitString lhs, const BitString rhs);
    friend BitString operator|(const BitString lhs, const BitString rhs);
    friend BitString operator~(const BitString tmp);
    friend BitString operator<<(const BitString tmp, int shift);
    friend BitString operator>>(const BitString tmp, int shift);
    friend bool operator>(const BitString lhs, const BitString rhs);
    friend bool operator<(const BitString lhs, const BitString rhs);
};

BitString operator ^(const BitString lhs, const BitString rhs) {
    return BitString(lhs.old^rhs.old, lhs.jun^rhs.jun);
}

BitString operator &(const BitString lhs, const BitString rhs) {
    return BitString(lhs.old&rhs.old, lhs.jun&rhs.jun);
}

BitString operator |(const BitString lhs, const BitString rhs) {
    return BitString(lhs.old|rhs.old, lhs.jun|rhs.jun);
}

BitString operator ~(const BitString tmp) {
    return BitString(~tmp.old, ~tmp.jun);
}

BitString operator<<(const BitString tmp, int shift){
    BitString a = tmp;
    for (int i = 0; i < shift; ++i) {
        a.old = a.old<<1;
        if ((a.jun >> 31)&1) a.old=a.old|1;
        a.jun = a.jun<<1;
    }
    return BitString(a.old, a.jun);
}

BitString operator>>(const BitString tmp, int shift){
    BitString a = tmp;
    for (int i = 0; i < shift; ++i) {
        a.jun = a.jun>>1;
        if (a.old&1) a.jun = a.jun|((a.jun|1) << 31);
        a.old = a.old>>1;
    }
    return BitString(a.old, a.jun);
}

int Countbin(const BitString tmp) {
    BitString a = tmp;
    int res = 0;
    while (a.old || a.jun) {
        if (a.old&1) ++res;
        if (a.jun&1) ++res;
        a.old = a.old >> 1;
        a.jun = a.jun >> 1;
    }
    return res;
}

bool operator>(const BitString lhs, const BitString rhs){
    return Countbin(lhs)>Countbin(rhs);
}

bool operator<(const BitString lhs, const BitString rhs){
    return Countbin(lhs)<Countbin(rhs);
}

bool Inclusion(const BitString lhs, const BitString rhs){
    BitString a = rhs;
    for (int i = 0; i < 95; ++i) {
        if (((lhs.old&a.old)||(a.old == lhs.old))&&((lhs.jun&a.jun)||(a.jun == lhs.jun))) return true;
        a = a >> 1;
    }
    return false;
}

BitString Compare(const string data){
    unsigned long long lhs = 0, l = 0;
    unsigned int rhs = 0, r = 0;
    int j = 0;
    for (int i = 63; i >=0; --i) {
        if (data[j] == '1') {
            lhs = lhs | ((l|1)<<i);
        }
        ++j;
    }
    for (int i = 31; i >=0; --i) {
        if (data[j] == '1') {
            rhs = rhs | ((r|1)<<i);
        }
        ++j;
    }
    return BitString(lhs, rhs);
}

void Interface() {
    cout << "Select an option:" << '\n';
    cout << "1.Add string" << '\n';
    cout << "2.Show all strings" << '\n';
    cout << "3.Operation XOR" << '\n';
    cout << "4.Operation AND" << '\n';
    cout << "5.Operation OR" << '\n';
    cout << "6.Operation NOT" << '\n';
    cout << "7.Bit Shift Left" << '\n';
    cout << "8.Bit Shift Right" << '\n';
    cout << "9.Count 1 in string" << '\n';
    cout << "10.Compare strings" << '\n';
    cout << "11.Inclusion of string " << '\n';
    cout << "12.Exit" << '\n' << '\n';
}

int main() {
    BitString arr[255];
    int arg, j = 0;
    bool flag = false;
    while (true) {
        Interface();
        unsigned long long left;
        unsigned int right;
        int lhs, rhs, cache, cnt;
        BitString tmp;
        string line;
        char simv;
        cin >> arg;
        cout << '\n';
        switch (arg) {
        case 1:
            cout << "Add string with 1)keyboard or 2)file?" << '\n';
            cin >> cache;
            if (cache == 2) {
                cout << "Enter file name" << '\n';
                cin >> line;
                ifstream in(line);
                while (getline(in, line)) {
                    arr[j] = Compare(line);
                    ++j;
                }
            } else {
                cin >> line;
                arr[j] = Compare(line);
                ++j;
                cout << "Added successful!" << '\n';
            }
            break;
        case 2:
            cout << "Available strings:" << '\n';
            for (int i = 0; i < j; ++i) {
                cout << i+1 << ')' << bitset<sizeof(arr[i].Getold()) * CHAR_BIT>(arr[i].Getold()) << bitset<sizeof(arr[i].Getjun()) * CHAR_BIT>(arr[i].Getjun()) << '\n';

            }
            cout << '\n';
            break;
        case 3:
            cout << "Enter 2 strings numbers to XOR" << '\n';
            cin >> lhs >> rhs;
            --lhs; --rhs;
            tmp = arr[lhs]^arr[rhs];
            cout << "Result:" << '\n';
            cout << bitset<sizeof(tmp.Getold()) * CHAR_BIT>(tmp.Getold()) << bitset<sizeof(tmp.Getjun()) * CHAR_BIT>(tmp.Getjun()) << '\n';
            break;
        case 4:
            cout << "Enter 2 strings numbers to AND" << '\n';
            cin >> lhs >> rhs;
            --lhs; --rhs;
            tmp = arr[lhs]&arr[rhs];
            cout << "Result:" << '\n';
            cout << bitset<sizeof(tmp.Getold()) * CHAR_BIT>(tmp.Getold()) << bitset<sizeof(tmp.Getjun()) * CHAR_BIT>(tmp.Getjun()) << '\n';
            break;
        case 5:
            cout << "Enter 2 strings numbers to OR" << '\n';
            cin >> lhs >> rhs;
            --lhs; --rhs;
            tmp = arr[lhs]|arr[rhs];
            cout << "Result:" << '\n';
            cout << bitset<sizeof(tmp.Getold()) * CHAR_BIT>(tmp.Getold()) << bitset<sizeof(tmp.Getjun()) * CHAR_BIT>(tmp.Getjun()) << '\n';
            break;
        case 6:
            cout << "Enter string number to NOT" << '\n';
            cin >> cache;
            --cache;
            tmp = ~arr[cache];
            cout << "Result:" << '\n';
            cout << bitset<sizeof(tmp.Getold()) * CHAR_BIT>(tmp.Getold()) << bitset<sizeof(tmp.Getjun()) * CHAR_BIT>(tmp.Getjun()) << '\n';
            break;
        case 7:
            cout << "Enter string number to leftShift and number of shifts" << '\n';
            cin >> cache >> cnt;
            --cache;
            tmp = arr[cache] << cnt;
            cout << bitset<sizeof(tmp.Getold()) * CHAR_BIT>(tmp.Getold()) << bitset<sizeof(tmp.Getjun()) * CHAR_BIT>(tmp.Getjun()) << '\n';
            break;
        case 8:
            cout << "Enter string number to rightShift and number of shifts" << '\n';
            cin >> cache >> cnt;
            --cache;
            tmp = arr[cache] >> cnt;
            cout << bitset<sizeof(tmp.Getold()) * CHAR_BIT>(tmp.Getold()) << bitset<sizeof(tmp.Getjun()) * CHAR_BIT>(tmp.Getjun()) << '\n';
            break;
        case 9:
            cout << "Enter string number to count 1 in it" << '\n';
            cin >> cache;
            --cache;
            cout << "Result:" << Countbin(arr[cache]) << '\n';
            break;
        case 10:
            cout << "Enter 1st string number, operation, 2nd string number" << '\n';
            cin >> lhs >> simv >> rhs;
            --lhs; --rhs;
            if (simv == '>') {
                if (arr[lhs]>arr[rhs]) cout << "True" << '\n'; else cout << "False" << '\n';
            } else
            if (simv == '<') {
                if (arr[lhs]<arr[rhs]) cout << "True" << '\n'; else cout << "False" << '\n';
            } else {
                cout << "Error!" << '\n';
                break;
            }
            break;
        case 11:
            cout << "Enter 1st string number that includes in 2nd string number" << '\n';
            cin >> lhs >> rhs;
            if (Inclusion(arr[lhs], arr[rhs])) cout << "True" << '\n'; else cout << "False" << '\n';
            break;
        case 12:
            flag = true;
            break;
        }
        if (flag) break;
    }
    return 0;
}
