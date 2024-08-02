#pragma once

#ifndef LOGGERWINDOW_H
#define LOGGERWINDOW_H

#include <QDialog>
#include <QTimer>
#include <sstream>
#include "logger.h"

namespace Ui {
class LoggerWindow;
}

class LoggerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoggerWindow(QWidget *parent = nullptr);
    ~LoggerWindow();

private slots:

    void on_submitBtn_clicked();
    void UpdateLogs();

private:
    QTimer* timer;
    Ui::LoggerWindow *ui;
};

#endif // LOGGERWINDOW_H
