#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int BIO_STREAM_CLASSES = 3;
const int MATH_STREAM_CLASSES = 5;
const int STUDENTS_PER_CLASS = 40;

// Function to calculate total marks for a student
int calculateTotalMarks(vector<int>& marks) {
  int totalMarks = 0;
  for (int mark : marks) {
    totalMarks += mark;
  }
  return totalMarks;
}

// Function to calculate school rank for a student
int calculateSchoolRank(vector<int>& totalMarks, int studentIndex) {
  vector<int> sortedTotalMarks = totalMarks;
  sort(sortedTotalMarks.rbegin(), sortedTotalMarks.rend());
  int schoolRank = 0;
  for (int i = 0; i < sortedTotalMarks.size(); i++) {
    if (sortedTotalMarks[i] == totalMarks[studentIndex]) {
      schoolRank = i + 1;
      break;
    }
  }
  return schoolRank;
}

// Function to calculate class rank for a student
int calculateClassRank(vector<int>& totalMarksInClass, int studentIndex) {
  vector<int> sortedTotalMarksInClass = totalMarksInClass;
  sort(sortedTotalMarksInClass.rbegin(), sortedTotalMarksInClass.rend());
  int classRank = 0;
  for (int i = 0; i < sortedTotalMarksInClass.size(); i++) {
    if (sortedTotalMarksInClass[i] == totalMarksInClass[studentIndex]) {
      classRank = i + 1;
      break;
    }
  }
  return classRank;
}

int main() {
  // Read student marks from file
  ifstream marksFile("marks.txt");
  if (!marksFile.is_open()) {
    cerr << "Error opening marks file" << endl;
    return 1;
  }

  int stream, subject, mark;
  vector<vector<vector<int>>> studentMarks(BIO_STREAM_CLASSES + MATH_STREAM_CLASSES, vector<vector<int>>(3));

  for (int i = 0; i < BIO_STREAM_CLASSES + MATH_STREAM_CLASSES; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < STUDENTS_PER_CLASS; k++) {
        marksFile >> stream >> subject >> mark;
        studentMarks[stream - 1][j][k] = mark;
      }
    }
  }
  marksFile.close();

  // Calculate total marks for each student
  vector<vector<int>> totalMarks(BIO_STREAM_CLASSES + MATH_STREAM_CLASSES, vector<int>(STUDENTS_PER_CLASS));

  for (int stream = 0; stream < BIO_STREAM_CLASSES + MATH_STREAM_CLASSES; stream++) {
    for (int classIndex = 0; classIndex < STUDENTS_PER_CLASS; classIndex++) {
      vector<int>& classMarks = studentMarks[stream][0];
      totalMarks[stream][classIndex] = calculateTotalMarks(classMarks);
    }
  }

  // Calculate school rank for each student
  for (int stream = 0; stream < BIO_STREAM_CLASSES + MATH_STREAM_CLASSES; stream++) {
    for (int classIndex = 0; classIndex < STUDENTS_PER_CLASS; classIndex++) {
      totalMarks[stream][classIndex] = calculateSchoolRank(totalMarks, stream * STUDENTS_PER_CLASS + classIndex);
    }
  }

  // Calculate class rank for each student
  for (int stream = 0; stream < BIO_STREAM_CLASSES + MATH_STREAM_CLASSES; stream
