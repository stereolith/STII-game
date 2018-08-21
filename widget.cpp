#include <QtGui>
#include <QPushButton>
#include <QGridLayout>
#include "widget.h"

meinWidget::meinWidget(QWidget *parent)
    : QWidget(parent)
{
    start = new QPushButton(tr("Start"));
    start->setFont(QFont("Times", 16, QFont::Bold));
    connect(start, SIGNAL(clicked()), this, SLOT(startPause()));

    points = new QLabel("Punkte");
    points->setFont(QFont("Times", 16));

    saver = new QPushButton(tr("Sichern"));
    saver->setFont(QFont("Times", 16, QFont::Bold));
    connect(saver, SIGNAL(clicked()), this, SLOT(saveFile()));
    saver->setEnabled(true);
    loader = new QPushButton(tr("Laden"));
    loader->setFont(QFont("Times", 16, QFont::Bold));
    connect(loader, SIGNAL(clicked()), this, SLOT(loadFile()));
    loader->setEnabled(true);

    meinspielFeld = new spielFeld;
    meinspielFeld->setPointsPtr(points);


    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(start, 0, 0);
    gridLayout->addWidget(points, 0, 1);
    gridLayout->addWidget(saver, 0, 4);
    gridLayout->addWidget(loader, 0, 5);
    gridLayout->addWidget(meinspielFeld, 1, 0, 6, 6);
    setLayout(gridLayout);
}

void meinWidget::startPause(void)
{
    if(meinspielFeld->getActive()) {
        meinspielFeld->setActive(false);
        saver->setEnabled(true);
        loader->setEnabled(true);
        start->setText(tr("Start"));
    }else{
        meinspielFeld->setActive(true);
        saver->setEnabled(false);
        loader->setEnabled(false);
        start->setText(tr("Pause"));
    }

}

void meinWidget::saveFile(void)
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getSaveFileName(this,
                                      tr("Speichern als"), ".", tr("stII-savegame (*.s2g)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht verwendet werden: ") + fileName,QMessageBox::Ok);
        }

        meinspielFeld->serialize(file);
        file.close();
        return;
    }
}

void meinWidget::loadFile(void)
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getOpenFileName(this,
                                      tr("Speichern als"), ".", tr("stII-savegame (*.s2g)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht geöffnet werden: ") + fileName,QMessageBox::Ok);
        }

        meinspielFeld->deserialize(file);
        file.close();
        return;
    }
}

