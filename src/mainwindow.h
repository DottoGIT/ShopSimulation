#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include "shop.h"
#include "logger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Shop* shop_, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Eventy QT
    void on_Wyloguj_clicked();
    void on_Dodaj_clicked();
    void on_ChangePhoto_clicked();
    void on_logOutButton_clicked();
    void on_logBtn_clicked();
    void on_goToRegistrationBtn_clicked();
    void on_retToLogButton_clicked();
    void on_registerButton_clicked();

    // Nasze funckje
    void ChangeView_Admin();
    void ChangeView_Login();
    void ChangeView_User();
    void ChangeView_Registration();
    void ChangeView_OrderFinalization();
    void UpdateAdminWindow();
    void UpdateOrdersAdmin();
    void UpdateProductsUser(const SearchFilter& searchFilter);
    void UpdateProductsUser();
    void UpdateOrdersUser();
    void ClearLogFields();
    void ClearRegistrationFields();
    void ClearFinalizationFields();
    void UpdateCartUser();
    unsigned CalculateBaseCartPrice();

    void on_filterButton_clicked();

    void on_addProductButton_clicked();

    void on_deleteFromCartButton_clicked();

    void on_changeQuantityButton_clicked();

    void on_orderButton_clicked();

    void on_retFromOrderPushButton_clicked();

    void on_promoCodePushButton_clicked();

    void on_orderConfirmPushButton_clicked();

    void on_selectedOrderInfoPushButton_clicked();

    void on_Potwierdz_clicked();

private:
    Shop* shop;
    Ui::MainWindow *ui;

    // Zmienne pomocnicze
    QString adminProductImgPath = "../Sklep/Images/placeholder.png";
};
#endif // MAINWINDOW_H
