#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_sizeEncrypt_editingFinished();

    void on_pushButton_2_clicked();

    void on_sizeDecrypt_editingFinished();

private:
    Ui::MainWindow *ui;
};
std::string encrypt(std::string s, int sizeOfBlocks, std::string key);
std::string decrypt(std::string s, int sizeOfBlocks, std::string key);
int comp1 (const void * a, const void * b);
#endif // MAINWINDOW_H
