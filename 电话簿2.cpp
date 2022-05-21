#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>
#include<unordered_map>
#include<fstream>
typedef long long ll;
using namespace std;
class Phone {
private:
    string name;
    string phoneNum;
    string address;
public:
    Phone() {}
    Phone(string name, string phoneNum, string address) {
        this->name = name;
        this->phoneNum = phoneNum;
        this->address = address;
    }
    void setName(string name) {
        this->name = name;
    }
    void setNum(string phoneNum) {
        this->phoneNum = phoneNum;
    }
    void setAddress(string address) {
        this->address = address;
    }
    string getName() {
        return this->name;
    }
    string getNum() {
        return this->phoneNum;
    }
    string getAddress() {
        return this->address;
    }
    void Print() {
        cout << "������" << this->name << "  �绰��" << this->phoneNum << "  סַ��" << this->address << endl;
    }
    
};
class PhoneBook {
private:
    unordered_multimap<string, Phone> m;
    int real_modify(unordered_multimap<string, Phone>::iterator tmp) {//��map�и�����һ��������޸Ĳ���
        cout << "��ѡ����Ҫ�޸ĵ���Ŀ��" << endl;
        cout << "1.����" << endl;
        cout << "2.�ֻ���" << endl;
        cout << "3.סַ" << endl;
        int opt; cin >> opt;
        while (opt != 1 && opt != 2 && opt != 3) {
            cout << "��������ȷ���!" << endl;
            cin >> opt;
        }
       if (opt == 1) {
           cout << "�������޸ĺ�����" << endl;
           string newName;
           cin >> newName;
           tmp->second.setName(newName);
           //cout << "�޸���ɣ�" << endl;
       }
       if (opt == 2) {
           cout << "�������޸ĺ��ֻ���" << endl;
           string newNum;
           cin >> newNum;
           tmp->second.setNum(newNum);
       }
       if (opt == 3) {
           cout << "�������޸ĺ�סַ" << endl;
           string newAddress;
           cin >> newAddress;
           tmp->second.setAddress(newAddress);
       }
       return 1;
    }
public:
    int add(string name, string phoneNum, string address) {//��map������
        m.insert(make_pair(name, Phone(name, phoneNum, address)));
        return 1;
    }
    int remove(string name) {//ɾ��map��keyֵΪname���ɾ���ɹ�����1�����򷵻�0.
        int n = m.count(name);
        if (n == 1) {
            auto tmp = m.find(name);
            m.erase(name);
            return 1;
        }
        if (n == 0) {
            return 0;
        }
        cout << "������Ҫɾ����Ŀ����ţ�" << endl;
        vector<unordered_multimap<string, Phone>::iterator> v(n);
        int j = 1;
        for (auto i = m.find(name); i->first == name; ++i, ++j) {
            v.push_back(i);
            cout << j << ". ";
            i->second.Print();
        }
        int index;
        string xt; cin >> xt;
        while (xt.length() != 1 || (xt[0] - '0' < 1 || xt[0] - '0' > j)) {
            cout << "������������ȷ���!" << endl;
            cin >> xt;
        }
        index = xt[0] - '0';
        m.erase(v[index - 1]);
        return 1;
    }
    int modify(string name) {//��nameΪkeyֵ��map�в�������ҳɹ�������޸ģ��޸ĳɹ�����1�����򷵻�0
        int n = m.count(name);
        if (n == 1) {
            if (real_modify(m.find(name)))
                return 1;
            else
                return 0;
        }
        if (n == 0) {
            return 0;
        }
        vector<unordered_multimap<string, Phone>::iterator> v(n);
        int j = 1;
        for (auto i = m.find(name); i->first == name; ++i, ++j) {
            v.push_back(i);
            cout << j << ". ";
            i->second.Print();
        }
        int index;
        cout << "������Ҫ�޸���Ŀ����ţ�" << endl;
        string xt; cin >> xt;
        while (xt.length() != 1 || (xt[0] - '0' < 1 || xt[0] - '0' > j)) {
            cout << "������������ȷ���!" << endl;
            cin >> xt;
        }
        index = xt[0] - '0';
        if (real_modify(v[index - 1]))
            return 1;
        else
            return 0;
    }
    int find(string name) {//��nameΪkeyֵ��map�в�������ҳɹ�����1�����򷵻�0
        int n = m.count(name);
        if (n == 1) {
            cout << "���ҽ��Ϊ��" << endl;
            auto tmp = m.find(name);
            tmp->second.Print();
            return 1;
        }
        if (n == 0) {
            return 0;
        }
        cout << "���ҽ��Ϊ��" << endl;
        for (auto i = m.find(name); i->first == name; ++i) {
            i->second.Print();
        }
    }
    int print() {//����绰�������б�����Ϣ
        if (m.empty()) return 0;
        for (auto i = m.begin(); i != m.end(); ++i) {
            i->second.Print();
        }
        return 1;
    }
    void FileWrite() {//���绰����Ϣ�����ı��ļ���
        ofstream file;
        file.open("phonebook.txt", ios::out);
        for (auto i = m.begin(); i != m.end(); ++i) {
            Phone tmp = i->second;
            file << tmp.getName() << " " << tmp.getNum() << " " << tmp.getAddress() << endl;
        }
        file.close();
    }
    void FileRead() {//����绰���ļ��������ļ���Ϣ����map
        ifstream file;
        file.open("phonebook.txt", ios::in);
        m.clear();
        string tmp_name, tmp_num, tmp_address;
        while (file >> tmp_name) {
            file >> tmp_num;
            file >> tmp_address;
            this->add(tmp_name, tmp_num, tmp_address);
        }
    }
};
PhoneBook b = *new PhoneBook();

int PrintScreen() {
    cout << "��ѡ����" << endl;
    cout << "1.����" << endl;
    cout << "2.ɾ��" << endl;
    cout << "3.�޸�" << endl;
    cout << "4.��ѯ" << endl;
    cout << "5.�鿴�绰��" << endl;
    cout << "6.�˳�ϵͳ" << endl;
    string xt; cin >> xt;
    while (xt.length() != 1||(xt[0]-'0'< 1 || xt[0]-'0'>6)) {
        cout << "��������ȷ���!" << endl;
        cin >> xt;
    }
    int opt = xt[0]-'0';
    if (opt == 1) {
        cout << "�������������ֻ����룬סַ:" << endl;
        string x, y, z;
        cin >> x>>y>>z;
        if(b.add(x, y, z)) 
            cout<<"��ӳɹ���"<<endl;
        cout << "����ʹ��������1���˳�ϵͳ������0" << endl;
        int flag; cin >> flag;
        return flag;
    }
    if (opt == 2) {
        cout << "������Ҫɾ��������:" << endl;
        string x; cin >> x;
        if (!b.remove(x))
            cout << "ɾ��ʧ�ܣ�" << endl;
        else 
            cout << "ɾ���ɹ���" << endl;
        cout << "����ʹ��������1���˳�ϵͳ������0" << endl;
        int flag; cin >> flag;
        return flag;
    }
    if (opt == 3) {
        cout << "������Ҫ�޸ĵ�����:" << endl;
        string x; cin >> x;
        if (!b.modify(x)) 
            cout << "�޸�ʧ�ܣ�" << endl;
        else
            cout << "�޸ĳɹ���" << endl;
        cout << "����ʹ��������1���˳�ϵͳ������0" << endl;
        int flag; cin >> flag;
        return flag;
    }
    if (opt == 4) {
        cout << "������Ҫ��ѯ������:" << endl;
        string x; cin >> x;
        if (!b.find(x))
            cout << "��ѯʧ�ܣ�" << endl;
        else
            cout << "��ѯ�ɹ���" << endl;
        cout << "����ʹ��������1���˳�ϵͳ������0" << endl;
        int flag; cin >> flag;
        return flag;
    }
    if (opt == 5) {
        if (b.print() == 0)
            cout << "�绰��Ϊ�գ�" << endl;
        cout << "����ʹ��������1���˳�ϵͳ������0" << endl;
        int flag; cin >> flag;
        return flag;
    }
    if (opt == 6) {
        return 0;
    }
}
int main() {
    b.FileRead();
    while (1) {
        if (!PrintScreen()) {
            b.FileWrite();//�ļ���ϵͳ�˳������һ�θ��±��档
            cout << "�绰����Ϣ�ѱ�����phonebook.txt��" << endl;
            cout << "��ӭ�´�ʹ��" << endl;
            break;
        }
    }
}

