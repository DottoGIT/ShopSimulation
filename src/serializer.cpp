#include "serializer.h"

Serializer::Serializer(OrderManager& orderManager_, ProductManager& productManager_, ClientManager& clientManager_) :
    orderManager(orderManager_), productManager(productManager_), clientManager(clientManager_)
{
    LoadProducts();
    LoadPromoCodes();
    LoadOrdersFromFile();
    LoadClients();
}

void Serializer::LoadPromoCodes()
{
    Logger::Info("<serialzier.h> Rozpoczecie ladowania kodow promocyjnych");
    rapidcsv::Document doc(PROMOCODES_DATABASE);
    std::vector<std::string> codes = doc.GetColumn<std::string>("code");
    std::vector<double> priceFactors = doc.GetColumn<double>("priceFactor");
    std::vector<PromoCode> promoCodes;
    for(size_t i = 0; i < doc.GetRowCount(); i++)
    {
        promoCodes.push_back(PromoCode(codes.at(i), priceFactors.at(i)));
    }
    orderManager.SetPromoCodes(promoCodes);
}

void Serializer::LoadOrdersFromFile()
{
    Logger::Info("<serialzier.h> Rozpoczecie ladowania zamowien");
    nlohmann::json fileData;
    std::ifstream file(ORDERS_DATABASE);
    if (file.is_open()){
        file >> fileData;
        file.close();

        for (auto& order: fileData.items())
        {
            Address adres = Address{
                order.value()["address"]["city"],
                order.value()["address"]["postalCode"],
                order.value()["address"]["streetAndNum"]
            };
            Client client = Client(
                order.value()["client"]["login"],
                order.value()["client"]["password"],
                order.value()["client"]["name"],
                order.value()["client"]["surname"]);
            std::map<unsigned, unsigned> prod_map;
            for (auto& prodData: order.value()["products"].items())
            {
                prod_map.insert(std::make_pair(prodData.value()["productId"], prodData.value()["quantity"]));
            }
            std::string date = order.value()["date"];
            Order orderToAdd = Order (client,
                                adres,
                                prod_map,
                                order.value()["price"],
                                date);
            std::string statusStr = order.value()["status"];
            if (statusStr == "w realizacji"){
                orderToAdd.SetStatus(Status::wRealizacji);
            }else if (statusStr == "w trakcie dostawy"){
                orderToAdd.SetStatus(Status::wTrakcieDostawy);
            }else if (statusStr == "zrealizowano"){
                orderToAdd.SetStatus(Status::zrealizowano);
            }else if (statusStr == "zwrot"){
                orderToAdd.SetStatus(Status::zwrot);
            }else if (statusStr == "anulowano"){
                orderToAdd.SetStatus(Status::anulowano);
            }

            orderManager.AddOrder(orderToAdd);
        }
    }
}

void Serializer::LoadProducts()
{
    Logger::Info("<serialzier.h> Rozpoczecie ladowania produktow");
    rapidcsv::Document doc(PRODUCTS_DATABASE);
    std::vector<std::string> Nazwa = doc.GetColumn<std::string>("Nazwa");
    std::vector<int> CenaZl = doc.GetColumn<int>("CenaZl");
    std::vector<int> CenaGr = doc.GetColumn<int>("CenaGr");
    std::vector<std::string> T0 = doc.GetColumn<std::string>("T0");
    std::vector<std::string> T1 = doc.GetColumn<std::string>("T1");
    std::vector<std::string> T2 = doc.GetColumn<std::string>("T2");
    std::vector<std::string> T3 = doc.GetColumn<std::string>("T3");
    std::vector<std::string> T4 = doc.GetColumn<std::string>("T4");
    std::vector<std::string> ImgPath = doc.GetColumn<std::string>("ImgPath");

    for(size_t i=0; i < doc.GetRowCount(); i++)
    {
        std::vector<ProductTags> Tags;
        if(T0[i] == "T") Tags.push_back(ProductTags::meble);
        if(T1[i] == "T") Tags.push_back(ProductTags::sport);
        if(T2[i] == "T") Tags.push_back(ProductTags::uroda);
        if(T3[i] == "T") Tags.push_back(ProductTags::zywnosc);
        if(T4[i] == "T") Tags.push_back(ProductTags::rozrywka);

        Product product(Nazwa[i], CenaZl[i], CenaGr[i], Tags ,ImgPath[i]);
        productManager.AddProduct(product);
    }
}

void Serializer::LoadClients()
{
    Logger::Info("<serialzier.h> Rozpoczecie ladowania klientow");
    rapidcsv::Document doc(CLIENTS_DATABASE);
    std::vector<std::string> login = doc.GetColumn<std::string>("login");
    std::vector<std::string> password = doc.GetColumn<std::string>("password");
    std::vector<std::string> name = doc.GetColumn<std::string>("name");
    std::vector<std::string> surname = doc.GetColumn<std::string>("surname");

    for(size_t i = 0; i < doc.GetRowCount(); i++)
    {
        clientManager.AddClient(Client(login.at(i), password.at(i), name.at(i), surname.at(i)));
    }
}


void Serializer::StoreOrdersInFile()
{
    Logger::Info("<serialzier.h> Zapisanie zamowien do pliku");
    nlohmann::json object;
    unsigned order_num = 1;
    for ( auto& order : orderManager.GetOrdersVector()){
        std::string order_field {"order"};
        order_field += std::to_string(order_num);
        object[order_field]["date"] = order.GetDate();
        object[order_field]["price"] = order.GetOverallPrice();
        object[order_field]["status"] = order.GetStatusStr();
        object[order_field]["client"]["login"] = order.GetClient().GetLogin();
        object[order_field]["client"]["password"] = order.GetClient().GetPassword();
        object[order_field]["client"]["name"] = order.GetClient().GetName();
        object[order_field]["client"]["surname"] = order.GetClient().GetSurname();
        object[order_field]["address"]["city"] = order.GetAddress().GetCity();
        object[order_field]["address"]["streetAndNum"] = order.GetAddress().GetStreetAndNumber();
        object[order_field]["address"]["postalCode"] = order.GetAddress().GetPostalCode();
        unsigned product_num = 1;
        for (const auto& pair: order.GetProductsAndQuantities()){
            std::string product_field {"product"};
            product_field += std::to_string(product_num);
            object[order_field]["products"][product_field]["productId"] = pair.first;
            object[order_field]["products"][product_field]["quantity"] = pair.second;
            ++product_num;
        }
        ++order_num;
    }
    std::ofstream file(ORDERS_DATABASE);
    if (file.is_open()){
        file.clear();
        file << std::setw(4) << object;
        file.close();
    }
}

void Serializer::SaveClients()
{
    Logger::Info("<serialzier.h> Zapisanie klientow do pliku");
    rapidcsv::Document doc(CLIENTS_DATABASE);
    std::vector<std::string> login {};
    std::vector<std::string> password {};
    std::vector<std::string> name {};
    std::vector<std::string> surname {};
    for (const auto& account : clientManager.GetClientsList()){
        login.push_back(account.GetLogin());
        password.push_back(account.GetPassword());
        name.push_back(account.GetName());
        surname.push_back(account.GetSurname());
    }
    doc.SetColumn<std::string>("login", login);
    doc.SetColumn<std::string>("password", password);
    doc.SetColumn<std::string>("name", name);
    doc.SetColumn<std::string>("surname", surname);
    doc.Save();
}

void Serializer::SaveReceipt(const Order& order) const
{
    std::string path;
    std::stringstream sso;
    if(order.GetPayment() == PaymentMethod::faktura)
    {
        path = "fakturaNr" + std::to_string(order.GetId()) + ".txt";
        sso << "Faktura dla zamowienia: " << order.GetId() << "\n"
            << "wystawiona dnia: " << order.GetDate() << "\n"
            << "NIP: " << order.GetNIP() << "\n"
            << "Nabywca: " << order.GetClient().GetName() << " " << order.GetClient().GetName() << "\n";
    }
    else
    {
        path = "paragonNr" + std::to_string(order.GetId()) + ".txt";
        sso << "Paragon dla zamowienia: " << order.GetId() << "\n"
            << "wystawiony dnia: " << order.GetDate() << "\n\n\n";
    }
    sso << "Zamowione produkty: \n";
    for(const auto& [p, q] : order.GetProductsAndQuantities())
    {
        sso << productManager.FindProductById(p).GetName() << "\t x" << q << "\n";
    }
    sso << "Suma: " << int(order.GetOverallPrice()/100) << "," << order.GetOverallPrice()%100 << "zl";

    std::ofstream file(RECEIPT_FOLDER + path);
    file << sso.str();
    file.close();
    Logger::Info("<seriazlier.h> Paragon zamowienia o id: "+ std::to_string(order.GetId()) + " zostal wystawiony");
}
