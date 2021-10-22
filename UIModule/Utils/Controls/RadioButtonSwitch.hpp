#ifndef RADIOBUTTONSWITCH_HPP
#define RADIOBUTTONSWITCH_HPP

#include "ISwitch.hpp"

#include <QRadioButton>

class RadioButtonSwitch: public ISwitch
{
    Q_OBJECT

public:
    RadioButtonSwitch(QRadioButton& on, QRadioButton& off, bool state = false);
    void changeState(bool state) override;
    bool getState() override;

public slots:
    void onSwitchChanged(bool state);

private:
    QRadioButton& on_;
    QRadioButton& off_;
    bool lastState_;
};

#endif // RADIOBUTTONSWITCH_HPP
