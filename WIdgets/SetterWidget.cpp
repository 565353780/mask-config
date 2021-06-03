#include "SetterWidget.h"
#include "Config/Setter/Setter.h"
#include "LabelDictWidget.h"
#include "Config/Setting/PolygonListSetting.h"
#include <QGridLayout>
#include "Config/Dict.h"
#include "InfoWidget.h"
#include "Config/Setter/PolygonsSetter.h"
#include "Config/Setter/BBoxSetter.h"
#include "TrackIdWidget.h"
#include "BindingWidget.h"
#include <QScrollArea>
#include <QShortcut>
#include <QKeySequence>
namespace MaskConfig{


CommandButton::CommandButton(const QString &command, QWidget *parent):QPushButton(parent), command_(command)
{
    this->setText(Dict::t(command));
    connect(this,SIGNAL(clicked(bool)),this,SLOT(slotCommand()));    

}

void CommandButton::slotCommand()
{
    emit this->signalCommand(command_);
}



SetterWidget::SetterWidget(const QString &key, Setter *setter, QWidget *parent):QWidget(parent),setter_(setter),key_(key)
{

    tracking_widget_ = NULL;

    QScrollArea* scrollarea = new QScrollArea(this);
    scrollarea->setWidget(new InfoWidget(setter_,scrollarea));
    info_widget_ = scrollarea;

    QList<Setter::Command> command_lists = setter->command_list();
//    QGridLayout* grid_layout = new QGridLayout(this);
    for(int i=0; i < command_lists.size(); i++)
    {
        CommandButton* button = new CommandButton(command_lists.at(i).command_,this);
        connect(button,SIGNAL(signalCommand(QString)),this,SLOT(slotCommand(QString)));
        QShortcut *shortcut= new QShortcut(QKeySequence("Ctrl+"+QString::number(i+1)),this);
        connect(shortcut,&QShortcut::activated,button,&CommandButton::click);
        button->setToolTip("Ctrl+"+QString::number(i+1));

        buttons_.push_back(button);
//        grid_layout->addWidget(button,i / 3, i % 3);
    }


//    this->setLayout(grid_layout);
    PolygonListSetting* setting = dynamic_cast<PolygonListSetting* >(setter->setting());
    if(setting)
    {
        for(int i=0; i < setting->label_dict_list_.size(); i++)
        {
            this->addLabelDict(setting->label_dict_list_[i].get());
        }
        PolygonsSetter* polys_setter =  dynamic_cast<PolygonsSetter* >(setter);
        if(polys_setter && polys_setter->bindingSize() > 0)
        {
            for(int i=0; i < polys_setter->bindingSize(); i++)
            {
                binding_widgets_.push_back(new BindingWidget(polys_setter->getBinding(i),this));
            }
        }

        BBoxSetter* bbox_setter =  dynamic_cast<BBoxSetter* >(setter);
        if(bbox_setter && bbox_setter->is_tracking())
        {
            tracking_widget_ = new TrackIdWidget(bbox_setter,this);
        }

    }



}

void SetterWidget::addLabelDict(LabelDict *dict)
{
    LabelDictWidget* w = new LabelDictWidget(dict,this);
    label_dict_widgets_.push_back(w);
    connect(w,SIGNAL(signalChanged()),this,SLOT(slotUpdate()));
    connect(setter_->setting(),SIGNAL(signalUpdate()),w,SLOT(slotUpdateValue()));

//    resetGeometry();
}

void SetterWidget::slotCommand(const QString &command)
{
    setter_->runCommand(command);
    emit this->signalUpdate();

}

void SetterWidget::slotUpdate()
{
    setter_->update();
}

void SetterWidget::resizeEvent(QResizeEvent *event)
{
    this->resetGeometry();
}

void SetterWidget::resetGeometry()
{
    int buttonWidth = 90;
    int buttonHeight = 25;
    int y = 0;
    for(int i=0; i < buttons_.size(); i++)
    {
        buttons_[i]->setGeometry(i % 3 * (buttonWidth+10)+5, i / 3 * (buttonHeight+5)+20,   buttonWidth,buttonHeight);
        y = buttons_[i]->y()+buttons_[i]->height();
    }
    y += 25;


    for(int i=0; i < binding_widgets_.size(); i++)
    {
        binding_widgets_[i]->setGeometry(10,y+10,this->width()-20,30);
        y = binding_widgets_[i]->y() + binding_widgets_[i]->height();
    }

    for(int i=0; i < label_dict_widgets_.size(); i++)
    {
        label_dict_widgets_[i]->setGeometry(10,y+10,this->width()-20,25);
        y = label_dict_widgets_[i]->y() + label_dict_widgets_[i]->height();
    }
    if(tracking_widget_)
    {
        tracking_widget_->setGeometry(10,y+10,this->width()-20,60);
        y = tracking_widget_->y() + tracking_widget_->height();
    }
    y += 30;
    if(info_widget_)
    {
         info_widget_->setGeometry(5,y,this->width()-15,this->height() -y);
    }

}


}
