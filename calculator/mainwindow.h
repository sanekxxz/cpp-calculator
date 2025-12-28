#pragma once

#include "enums.h"

#include <QMainWindow>

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
    void SetInputText(const std::string& text);
    void SetErrorText(const std::string& text);
    void SetFormulaText(const std::string& text);
    void SetMemText(const std::string& text);
    void SetExtraKey(const std::optional<std::string>& key);

    void SetDigitKeyCallback(std::function<void(int key)> cb);
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb);
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb);
    void SetControllerCallback(std::function<void(ControllerType controller)> cb);

private slots:
    void OnPbZeroClicked();
    void OnPbOneClicked();
    void OnPbTwoClicked();
    void OnPbThreeClicked();
    void OnPbFourClicked();
    void OnPbFiveClicked();
    void OnPbSixClicked();
    void OnPbSevenClicked();
    void OnPbEightClicked();
    void OnPbNineClicked();
    void OnTbExtraClicked();
    void OnPbBackspaceClicked();
    void OnPbEqualsClicked();
    void OnPbAdditionClicked();
    void OnPbMinusClicked();
    void OnPbMultiplicationClicked();
    void OnPbDivisionClicked();
    void OnPbToNegativeClicked();
    void OnPbClearClicked();
    void OnPbMemoryClearClicked();
    void OnPbMemoryReadClicked();
    void OnPbMemorySaveClicked();
    void OnPbRaiseToDeegreClicked();
    void OnCmbControllerClicked();

private:
    Ui::MainWindow* ui;

    std::function<void(int key)> digit_key_callback_;
    std::function<void(Operation key)> process_operation_key_callback_;
    std::function<void(ControlKey key)> process_control_key_callback_;
    std::function<void(ControllerType controller)> controller_callback_;
};
