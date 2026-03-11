#include "Student.h"
#include <string>
#include <sstream>
#include "Class.h"

std::string Student::toString() const
{
    // TODO: uncomment the following code after implementing class Student.

    std::ostringstream oss;
    oss << "Student Information:"
        << "\n\tid: " << id
        << "\n\tname: " << name
        << "\n\tenrollment year: " << year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << std::endl;
    return oss.str();

    return "";
}

// TODO: implement functions which are declared in Student.h.
void Student::addClass(Class *cl)
{
    // TODO implement addClass.
    classes.push_back(cl);
}

double Graduate::getGpa() const
{
    // TODO implement getGpa for Graduate.
    double totalPoints = 0.0;
    int totalCredits = 0;
    for (auto cl : classes) {
        StudentWrapper &sw = cl -> getStudentWrapper(id);
        int score = sw.getScore();
        
        if (score < 0) continue; // Skip if score is invalid
        switch (score / 10) {
            case 10:
            case 9:
                totalPoints += 4.0 * cl -> point;
                break;
            case 8:
                totalPoints += 3.0 * cl -> point;
                break;
            case 7:
                totalPoints += 2.0 * cl -> point;
                break;
            case 6:
                totalPoints += 1.0 * cl -> point;
                break;
            default:
                break; // No points for scores below 60
        }

        totalCredits += cl -> point;  //way to calculate total credits: sum of points of all classes taken by the student.
    }

    return totalPoints / totalCredits; //way to calculate GPA: total points divided by total credits.
}

double Graduate::getAvgScore() const 
{
    // TODO implement getAvgScore for Graduate.
    int totalScore = 0;
    int count = 0;
    for(Class* cl : classes) {
        StudentWrapper &sw = cl -> getStudentWrapper(id);
        int score = sw.getScore();
        if (score >= 0) { // Only consider valid scores
            totalScore += score;
            count++;
        }
    }
    //way to calculate average score: total score divided by number of classes with valid scores.
    return count > 0 ? static_cast<double>(totalScore) / count : 0.0; 
}

double Undergraduate::getGpa() const
{
    // TODO implement getGpa for Undergraduate.
    double totalPoints = 0.0;
    int totalCredits = 0;
    for (Class* cl : classes) {
        StudentWrapper &sw = cl -> getStudentWrapper(id);
        double score = sw.getScore();

        if (score < 0) continue; // Skip if score is invalid
        double gpaPoints = score / 20;
        totalPoints += gpaPoints * cl -> point; //way to calculate total points: sum of (GPA points multiplied by class points) for
        totalCredits += cl -> point; //way to calculate total credits: sum of points of all classes taken by the student.
    }
    return totalCredits > 0 ? totalPoints / totalCredits : 0.0; //way to calculate GPA: total points divided by total credits.
}

double Undergraduate::getAvgScore() const
{
    // TODO implement getAvgScore for Undergraduate.
    int totalScore = 0;
    int count = 0;
    for(Class* cl : classes) {
        StudentWrapper &sw = cl -> getStudentWrapper(id);
        int score = sw.getScore();
        if (score >= 0) { // Only consider valid scores
            totalScore += score;
            count++;
        }
    }
    //way to calculate average score: total score divided by number of classes with valid scores.
    return count > 0 ? static_cast<double>(totalScore) / count : 0.0; 
}