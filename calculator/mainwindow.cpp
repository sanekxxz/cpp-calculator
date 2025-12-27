#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->pb_zero, &QPushButton::clicked, this, &MainWindow::OnPbZeroClicked);
    connect(ui->pb_one, &QPushButton::clicked, this, &MainWindow::OnPbOneClicked);
    connect(ui->pb_two, &QPushButton::clicked, this, &MainWindow::OnPbTwoClicked);
    connect(ui->pb_three, &QPushButton::clicked, this, &MainWindow::OnPbThreeClicked);
    connect(ui->pb_four, &QPushButton::clicked, this, &MainWindow::OnPbFourClicked);
    connect(ui->pb_five, &QPushButton::clicked, this, &MainWindow::OnPbFiveClicked);
    connect(ui->pb_six, &QPushButton::clicked, this, &MainWindow::OnPbSixClicked);
    connect(ui->pb_seven, &QPushButton::clicked, this, &MainWindow::OnPbSevenClicked);
    connect(ui->pb_eight, &QPushButton::clicked, this, &MainWindow::OnPbEightClicked);
    connect(ui->pb_nine, &QPushButton::clicked, this, &MainWindow::OnPbNineClicked);
    connect(ui->tb_extra, &QPushButton::clicked, this, &MainWindow::OnTbExtraClicked);
    connect(ui->pb_backspace, &QPushButton::clicked, this, &MainWindow::OnPbBackspaceClicked);
    connect(ui->pb_addition, &QPushButton::clicked, this, &MainWindow::OnPbAdditionClicked);
    connect(ui->pb_minus, &QPushButton::clicked, this, &MainWindow::OnPbMinusClicked);
    connect(ui->pb_division, &QPushButton::clicked, this, &MainWindow::OnPbDivisionClicked);
    connect(ui->pb_multiplication, &QPushButton::clicked, this, &MainWindow::OnPbMultiplicationClicked);
    connect(ui->pb_to_negative, &QPushButton::clicked, this, &MainWindow::OnPbToNegativeClicked);
    connect(ui->pb_clear, &QPushButton::clicked, this, &MainWindow::OnPbClearClicked);
    connect(ui->pb_equals, &QPushButton::clicked, this, &MainWindow::OnPbEqualsClicked);
    connect(ui->pb_raise_to_deegre, &QPushButton::clicked, this, &MainWindow::OnPbRaiseToDeegreClicked);
    connect(ui->pb_memory_save, &QPushButton::clicked, this, &MainWindow::OnPbMemorySaveClicked);
    connect(ui->pb_memory_clear, &QPushButton::clicked, this, &MainWindow::OnPbMemoryClearClicked);
    connect(ui->pb_memory_read, &QPushButton::clicked, this, &MainWindow::OnPbMemoryReadClicked);
    connect(ui->cmb_controller, &QComboBox::currentIndexChanged, this, &MainWindow::OnCmbControllerClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetInputText(const std::string& text){
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text){
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text){
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text){
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key){
    if(!key.has_value()){
        ui->tb_extra->hide();
        return;
    }
    ui->tb_extra->setText(QString::fromStdString(*key));
}

void MainWindow::SetDigitKeyCallback(std::function<void(int key)> cb){
    if(cb){
        digit_key_callback_=cb;
    }
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> cb){
    if(cb){
        process_operation_key_callback_ = cb;
    }
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb){
    if(cb){
        process_control_key_callback_ = cb;
    }
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType controller)> cb){
    if(cb){
        controller_callback_=cb;
    }
}

void MainWindow::OnPbZeroClicked(){
    digit_key_callback_(0);
}

void MainWindow::OnPbOneClicked(){
    digit_key_callback_(1);
}

void MainWindow::OnPbTwoClicked(){
    digit_key_callback_(2);
}

void MainWindow::OnPbThreeClicked(){
    digit_key_callback_(3);
}

void MainWindow::OnPbFourClicked(){
    digit_key_callback_(4);
}

void MainWindow::OnPbFiveClicked(){
    digit_key_callback_(5);
}

void MainWindow::OnPbSixClicked(){
    digit_key_callback_(6);
}

void MainWindow::OnPbSevenClicked(){
    digit_key_callback_(7);
}

void MainWindow::OnPbEightClicked(){
    digit_key_callback_(8);
}

void MainWindow::OnPbNineClicked(){
    digit_key_callback_(9);
}

void MainWindow::OnTbExtraClicked(){
    process_control_key_callback_(ControlKey::EXTRA_KEY);
}

void MainWindow::OnPbBackspaceClicked(){
    process_control_key_callback_(ControlKey::BACKSPACE);
}

void MainWindow::OnPbEqualsClicked(){
    process_control_key_callback_(ControlKey::EQUALS);
}

void MainWindow::OnPbAdditionClicked(){
    process_operation_key_callback_(Operation::ADDITION);
}

void MainWindow::OnPbMinusClicked(){
    process_operation_key_callback_(Operation::SUBTRACTION);
}

void MainWindow::OnPbMultiplicationClicked(){
    process_operation_key_callback_(Operation::MULTIPLICATION);
}

void MainWindow::OnPbDivisionClicked(){
    process_operation_key_callback_(Operation::DIVISION);
}

void MainWindow::OnPbToNegativeClicked(){
    process_control_key_callback_(ControlKey::PLUS_MINUS);
}

void MainWindow::OnPbClearClicked(){
    process_control_key_callback_(ControlKey::CLEAR);
}

void MainWindow::OnPbMemoryClearClicked(){
    process_control_key_callback_(ControlKey::MEM_CLEAR);
}

void MainWindow::OnPbMemoryReadClicked(){
    process_control_key_callback_(ControlKey::MEM_LOAD);
}

void MainWindow::OnPbMemorySaveClicked(){
    process_control_key_callback_(ControlKey::MEM_SAVE);
}

void MainWindow::OnPbRaiseToDeegreClicked(){
    process_operation_key_callback_(Operation::POWER);
}

void MainWindow::OnCmbControllerClicked(){
    int index = ui->cmb_controller->currentIndex();
    switch(index){
    case 0:
        controller_callback_(ControllerType::DOUBLE);
        break;
    case 1:
        controller_callback_(ControllerType::FLOAT);
        break;
    case 2:
        controller_callback_(ControllerType::UINT8_T);
        break;
    case 3:
        controller_callback_(ControllerType::INT);
        break;
    case 4:
        controller_callback_(ControllerType::INT64_T);
        break;
    case 5:
        controller_callback_(ControllerType::SIZE_T);
        break;
    case 6:
        controller_callback_(ControllerType::RATIONAL);
        break;
    }
}
