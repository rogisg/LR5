#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <numeric>

using namespace std;

struct Student {
    string Name;
    string GroupId;
    vector<unsigned> Ratings;
    vector<string> Subjects;
};

struct Group {
    string Id;
    vector<Student> Students;
};

void SortByName(vector<Student>& students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.Name < b.Name;
    });
}

void SortByRating(vector<Student>& students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        double avgA, avgB;

        if (a.Ratings.empty()) {
            avgA = 0.0;
        } else {
            avgA = accumulate(a.Ratings.begin(), a.Ratings.end(), 0.0) / a.Ratings.size();
        }

        if (b.Ratings.empty()) {
            avgB = 0.0;
        } else {
            avgB = accumulate(b.Ratings.begin(), b.Ratings.end(), 0.0) / b.Ratings.size();
        }

        return avgA > avgB;
    });
}


size_t CountTwoness(const vector<Student>& students) {
    return count_if(students.begin(), students.end(), [](const Student& student) {
        return any_of(student.Ratings.begin(), student.Ratings.end(), [](unsigned rating) {
            return rating == 2;
        });
    });
}

size_t CountExcellent(const vector<Student>& students) {
    return count_if(students.begin(), students.end(), [](const Student& student) {
        return all_of(student.Ratings.begin(), student.Ratings.end(), [](unsigned rating) {
            return rating == 5;
        });
    });
}

vector<Student> VectorMathExcellent(const vector<Student>& students) {
    vector<Student> result;
    for (const auto& student : students) {
        auto it = find(student.Subjects.begin(), student.Subjects.end(), "Matan");
        if (it != student.Subjects.end()) {
            size_t index = distance(student.Subjects.begin(), it);
            if (index < student.Ratings.size() && student.Ratings[index] == 5) {
                result.push_back(student);
            }
        }
    }
    return result;
}

vector<string> GroupsId(const vector<Student>& students) {
    unordered_set<string> uniqueGroups;
    for (const auto& student : students) {
        uniqueGroups.insert(student.GroupId);
    }
    return vector<string>(uniqueGroups.begin(), uniqueGroups.end());
}

vector<Group> Groups(const vector<Student>& students) {
    map<string, Group> groupsMap;
    for (const auto& student : students) {
        groupsMap[student.GroupId].Id = student.GroupId;
        groupsMap[student.GroupId].Students.push_back(student);
    }
    vector<Group> groups;
    for (const auto& entry : groupsMap) {
        groups.push_back(entry.second);
    }
    return groups;
}

int main() {
    vector<Student> students = {
        {"Egor", "ИУ8-14", {5, 4, 3}, {"Matan", "Angem", "Teorinf"}},
        {"Vlad", "ИУ8-14", {2, 5, 4}, {"Matan", "Angem", "Teorinf"}},
        {"Igor", "ИУ8-14", {5, 5, 5}, {"Matan", "Angem", "Teorinf"}},
        {"Ivan", "ИУ8-15", {3, 2, 4}, {"Matan", "Angem", "Teorinf"}},
        {"Vova", "ИУ8-14", {5, 3, 5}, {"Matan", "Angem", "Teorinf"}}
    };

    SortByName(students);
    cout << "Сортировка по имени:"<<endl;
    for (const auto& student : students) {
        cout << student.Name << endl;
    }

    SortByRating(students);
    cout << "Сортировка по рейтингу:"<<endl;
    for (const auto& student : students) {
        cout << student.Name <<  endl;
    }

    size_t countTwos = CountTwoness(students);
    cout << "Eсть 2 хотя бы по одному предмету:" << countTwos << endl;

    size_t countExcellent = CountExcellent(students);
    cout << "Сдали все экзамены на 5: " << countExcellent << endl;

    auto mathExcellentStudents = VectorMathExcellent(students);
    cout << "Студенты с '5' по матану:"<<endl;
    for (const auto& student : mathExcellentStudents) {
        cout << student.Name << endl;
    }

    auto groupIds = GroupsId(students);
    cout << "Все существующие группы:"<<endl;
    for (const auto& id : groupIds) {
        cout << id << endl;
    }

    auto groups = Groups(students);
    cout << "Список групп:"<<endl;
    for (const auto& group : groups) {
        cout << group.Id << endl;
        for (const auto& student : group.Students) {
            cout << student.Name << endl;
        }
    }

    return 0;
}
