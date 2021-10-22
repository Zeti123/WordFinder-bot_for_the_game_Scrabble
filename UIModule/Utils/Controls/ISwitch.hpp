#ifndef ISWITCH_HPP
#define ISWITCH_HPP

#include <QObject>

class ISwitch: public QObject
{
    Q_OBJECT

public:
    virtual ~ISwitch() = default;
    virtual void changeState(bool state) = 0;
    virtual bool getState() = 0;

signals:
    void stateChanged(bool state);
};

#endif // ISWITCH_HPP
