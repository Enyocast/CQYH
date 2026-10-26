#ifndef BTEDITORWINDOW_H
#define BTEDITORWINDOW_H

#include <QtGui/QMainWindow>

#include "ui_bteditorwindow.h"

struct BTNod;
class BTModel;
class BTEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    BTEditorWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~BTEditorWindow();

    bool Init( const char* pcszFileName );
	bool UnInit(void);

    QTreeView* GetView();
    BTModel* GetModel();

private slots:

    void newFile();
    void openFile();
    bool saveFile();
    bool saveAsFile();
    void closeFile();

    void insertChild();
    void insertSibling();
    void removeNode();
    void copyTree();
    void copyNode();
    void cutTree();
    void cutNode();
    void pasteAsChild();
    void pasteAsSibling();
    void unrealLocation();

    void up();
    void down();
    void promote();
    void demote();

    void check();

    void about();
    void setCurrentIndex(const QModelIndex &index);
    void setDirty(bool isDirty);

private:
    void expandItem(const QModelIndex &parentIndex);

    bool saveIfNeed();
    bool okToDelete(QWidget *parent, const QString &title, const QString &text, const QString &detailedText=QString());

    void updateUi();

    void createActions();
    void createPopupMenus();

	void resizeColumn(void);
	void resizeEvent(QResizeEvent* e);
	void showEvent(QShowEvent* e);
    void closeEvent(QCloseEvent *event);

private:
    Ui::BTEditorWindowClass ui;
	BTModel* m_pModel;

    QAction *ActionUndo;
    QAction *ActionRedo;
    QUndoStack *undoStack;
    QUndoView *undoView;
};

#endif // BTEDITORWINDOW_H
