#ifndef LABELDICTWIDGET_H
#define LABELDICTWIDGET_H
#include <QWidget>
class QComboBox;
class QLabel;
namespace MaskConfig {
class LabelDict;
/**
 * @brief 含标签及下拉列表的组合widget
 */
class LabelDictWidget : public QWidget
{
    Q_OBJECT
public:
   explicit LabelDictWidget(LabelDict* dict, QWidget* parent);

    void init();
protected:
    void resizeEvent(QResizeEvent *event);

signals:
    void signalChanged();
public slots:
    /**
     * @brief 列表选择变化
     * @param index
     */
    void slotChanged(int index);
    void slotUpdateValue();
private:
    LabelDict* dict_;

    QLabel* label_;
    QComboBox* combobox_;

    QString key_;

};
}
#endif // LABELDICTWIDGET_H
