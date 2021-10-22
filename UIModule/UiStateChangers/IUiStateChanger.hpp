#ifndef IUISTATECHANGER_HPP
#define IUISTATECHANGER_HPP

#include <QObject>

class IUiStateChanger: public QObject
{
    Q_OBJECT

public:
    virtual ~IUiStateChanger() = default;
    virtual void lostFocus() = 0;
    virtual void otherMadeChange() = 0;

signals:
    void focusIntercepted();
    void changeMade();
};

#endif // IUISTATECHANGER_HPP
