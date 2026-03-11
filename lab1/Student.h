#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>

class Class;

enum Degree {
    undergraduate,
    graduate
};

class Student {
    // TODO: implement class Student.
private:

protected:
    std::vector<Class *> classes;
public:
    const std::string id;
    const std::string name;
    const Degree degree;
    std::string toString() const;

    virtual double getGpa() const = 0; // Pure Virtual Function, which means Student is an Abstract Class.
    virtual double getAvgScore() const = 0; // Pure Virtual Function, which means Student is an Abstract Class.
    Student(const std::string &id, const std::string &name, const Degree degree)
        : id(id), name(name), degree(degree) { }
    std::string toString() const;
    void addClass(Class *cl);
};

// TODO: implement class Graduate.
class Graduate : public Student {
    public:
        Graduate(const std::string &id, const std::string &name) : Student(id, name, graduate) {}
        double getGpa() const override ;
        double getAvgScore() const override ;
};

// TODO: implement class Undergraduate.
class Undergraduate : public Student {
    public:
        Undergraduate(const std::string &id, const std::string &name) : Student(id, name, undergraduate) {}
        double getGpa() const override ;
        double getAvgScore() const override ;
};

class StudentWrapper {
private:
    const Student &student;
    double score = -1.0; // Invalid Score
public:
    const std::string id;
    // TODO: fix error
    StudentWrapper(const std::string &id, const Student &student) : id(id), student(student) {}

    void setScore(double score)
    {
        if (score < 0 || score > 100)
            throw "Wrong Score!";
        this->score = score;
    }

    double getScore() const
    {
        return this->score;
    }

    std::string toString() const
    {
        return student.toString();
    }
};

#endif // STUDENT_H_
