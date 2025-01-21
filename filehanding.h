
#ifndef FILEHANDING_H
#define FILEHANDING_H
#include "student.h"
#include "book.h"
#include "staff.h"
#include "student.h"
#include "borrowedbook.h"

extern FILE* studentFile;


void openStudentFileForReadingWriting();
void closeStudentFile();
void loadStudentsFromFile();
void addStudentToFile();
void deleteStudentInFile(int studentId);
void updateStudentInFile();
long findStudentPosition();
void save_student_to_file();

void loadBooksFromFile();
void writeBookstoFile();
void addBooksToFile();
void deleteBooksInFile();
long findBooksPosition();
void updateBooksInFile(int book_id, const char* new_title, const char* new_author, int new_total_copies);
void save_Book_To_File();

void loadStaffFromfile();
void writeStaffToFile();
void addStaffToFile();
void deleteStaffInFile(int staffId);
long findStaffPosition();
void updateStaffInFile();
void saveStaffToFile(void);

void loadBorrowedBooksFromFile(void);
void saveBorrowedBooksToFile(void);

void saveReturnedBooksToFile(void);
void loadReturnedBooksFromFile(void);

#endif // FILEHANDING_H
