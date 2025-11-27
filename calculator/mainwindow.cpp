#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

QString RemoveTrailingZeroes(const QString &text) {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text[i] != '0') {
            return text.mid(i);
        }
    }
    return "";
}

QString NormalizeNumber(const QString &text) {
    if (text.isEmpty()) {
        return "0";
    }
    if (text.startsWith('.')) {
        // Рекурсивный вызов.
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-')) {
        // Рекурсивный вызов.
        return "-" + NormalizeNumber(text.mid(1));
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveTrailingZeroes(text));
    }
    return text;
}

QString MainWindow::OpToString(const Operation op)
{
    switch(op) {
    case Operation::NO_OPERATION: return "";
    case Operation::ADDITION: return "+";
    case Operation::DIVISION: return "÷";
    case Operation::MULTIPLICATION: return "×";
    case Operation::SUBTRACTION: return "−";
    case Operation::POWER: return "^";
    }
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");

    //Числа
    connect(ui->pb_zero, &QPushButton::clicked, this, [this](){AddText("0");});
    connect(ui->pb_one, &QPushButton::clicked, this, [this](){AddText("1");});
    connect(ui->pb_two, &QPushButton::clicked, this, [this](){AddText("2");});
    connect(ui->pb_three, &QPushButton::clicked, this, [this](){AddText("3");});
    connect(ui->pb_four, &QPushButton::clicked, this, [this](){AddText("4");});
    connect(ui->pb_five, &QPushButton::clicked, this, [this](){AddText("5");});
    connect(ui->pb_six, &QPushButton::clicked, this, [this](){AddText("6");});
    connect(ui->pb_sever, &QPushButton::clicked, this, [this](){AddText("7");});
    connect(ui->pb_eng, &QPushButton::clicked, this, [this](){AddText("8");});
    connect(ui->pb_nine, &QPushButton::clicked, this, [this](){AddText("9");});
    connect(ui->pb_point, &QPushButton::clicked, this, [this](){AddText(".");});
    connect(ui->pb_add_plus_or_minus, &QPushButton::clicked, this, [this](){AddText("-");});
    connect(ui->pb_clear, &QPushButton::clicked, this, [this](){SetText("0");});
    //Операции с числами
    connect(ui->pb_plus, &QPushButton::clicked, this, [this](){SetOperation(Operation::ADDITION);}); // +
    connect(ui->pb_minus, &QPushButton::clicked, this, [this](){SetOperation(Operation::SUBTRACTION);}); // -
    connect(ui->pb_multiplay, &QPushButton::clicked, this, [this](){SetOperation(Operation::MULTIPLICATION);}); // *
    connect(ui->pb_divide, &QPushButton::clicked, this, [this](){SetOperation(Operation::DIVISION);}); // Делить
    connect(ui->pb_pow, &QPushButton::clicked, this, [this](){SetOperation(Operation::POWER);}); // Возведение в степень
    //Самая важная кнопка – =
    connect(ui->pb_result, &QPushButton::clicked, this, &MainWindow::result);
    //Сохранить в память число
    connect(ui->pb_save_memory, &QPushButton::clicked, this, &MainWindow::save_memory);
    //Удалить из памяти число
    connect(ui->pb_clear_memory, &QPushButton::clicked, this, &MainWindow::clear_memory);
    //Загрузить из памяти
    connect(ui->pb_load_memory, &QPushButton::clicked, this, &MainWindow::load_memory);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetText(const QString &text)
{
    if(text == "0")
    {
        current_operation_ = Operation::NO_OPERATION;
        ui->l_formula->setText("");
        ui->l_result->setText(text);
        input_number_.clear();
        active_number_ = 0;
    }else{
        active_number_ = input_number_.toDouble();
        ui->l_result->setText(text);
    }
}

void MainWindow::AddText(const QString &suffix)
{
    if(suffix == "."){
        if(!input_number_.contains('.'))
        {
            if(input_number_.isEmpty())
            {
                input_number_ += "0.";
            }else{
                input_number_ += ".";
            }
        }
    }else if(suffix == "-")
    {
        if (input_number_.startsWith("-"))
        {
            input_number_ = input_number_.mid(1);
        }else{
            input_number_ = input_number_.prepend("-");
        }
    }else{
        input_number_ += suffix;
    }
    input_number_ = NormalizeNumber(input_number_);
    SetText(input_number_);
}

void MainWindow::SetOperation(Operation op)
{
    if(current_operation_ == Operation::NO_OPERATION)
    {
        calculator_.Set(active_number_);
    }
    current_operation_ = op;
    QString form = "%1 %2";
    QString res = form.arg(calculator_.GetNumber()).arg(OpToString(current_operation_));
    ui->l_formula->setText(res);
    input_number_ = "";
}

void MainWindow::on_pb_delete_last_char_clicked()
{
    input_number_.chop(1);
    input_number_ = NormalizeNumber(input_number_);
    SetText(input_number_);
}

void MainWindow::result()
{
    if(!(current_operation_ == Operation::NO_OPERATION))
    {
        QString form = "%1 %2 %3 =";
        QString res = form
                          .arg(calculator_.GetNumber())
                          .arg(OpToString(current_operation_))
                          .arg(active_number_);
        ui->l_formula->setText(res);
        switch (current_operation_) {
        case 1:
            calculator_.Add(active_number_);
            break;
        case 2:
            calculator_.Sub(active_number_);
            break;
        case 3:
            calculator_.Mul(active_number_);
            break;
        case 4:
            calculator_.Div(active_number_);
            break;
        case 5:
            calculator_.Pow(active_number_);
            break;
        default:
            break;
        }
        QString qstr = QString::fromStdString(calculator_.GetNumberRepr());
        qDebug() << qstr;
        active_number_ = qstr.toDouble();
        ui->l_result->setText(QString::number(active_number_));
        input_number_ = "";
        current_operation_ = Operation::NO_OPERATION;
    }
}

void MainWindow::save_memory()
{
    hasmem_ = active_number_;
    ui->l_memory->setText("M");
    is_flag_hasmem_ = true;
}

void MainWindow::clear_memory()
{
    if(is_flag_hasmem_){
        ui->l_memory->setText("");
        is_flag_hasmem_ = false;
        hasmem_ = 0;
    }
}

void MainWindow::load_memory()
{
    if(is_flag_hasmem_)
    {
        active_number_ = hasmem_;
        ui->l_result->setText(QString::number(active_number_));
        input_number_.clear();
    }
}

