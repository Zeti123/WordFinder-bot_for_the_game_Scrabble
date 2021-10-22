#include "RadioButtonSwitch.hpp"

RadioButtonSwitch::RadioButtonSwitch(QRadioButton& on, QRadioButton& off, bool state)
    :on_(on), off_(off), lastState_(state)
{
    if (state)
        on_.setChecked(state);
    else
        off_.setChecked(!state);
    connect(&on_, &QRadioButton::toggled, this, &RadioButtonSwitch::onSwitchChanged);
}

void RadioButtonSwitch::onSwitchChanged(bool state)
{
    if (state == lastState_)
        return;

    lastState_ = state;
    emit stateChanged(state);
}

void RadioButtonSwitch::changeState(bool state)
{
    if (state == lastState_)
        return;

    // this will call onSwitchChanged
    if (state)
        on_.setChecked(state);
    else
        off_.setChecked(!state);
}

bool RadioButtonSwitch::getState()
{
    return lastState_;
}
