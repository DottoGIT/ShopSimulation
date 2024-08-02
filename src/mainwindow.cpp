#include <QMessageBox>
#include <QFileDialog>
#include <QtUiTools/QUiLoader>
#include <QWidget>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "codenotfoundexception.h"


enum StackedWidgetPages
{
    login = 0,
    admin = 1,
    user = 2,
    registration = 3,
    order_finalization = 4
};

MainWindow::MainWindow(Shop* shop_, QWidget *parent)
    : QMainWindow(parent), shop(shop_), ui(new Ui::MainWindow)
{
    Logger::Info("<mainwindow.h> Uruchomiono aplikacje okienkowa");
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/////////////////////////////// CHANGE VIEW FUNCTIONS ///////////////////////////////

void MainWindow::ChangeView_Admin()
{
    UpdateAdminWindow();
    ui->stackedWidget->setCurrentIndex(StackedWidgetPages::admin);
}

void MainWindow::ChangeView_Login()
{
    ui->stackedWidget->setCurrentIndex(StackedWidgetPages::login);
}

void MainWindow::ChangeView_User()
{
    UpdateProductsUser();
    UpdateOrdersUser();
    ui->stackedWidget->setCurrentIndex(StackedWidgetPages::user);
}

void MainWindow::ChangeView_Registration()
{
    ui->stackedWidget->setCurrentIndex((StackedWidgetPages::registration));
}

void MainWindow::ChangeView_OrderFinalization()
{
    ui->stackedWidget->setCurrentIndex((StackedWidgetPages::order_finalization));
}
/////////////////////////////// ADMIN WINDOW FUNCTIONS ///////////////////////////////

void MainWindow::UpdateAdminWindow()
{
    ui->ListaProduktow->clear();
    // Wyświetl Produkty
    auto products = shop->GetProductManager()->GetProductsList();
    for(const auto& product : products)
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setIcon(QIcon(QString::fromStdString(product.GetImgPath())));
        item->setText(QString::fromStdString(std::string(product)));
        ui->ListaProduktow->addItem(item);
    }
    UpdateOrdersAdmin();
}

void MainWindow::UpdateOrdersAdmin()
{
    ui->adminOrdersListWidget->clear();
    for (auto& order: shop->GetOrderManager()->GetOrdersVector())
    {
        QListWidgetItem *item = new QListWidgetItem;
        std::stringstream ss;
        ss << "Zamowienie nr: " << std::to_string(order.GetId()) << " status: " << order.GetStatusStr();
        item->setText(QString::fromStdString(ss.str()));
        item->setData(Qt::UserRole, QVariant(static_cast<quint32>(order.GetId())));
        ui->adminOrdersListWidget->addItem(item);
    }
}

void MainWindow::on_Wyloguj_clicked()
{
    shop->GetClientManager()->LogOut();
    ChangeView_Login();
}

void MainWindow::on_Dodaj_clicked()
{
    // Pobierz dane z widoku dodawania produktu
    std::string productName = ui->In_Nazwa->text().toStdString();
    unsigned int productZl = static_cast<unsigned int>(ui->In_Cena->value());
    unsigned int productGr = static_cast<unsigned int>(ui->In_Cena->value()*100)%100;

    std::vector<ProductTags> tags;
    if(ui->checkBox->isChecked())
        tags.push_back(ProductTags::meble);
    if(ui->checkBox_2->isChecked())
        tags.push_back(ProductTags::rozrywka);
    if(ui->checkBox_3->isChecked())
        tags.push_back(ProductTags::sport);
    if(ui->checkBox_4->isChecked())
        tags.push_back(ProductTags::uroda);
    if(ui->checkBox_5->isChecked())
        tags.push_back(ProductTags::zywnosc);

    // Sprawdz czy dane wprowadzone sa poprawnie
    if(tags.empty())
    {
        QMessageBox::information(this, "Informacja", "Produkt musi posiadac przynajmniej jeden tag");
        return;
    }

    if(productName.empty())
    {
        QMessageBox::information(this, "Informacja", "Produkt nie moze miec pustej nazwy");
        return;
    }

    // Dodaj produkt do bazy
    Product product(productName, productZl, productGr, tags, adminProductImgPath.toStdString());
    shop->GetProductManager()->AddProduct(product);

    // Zresetuj widok dodawania produktu
    ui->In_Nazwa->setText("");
    ui->In_Cena->setValue(0.25);
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
    ui->checkBox_5->setChecked(false);
    adminProductImgPath = "../Sklep/Images/placeholder.png";
    ui->Zdjecie->setPixmap(QPixmap(adminProductImgPath));

    // Dodaj produkt do listy QT
    UpdateAdminWindow();
}

void MainWindow::on_ChangePhoto_clicked()
{
    QString pixPath = QFileDialog::getOpenFileName(this, "Wybierz zdjęcie", "../Sklep/Images");
    ui->Zdjecie->setPixmap(QPixmap(pixPath));
    adminProductImgPath = pixPath;
}

void MainWindow::on_Potwierdz_clicked()
{
    unsigned short orderNum = ui->orderNum->value();
    unsigned short statusNum = ui->orderStatusOption->currentIndex();
    Status orderStatus = Status::oczekujeNaPlatnosc;
    switch(statusNum)
    {
    case 0: orderStatus = Status::oczekujeNaPlatnosc; break;
    case 1: orderStatus = Status::wRealizacji; break;
    case 2: orderStatus = Status::wTrakcieDostawy; break;
    case 3: orderStatus = Status::zrealizowano; break;
    case 4: orderStatus = Status::zwrot; break;
    case 5: orderStatus = Status::anulowano; break;
    }
    try
    {
        Order& order = shop->GetOrderManager()->FindOrderById(orderNum);
        order.SetStatus(orderStatus);
        UpdateOrdersAdmin();
        shop->GetSerializer()->StoreOrdersInFile();
    }
    catch(OrderNotFoundException& e)
    {
        QMessageBox::information(this, "Informacja", "Wprowadzono błędne id zamówienia");
    }
}

/////////////////////////////// LOGIN WINDOW FUNCTIONS ///////////////////////////////

void MainWindow::ClearLogFields()
{
    ui->logLineEdit->clear();
    ui->pswrdLineEdit->clear();
}


void MainWindow::on_logBtn_clicked()
{
    std::string enteredLogin {(ui->logLineEdit->text()).toStdString()};
    std::string enteredPassword {(ui->pswrdLineEdit->text()).toStdString()};

    shop->GetClientManager()->LogClient(enteredLogin, enteredPassword);
    std::string currentUsername (shop->GetClientManager()->GetCurClient().GetLogin());
    if (currentUsername == "admin"){
        ChangeView_Admin();
        ClearLogFields();
    }else if (currentUsername == enteredLogin){
        ui->usrnameLabel->setText(QString::fromStdString(currentUsername));
        ChangeView_User();
        ClearLogFields();
    }else{
        QMessageBox::information(this, "Informacja", "Wprowadzono błędne dane logowania");  // w tym przypadku nie chce czyscic pol wprowadzania
    }
}

void MainWindow::on_goToRegistrationBtn_clicked()
{
    ChangeView_Registration();
    ClearLogFields();
}

/////////////////////////////// REGISTRATION WINDOW FUNCTIONS ///////////////////////////////

void MainWindow::on_retToLogButton_clicked()
{
    ChangeView_Login();
}


void MainWindow::on_registerButton_clicked()
{
    shop->GetClientManager()->AddClient(Client((ui->logEnterLineEdit->text()).toStdString(),
                                             (ui->passwordEnterLineEdit->text()).toStdString(),
                                             (ui->nameEnterLineEdit->text()).toStdString(),
                                               (ui->surnameEnterLineEdit->text()).toStdString()));
    shop->GetSerializer()->SaveClients();
    QMessageBox::information(this, "Informacja", "Użytkownik został utworzony");
}

void MainWindow::ClearRegistrationFields()
{
    ui->logEnterLineEdit->clear();
    ui->passwordEnterLineEdit->clear();
    ui->nameEnterLineEdit->clear();
    ui->surnameEnterLineEdit->clear();
}

/////////////////////////////// ORDER FINALIZATION WINDOW FUNCTIONS ///////////////////////////////

void MainWindow::on_orderConfirmPushButton_clicked()
{
    Address adres = Address(ui->cityEnterLineEdit->text().toStdString(),
                            ui->postalCodeEnterLineEdit->text().toStdString(),
                            ui->streetEnterLineEdit->text().toStdString());

    PaymentMethod payment = PaymentMethod::paragon;

    std::string NIP = ui->NIPInput->text().toStdString();
    if(!NIP.empty())
        payment = PaymentMethod::faktura;

    Order order = Order(shop->GetClientManager()->GetCurClient(),
                        adres,
                        shop->GetShoppingCart()->getProductsInCartMap(),
                        CalculateBaseCartPrice(),
                        payment,
                        NIP);
    if (ui->promoCodeLineEdit->text().isEmpty()){
        shop->GetOrderManager()->AddOrder(order);
        shop->GetSerializer()->SaveReceipt(order);
        QMessageBox::information(this, "Informacja", "Zamowienie zlozone poprawnie");
    }else{
        try{
            shop->GetOrderManager()->AddOrder(order,
                                              ui->promoCodeLineEdit->text().toStdString());
            QMessageBox::information(this, "Informacja", "Zamowienie zlozone poprawnie");
        }
        catch(const CodeNotFoundException& e){
            QMessageBox::information(this, "Informacja", "Nie znaleziono podanego kodu promocyjnego");
        }
    }
    shop->GetSerializer()->StoreOrdersInFile();
    shop->GetShoppingCart()->clearCart();
    UpdateCartUser();
    ClearFinalizationFields();
    UpdateOrdersUser();
    ChangeView_User();
}

void MainWindow::on_retFromOrderPushButton_clicked()
{
    ChangeView_User();
}

void MainWindow::on_promoCodePushButton_clicked()
{
    try{
        std::stringstream ss; // CalculateBaseCartPrice()
    //    std::string code = ui->promoCodeLineEdit->text().toStdString();
        ss << std::fixed << std::setprecision(2)
           << (static_cast<double>(shop->GetOrderManager()
                                       ->CalculatePriceWithCode(CalculateBaseCartPrice(),
                                                                ui->promoCodeLineEdit->text().toStdString())) / 100);
        ui->ovarallPriceLabel->setText(QString::fromStdString("w sumie: " + ss.str()));
    }
    catch (CodeNotFoundException& e){
        QMessageBox::information(this, "Informacja", "Nie znaleziono kodu promocyjnego");
    }
}

void MainWindow::ClearFinalizationFields(){
    ui->cityEnterLineEdit->clear();
    ui->postalCodeEnterLineEdit->clear();
    ui->streetEnterLineEdit->clear();
    ui->promoCodeLineEdit->clear();
    ui->NIPInput->clear();
}

/////////////////////////////// USER WINDOW FUNCTIONS ///////////////////////////////

void MainWindow::UpdateProductsUser(const SearchFilter& searchFilter)
{
    ui->ListaProduktowUser->clear();
    // Wyświetl Produkty
    auto products = shop->GetProductManager()->GetProductsList(searchFilter);
    for(const auto& product : products)
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setIcon(QIcon(QString::fromStdString(product.GetImgPath())));
        item->setText(QString::fromStdString(std::string(product)));
        item->setData(Qt::UserRole, QVariant(static_cast<quint32>(product.GetId())));
        ui->ListaProduktowUser->addItem(item);
    }
}

void MainWindow::UpdateProductsUser()
{
    ui->ListaProduktowUser->clear();
    // Wyświetl Produkty
    auto products = shop->GetProductManager()->GetProductsList();
    for(const auto& product : products)
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setIcon(QIcon(QString::fromStdString(product.GetImgPath())));
        item->setText(QString::fromStdString(std::string(product)));
        item->setData(Qt::UserRole, QVariant(static_cast<quint32>(product.GetId())));
        ui->ListaProduktowUser->addItem(item);
    }
}

void MainWindow::on_logOutButton_clicked()
{
    ChangeView_Login();
    shop->GetClientManager()->LogOut();
    shop->GetShoppingCart()->clearCart();
}

void MainWindow::on_filterButton_clicked()
{
    std::string phrase = ui->searchPhrase->text().toStdString();
    unsigned int bottomPriceGr = static_cast<unsigned int>((ui->fromPrice->value())*100);
    unsigned int topPriceGr = static_cast<unsigned int>((ui->toPrice->value())*100);

    std::vector<ProductTags> tags;
    if(ui->rozrywkaCheckBox->isChecked()) tags.push_back(ProductTags::rozrywka);
    if(ui->zywnoscCheckBox->isChecked()) tags.push_back(ProductTags::zywnosc);
    if(ui->urodaCheckBox->isChecked()) tags.push_back(ProductTags::uroda);
    if(ui->sportCheckBox->isChecked()) tags.push_back(ProductTags::sport);
    if(ui->mebleCheckBox->isChecked()) tags.push_back(ProductTags::meble);

    SortType sortType;
    switch(ui->sortowanieCombo->currentIndex())
    {
    case 0: sortType = SortType::ByIdLowest; break;
    case 1: sortType = SortType::ByIdHighest; break;
    case 2: sortType = SortType::ByPriceLowest; break;
    case 3: sortType = SortType::ByPriceHighest; break;
    default: QMessageBox::information(this, "Informacja", "Wystąpił błąd podczas wybierania typu sortowania");
        sortType = SortType::ByIdLowest;
    }
    SearchFilter filter(bottomPriceGr, topPriceGr, phrase, sortType, tags);
    UpdateProductsUser(filter);

}

void MainWindow::UpdateCartUser()
{
    ui->cartListWidget->clear();
    for (auto& pair: shop->GetShoppingCart()->getProductsInCartMap()){
        QListWidgetItem *item = new QListWidgetItem;
        Product cur_prod = shop->GetProductManager()->FindProductById(pair.first);
        std::stringstream sso;
        sso << cur_prod.GetName() << ": " << cur_prod.PriceToString()
            << "\tilosc: " << std::to_string(pair.second);
        item->setText(QString::fromStdString(sso.str()));
        item->setData(Qt::UserRole, QVariant(static_cast<quint32>(pair.first)));
        ui->cartListWidget->addItem(item);
    }
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << (static_cast<double>(CalculateBaseCartPrice()) / 100);
    ui->priceSumLabel->setText(QString::fromStdString(ss.str() + " zl"));
}

void MainWindow::UpdateOrdersUser()
{
    ui->ordersListWidget->clear();
    for (auto& order: shop->GetOrderManager()->GetOrdersVector())
    {
        if (order.GetClient().GetLogin() == shop->GetClientManager()->GetCurClient().GetLogin()){
            QListWidgetItem *item = new QListWidgetItem;
            std::stringstream ss;
            ss << "Zamowienie nr: " << std::to_string(order.GetId()) << " status: " << order.GetStatusStr();
            item->setText(QString::fromStdString(ss.str()));
            item->setData(Qt::UserRole, QVariant(static_cast<quint32>(order.GetId())));
            ui->ordersListWidget->addItem(item);
        }
    }
}

unsigned MainWindow::CalculateBaseCartPrice()
{
    unsigned price{};
    for (auto& pair: shop->GetShoppingCart()->getProductsInCartMap()){
        Product cur_prod = shop->GetProductManager()->FindProductById(pair.first);
        price += cur_prod.GetPriceGr() * pair.second;
    }
    return price;
}

void MainWindow::on_addProductButton_clicked()
{
    if (!ui->ListaProduktowUser->selectedItems().isEmpty()){
        shop->GetShoppingCart()->addToCart(ui->ListaProduktowUser->currentItem()->data(Qt::UserRole).toUInt(),
                                               ui->prodQuantitySpinBox->value());
        UpdateCartUser();
    }else{
        QMessageBox::information(this, "Informacja", "Aby dodac produkt do koszyka, najpierw nalezy wybrac go z listy produktow");
    }
}


void MainWindow::on_deleteFromCartButton_clicked()
{
    if (!ui->cartListWidget->selectedItems().isEmpty()){
        shop->GetShoppingCart()->deleteFromCart(ui->cartListWidget->currentItem()->data(Qt::UserRole).toUInt());
        UpdateCartUser();
    }else{
        QMessageBox::information(this, "Informacja", "Aby usunac produkt z koszyka, najpierw nalezy wybrac produkt z listy produktow w koszyku");
    }
}


void MainWindow::on_changeQuantityButton_clicked()
{
    if (!ui->cartListWidget->selectedItems().isEmpty()){
        shop->GetShoppingCart()->setQuantity(ui->cartListWidget->currentItem()->data(Qt::UserRole).toUInt(),
                                         ui->setQuantitySpinBox->value());
        UpdateCartUser();
    }else{
        QMessageBox::information(this, "Informacja", "Aby zmienic ilosc produktu w koszyku, najpierw nalezy wybrac produkt z listy produktow w koszyku");
    }
}


void MainWindow::on_orderButton_clicked()
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << (static_cast<double>(CalculateBaseCartPrice()) / 100);
    ui->ovarallPriceLabel ->setText("w sumie: " + QString::fromStdString(ss.str()));
    ChangeView_OrderFinalization();
}

void MainWindow::on_selectedOrderInfoPushButton_clicked()
{
    if (!ui->ordersListWidget->selectedItems().isEmpty()){
        Order order = shop->GetOrderManager()->FindOrderById(ui->ordersListWidget->currentItem()->data(Qt::UserRole).toUInt());
        std::stringstream sso;
        sso << "Id: " << order.GetId() << "\nStatus: " << order.GetStatusStr() << "\nAdres dostawy: "
            << order.GetAddress().GetPostalCode() << " " << order.GetAddress().GetCity() << " " << order.GetAddress().GetStreetAndNumber()
            << "\nData zlozenia: " << order.GetDate() << "\nProdukty:\n";
        for (auto& pair: order.GetProductsAndQuantities()){
            sso << shop->GetProductManager()->FindProductById(pair.first).GetName() << " x" << pair.second << "\n";
        }
        QMessageBox::information(this, "Informacja o zamowieniu", QString::fromStdString(sso.str()));
    }else{
        QMessageBox::information(this, "Informacja", "Aby wyswietlic informacje o zamowieniu, najpierw wybierz je z listy");
    }
}



