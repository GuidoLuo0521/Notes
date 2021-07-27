#ifndef QFILETEST_H
#define QFILETEST_H

#include <QFileDialog>
#include <QDebug>
#include <QTime>

void OpenFileWithQFile()
{
    QString strPath = QFileDialog::getOpenFileName();
    QFile file(strPath);

    if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        while (!file.atEnd()) {
            qDebug() << file.readLine();
        }

        file.close();
    }
}

void OpenFileWithQTextStream()
{
    QString strPath = QFileDialog::getOpenFileName();
    QFile file(strPath);

    if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        QTextStream stream(&file);

        while (!stream.atEnd()) {
            qDebug() << stream.readLine();
        }

        file.close();
    }
}

void SaveFileWithQDataStream()
{
    QString strPath = QFileDialog::getSaveFileName();
    QFile file(strPath);

   if( file.open(QIODevice::WriteOnly) )
    {
        QDataStream stream(&file);

        QString strName = "Guido";
        QDate date = QDate::currentDate();
        int nAge = 27;
        stream << strName << nAge << date;

        file.flush();
        file.close();
    }
}

void OpenFileWithQDataStream()
{
    QString strPath = QFileDialog::getOpenFileName();
    QFile file(strPath);

    if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        QDataStream stream(&file);

        QString strName;
        QDate date;
        int nAge;
        stream >> strName >> nAge >> date;
        qDebug() << strName << nAge << date;

        file.close();
    }
}

#endif // QFILETEST_H
