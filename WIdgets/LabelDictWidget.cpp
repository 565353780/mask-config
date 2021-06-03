#include "LabelDictWidget.h"
#include <QComboBox>
#include "Config/Setting/LabelDict.h"
#include <QLabel>
#include <QKeyEvent>
#include <QDebug>
namespace MaskConfig {
LabelDictWidget::LabelDictWidget(LabelDict *dict, QWidget *parent):QWidget(parent),dict_(dict)
{
    this->init();
}

void LabelDictWidget::init()
{
    label_ = new QLabel(dict_->ui_name(),this);
    combobox_ = new QComboBox(this);
    foreach (const QString& key, dict_->option_keys_)
    {
        combobox_->addItem(dict_->options_[key], key);
    }
    key_ = dict_->key_;

    combobox_->setCurrentText(dict_->options_[key_]);
    combobox_->clearFocus();

    connect(combobox_,SIGNAL(currentIndexChanged(int)),this,SLOT(slotChanged(int)));

}

void LabelDictWidget::resizeEvent(QResizeEvent *event)
{
    label_->move(3,3);
    combobox_->move(100,3);
}

void LabelDictWidget::slotChanged(int index)
{
    key_ = combobox_->currentData().toString();
    dict_->key_ = key_;
    emit signalChanged();
}

void LabelDictWidget::slotUpdateValue()
{
    key_ = dict_->key_;
    combobox_->setCurrentText(dict_->options_[dict_->key_]);
}
}
