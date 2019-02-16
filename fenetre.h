#ifndef FENETRE_H
#define FENETRE_H

#include <QApplication>
#include <QWidget>
#include <QString>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QLabel>

class Fenetre : public QWidget
{
    Q_OBJECT

    public:
    Fenetre();

    public slots:
    void quitter();
    void apropos();
    void ouvrir();
    void sauvegarder();
    void nouveau();
    void updateInfos();


    private:
    QTextEdit *m_texte;
    QPushButton *bouton_ouvrir;
    QPushButton *bouton_sauvegarder;
    QPushButton *bouton_apropos;
    QPushButton *bouton_quitter;
    QPushButton *bouton_nouveau;
    QGridLayout *m_layout;
    QLabel *infos;
};

#endif
