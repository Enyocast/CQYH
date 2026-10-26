
#ifndef COMMANDS_H
#define COMMANDS_H

#include <QUndoCommand>
#include "btree_file.h"

struct BT_EDIT_NOD;
class BTModel;

class InOutCommand : public QUndoCommand
{
public:
    InOutCommand(BT_EDIT_NOD* pItem,  int nParentIndex, 
                  int pos, int rows, BTModel *pModel, QUndoCommand *parent = NULL);
    ~InOutCommand();

    void nodIn();
    void nodOut();

private:
    //BT_EDIT_NOD *pEditNod;
    std::list<BT_EDIT_NOD *>EditNodList;

    int         nParentNodIndex;
    int         nPos;
    int         nRows;

    BTModel *pBTModel;
};

class RemoveCommand : public InOutCommand 
{
public:
    RemoveCommand( BT_EDIT_NOD* pItem, int nParentIndex,
        int pos, int rows, BTModel *pModel, QUndoCommand *parent = NULL);

    void undo();
    void redo();
};

class InsertCommand : public InOutCommand  
{
public:
    InsertCommand( BT_EDIT_NOD* pItem, int nParentIndex,
        int pos, int rows, BTModel *pModel, QUndoCommand *parent = NULL);

    void undo();
    void redo();
};

class ChangeValueCommand : public QUndoCommand
{
public:
    ChangeValueCommand(QString oldValue, QString newValue,  
        int nNodIndex, int nCol, BTModel *pModel, QUndoCommand *parent = NULL);

    void undo();
    void redo();

private:
    QString     oldValue;
    QString     newValue;

    int         nCol;
    int         nNodIndex;

    BTModel *pBTModel;
};

enum NodMoveToDirection
{
    nmtdPromote = 0,
    nmtdDemote,
    nmtdPrior,
    nmtdNext,
    nmtdTotal,
};
class MoveToCommand : public QUndoCommand
{
public:
    MoveToCommand(const QModelIndex& SrcIndex, int nDirection, //NodMoveToDirection
        BTModel *pModel, QUndoCommand *parent = NULL);
    bool MakeSureDst();

    void redo(); 
    void undo(); 

protected:
    bool PreparePromote();
    bool PrepareDemote();
    bool PrepareMovePrior();
    bool PrepareMoveNext();

    int nDstPos;
    int nDstParentNodIndex;

    int nSrcPos;
    int nSrcParentNodIndex;

    int nDirection; //NodMoveToDirection

private:

    BTModel *pBTModel;
};

QString createCommandString(BT_EDIT_NOD *item, int row, BT_EDIT_NOD* parent_item);

#endif
