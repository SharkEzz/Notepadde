#include "fenetre.h"

Fenetre::Fenetre() : QWidget()
{
    resize(1024,600);

    setWindowTitle("Notepadde");

    m_texte = new QTextEdit(this);
    bouton_nouveau = new QPushButton("Nouveau", this);
    bouton_ouvrir = new QPushButton("Ouvrir", this);
    bouton_sauvegarder = new QPushButton("Sauvegarder", this);
    bouton_quitter = new QPushButton("Quitter", this);
    bouton_apropos = new  QPushButton("A Propos", this);
    infos = new QLabel(this);
    m_layout = new QGridLayout(this);

    infos->setText("0 caractère");

    m_layout->addWidget(infos, 2, 4, 1, 1);
    m_layout->addWidget(bouton_nouveau, 0, 0, 1, 1);
    m_layout->addWidget(bouton_ouvrir, 0, 1, 1, 1);
    m_layout->addWidget(bouton_sauvegarder, 0, 2, 1, 1);
    m_layout->addWidget(bouton_apropos, 0, 3, 1, 1);
    m_layout->addWidget(bouton_quitter, 0, 4, 1, 1);
    m_layout->addWidget(m_texte, 1, 0, 1, 5);

    this->setLayout(m_layout);

    connect(bouton_quitter, SIGNAL(clicked()), this, SLOT(quitter()));
    connect(bouton_apropos, SIGNAL(clicked()), this, SLOT(apropos()));
    connect(bouton_ouvrir, SIGNAL(clicked()), this, SLOT(ouvrir()));
    connect(bouton_sauvegarder, SIGNAL(clicked()), this, SLOT(sauvegarder()));
    connect(bouton_nouveau, SIGNAL(clicked()), this, SLOT(nouveau()));
    connect(m_texte, SIGNAL(cursorPositionChanged()), this, SLOT(updateInfos()));
}

void Fenetre::quitter()
{
    int reponse = QMessageBox::warning(this, "Quitter Notepadde", "Voulez vous vraiment quitter <strong>Notepadde</stong> ?", QMessageBox::Yes, QMessageBox::No);

    if(reponse == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}

void Fenetre::apropos()
{
    QMessageBox::information(this, "A propos de Notepadde", "Sous licence GPLv3<br>Source disponible sur <a href=\"http://github.com/SharkEzz/notepadde\">GitHub</a><br><br>2019");
}

void Fenetre::ouvrir()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Tous les fichiers (*.*)");
    QByteArray contenu;

    QFile file(fichier);
    if(fichier != "")
    {
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::critical(this, "Erreur de lecture", "Impossible d'ouvrir le fichier en lecture !", QMessageBox::Yes);
        }
        else
        {
            m_texte->setText("");
            while(!file.atEnd())
            {
                contenu = file.readAll();
                m_texte->append(contenu);
            }
        }
    }
}

void Fenetre::sauvegarder()
{
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Tous les fichier (*.*)");

    QFile file(fichier);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Erreur d'écriture", "Impossible d'écrire dans le fichier", QMessageBox::Yes);
    }
    else
    {
        QTextStream stream(&file);

        stream << m_texte->toPlainText();
        file.close();
    }
}

void Fenetre::nouveau()
{
    int nouveau = QMessageBox::warning(this, "Attention", "Etes-vous sûr de vouloir créer un nouveau document ?", QMessageBox::Yes, QMessageBox::No);

    if(nouveau == QMessageBox::Yes)
        m_texte->setText("");

}

void Fenetre::updateInfos()
{
    QString longueur = QString::number(m_texte->toPlainText().length());

    if(longueur == "0")
    {
        infos->setText(longueur + " caractère");
    }
    else
    {
        infos->setText(longueur + " caractères");
    }

}
