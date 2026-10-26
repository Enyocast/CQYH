#include "stdafx.h"

#include <QtGui>
#include <QtGui/QTreeView>
#include <QPersistentModelIndex>

#include "btree_file.h"
#include "bt_model.h"

#include "undoredo_commands.h"

InOutCommand::InOutCommand(BT_EDIT_NOD* pItem, int nParentIndex,
                             int pos, int rows, BTModel *pModel, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    pBTModel = pModel;

    if ( pItem )
    {
        BT_EDIT_NOD* pNod = CloneNod( pItem );
        Q_ASSERT(pNod);
        EditNodList.push_back(pNod);
    }

    this->nParentNodIndex = nParentIndex;
    Q_ASSERT( this->nParentNodIndex >= -1 );

    this->nPos = pos;
    this->nRows = rows;
    Q_ASSERT(this->nRows == 1);
}

InOutCommand::~InOutCommand()
{
    std::list<BT_EDIT_NOD*>::iterator it;
    for ( it = EditNodList.begin(); it != EditNodList.end(); ++it )
    {
        DestroyNod( *it );
    }
}

void InOutCommand::nodIn()
{
    Q_ASSERT( pBTModel );

    QModelIndex ParentIndex = QModelIndex();
    if ( nParentNodIndex >= 0)
    {
        Q_ASSERT( pBTModel->GetBTreeFile() );
        BT_EDIT_NOD* pNod = pBTModel->GetBTreeFile()->GetNodeByIndex( nParentNodIndex );
        Q_ASSERT(pNod);
        ParentIndex = pBTModel->Nod2Index(pNod);
    }

    int i = 0;
    std::list<BT_EDIT_NOD*>::iterator it = EditNodList.begin();
    for ( int i = 0; i < nRows; ++i )
    {
        BT_EDIT_NOD* pEditNod = NULL;
        if ( it != EditNodList.end() )
        {
            pEditNod = *it++;
        }               

        if ( pEditNod )
        {
            pBTModel->cloneNodTreeByCommands(nPos+ i, ParentIndex, pEditNod );
        }
        else
        {
            pBTModel->insertRowsByCommands(nPos + i, 1, ParentIndex);
        }
    }

    pBTModel->emitModelDirty();
}

void InOutCommand::nodOut()
{
    Q_ASSERT( pBTModel );
  
    Q_ASSERT( pBTModel->GetBTreeFile() );
    
    QModelIndex ParentIndex = QModelIndex();
    if ( nParentNodIndex >= 0)
    {
        BT_EDIT_NOD* pNod = pBTModel->GetBTreeFile()->GetNodeByIndex( nParentNodIndex );
        Q_ASSERT( pNod );
        ParentIndex = pBTModel->Nod2Index(pNod);
    }

    pBTModel->removeRowsByCommands(nPos, nRows, ParentIndex);

    pBTModel->emitModelDirty();
}

RemoveCommand::RemoveCommand(BT_EDIT_NOD* pItem, int nParentIndex, 
                             int pos, int rows, BTModel *pModel, QUndoCommand *parent)
                             : InOutCommand( pItem, nParentIndex, pos, rows, pModel, parent )
{
    //setText(QObject::tr("Remove %1").arg(createCommandString(NULL, nSiblingRank, pParentItem)));
}
void RemoveCommand::undo()
{
    InOutCommand::nodIn();
}
void RemoveCommand::redo()
{
    InOutCommand::nodOut();
}

InsertCommand::InsertCommand(BT_EDIT_NOD* pItem, int nParentIndex, 
                       int pos, int rows, BTModel *pModel, QUndoCommand *parent)
    : InOutCommand( pItem, nParentIndex, pos, rows, pModel, parent )
{
    //setText(QObject::tr("Insert %1").arg(createCommandString(NULL, nSiblingRank, pParentItem)));
}
void InsertCommand::undo()
{
    InOutCommand::nodOut();
}
void InsertCommand::redo()
{
    InOutCommand::nodIn();
}

ChangeValueCommand::ChangeValueCommand(QString oldValue, QString newValue,  
                   int nNodIndex, int nCol, BTModel *pModel, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    this->oldValue = oldValue;
    this->newValue = newValue;

    this->nCol = nCol;
    this->nNodIndex = nNodIndex;
    Q_ASSERT( this->nNodIndex >= 0 );

    this->pBTModel = pModel;

    //setText(QObject::tr("Update %1").arg(createCommandString(NULL, nSiblingRank, pParentItem)));
}

void ChangeValueCommand::undo()
{
    if ( oldValue == newValue )
        return ;
    
    Q_ASSERT( pBTModel );
    Q_ASSERT( pBTModel->GetBTreeFile() );
    BT_EDIT_NOD* pNod = pBTModel->GetBTreeFile()->GetNodeByIndex( nNodIndex );
    Q_ASSERT(pNod);
    QModelIndex CurrentIndex = pBTModel->Nod2Index(pNod, nCol);
    
    pBTModel->setDataByCommands(CurrentIndex, QVariant(oldValue), Qt::EditRole );
    pBTModel->emitModelDirty();
}

void ChangeValueCommand::redo()
{
    if ( oldValue == newValue )
        return ;

    Q_ASSERT( pBTModel );
    Q_ASSERT( pBTModel->GetBTreeFile() );
    BT_EDIT_NOD* pNod = pBTModel->GetBTreeFile()->GetNodeByIndex( nNodIndex );
    Q_ASSERT(pNod);
    QModelIndex CurrentIndex = pBTModel->Nod2Index(pNod, nCol);

    pBTModel->setDataByCommands(CurrentIndex, QVariant(newValue), Qt::EditRole );
    pBTModel->emitModelDirty();
}

bool MoveToCommand::MakeSureDst(void )
{
    bool nRetCode = false;
    switch (nDirection)
    {
    case nmtdPromote:
        nRetCode = PreparePromote();
        break;
    case nmtdDemote:
        nRetCode = PrepareDemote();
        break;
    case nmtdPrior:
        nRetCode = PrepareMovePrior();
        break;
    case nmtdNext:
        nRetCode = PrepareMoveNext();
        break;
    default:
        Q_ASSERT(false);
    }

    if ( nDstPos < 0 || nSrcParentNodIndex < -1 || nDstPos < 0 || nDstParentNodIndex < -1 )
        return false;

    return nRetCode;
}

bool MoveToCommand::PreparePromote()
{    
    Q_ASSERT( pBTModel );
    Q_ASSERT( pBTModel->GetBTreeFile() );

    if (nDstParentNodIndex < -1)
    {
        Q_ASSERT(nDstPos < 0);
        Q_ASSERT(nSrcParentNodIndex >= -1 && nSrcPos >=0);

        BT_EDIT_NOD* pSrcParentNod = pBTModel->GetBTreeFile()->GetNodeByIndex( nSrcParentNodIndex );
        if( NULL == pSrcParentNod)
            return false;

        BT_EDIT_NOD* pDstParentNod = pSrcParentNod->pParent;
        if(pDstParentNod)
        {
            nDstParentNodIndex = pBTModel->GetBTreeFile()->GetNodeIndex(pDstParentNod);

            std::list<BT_EDIT_NOD*>::iterator it = pDstParentNod->Children.begin();
            for (int i=0; i<pDstParentNod->Children.size(); ++i)
            {
                Q_ASSERT( it != pDstParentNod->Children.end() );
                if ( *it == pSrcParentNod )
                {
                    nDstPos = i + 1;
                    break;
                }
                ++it;
            }
        }
        else
        {
            //return false;
            nDstParentNodIndex = -1;
            for (int i=0; i<pBTModel->GetBTreeFile()->GetTreeCount(); ++i )
            {
                if( pBTModel->GetBTreeFile()->GetRootNode(i) == pSrcParentNod )
                {
                    nDstPos = i + 1;
                }
            }
            Q_ASSERT(nDstPos >=0);
        }
    }

    return true;
}

bool MoveToCommand::PrepareDemote()
{     
    Q_ASSERT( pBTModel );
    Q_ASSERT( pBTModel->GetBTreeFile() );

    if (nDstParentNodIndex < -1)
    {
        Q_ASSERT(nDstPos < 0);
        Q_ASSERT(nSrcParentNodIndex >= -1 && nSrcPos >=0);

        if( nSrcPos == 0)
            return false;

        if(nSrcParentNodIndex > -1)
        {
            BT_EDIT_NOD* pSrcParentNod = pBTModel->GetBTreeFile()->GetNodeByIndex( nSrcParentNodIndex );
            Q_ASSERT(pSrcParentNod);
            std::list<BT_EDIT_NOD*>::iterator it = pSrcParentNod->Children.begin();
            for (int i=0;i<pSrcParentNod->Children.size(); ++i)
            {
                Q_ASSERT( it != pSrcParentNod->Children.end() );
                if ( i == nSrcPos - 1 )
                {
                    BT_EDIT_NOD* pDstParentNod = *it;
                    Q_ASSERT(pDstParentNod);
                    nDstParentNodIndex = pBTModel->GetBTreeFile()->GetNodeIndex(pDstParentNod);

                    nDstPos = pDstParentNod->Children.size();
                    break;
                }
                ++it;
            }
        }
        else if(nSrcParentNodIndex == -1)
        {
            for (int i=0; i<pBTModel->GetBTreeFile()->GetTreeCount(); ++i )
            {
                if ( i == nSrcPos - 1 )
                {
                    BT_EDIT_NOD* pDstParentNod = pBTModel->GetBTreeFile()->GetRootNode(i);
                    Q_ASSERT(pDstParentNod);
                    nDstParentNodIndex = pBTModel->GetBTreeFile()->GetNodeIndex(pDstParentNod);

                    nDstPos = pDstParentNod->Children.size();
                    break;
                }
            }
        }
    }

    return true;
}

bool MoveToCommand::PrepareMovePrior()
{     
    Q_ASSERT( pBTModel );
    Q_ASSERT( pBTModel->GetBTreeFile() );

    if (nDstParentNodIndex < -1)
    {
        Q_ASSERT(nDstPos < 0);
        Q_ASSERT(nSrcParentNodIndex >= -1 && nSrcPos >=0);

        if( nSrcPos == 0)
            return false;

        nDstPos = nSrcPos - 1;
        nDstParentNodIndex = nSrcParentNodIndex;
    }
    return true;
}

bool MoveToCommand::PrepareMoveNext()
{     
    Q_ASSERT( pBTModel );
    Q_ASSERT( pBTModel->GetBTreeFile() );

    if (nDstParentNodIndex < -1)
    {
        Q_ASSERT(nDstPos < 0);
        Q_ASSERT(nSrcParentNodIndex >= -1 && nSrcPos >=0);

        if(nSrcParentNodIndex > -1)
        {
            BT_EDIT_NOD* pSrcParentNod = pBTModel->GetBTreeFile()->GetNodeByIndex( nSrcParentNodIndex );
            Q_ASSERT(pSrcParentNod);
            if( nSrcPos >= pSrcParentNod->Children.size() - 1 )
                return false;

        }
        else if(nSrcParentNodIndex == -1)
        {
            if( nSrcPos >= pBTModel->GetBTreeFile()->GetTreeCount() - 1 )
                return false;
        }

        nDstPos = nSrcPos + 1;
        nDstParentNodIndex = nSrcParentNodIndex;
    }
    return true;
}

MoveToCommand::MoveToCommand(const QModelIndex& SrcIndex, int nDirection, //NodMoveToDirection
              BTModel *pModel, QUndoCommand *parent)
              : QUndoCommand(parent)
{
    this->pBTModel = pModel;
    this->nDirection = nDirection;

    this->nDstParentNodIndex = -2;
    this->nDstPos = -1;

    this->nSrcPos = SrcIndex.row();
    Q_ASSERT(this->nSrcPos >= 0);

    QModelIndex SrcParentIndex = SrcIndex.parent();
    BT_EDIT_NOD* pSrcParentNod = (BT_EDIT_NOD*)SrcParentIndex.internalPointer();
    this->nSrcParentNodIndex = pModel->GetBTreeFile()->GetNodeIndex(pSrcParentNod);
    Q_ASSERT( this->nSrcParentNodIndex >= -1 );
}

void MoveToCommand::undo()
{
    Q_ASSERT( pBTModel );
    Q_ASSERT( pBTModel->GetBTreeFile() );
    BT_EDIT_NOD* pNod = NULL;

    QModelIndex SrcParentIndex = QModelIndex();
    pNod = pBTModel->GetBTreeFile()->GetNodeByIndex( nSrcParentNodIndex );
    if(pNod)
    {
        SrcParentIndex = pBTModel->Nod2Index(pNod);
    }
    QModelIndex DstParentIndex = QModelIndex();
    pNod = pBTModel->GetBTreeFile()->GetNodeByIndex( nDstParentNodIndex );
    if(pNod)
    {
        DstParentIndex = pBTModel->Nod2Index(pNod);
    }

    pBTModel->moveToByCommands( DstParentIndex, nDstPos, SrcParentIndex, nSrcPos );
    pBTModel->emitModelDirty();
}

void MoveToCommand::redo()
{
    Q_ASSERT( pBTModel );
    Q_ASSERT( pBTModel->GetBTreeFile() );
    BT_EDIT_NOD* pNod = NULL;

    QModelIndex SrcParentIndex = QModelIndex();
    pNod = pBTModel->GetBTreeFile()->GetNodeByIndex( nSrcParentNodIndex );
    if(pNod)
    {
        SrcParentIndex = pBTModel->Nod2Index(pNod);
    }

    QModelIndex DstParentIndex = QModelIndex();
    pNod = pBTModel->GetBTreeFile()->GetNodeByIndex( nDstParentNodIndex );
    if(pNod)
    {
        DstParentIndex = pBTModel->Nod2Index(pNod);
    }

    pBTModel->moveToByCommands( SrcParentIndex, nSrcPos, DstParentIndex, nDstPos );
    pBTModel->emitModelDirty();
}

QString createCommandString(BT_EDIT_NOD *nod, int row, BT_EDIT_NOD* parentNod)
{
    QString strItem;
    if( nod )
      QTextStream(&strItem) << nod->szType; //<< ", param={" << nod->szParam[0] <<", ...}";

    QString strParentItem;
    if( parentNod )
        QTextStream(&strParentItem) << parentNod->szType; //<<", param={" << parentNod->szParam[0] <<", ...}";

    return QObject::tr("%1 at node %2's child %3")
        .arg(strItem)
        .arg(strParentItem)
        .arg(row);
}
