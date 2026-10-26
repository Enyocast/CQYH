#include "stdafx.h"
#include "bteditorwindow.h"

#include <QDir>

#include "bt_editor_delegate.h"
#include "bt_model.h"
#include "script_mgr.h"

const char* NewFileName = "untitled.uh";

BTEditorWindow::BTEditorWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);

	m_pModel = NULL;
}

BTEditorWindow::~BTEditorWindow()
{
}

bool BTEditorWindow::Init( const char* pcszFileName )
{
	INT32 nRetCode = 0;

    BTEditorDelegate* pDelegate = new BTEditorDelegate( this );
    LOG_PROCESS_ERROR(pDelegate);
    ui.MainTreeView->setItemDelegate(pDelegate);

    undoStack = new QUndoStack();
    undoView = new QUndoView(undoStack);
    undoView->setWindowTitle(tr("Command List"));
    undoView->setAttribute(Qt::WA_QuitOnClose, false);
    //undoView->show();

    {
        m_pModel = new BTModel(undoStack, this);
        LOG_PROCESS_ERROR(m_pModel);

        nRetCode = m_pModel->Init(&g_BTreeFile);
        LOG_PROCESS_ERROR(nRetCode);

        nRetCode = m_pModel->ReLoad(pcszFileName);
        LOG_PROCESS_ERROR(nRetCode);

        connect( m_pModel, SIGNAL(ItemFocused(const QModelIndex &) ), this, SLOT(setCurrentIndex(const QModelIndex &)) );
        connect( m_pModel, SIGNAL(ModelDirty(bool) ), this, SLOT(setDirty(bool)) );

        ui.MainTreeView->setModel(m_pModel);
        ui.MainTreeView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui.MainTreeView->expandAll();
    }

    createActions();
    createPopupMenus();
    const char* pcszFilename = pcszFileName ? pcszFileName : "untitled";
    setWindowTitle(tr("%1[*] - %2").arg(tr(pcszFilename)).arg(QApplication::applicationName()));
    setDirty(false);

	return true;
Exit0:
	return false;
}

bool BTEditorWindow::UnInit(void)
{
	m_pModel->UnInit();
	SAFE_DELETE(m_pModel);

	return true;
}

QTreeView* BTEditorWindow::GetView()
{
    return ui.MainTreeView;
}
BTModel* BTEditorWindow::GetModel()
{
    return qobject_cast<BTModel*>(GetView()->model());
}

void BTEditorWindow::createActions()
{
    QHash<QAction*, QString> slotForAction;
    slotForAction[ui.actionNew] = SLOT(newFile());
    slotForAction[ui.actionOpen] = SLOT(openFile());
    slotForAction[ui.actionSave] = SLOT(saveFile());
    slotForAction[ui.actionSave_as] = SLOT(saveAsFile());
    slotForAction[ui.actionAdd_Child] = SLOT(insertChild());
    slotForAction[ui.actionAdd_Sibling] = SLOT(insertSibling());
    slotForAction[ui.actionRemove_Node] = SLOT(removeNode());
    slotForAction[ui.actionCopy_Tree] = SLOT(copyTree());
    slotForAction[ui.actionCopy_Node] = SLOT(copyNode());
    slotForAction[ui.actionCut_Tree] = SLOT(cutTree());
    slotForAction[ui.actionCut_Node] = SLOT(cutNode());
    slotForAction[ui.actionPaste_As_Child] = SLOT(pasteAsChild());
    slotForAction[ui.actionPaste_As_Sibling] = SLOT(pasteAsSibling());
    slotForAction[ui.actionUnrealEd_Location] = SLOT(unrealLocation());

    slotForAction[ui.actionUp] = SLOT(up());
    slotForAction[ui.actionDown] = SLOT(down());
    slotForAction[ui.actionPromote] = SLOT(promote());
    slotForAction[ui.actionDemote] = SLOT(demote());
    slotForAction[ui.actionAbout_BT_Editor] = SLOT(about());

    QHashIterator<QAction*, QString> i(slotForAction);
    while (i.hasNext()) 
    {
        i.next();
        connect(i.key(), SIGNAL(triggered()), this, qPrintable(i.value()));
    }

    Q_ASSERT(undoStack);
    ActionUndo = undoStack->createUndoAction(this, tr("&Undo"));
    ActionUndo->setShortcuts(QKeySequence::Undo);

    ActionRedo = undoStack->createRedoAction(this, tr("&Redo"));
    ActionRedo->setShortcuts(QKeySequence::Redo);

    ui.mainToolBar->addSeparator();
    ui.mainToolBar->addAction(ActionUndo);
    ui.mainToolBar->addAction(ActionRedo);
}

void BTEditorWindow::createPopupMenus()
{
    ui.MainTreeView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui.MainTreeView->addAction(ui.actionCopy_Node);
    ui.MainTreeView->addAction(ui.actionCopy_Tree);
    ui.MainTreeView->addAction(ui.actionCut_Node);
    ui.MainTreeView->addAction(ui.actionCut_Tree);
    ui.MainTreeView->addAction(ui.actionPaste_As_Child);
    ui.MainTreeView->addAction(ui.actionPaste_As_Sibling);

    ui.MainTreeView->addAction(ui.actionUnrealEd_Location);
}

bool BTEditorWindow::saveIfNeed()
{
    BTModel *pModel = static_cast<BTModel*>( ui.MainTreeView->model() );

    if (pModel && pModel->GetBTreeFile() && pModel->GetBTreeFile()->IsModified() ) 
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, QObject::tr("Application"),
            QObject::tr("The document has been modified.\nDo you want to save your changes?"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return saveFile();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void BTEditorWindow::newFile()
{
    INT32 nRetCode = 0;

    nRetCode = saveIfNeed();
    PROCESS_ERROR( nRetCode );

    {        
        nRetCode = m_pModel->ReLoad( NULL );
        LOG_PROCESS_ERROR(nRetCode);

        ui.MainTreeView->setCurrentIndex(QModelIndex());
        ui.MainTreeView->expandAll();
    }

    resizeColumn();
    setWindowTitle(tr("%1[*] - %2").arg(tr("untitled")).arg(QApplication::applicationName()));
    setDirty(false);
Exit0:
    return;
}

void BTEditorWindow::openFile()
{
    INT32 nRetCode = 0;
    QString fileName;

    nRetCode = saveIfNeed();
    PROCESS_ERROR( nRetCode );

    fileName = QFileDialog::getOpenFileName(this, "open behavior tree file", 
            CScriptMgr::GetInstance().GetRootPath(), tr("bt script (*.uh *.lua)") );
    PROCESS_ERROR(!fileName.isEmpty());
    fileName = QDir(CScriptMgr::GetInstance().GetRootPath()).relativeFilePath(fileName);

    { 
        nRetCode = m_pModel->ReLoad( fileName.toAscii() );
        LOG_PROCESS_ERROR(nRetCode);
        //ui.MainTreeView->repaint();

        ui.MainTreeView->setCurrentIndex(QModelIndex());
        ui.MainTreeView->expandAll();
    }

	resizeColumn();
	setWindowTitle(tr("%1[*] - %2").arg(fileName).arg(QApplication::applicationName()));
    setDirty(false);
Exit0:
	return;
}

bool BTEditorWindow::saveFile()
{
	INT32 nRetCode = 0;

    BTModel* model = GetModel();
    LOG_PROCESS_ERROR(model);
    LOG_PROCESS_ERROR(model->GetBTreeFile());
    if ( model->GetBTreeFile()->GetFileName() == NULL )
    {
        nRetCode = saveAsFile();
        LOG_PROCESS_ERROR(nRetCode);
    }
    else
    {
        nRetCode = g_BTreeFile.Save();
        LOG_PROCESS_ERROR(nRetCode);

        model->emitModelDirty();
    }

	ui.statusBar->showMessage(QString("save file %1 successfully").arg(g_BTreeFile.GetFileName()), 2000);

	return true;
Exit0:
    if ( CBTreeFile::GetErrorString() )
    {
        ui.statusBar->showMessage(QString("failed to save file %1, due to %2").arg(g_BTreeFile.GetFileName()).arg( CBTreeFile::GetErrorString() ), 2000);
    }
    else
    {
	    ui.statusBar->showMessage(QString("failed to save file %1").arg(g_BTreeFile.GetFileName()), 2000);
    }

	return false;
}

bool BTEditorWindow::saveAsFile()
{
    BTModel* model = GetModel();
    QString filename;
    QString dir;
    LOG_PROCESS_ERROR(model);
    LOG_PROCESS_ERROR(model->GetBTreeFile());

    filename = model->GetBTreeFile()->GetFileName();
    dir = QDir::currentPath() + "/" + CScriptMgr::GetInstance().GetRootPath() + "/" + QFileInfo(filename).path();

    filename = QFileDialog::getSaveFileName(this, tr("%1 - Save As").arg(QApplication::applicationName()),
                                             dir, tr("bt script (*.uh *.lua);;AI script (*.uh);;scene script (*.lua)"));
    if (filename.isEmpty())
        return false;

    filename = QDir(CScriptMgr::GetInstance().GetRootPath()).relativeFilePath(filename);

    //if (!filename.toLower().endsWith(".uh"))
    //    filename += ".uh";

    model->SetFileName(filename.toAscii());

    bool ret = saveFile();
    LOG_PROCESS_ERROR( ret );

    setWindowTitle(tr("%1[*] - %2").arg( filename ).arg(QApplication::applicationName()));

Exit0:
    return false;
}

void BTEditorWindow::closeFile()
{

}

void BTEditorWindow::resizeColumn(void)
{
	INT32 w = ui.MainTreeView->width();
	ui.MainTreeView->setColumnWidth(0, w / 3);
	ui.MainTreeView->setColumnWidth(1, w / 6);
	ui.MainTreeView->setColumnWidth(2, w / 6);
	ui.MainTreeView->setColumnWidth(3, w / 6);
	ui.MainTreeView->setColumnWidth(4, w / 6);
}

void BTEditorWindow::resizeEvent(QResizeEvent* e)
{
	resizeColumn();
}

void BTEditorWindow::showEvent(QShowEvent* e)
{
	resizeColumn();
}

void BTEditorWindow::closeEvent(QCloseEvent *event)
{
    if (saveIfNeed()) 
    {
        event->accept();
    } 
    else 
    {
        event->ignore();
    }
}

void BTEditorWindow::expandItem(const QModelIndex &parentIndex)
{
    GetView()->expand(parentIndex);
    for (int i=0; i < GetModel()->rowCount(parentIndex); ++i)
    {
        QModelIndex currentIndex = GetModel()->index(i,0,parentIndex);
        GetView()->expand(currentIndex);
        if (GetModel()->rowCount(currentIndex) > 0)
        {
            expandItem(currentIndex);
        }
    }
}
void BTEditorWindow::setCurrentIndex(const QModelIndex &index)
{
    if (index.isValid()) 
    {
        ui.MainTreeView->scrollTo(index);
        ui.MainTreeView->setCurrentIndex(index);

        expandItem(index);
    }
}

void BTEditorWindow::setDirty( bool isDirty )
{
    setWindowModified(isDirty);
    updateUi();
}


void BTEditorWindow::updateUi()
{
    //bool enable = GetView()->currentIndex().isValid();
    //foreach(QAction *action, QList<QAction*>()  << ui.actionInsert_Node << ui.actionRemove_Node
    //    << ui.actionUp          << ui.actionDown 
    //    << ui.actionPromote     << ui.actionDemote )
    //{
    //    action->setEnabled(enable);
    //}

    int rows = m_pModel->rowCount();
    ui.actionSave->setEnabled(isWindowModified());
    ui.actionSave_as->setEnabled(isWindowModified() || rows);

    ui.actionCopy_Node->setEnabled(rows);
    ui.actionCopy_Tree->setEnabled(rows);
    ui.actionCut_Node->setEnabled(rows);
    ui.actionCut_Tree->setEnabled(rows);
    ui.actionPaste_As_Child->setEnabled( GetModel()->HasHoldTree() );
    ui.actionPaste_As_Sibling->setEnabled( GetModel()->HasHoldTree() );

    ui.actionUnrealEd_Location->setEnabled(true);
}

void BTEditorWindow::insertChild()
{
    QModelIndex index = ui.MainTreeView->currentIndex();

    if (m_pModel->insertRows(0, 1, index)) 
    {
        //QModelIndex currentIndex = m_pModel->index(0, 0, index);
        //setCurrentIndex(currentIndex);

        //ui.MainTreeView->edit(index);
    }
}

void BTEditorWindow::insertSibling()
{
    QModelIndex index = ui.MainTreeView->currentIndex();

    if (m_pModel->insertSibling(index)) 
    {
        //QModelIndex currentIndex = m_pModel->index(0, 0, index);
        //setCurrentIndex(currentIndex);

        //ui.MainTreeView->edit(index);
    }
}

bool BTEditorWindow::okToDelete(QWidget *parent, const QString &title, const QString &text, const QString &detailedText)
{
    QScopedPointer<QMessageBox> messageBox(new QMessageBox(parent));

    if (parent)
        messageBox->setWindowModality(Qt::WindowModal);

    messageBox->setIcon(QMessageBox::Question);
    messageBox->setWindowTitle(QString("%1 - %2").arg(QApplication::applicationName()).arg(title));
    messageBox->setText(text);
    if (!detailedText.isEmpty())
        messageBox->setInformativeText(detailedText);

    QAbstractButton *deleteButton = messageBox->addButton(QObject::tr("&Delete"), QMessageBox::AcceptRole);
    messageBox->addButton(QObject::tr("Do &Not Delete"), QMessageBox::RejectRole);
    messageBox->setDefaultButton( qobject_cast<QPushButton*>(deleteButton));
    messageBox->exec();
    return messageBox->clickedButton() == deleteButton;
}

void BTEditorWindow::removeNode()
{
    QModelIndex index = ui.MainTreeView->currentIndex();
    if (!index.isValid())
        return;

    //QString name = m_pModel->data(index, Qt::EditRole ).toString();
    //int rows = m_pModel->rowCount(index);

    //QString message;
    //if (rows == 0)
    //    message = tr("<p>Delete '%1'").arg(name);
    //else if (rows == 1)
    //    message = tr("<p>Delete '%1' and its child (and grandchildren etc.)").arg(name);
    //else if (rows > 1)
    //    message = tr("<p>Delete '%1' and its %2 children (and grandchildren etc.)").arg(name).arg(rows);

    //if (!okToDelete(this, tr("Delete"), message))
    //    return;

    m_pModel->removeRows(index.row(), 1, index.parent() );
}

void BTEditorWindow::copyTree()
{
    QModelIndex index = ui.MainTreeView->currentIndex();

    m_pModel->CopyTree(index);

    updateUi();
}
void BTEditorWindow::copyNode()
{
    QModelIndex index = ui.MainTreeView->currentIndex();

    m_pModel->CopyNode(index);

    updateUi();
}
void BTEditorWindow::cutTree()
{
    QModelIndex index = ui.MainTreeView->currentIndex();

    m_pModel->CutTree(index);

    updateUi();
}
void BTEditorWindow::cutNode()
{
    QModelIndex index = ui.MainTreeView->currentIndex();

    m_pModel->CutNode(index);

    updateUi();
}
void BTEditorWindow::pasteAsChild()
{
    QModelIndex index = ui.MainTreeView->currentIndex();

    m_pModel->PasteAsChild( index );
}
void BTEditorWindow::pasteAsSibling()
{
    QModelIndex index = ui.MainTreeView->currentIndex();

    m_pModel->PasteAsSibling( index );
}
void BTEditorWindow::unrealLocation()
{
    QModelIndex index = ui.MainTreeView->currentIndex();

    bool ret = m_pModel->UnrealLocation( index );
    if ( !ret )
    {
        ui.statusBar->showMessage( QString("Unreal Location failed!") );
    }
}
void BTEditorWindow::up()
{
    GetModel()->moveUp(GetView()->currentIndex() );
}
void BTEditorWindow::down()
{
    GetModel()->moveDown(GetView()->currentIndex() );
}
void BTEditorWindow::promote()
{
    GetModel()->promote(GetView()->currentIndex() );
}
void BTEditorWindow::demote()
{
    GetModel()->demote(GetView()->currentIndex() );
}

void BTEditorWindow::check()
{

}

void BTEditorWindow::about()
{
    QMessageBox::about(this, tr("About Behavior Tree Editor"), tr("The <b>BT Editor</b> used to editor behavior tree"));
}
