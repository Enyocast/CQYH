
#ifndef BT_EDITOR_DELEGATE_H
#define BT_EDITOR_DELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>

class BTEditorDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    BTEditorDelegate(QObject *parent = 0);

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
};

#endif // BT_EDITOR_DELEGATE_H
