
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student {

private:
    int id;
    string name;
    int age;
    float gpa;

public:
    Student(int id, string name, int age, float gpa) {
        this->id = id;
        this->name = name;
        this->age = age;
        this->gpa = gpa;
    }
    int getID() const { return id; }
    string getName() { return name; }
    int getAge() { return age; }
    float getGPA() { return gpa; }

    void setName(string name) { this->name = name; }
    void setAge(int age) { this->age = age; }
    void setGPA(float gpa) { this->gpa = gpa; }

    bool operator==(const Student &s) { return this->getID() == s.getID(); }
    bool operator<(const Student &s) { return this->getID() < s.getID(); }

    static int linearSearch(vector<Student> students, Student key);
    static int binarySearch(vector<Student> students, Student key);

    static int selectionSort(vector<Student> &students);
    static int insertionSort(vector<Student> &students);
    static int mergeSort(vector<Student> &students);
};

int Student::linearSearch(vector<Student> students, Student key) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i] == key)
            return i;
    }
    return -1;
}

int binarySearchHelper(vector<Student> students, Student key, int start, int end) {

    if (start > end)
        return -1;
    if (start == end) {
        if (students[start] == key) {
            return start;
        } else {
            return -1;
        }
    }
    int mid = (start + end) / 2;
    if (students[mid] == key)
        return mid;
    if (students[mid] < key)
        return binarySearchHelper(students, key, mid + 1, end);
    return binarySearchHelper(students, key, start, mid - 1);
}

int Student::binarySearch(vector<Student> students, Student key) {
    return binarySearchHelper(students, key, 0, students.size() - 1);
}

int Student::selectionSort(vector<Student> &students) {

    int comparisons = 0;
    for (int i = 0; i < students.size() - 1; i++) {
        int minPosition = i;
        for (int j = i + 1; j < students.size(); j++) {
            comparisons++;
            if (students[j] < students[minPosition]) {
                minPosition = j;
            }
        }
        Student temp = students[i];
        students[i] = students[minPosition];
        students[minPosition] = temp;
    }
    return comparisons;
}

int Student::insertionSort(vector<Student> &students) {

    int comparisons = 0;
    for (int i=1; i<students.size(); i++) {

        int j = i;
        // while ((j > 0) &&                                                                        ) {
        //     comparisons++;
        //     Student temp = students[j];
        //     students[j] = students[j-1];
        //     students[j-1] = temp;
        //     j--;
        // }
    }
    return comparisons;

}

void merge(vector<Student> left, vector<Student> right, vector<Student> &result) {

    int leftIndex = 0;
    int rightIndex =0;
    int resultIndex = 0;
 
    while ((leftIndex < left.size()) && (rightIndex < right.size())) {
        if (left[leftIndex] < right[rightIndex]) {
            // Move next from left to result
            result[resultIndex] = left[leftIndex];
            leftIndex++;
            resultIndex++;
        } else {
            // Move next from left to result
            result[resultIndex] = right[rightIndex];
            rightIndex++;
            resultIndex++;

        }
    }
    while (leftIndex < left.size()) {
        result[resultIndex] = left[leftIndex];
        leftIndex++;
        resultIndex++;
    }
    while (rightIndex < right.size()) {
        result[resultIndex] = right[rightIndex];
        rightIndex++;
        resultIndex++;
    }


}

int Student::mergeSort(vector<Student> &students) {

    int comparisons=0;
    if (students.size() <= 1) return 0;
    int middlePosition = students.size() / 2;
    vector<Student> leftHalf;
    for(int i=0; i<middlePosition; i++) {
        leftHalf.push_back(students[i]);
    }
    vector<Student> rightHalf;
    for (int i = middlePosition; i < students.size(); i++) {
        rightHalf.push_back(students[i]);
    }
    mergeSort(leftHalf);
    mergeSort(rightHalf);
    merge(leftHalf, rightHalf, students);
    return comparisons;
}

int main() {

    Student s1(1, "Ana", 19, 4.0);
    Student s2(2, "José", 20, 3.8);
    Student s3(3, "Juan", 18, 3.1);
    Student s4(4, "María", 21, 3.9);
    Student s5(5, "Carmen", 19, 3.2);

    vector<Student> allStudents{s1, s2, s3, s4, s5};
    vector<Student> maleStudents{s2, s3};
    vector<Student> femaleStudents{s1, s4, s5};
    vector<Student> allReversed{s5, s4, s3, s2, s1};

    Student key(4, "María", 21, 3.9);

    cout << "Position for Maria among all: " << Student::linearSearch(allStudents, key) << endl;
    cout << "Position for Maria among males: " << Student::linearSearch(maleStudents, key) << endl;

    cout << "Position for Maria among all: " << Student::binarySearch(allStudents, key) << endl;
    cout << "Position for Maria among males: " << Student::binarySearch(maleStudents, key) << endl;

    //cout << "Total comparisons for insertionSort on allReversed: " << Student::insertionSort(allReversed);
    cout << "Total comparisons for mergeSort on allReversed: " << Student::mergeSort(allReversed);

    exit(0);
}