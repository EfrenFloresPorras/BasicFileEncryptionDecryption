#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    progressBar = new QProgressBar(this);
    progressBar->setVisible(false);
    statusBar()->addWidget(progressBar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_encryptionButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select File"), "", tr("All Files (*.*)"));

    if (!filePath.isEmpty()) {
        encryptFile(filePath);
    }
}

void MainWindow::on_decryptionButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Encrypted File"), "", tr("All Files (*.*)"));

    if (!filePath.isEmpty()) {
        decryptFile(filePath);
    }
}

void MainWindow::displayFileBytes(const QByteArray& fileData)
{
    qDebug() << "Last 16 File Bytes:";
    int startIndex = qMax(0, fileData.size() - 16);
    for (int i = startIndex; i < fileData.size(); ++i) {
        qDebug().noquote() << QString("%1").arg(static_cast<quint8>(fileData[i]), 2, 16, QLatin1Char('0'));
    }
}

void MainWindow::encryptFile(const QString &filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray fileData = file.readAll();
        file.close();

        displayFileBytes(fileData); // Displays bytes before encryption.

        QString encryptedFilePath = filePath + ".encrypted";
        QFile encryptedFile(encryptedFilePath);
        if (encryptedFile.open(QIODevice::WriteOnly)) {
            progressBar->setVisible(true);
            progressBar->setValue(0);
            progressBar->setRange(0, fileData.size());

            for (int i = 0; i < fileData.size(); i++) {
                char encryptedByte = fileData[i] + 1; // incrementing each byte by 1
                encryptedFile.write(&encryptedByte, sizeof(encryptedByte));
                progressBar->setValue(i);
            }

            progressBar->setVisible(false);
            encryptedFile.close();
            QMessageBox::information(this, tr("Encryption"), tr("File encrypted succesfully!"));
        } else {
            QMessageBox::critical(this, tr("Encryption"), tr("Failed to write encrypted file."));
        }
    } else {
        QMessageBox::critical(this, tr("Encryption"), tr("Failed to open file for reading."));

    }
}

void MainWindow::decryptFile(const QString& filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray fileData = file.readAll();
        file.close();

        displayFileBytes(fileData); // Displays bytes before decryption.

        QString decryptedFilePath = filePath.left(filePath.lastIndexOf(".encrypted"));
        QFile decryptedFile(decryptedFilePath);
        if (decryptedFile.open(QIODevice::WriteOnly)) {
            progressBar->setVisible(true);
            progressBar->setValue(0);
            progressBar->setRange(0,fileData.size());

            for (int i = 0; i < fileData.size(); i ++) {
                char decryptedByte = fileData[i] - 1; // decrementing each byte by 1
                decryptedFile.write(&decryptedByte, sizeof(decryptedByte));
                progressBar->setValue(i);
            }

            progressBar->setVisible(false);
            decryptedFile.close();
            QMessageBox::information(this, tr("Decryption"), tr("File decrypted succesfully!"));
        } else {
            QMessageBox::critical(this, tr("Decryption"), tr("Failed to write decrypted file"));
        }
    } else {
        QMessageBox::critical(this, tr("Decryption"), tr("Failed to open file for reading"));
    }
}
