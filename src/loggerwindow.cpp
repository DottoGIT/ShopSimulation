#include "loggerwindow.h"
#include "ui_loggerwindow.h"

LoggerWindow::LoggerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoggerWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(UpdateLogs()));
    timer->start(100);

    Logger::SetPriority(LogPriority::DebugPriority);
}

LoggerWindow::~LoggerWindow()
{
    delete timer;
    delete ui;
}

void LoggerWindow::on_submitBtn_clicked()
{
    unsigned short logPriorityNum = ui->prioOption->currentIndex();
    switch(logPriorityNum)
    {
    case 0: Logger::SetPriority(LogPriority::DebugPriority); break;
    case 1: Logger::SetPriority(LogPriority::InfoPriority); break;
    case 2: Logger::SetPriority(LogPriority::WarningPriority); break;
    case 3: Logger::SetPriority(LogPriority::ErrorPriority); break;
    }
}

void LoggerWindow::UpdateLogs()
{
    ui->logsList->clear();
    for(const auto& log : Logger::GetLogs())
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(QString::fromStdString(log.GetContent()));
        ui->logsList->addItem(item);
    }
}

