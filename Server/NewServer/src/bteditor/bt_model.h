
#ifndef BT_MODEL_H
#define BT_MODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QMimeData>

#include "btree_file.h"

const QString BTMimeType = "application/btree.xml.task.z";
const int MaxCompression = 9;

class BTModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    BTModel(QUndoStack * undoStack, QObject *parent = NULL);
    ~BTModel();

	BOOL Init(CBTreeFile* pBTreeFile);
	BOOL UnInit(void);
    BOOL ReLoad(const char* pcszFileName);

	CBTreeFile* GetBTreeFile(void);
    bool SetFileName(const char* pcszFileName);

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &index) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole);

    bool insertSibling( const QModelIndex& current );

    virtual bool insertColumns(int position, int columns, const QModelIndex &parent = QModelIndex());
    virtual bool removeColumns(int position, int columns, const QModelIndex &parent = QModelIndex());
    virtual bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
    virtual bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());

    virtual Qt::DropActions supportedDragActions() const
    { return Qt::MoveAction | Qt::CopyAction; }
    virtual Qt::DropActions supportedDropActions() const
    { return Qt::MoveAction | Qt::CopyAction; }
    virtual QStringList mimeTypes() const
    { return QStringList() << BTMimeType; }
    virtual QMimeData *mimeData(const QModelIndexList &indexes) const;
    virtual bool dropMimeData(const QMimeData *mimeData, Qt::DropAction action, 
                int row, int column, const QModelIndex &parent);

    BT_EDIT_NOD * restoreNod(QXmlStreamReader *reader);
    void storeNod(QXmlStreamWriter *writer, BT_EDIT_NOD *nod) const;
    BT_EDIT_NOD* ChildNod(const QModelIndex& ParentIndex, int nPos);

    BT_EDIT_NOD* Index2Nod(const QModelIndex &index) const;
    QModelIndex  Nod2Index(const BT_EDIT_NOD *nod, int col = 0) const;
    QModelIndex  Nod2Index(const QModelIndex& parent, const BT_EDIT_NOD *nod, int col = 0) const;

    bool moveUp(const QModelIndex &index);
    bool moveDown(const QModelIndex &index);
    bool promote(const QModelIndex &index );
    bool demote(const QModelIndex &index );

    bool CopyTree(const QModelIndex& index );
    bool CopyNode(const QModelIndex& index );
    bool CutTree(const QModelIndex& index );
    bool CutNode(const QModelIndex& index );
    bool PasteAsChild( const QModelIndex& parent );
    bool PasteAsSibling( const QModelIndex& current );
    bool UnrealLocation( const QModelIndex& current );
    bool HasHoldTree();

    void emitItemFocused( const QModelIndex &index);
    void emitModelDirty(void);
signals:
    void ItemFocused ( const QModelIndex & index );
    void ModelDirty ( bool isDirty );

private:
    friend class InOutCommand;
    friend class ChangeValueCommand;
    friend class MoveToCommand;
    bool m_ResultByCommands;

    bool setDataByCommands(const QModelIndex &index, const QVariant &value, int role);
    bool removeRowsByCommands(int position, int rows, const QModelIndex &parent);
    bool insertRowsByCommands(int position, int rows, const QModelIndex &parent);
    bool cloneNodTreeByCommands(int position, const QModelIndex &parent, BT_EDIT_NOD* pRootNod );
    bool moveToByCommands(QModelIndex& SrcParentIndex, int nSrcPos, QModelIndex& DstParentIndex, int nDstPos );
    bool swapItemByCommands(QModelIndex& SrcParentIndex, int nSrcPos, QModelIndex& DstParentIndex, int nDstPos );

    bool ParseSUIDInfo( const QModelIndex& current, char** pcszType, int& nID );

private:
	CBTreeFile*		m_pBTreeFile;

    BT_EDIT_NOD*    m_pHoldTree;    // for copy, paste

    QUndoStack *    m_pUndoStack;
};

#endif // BT_MODEL_H
