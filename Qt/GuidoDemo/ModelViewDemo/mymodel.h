/*! @简要说明:
 *  @详细说明:
 *  @作者   : Guido
 *  @创建日期: 2022-01-26 15:21:05
 *  @版权   : Copyright By LIFOTRONIC, All Rights Reserved
 *
 **********************************************************
 *  @注意事项:
 *  @修改日志:
 *    1、https://doc.qt.io/qt-5/modelview.html#1-2-model-view-to-the-rescue
 *
 **********************************************************/


#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>

class MyModel : QAbstractTableModel
{
    Q_OBJECT

public:
    MyModel();


};

#endif // MYMODEL_H
