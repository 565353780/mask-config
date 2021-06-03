#ifndef SetterCOMMANDWIDGET_H
#define SetterCOMMANDWIDGET_H
#include <QWidget>
#include <QPushButton>
namespace MaskConfig {
class Setter;
class LabelDict;
class LabelDictWidget;
class BindingWidget;
/**
 * @brief 对标定框的命令按钮
 */
class CommandButton : public QPushButton
{
    Q_OBJECT
public:
     explicit CommandButton(const QString& command, QWidget* parent);
signals:
    void signalCommand(const QString& command);

public slots:
    void slotCommand();
private:
    QString command_;
};
/**
 * @brief 对标定框进行操作命令的widget
 */
class SetterWidget : public QWidget
{
    Q_OBJECT
public:
   explicit SetterWidget(const QString& key, Setter* setter, QWidget* parent);

    /**
     * @brief 添加"LabelDict"（下拉列表）
     * @param dict
     */
    void addLabelDict(LabelDict* dict);
signals:
    void signalUpdate();
public slots:
    /**
     * @brief 运行command
     * @param command
     */
    void slotCommand(const QString& command);
    void slotUpdate();
public:
    QString key() const {return key_;}

protected:
    void resizeEvent(QResizeEvent *event);
    void resetGeometry();
private:
    QString key_;
    Setter* setter_;

    QList<CommandButton* > buttons_;
    QList<LabelDictWidget* > label_dict_widgets_;
    QList<BindingWidget* > binding_widgets_;
    QWidget* tracking_widget_;
    QWidget* info_widget_;


};
}
#endif // COMMANDWIDGET_H
