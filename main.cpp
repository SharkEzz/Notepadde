#include "fenetre.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Fenetre notepadde;

    notepadde.show();

    return app.exec();
}
