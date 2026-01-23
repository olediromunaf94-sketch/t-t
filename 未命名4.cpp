#include <iostream>
#include <iomanip>
#include <string>
class Student {
private:
    int num;
    std::string name;
    int score[4];
    static int stusum;
    static int sumscore[3];
    static int avescore[3];
    static const int credit[3];
public:
    Student() {}
    Student(int num, std::string name) : num(num), name(name) {}
    int getnum() const { return num; }
    std::string getname() const { return name; }
    void inputscore();
    static void getavescore();
    friend void queryscore(const Student& p);
    static void sortscore(Student p[], int len);
};

int Student::stusum = 0;
int Student::sumscore[3] = {0, 0, 0};
int Student::avescore[3] = {0, 0, 0};
const int Student::credit[3] = {5, 3, 3};

void Student::inputscore() {
    std::cout << "请输入" << name << "的数学成绩: ";
    std::cin >> score[0];
    std::cout << "请输入" << name << "的英语成绩: ";
    std::cin >> score[1];
    std::cout << "请输入" << name << "的C++成绩: ";
    std::cin >> score[2];
    int totalCredit = credit[0] + credit[1] + credit[2];
    score[3] = (score[0] * credit[0] + score[1] * credit[1] + score[2] * credit[2]) / totalCredit;
    sumscore[0] += score[0];
    sumscore[1] += score[1];
    sumscore[2] += score[2];
    stusum++;
}

void Student::getavescore() {
    if (stusum > 0) {
        avescore[0] = sumscore[0] / stusum;
        avescore[1] = sumscore[1] / stusum;
        avescore[2] = sumscore[2] / stusum;
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "数学课程平均分: " << avescore[0] << std::endl;
        std::cout << "英语课程平均分: " << avescore[1] << std::endl;
        std::cout << "C++课程平均分: " << avescore[2] << std::endl;
    } else {
        std::cout << "还没有录入学生成绩" << std::endl;
    }
}

void queryscore(const Student& p) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "学号: " << p.num << ", 姓名: " << p.name << std::endl;
    std::cout << "数学成绩: " << p.score[0] << std::endl;
    std::cout << "英语成绩: " << p.score[1] << std::endl;
    std::cout << "C++成绩: " << p.score[2] << std::endl;
    std::cout << "绩点分: " << p.score[3] << std::endl;
}

void Student::sortscore(Student p[], int len) {
    std::cout << "请选择排序的科目(0:数学, 1:英语, 2:C++, 3:绩点分): ";
    int choice;
    std::cin >> choice;
    if (choice < 0 || choice > 3) {
        std::cout << "选择错误" << std::endl;
        return;
    }
    auto cmp = [choice](const Student& a, const Student& b) {
        return a.score[choice] > b.score[choice];
    };
    std::sort(p, p + len, cmp);
    std::cout << "排序后的结果: " << std::endl;
    for (int i = 0; i < len; ++i) {
        std::cout << "学号: " << p[i].num << ", 姓名: " << p[i].name << ", " 
                  << (choice == 3? "绩点分: " : "成绩: ") << p[i].score[choice] << std::endl;
    }
}

int main() {
    Student students[5];
    int choice;
    while (true) {
        cout << "请输入您要执行的操作,菜单如下:" << std::endl;
        std::cout << "0-----结束程序!" << std::endl;
        std::cout << "1-----输入学生成绩" << std::endl;
        std::cout << "2-----按学号查询学生成绩" << std::endl;
        std::cout << "3-----查询所有课程的班级平均分" << std::endl;
        std::cout << "4-----按成绩对学生进行排序" << std::endl;
        std::cin >> choice;
        switch (choice) {
            case 0:
                return 0;
            case 1:
                for (int i = 0; i < 5; ++i) {
                    int num;
                    std::string name;
                    std::cout << "请输入第" << i + 1 << "个学生的学号: ";
                    std::cin >> num;
                    std::cout << "请输入第" << i + 1 << "个学生的姓名: ";
                    std::cin >> name;
                    students[i] = Student(num, name);
                    students[i].inputscore();
                }
                break;
            case 2:
                int queryNum;
                std::cout << "请输入要查询的学号: ";
                std::cin >> queryNum;
                for (int i = 0; i < 5; ++i) {
                    if (students[i].getnum() == queryNum) {
                        queryscore(students[i]);
                        break;
                    }
                }
                break;
            case 3:
                Student::getavescore();
                break;
            case 4:
                Student::sortscore(students, 5);
                break;
            default:
                std::cout << "无效的选择,请重新输入" << std::endl;
        }
    }
    return 0;
}
