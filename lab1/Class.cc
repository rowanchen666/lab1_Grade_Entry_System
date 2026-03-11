#include "Class.h"
#include <string>
#include <vector>
#include "Student.h"
#include <sstream>
#include <fstream>
#include <iostream>

std::string Class::toString() const {
    std::ostringstream oss;
    oss << "Class Information:"
        << "\n\tname: " << name
        << "\n\tpoint: " << point
        << std::endl;
    return oss.str();
}

void Class::addStudent(const Student& st) {
    StudentWrapper sw(st.id, st);
    students.push_back(sw);
}

StudentWrapper& Class::getStudentWrapper(const std::string& studentId) {
    for (std::vector<StudentWrapper>::iterator it = students.begin();
            it != students.end();
            ++ it) {
        if (it->id == studentId)
            return *it;
    }
    throw "No Match Student!";
}

double Class::getHighestScore() {
    // TODO implement getHighestScore
    double highest = -1.0; // Invalid Score
    for (std::vector<StudentWrapper>::iterator it = students.begin() ; 
        it != students.end(); ++it) {
        if (it->getScore() > highest)
            highest = it->getScore();
    }
    return highest;
}

double Class::getLowestScore() {
    // TODO implement getLowestScore
    double lowest = 101.0; // Invalid Score
    for (std::vector<StudentWrapper>::iterator it = students.begin(); it != students.end(); ++it) {
        if (it->getScore() < lowest)
            lowest = it->getScore();
    }
    return lowest;
}

double Class::getAvgScore() {
    // TODO implement getAvgScore
    double totalScore = 0.0;
    int count = 0;
    for (std::vector<StudentWrapper>::iterator it = students.begin(); it != students.end(); ++it) {
        if (it->getScore() >= 0) { // Only consider valid scores
            totalScore += it->getScore();
            count++;
        }
    }    
    if (count > 0)
        return totalScore / count;
    return 0.0;
}

void Class::saveScore(const std::string& filename) {
    // TODO implement saveScore
    std::ofstream outFile(filename, std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Error: Cannot open " << filename << " for writing" << std::endl;
        return;
    }
    
    // Always output the class name
    outFile << name << std::endl;
    
    // Output valid scores only
    for (std::vector<StudentWrapper>::iterator it = students.begin();
         it != students.end();
         ++it) {
        double score = it->getScore();
        if (score >= 0) {
            outFile << it->id << "," << static_cast<int>(score) << std::endl;
        }
    }
    
    outFile.close();
}
