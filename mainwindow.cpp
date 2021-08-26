#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    try {
        std::string s;
        if (ui->textEncrypt->displayText().isEmpty())
            throw std::invalid_argument("Введите текст");
        s = ui->textEncrypt->text().toStdString();
        int size = s.length();
        int sizeOfBlocks;
        sizeOfBlocks = ui->sizeEncrypt->text().toInt();
        std::string key;
        int blocks = size % sizeOfBlocks == 0 ? size / sizeOfBlocks : size / sizeOfBlocks + 1;
        key = ui->keyEncrypt->text().toStdString();
        int keySize = key.length();
        if (keySize != blocks)
            throw std::invalid_argument("Введите корректный ключ");
        bool checkArr[keySize];
        for (int i = 0; i < keySize; ++i)
            checkArr[i] = 0;
        for (int i = 0; i < keySize; ++i)
            checkArr[key[i] -'0' - 1] = 1;
        for (int i = 0; i < keySize; ++i)
            if(!checkArr[i])
                throw std::invalid_argument("Введите корректный ключ");
        std::string encryptedString = encrypt(s, sizeOfBlocks, key);
        ui->resultEncrypt->setText(QString::fromStdString(encryptedString));
    } catch (std::invalid_argument const & e) {
        QString s = e.what();
        QMessageBox::critical(this, "Ошибка", s);
        return;
    }
}

std::string encrypt(std::string s, int sizeOfBlocks, std::string key){
    int size = s.length();
    int keySize = key.length();
    std::string sArray[keySize];
    for (int i = 0; i < size; ++i)
        sArray[i / sizeOfBlocks] += s[i];
    int keyArr[keySize];
    for (int i = 0; i < keySize; ++i)
        keyArr[i] = key[i] - '0' - 1;
    std::string sout;
    for (int i = 0; i < keySize; ++i)
        sout += sArray[keyArr[i]];
    return sout;
}

void MainWindow::on_sizeEncrypt_editingFinished()
{
    std::string s;
    s = ui->textEncrypt->text().toStdString();
    int size = s.length();
    int sizeOfBlocks;
    sizeOfBlocks = ui->sizeEncrypt->text().toInt();
    int blocks = size % sizeOfBlocks == 0 ? size / sizeOfBlocks : size / sizeOfBlocks + 1;
    ui->keyLabelEncrypt->setText("Введите ключ размером " + QString::fromStdString(std::to_string(blocks)) + ":");
}

void MainWindow::on_pushButton_2_clicked()
{
    try {
        std::string s;
        if (ui->textDecrypt->displayText().isEmpty())
            throw std::invalid_argument("Введите текст");
        s = ui->textDecrypt->text().toStdString();
        int size = s.length();
        int sizeOfBlocks;
        sizeOfBlocks = ui->sizeDecrypt->text().toInt();
        std::string key;
        int blocks = size % sizeOfBlocks == 0 ? size / sizeOfBlocks : size / sizeOfBlocks + 1;
        key = ui->keyDecrypt->text().toStdString();
        int keySize = key.length();
        if (keySize != blocks)
            throw std::invalid_argument("Введите корректный ключ");
        bool checkArr[keySize];
        for (int i = 0; i < keySize; ++i)
            checkArr[i] = 0;
        for (int i = 0; i < keySize; ++i)
            checkArr[key[i] -'0' - 1] = 1;
        for (int i = 0; i < keySize; ++i)
            if(!checkArr[i])
                throw std::invalid_argument("Введите корректный ключ");
        std::string decryptedString = decrypt(s, sizeOfBlocks, key);
        ui->resultDecrypt->setText(QString::fromStdString(decryptedString));
    } catch (std::invalid_argument const & e) {
        QString s = e.what();
        QMessageBox::critical(this, "Ошибка", s);
        return;
    }
}

std::string decrypt(std::string s, int sizeOfBlocks, std::string key){
    int size = s.length();
    int keySize = key.length();
    int empty = keySize - size % keySize;
    if (empty == keySize)
        empty = 0;
    int keyArr[keySize];
    for (int i = 0; i < keySize; ++i){
        keyArr[i] = key[i] - '0' - 1;
        if (keyArr[i] == keySize - 1)
            s.insert(sizeOfBlocks * i + sizeOfBlocks - empty, empty, ' ');
    }
    std::string sArr[keySize];
    for (int i = 0; i < size + empty; ++i)
        sArr[i / sizeOfBlocks] += s[i];
    std::string sout;
    for (int i = 0; i < keySize; ++i)
        for (int j = 0; j < keySize; ++j)
            if (i == keyArr[j])
                sout += sArr[j];
    return sout;
}

void MainWindow::on_sizeDecrypt_editingFinished()
{
    std::string s;
    s = ui->textDecrypt->text().toStdString();
    int size = s.length();
    int sizeOfBlocks;
    sizeOfBlocks = ui->sizeDecrypt->text().toInt();
    int blocks = size % sizeOfBlocks == 0 ? size / sizeOfBlocks : size / sizeOfBlocks + 1;
    ui->keyLabelDecrypt->setText("Введите ключ размером " + QString::fromStdString(std::to_string(blocks)) + ":");
}

int comp1 (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}
