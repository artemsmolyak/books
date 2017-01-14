/****************************************************************************
 **
 ** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Commercial Usage
 ** Licensees holding valid Qt Commercial licenses may use this file in
 ** accordance with the Qt Commercial License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Nokia.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Nokia gives you certain additional
 ** rights.  These rights are described in the Nokia Qt LGPL Exception
 ** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3.0 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU General Public License version 3.0 requirements will be
 ** met: http://www.gnu.org/copyleft/gpl.html.
 **
 ** If you have questions regarding the use of this file, please contact
 ** Nokia at qt-info@nokia.com.
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

 #include "tablemodel.h"
#include "qdebug.h"

 TableModel::TableModel(QObject *parent)
     : QAbstractTableModel(parent)
 {
 }

 TableModel::TableModel(QList<Data> listofData, QObject *parent)
     : QAbstractTableModel(parent)
 {
     this->listofData=listofData;
 }

 int TableModel::rowCount(const QModelIndex &parent) const
 {
     Q_UNUSED(parent);
     return listofData.size();
 }

 int TableModel::columnCount(const QModelIndex &parent) const
 {
     Q_UNUSED(parent);
     return 5;
 }

 QVariant TableModel::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
         return QVariant();

     if (index.row() >= listofData.size() || index.row() < 0)
         return QVariant();

     if (role == Qt::DisplayRole) {
         Data data = listofData.at(index.row());


         switch (index.column()) {
         case 0:
             return data.getId();
         case 1:
            return data.getBookTitle();
         case 2:
            return data.getAuthorName();
         case 3:
            return data.getAnnotation();
         case 4:
            return data.getDate();
         default:
             break;
         }

     }
     return QVariant();
 }

 QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
     if (role != Qt::DisplayRole)
         return QVariant();

     if (orientation == Qt::Horizontal) {
         switch (section) {
             case 0:
                 return tr("id");

             case 1:
                 return tr("Title");

             case 2:
                 return tr("Author");

             default:
                 return QVariant();
         }
     }
     return QVariant();
 }

 bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
 {
     Q_UNUSED(index);
     beginInsertRows(QModelIndex(), position, position+rows-1);

//     for (int row=0; row < rows; row++) {
//         QPair<QString, QString> pair(" ", " ");
//         listofData.insert(position, pair);
//     }

     endInsertRows();
     return true;
 }

 bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
 {
     Q_UNUSED(index);
     beginRemoveRows(QModelIndex(), position, position+rows-1);

     for (int row=0; row < rows; ++row) {
         listofData.removeAt(position);
     }

     endRemoveRows();
     return true;
 }

 bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
 {
//         if (index.isValid() && role == Qt::EditRole) {
//                 int row = index.row();

//                 QPair<QString, QString> p = listOfPairs.value(row);

//                 if (index.column() == 0)
//                         p.first = value.toString();
//                 else if (index.column() == 1)
//                         p.second = value.toString();
//         else
//             return false;

//         listofData.replace(row, p);
//                 emit(dataChanged(index, index));

//         return true;
//         }

         return false;
 }

 Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
 {
     if (!index.isValid())
         return Qt::ItemIsEnabled;

     return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
 }

 QList<Data> TableModel::getList()
 {
     return listofData;
 }
