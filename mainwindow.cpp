#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <sstream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // ── Blue & white theme ──
    this->setStyleSheet(R"(
        QMainWindow {
            background-color: #f4f8fc;
        }
        QTabWidget::pane {
            border: 1px solid #cdddee;
            background: white;
            border-radius: 6px;
        }
        QTabBar::tab {
            background: #e3edf9;
            color: #1a4480;
            padding: 10px 20px;
            margin-right: 2px;
            border-top-left-radius: 6px;
            border-top-right-radius: 6px;
            font-weight: bold;
        }
        QTabBar::tab:selected {
            background: #2563eb;
            color: white;
        }
        QLabel {
            color: #1a3a5c;
            font-size: 13px;
            padding: 2px;
        }
        QLineEdit {
            border: 1px solid #b8d0ea;
            border-radius: 5px;
            padding: 6px;
            background: white;
            font-size: 13px;
        }
        QLineEdit:focus {
            border: 1px solid #2563eb;
        }
        QPushButton {
            background-color: #2563eb;
            color: white;
            border: none;
            border-radius: 5px;
            padding: 8px 16px;
            font-weight: bold;
            font-size: 13px;
        }
        QPushButton:hover {
            background-color: #1d4ed8;
        }
        QPushButton:pressed {
            background-color: #1e40af;
        }
        QTextEdit {
            background-color: #f9fbfd;
            border: 1px solid #cdddee;
            border-radius: 6px;
            padding: 8px;
            font-family: Consolas, monospace;
            font-size: 12px;
            color: #1a3a5c;
        }
    )");

    uni = new University("ENSIA University");
    uni->loadFromFile(dataFile.toStdString());
    log("Welcome to UDRMS!");

    // Connect buttons to slots
    connect(ui->btnAddStudent,     &QPushButton::clicked, this, &MainWindow::onAddStudent);
    connect(ui->btnViewStudents,   &QPushButton::clicked, this, &MainWindow::onViewStudents);
    connect(ui->btnRemoveStudent,  &QPushButton::clicked, this, &MainWindow::onRemoveStudent);

    connect(ui->btnAddDorm,        &QPushButton::clicked, this, &MainWindow::onAddDormitory);
    connect(ui->btnAddRoom,        &QPushButton::clicked, this, &MainWindow::onAddRoom);
    connect(ui->btnAssign,         &QPushButton::clicked, this, &MainWindow::onAssignStudent);
    connect(ui->btnViewUniversity, &QPushButton::clicked, this, &MainWindow::onViewUniversity);

    connect(ui->btnSetMenu,        &QPushButton::clicked, this, &MainWindow::onSetMenu);
    connect(ui->btnViewMenu,       &QPushButton::clicked, this, &MainWindow::onViewMenu);

    connect(ui->btnSave,           &QPushButton::clicked, this, &MainWindow::onSaveData);
    connect(ui->btnLoad,           &QPushButton::clicked, this, &MainWindow::onLoadData);
}

MainWindow::~MainWindow() {
    uni->saveToFile(dataFile.toStdString());
    delete uni;
    delete ui;
}

void MainWindow::log(const QString& text) {
    ui->textOutput->setPlainText(text);
}

// ───── Students ─────
void MainWindow::onAddStudent() {
    int id = ui->lineStuId->text().toInt();
    QString name = ui->lineStuName->text();
    int year = ui->lineStuYear->text().toInt();

    if (id == 0 || name.isEmpty()) {
        log("Please fill in all student fields.");
        return;
    }
    uni->addStudent(id, name.toStdString(), year);
    log("Student added:\n  ID: " + QString::number(id) +
        "\n  Name: " + name + "\n  Year: " + QString::number(year));
}

void MainWindow::onViewStudents() {
    // Capture cout output
    std::ostringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    uni->displayAllStudents();
    std::cout.rdbuf(old);
    QString result = QString::fromStdString(ss.str());
    log(result.isEmpty() ? "No students yet." : result);
}

void MainWindow::onRemoveStudent() {
    int id = ui->lineStuId->text().toInt();
    uni->removeStudent(id);
    log("Removed student ID: " + QString::number(id));
}

// ───── Dormitories ─────
void MainWindow::onAddDormitory() {
    QString name = ui->lineDormName->text();
    if (name.isEmpty()) { log("Enter a dormitory name."); return; }
    uni->addDormitory(Dormitory(name.toStdString()));
    log("Dormitory added: " + name);
}

void MainWindow::onAddRoom() {
    QString dormName = ui->lineRoomDorm->text();
    int roomNum = ui->lineRoomNum->text().toInt();
    int cap = ui->lineRoomCap->text().toInt();

    Dormitory* d = uni->findDormitory(dormName.toStdString());
    if (!d) { log("Dormitory not found: " + dormName); return; }

    d->addRoom(Room(roomNum, cap));
    log("Room " + QString::number(roomNum) + " (capacity " + QString::number(cap) +
        ") added to " + dormName);
}

void MainWindow::onAssignStudent() {
    QString dormName = ui->lineAssignDorm->text();
    int sid = ui->lineAssignSid->text().toInt();
    int roomNum = ui->lineAssignRoom->text().toInt();

    Dormitory* d = uni->findDormitory(dormName.toStdString());
    Student* s = uni->findStudent(sid);

    if (!d || !s) { log("Dormitory or student not found."); return; }

    d->registerStudent(s);
    d->assignStudentToRoom(s, roomNum);
    log("Student " + QString::number(sid) + " assigned to room " +
        QString::number(roomNum) + " in " + dormName);
}

void MainWindow::onViewUniversity() {
    std::ostringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    uni->display();
    std::cout.rdbuf(old);
    log(QString::fromStdString(ss.str()));
}

// ───── Restaurant ─────
void MainWindow::onSetMenu() {
    QString dormName = ui->lineRestDorm->text();
    Dormitory* d = uni->findDormitory(dormName.toStdString());
    if (!d) { log("Dormitory not found: " + dormName); return; }

    d->getRestaurant().setBreakfastMenu(ui->lineBreak->text().toStdString());
    d->getRestaurant().setLunchMenu(ui->lineLunch->text().toStdString());
    d->getRestaurant().setDinnerMenu(ui->lineDinner->text().toStdString());
    log("Menu updated for " + dormName);
}

void MainWindow::onViewMenu() {
    QString dormName = ui->lineRestDorm->text();
    Dormitory* d = uni->findDormitory(dormName.toStdString());
    if (!d) { log("Dormitory not found: " + dormName); return; }

    QString result = "Menu for " + dormName + ":\n";
    result += "  Breakfast: " + QString::fromStdString(d->getRestaurant().getBreakfastMenu()) + "\n";
    result += "  Lunch: "     + QString::fromStdString(d->getRestaurant().getLunchMenu())     + "\n";
    result += "  Dinner: "    + QString::fromStdString(d->getRestaurant().getDinnerMenu());
    log(result);
}

// ───── File ─────
void MainWindow::onSaveData() {
    uni->saveToFile(dataFile.toStdString());
    log("Data saved to " + dataFile);
}

void MainWindow::onLoadData() {
    uni->loadFromFile(dataFile.toStdString());
    log("Data loaded from " + dataFile);
}