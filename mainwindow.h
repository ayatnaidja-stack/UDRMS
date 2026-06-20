#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include "University.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddStudent();
    void onViewStudents();
    void onRemoveStudent();

    void onAddDormitory();
    void onAddRoom();
    void onAssignStudent();
    void onViewUniversity();

    void onSetMenu();
    void onViewMenu();

    void onSaveData();
    void onLoadData();

private:
    Ui::MainWindow *ui;
    University* uni;
    const QString dataFile = "university_data.txt";

    void log(const QString& text);
};

#endif