#include <iostream>
#include <fstream>

const size_t BIGGEST_GRADE = 6;
const size_t SMALLEST_GRADE = 2;

struct student{
    std::string name;
    size_t grade;
    
    student() = default;
    student(const std::string& name,size_t grade) : name(name),grade(grade){}
    friend std::ostream& operator<<(std::ostream& os,const student& obj){
        os<<obj.name<<" "<<obj.grade<<std::endl;
        return os;
    }
};


void counting_sort(std::vector<student>& students){
    std::vector<size_t> counting(BIGGEST_GRADE - SMALLEST_GRADE + 1,0);
    //counting
    for(int i = 0;i<students.size();i++)
        counting[students[i].grade - 2]++;
    //accumulating
    for(int i = 1;i<students.size();i++)
        counting[i] += counting[i - 1];
    
    std::vector<student> temp(students.size());
    for(int i = temp.size() - 1;i>=0;i--){
        student curr_student = students[i];
        auto index = --counting[curr_student.grade - 2];
        temp[index] = curr_student;
    }
    
    std::swap(students,temp);
}

int main(int argc, const char * argv[]) {
    student st1("ivan",2);
    student st2("icaka",6);
    student st3("mishaka",2);
    student st4("jozko",6);
    student st5("chica",3);
    
    std::vector<student> students = {st1,st2,st3,st4,st5};
    counting_sort(students);
    for(const auto& student : students)
        std::cout<<student;
}
