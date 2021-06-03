#include "Setter.h"
#include "Config/Setting/Setting.h"
#include <QPainter>
#include <QDebug>
namespace MaskConfig {
Setter::Setter(Setting *setting):setting_(setting),v_size_(1,1),i_size_(1,1),current_id_(-1)
{

}

QString Setter::name() const
{
    if(setting_)
    {
        return setting_->name();
    }
}

void Setter::setVideoSize(int w, int h)
{
    v_size_.setWidth(w);
    v_size_.setHeight(h);
}

int Setter::resize(int w, int h)
{
    i_size_.setWidth(w);
    i_size_.setHeight(h);
    return 0;
}


QPointF Setter::VideoPosFromScreenPos(QPointF p)
{
    QPointF point;
    point.rx() = p.x() * v_size_.width() / i_size_.width();
    point.ry() = p.y() * v_size_.height() / i_size_.height();
    return point;
}

QPointF Setter::ScreenPosFromVideoPos(QPointF p)
{
    QPointF point;
    point.rx() = p.x() / (double)v_size_.width() * i_size_.width();
    point.ry() = p.y() / (double)v_size_.height() * i_size_.height();
    return point;
}

void Setter::paintStart(QPainter &painter)
{
    painter.scale(i_size_.width() / v_size_.width(), i_size_.height() / v_size_.height());

}

void Setter::paintEnd(QPainter &painter)
{
    painter.scale(v_size_.width() / i_size_.width(), v_size_.height() / i_size_.height());
}

void Setter::set_current_id(int id)
{
    current_id_ = id;
}

int Setter::current_id() const
{
    return current_id_;
}

}
