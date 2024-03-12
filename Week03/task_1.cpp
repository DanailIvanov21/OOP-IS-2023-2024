#include <iostream>
#include <fstream>
const int MAX = 50;


struct  Student
{
    char name[MAX];
    int facNum;
    char email[MAX];
    size_t passed;
    size_t failed;
    double avgGrade;
};

void writeFile(const Student* students,int count, std::ofstream& out)
{
     out.write((const char*)students, count * sizeof(Student));
    
}
size_t getFileSize(std::ifstream& file)
{
    size_t curr = file.tellg();
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(curr,std::ios::beg);
    return size;
}
void readFile(Student* ptr, size_t& studentsCount, std::ifstream& in)
{
    size_t sizeFile = getFileSize(in);
    studentsCount = sizeFile / sizeof(Student);
    ptr = new Student[studentsCount];
    in.read((char*)ptr, sizeFile);
}

int* faculty(Student* student, std::ifstream& in)
{
    size_t sizeFile = getFileSize(in);
    size_t studentsCount = sizeFile / sizeof(Student);
    student = new Student[studentsCount];
    in.read((char*)student, sizeFile);
    for (int i = 0; i < studentsCount - 1; i++) {

        for (int j = i + 1; j < studentsCount; j++) {
            if (student[j].avgGrade < student[i].avgGrade) {
                std::swap(student[j], student[i]);

            }
        }
        int* arrayOfNumbers =  new int[studentsCount];
        for (size_t i = 0; i < studentsCount; i++)
        {
            arrayOfNumbers[i] = student[i].facNum;
        }

        return arrayOfNumbers;
    }
}

int main()
{
    int count;
    std::cout << "vivedi broi studenti: ";
    std::cin >> count;

    Student* students = new Student[count];

    for (int i = 0; i < count; i++)
    {
        std::cout << "Student name " << i + 1 << "= " << std::endl;
       std::cin >> students[i].name;
      std::cout << " faculty number: " << std::endl;
        std::cin >> students[i].facNum;
        std::cout << "email" << i + 1 << "= " << std::endl;
      
        std::cin >> students[i].email;
        std::cout << "Passed exam:" << std::endl;
     std::cin >> students[i].passed; 
     std::cout << "Failled exam:";
     std::cin >> students[i].failed;
        std::cout << "  Averrage grade:  " <<std::endl;
        std::cin >> students[i].avgGrade;
        
    }
   
    std::ofstream out("students.bin", std::ios::binary);
    if (!out.is_open())
    {
        std::cout << "Error!" << std::endl;
        return -1;
    }
    writeFile(students,count, out);
    out.close();

    std::ifstream in("students.bin", std::ios::binary);
    if (!in.is_open())
    {
        std::cout << "Error!" << std::endl;
        return -1;
    }

    int* arrayOfFacultyNumbers = faculty(students, in);

    for (size_t i = 0; i < count; i++)
    {
        std::cout << arrayOfFacultyNumbers[i] << std::endl;
    }

    in.close();
    delete[] arrayOfFacultyNumbers;
    delete[] students;

}
