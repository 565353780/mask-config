#include "PaintWidget.h"
#include <QMouseEvent>
#include "ConfigWidget.h"
#include "Config/Setter/Setter.h"
#include <QPainter>
#include <QKeyEvent>

#include <QDebug>
namespace MaskConfig{

PaintWidget::PaintWidget(ConfigWidget *parent):QWidget(parent),config_widget_(parent)
{

}

void PaintWidget::resizeEvent(QResizeEvent *event)
{
    if(config_widget_->current_setter())
    {
        config_widget_->current_setter()->resize(this->width(),this->height());
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    if(config_widget_->current_setter())
    {
        config_widget_->current_setter()->mousePress(event->pos().x(),event->pos().y(),event->buttons(),event->modifiers());
        this->update();
    }
    this->setFocus();
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(config_widget_->current_setter())
    {
        config_widget_->current_setter()->mouseMove(event->pos().x(),event->pos().y());
        this->update();
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(config_widget_->current_setter())
    {
        config_widget_->current_setter()->mouseRelease(event->pos().x(),event->pos().y(),event->buttons(),event->modifiers());
        this->update();
    }

}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawImage(QRectF(0,0,this->width(),this->height()),config_widget_->image());
    if(config_widget_->current_setter())
    {
        config_widget_->current_setter()->paint(painter);
    }
}

}
