#pragma once 
 
#include "calculator.h" 
 
#include <QMainWindow> 
 
enum Operation { 
    NO_OPERATION, 
    ADDITION, 
    SUBTRACTION, 
    MULTIPLICATION, 
    DIVISION, 
    POWER 
}; 
 
QT_BEGIN_NAMESPACE 
namespace Ui { 
class MainWindow; 
} 
QT_END_NAMESPACE 
 
class MainWindow : public QMainWindow { 
    Q_OBJECT 
 
public: 
    MainWindow(QWidget* parent = nullptr); 
    ~MainWindow(); 
private slots: 
    void on_pb_delete_last_char_clicked(); 
 
private: 
    Ui::MainWindow* ui; 
    Calculator calculator_; 
    QString input_number_; 
    Number memory_save_; 
    Number active_number_ = 0; 
    Number hasmem_ = 0; 
    bool is_flag_hasmem_ = false; 
    Operation current_operation_ = Operation::NO_OPERATION; 
    void SetText(const QString& text); 
    void AddText(const QString& suffix); 
    void SetOperation(Operation op); 
    QString OpToString(const Operation op); 
    void result(); 
    void save_memory(); 
    void clear_memory(); 
    void load_memory(); 
    void pb_point(); 
    void pb_add_plus_or_minus(); 
    void pb_clear(); 
}; 